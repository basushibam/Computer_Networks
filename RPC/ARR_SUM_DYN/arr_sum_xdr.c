/*
 * Please do not edit this file.
 * It was generated using rpcgen.
 */

#include "arr_sum.h"

bool_t
xdr_data (XDR *xdrs, data *objp)
{
	register int32_t *buf;

	 if (!xdr_int (xdrs, &objp->arr_size))
		 return FALSE;
	 if (!xdr_pointer (xdrs, (char **)&objp->arr_pointer, sizeof (int), (xdrproc_t) xdr_int))
		 return FALSE;
	return TRUE;
}