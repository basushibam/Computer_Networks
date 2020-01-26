#include <pcap.h>
#include <bits/stdc++.h>
#include<stdio.h> //For standard things
#include<stdlib.h>    //malloc
#include <unistd.h>
#include<string.h>    //memset
#include<netinet/ip_icmp.h>   //Provides declarations for icmp header
#include<netinet/udp.h>   //Provides declarations for udp header
#include<netinet/tcp.h>   //Provides declarations for tcp header
#include<netinet/ip.h>    //Provides declarations for ip header
#include<sys/socket.h>
#include<arpa/inet.h>
using namespace std; 

void process_packet(char *buffer)
{
    struct iphdr *iph = (struct iphdr*)(buffer + 14);
    unsigned short iphdrlen;
    iphdrlen =iph->ihl*4;
    struct tcphdr *tcph = (struct tcphdr*)(buffer+14+iphdrlen);
    printf("TCP Header Length = %d bytes\n",tcph->doff*4 );
    char *msg=(char*)(buffer+14+iphdrlen+tcph->doff*4);

    
    struct sockaddr_in saddr,daddr,source,dest;
    memset(&source, 0, sizeof(source));
    source.sin_addr.s_addr = iph->saddr;
    memset(&dest, 0, sizeof(dest));
    dest.sin_addr.s_addr = iph->daddr;
    FILE* logfile = stdout; 
    fprintf(logfile,"\n");
    fprintf(logfile,"IP Header\n");
    fprintf(logfile,"   |-IP Version        : %d\n",(unsigned int)iph->version);
    fprintf(logfile,"   |-IP Header Length  : %d DWORDS or %d Bytes\n",(unsigned int)iph->ihl,((unsigned int)(iph->ihl))*4);
    fprintf(logfile,"   |-Type Of Service   : %d\n",(unsigned int)iph->tos);
    fprintf(logfile,"   |-IP Total Length   : %d  Bytes(Size of Packet)\n",ntohs(iph->tot_len));
    fprintf(logfile,"   |-Identification    : %d\n",ntohs(iph->id));
    //fprintf(logfile,"   |-Reserved ZERO Field   : %d\n",(unsigned int)iphdr->ip_reserved_zero);
    //fprintf(logfile,"   |-Dont Fragment Field   : %d\n",(unsigned int)iphdr->ip_dont_fragment);
    //fprintf(logfile,"   |-More Fragment Field   : %d\n",(unsigned int)iphdr->ip_more_fragment);
    fprintf(logfile,"   |-TTL      : %d\n",(unsigned int)iph->ttl);
    fprintf(logfile,"   |-Protocol : %d\n",(unsigned int)iph->protocol);
    fprintf(logfile,"   |-Checksum : %d\n",ntohs(iph->check));
    fprintf(logfile,"   |-Source IP        : %s\n",inet_ntoa(source.sin_addr));
    fprintf(logfile,"   |-Destination IP   : %s\n",inet_ntoa(dest.sin_addr));
    fprintf(logfile, "Message : %s\n",msg );
}

int main(int argc, char const *argv[])
{
	int rsfd = socket(AF_INET,SOCK_RAW,6);
	int optval=1;
	setsockopt(rsfd,IPPROTO_IP,IP_HDRINCL,&optval,sizeof(optval));
	while(1)
	{
		char buffer[100];
		struct sockaddr_in naddr; socklen_t len;
		recvfrom(rsfd,buffer,100,0,(struct sockaddr*)&naddr,&len);
		process_packet(buffer);
	}
	return 0;
}