/******************************************************************
*
*	CyberBittorrent for C
*
*	Copyright (C) Satoshi Konno 2007
*
*	File: cdownloadmgr.h
*
*	Revision:
*
*	07/07/07
*		- first revision
*
******************************************************************/

#ifndef _CG_BITTORRENT_DOWNLOADMGR_H_
#define _CG_BITTORRENT_DOWNLOADMGR_H_

#include <cybergarage/bittorrent/ctracker.h>

#ifdef  __cplusplus
extern "C" {
#endif

/****************************************
* Data Type
****************************************/

typedef struct _CgBittorrentDownloadMgr {
	int test;
} CgBittorrentDownloadMgr;

/****************************************
* Function (DownloadMgr)
****************************************/

/**
 * Create a new downloadmgr.
 *
 * \return New downloadmgr.
 */
CgBittorrentDownloadMgr *cg_bittorrent_downloadmgr_new(void);

/**
 * Destroy a downloadmgr.
 *
 * \param dlmgr DownloadMgr to destroy.
 */
void cg_bittorrent_downloadmgr_delete(CgBittorrentDownloadMgr *dlmgr);

/**
 * Set a downloadmgr type.
 *
 * \param dlmgr DownloadMgr in question.
 * \param value Type to set.
 */
#define cg_bittorrent_downloadmgr_settype(dlmgr, value) (dlmgr->type = value)

/**
 * Return a downloadmgr type.
 *
 * \param dlmgr DownloadMgr in question.
 *
 * \return DownloadMgr type.
 */
#define cg_bittorrent_downloadmgr_gettype(dlmgr) (dlmgr->type)

#ifdef  __cplusplus
}
#endif

#endif
