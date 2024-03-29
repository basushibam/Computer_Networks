/*
 * Please do not edit this file.
 * It was generated using rpcgen.
 */

#ifndef _NFS_H_RPCGEN
#define _NFS_H_RPCGEN

#include <rpc/rpc.h>


#ifdef __cplusplus
extern "C" {
#endif


struct data {
	char arr[1000];
};
typedef struct data data;

#define READ_FILE_PROG 0x23456789
#define READ_FILE_VERS 2

#if defined(__STDC__) || defined(__cplusplus)
#define get_file_contents 1
extern  data * get_file_contents_2(data *, CLIENT *);
extern  data * get_file_contents_2_svc(data *, struct svc_req *);
extern int read_file_prog_2_freeresult (SVCXPRT *, xdrproc_t, caddr_t);

#else /* K&R C */
#define get_file_contents 1
extern  data * get_file_contents_2();
extern  data * get_file_contents_2_svc();
extern int read_file_prog_2_freeresult ();
#endif /* K&R C */

/* the xdr functions */

#if defined(__STDC__) || defined(__cplusplus)
extern  bool_t xdr_data (XDR *, data*);

#else /* K&R C */
extern bool_t xdr_data ();

#endif /* K&R C */

#ifdef __cplusplus
}
#endif

#endif /* !_NFS_H_RPCGEN */
