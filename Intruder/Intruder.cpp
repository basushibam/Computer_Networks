#include <pcap.h>
#include <bits/stdc++.h>
#include<stdio.h> //For standard things
#include<stdlib.h>    //malloc
#include <unistd.h>
#include<string.h>    //memset
#include<net/ethernet.h>
#include<netinet/ip_icmp.h>   //Provides declarations for icmp header
#include<netinet/udp.h>   //Provides declarations for udp header
#include<netinet/tcp.h>   //Provides declarations for tcp header
#include<netinet/ip.h>    //Provides declarations for ip header
#include<sys/socket.h>
#include<arpa/inet.h>
using namespace std; 

int target=0;


void process_packet(u_char *args, const struct pcap_pkthdr *header, const u_char *buffer)
{
	

	int sfd;
    struct iphdr *iph = (struct iphdr*)(buffer + 14);
    unsigned short iphdrlen;
    iphdrlen =iph->ihl*4;
    struct udphdr *udph = (struct udphdr*)(buffer + iphdrlen  + 14);
    int header_size =  sizeof(struct ethhdr) + iphdrlen + sizeof udph;
    char *msg= (char*)(buffer+header_size);
    struct sockaddr_in saddr,daddr,source,dest;
    socklen_t serv_len;
    if(target==0)
    {
    	printf("-----------------My target = %d ----------------\n", target);
    	target= ntohs(udph->source);
	    memset(&source, 0, sizeof(source));
	    source.sin_family=AF_INET; source.sin_port=htons(ntohs(udph->source));
	    source.sin_addr.s_addr = iph->saddr;
	    if((sfd = socket(AF_INET , SOCK_DGRAM , 0))==-1)
		{perror("\n socket in process_packet"); exit(0);}
		else printf("\n socket created successfully\n");
		serv_len = sizeof(source);
    }
    else if(target!=ntohs(udph->source)) return;
    int l=strlen(msg);

    printf("Original message : %s \n",msg );
    
    
    

    // memset(&dest, 0, sizeof(dest));
    // dest.sin_port=htons(ntohs(udph->dest));
    // dest.sin_addr.s_addr = iph->daddr;
    // FILE* logfile = stdout; 
    // fprintf(logfile,"\n");
    // fprintf(logfile,"IP Header\n");
    // fprintf(logfile,"   |-IP Version        : %d\n",(unsigned int)iph->version);
    // fprintf(logfile,"   |-IP Header Length  : %d DWORDS or %d Bytes\n",(unsigned int)iph->ihl,((unsigned int)(iph->ihl))*4);
    // fprintf(logfile,"   |-Type Of Service   : %d\n",(unsigned int)iph->tos);
    // fprintf(logfile,"   |-IP Total Length   : %d  Bytes(Size of Packet)\n",ntohs(iph->tot_len));
    // fprintf(logfile,"   |-Identification    : %d\n",ntohs(iph->id));
    // //fprintf(logfile,"   |-Reserved ZERO Field   : %d\n",(unsigned int)iphdr->ip_reserved_zero);
    // //fprintf(logfile,"   |-Dont Fragment Field   : %d\n",(unsigned int)iphdr->ip_dont_fragment);
    // //fprintf(logfile,"   |-More Fragment Field   : %d\n",(unsigned int)iphdr->ip_more_fragment);
    // fprintf(logfile,"   |-TTL      : %d\n",(unsigned int)iph->ttl);
    // fprintf(logfile,"   |-Protocol : %d\n",(unsigned int)iph->protocol);
    // fprintf(logfile,"   |-Checksum : %d\n",ntohs(iph->check));
    // fprintf(logfile,"   |-Source IP        : %s\n",inet_ntoa(source.sin_addr));
    // fprintf(logfile,"   |-Destination IP   : %s\n",inet_ntoa(dest.sin_addr));
    // fprintf(logfile, "Message : %s\n",msg );
    
    reverse(msg,msg+l);
    //msg[l]=0;
	
	
	
	printf("Intruder sending message to %s:%d\n",inet_ntoa(source.sin_addr),ntohs(source.sin_port));
	printf("Intruder sending message : %s \n",msg );
	sendto(sfd , msg , 100 , 0 , ( struct sockaddr * ) &source ,  serv_len);
	printf("Intruder sent message successfully to client \n");
}

int main(int argc, char *argv[])
{
    printf("######################## Intruder #########################\n");
    if(argc != 3)
    {
        printf("\nUsage: %s <protocol> <device_to_be_sniffed>\n",argv[0]);
        return 0;
    }
    char errbuf[PCAP_ERRBUF_SIZE];
    char *device = argv[2];
    pcap_t* descr;
    struct bpf_program fp;        /* to hold compiled program */
    bpf_u_int32 pMask;            /* subnet mask */
    bpf_u_int32 pNet;             /* ip address*/
    
    printf("Device that shall be sniffed = %s \n", device);
    int promiscous_mode=0;
    pcap_lookupnet(device, &pNet, &pMask, errbuf);
    descr = pcap_open_live(device, BUFSIZ, promiscous_mode,-1, errbuf);
    // Compile the filter expression
    if(pcap_compile(descr, &fp, argv[1], 0, pNet) == -1)
    {
        perror("\npcap_compile() failed\n");
        return -1;
    }
    printf("pcap compiled successful\n");
    // Set the filter compiled above
    if(pcap_setfilter(descr, &fp) == -1)
    {
        printf("\npcap_setfilter() failed\n");
        exit(1);
    }
    printf("pcap filet set \n");
    //memset(sent,0,sizeof(sent));
    pcap_loop(descr ,0 , process_packet , NULL);
    printf("Exiting \n");
    return 0;
}