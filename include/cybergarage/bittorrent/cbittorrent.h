/******************************************************************
*
*	CyberBittorrent for C
*
*	Copyright (C) Satoshi Konno 2007
*
*	File: cbittorrent.h
*
*	Revision:
*
*	01/25/07
*		- first revision
*
******************************************************************/

#ifndef _CG_BITTORRENT_H_
#define _CG_BITTORRENT_H_

#include <cybergarage/bittorrent/ctracker.h>
#include <cybergarage/bittorrent/cdownloadmgr.h>

#ifdef  __cplusplus
extern "C" {
#endif

/****************************************
* Define
****************************************/

/****************************************
* Data Type
****************************************/

typedef struct _CgBittorrent {
	int port;
} CgBittorrent;

/****************************************
* Function
****************************************/

/**
 * Create a new instance of the bittorrent.
 *
 * \return New instance.
 */
CgBittorrent *cg_bittorrent_new();

/**
 * Destroy a instance of the bittorrent.
 *
 * \param cbbList Bencoding list to destory.
 */
void cg_bittorrent_delete(CgBittorrent *cb);

#ifdef  __cplusplus
}
#endif

#endif
