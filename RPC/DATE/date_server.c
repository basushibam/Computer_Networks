/*
 * This is sample code generated by rpcgen.
 * These are only templates and you can use them
 * as a guideline for developing your own functions.
 */

#include "date.h"

long *
bin_date_1_svc(void *argp, struct svc_req *rqstp)
{
	printf("BIN_DATE() called \n");
	static long  timeval;
	long time();
	timeval = time((long*)0);

	/*
	 * insert server code here
	 */

	return &timeval;
}

char **
str_date_1_svc(long *argp, struct svc_req *rqstp)
{
	printf("STR_DATE() called \n");
	static char *ptr;
	char *ctime();
	ptr = ctime(argp); /* convert to local time */
	return(&ptr); /* return the address of pointer */
}