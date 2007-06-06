/******************************************************************
*
*	CyberBittorrent for C
*
*	Copyright (C) Satoshi Konno 2007
*
*	File: chttp.h
*
*	Revision:
*
*	03/20/07
*		- first revision
*
******************************************************************/

#ifndef _CG_BITTORRENT_HTTP_H_
#define _CG_BITTORRENT_HTTP_H_

#include <cybergarage/http/chttp.h>

#ifdef  __cplusplus
extern "C" {
#endif

/****************************************
* Function
****************************************/

BOOL cg_bittorrent_http_fetch(char *url, CgString *str);

#ifdef  __cplusplus
}
#endif

#endif
