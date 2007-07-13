/******************************************************************
*
*	CyberBittorrent for C
*
*	Copyright (C) Satoshi Konno 2007
*
*	File: cfilemgr.h
*
*	Revision:
*
*	07/07/07
*		- first revision
*
******************************************************************/

#ifndef _CG_BITTORRENT_FILEMGR_H_
#define _CG_BITTORRENT_FILEMGR_H_

#include <cybergarage/bittorrent/cblockdevmgr.h>

#ifdef  __cplusplus
extern "C" {
#endif

/****************************************
* Data Type
****************************************/

typedef CgBittorrentBlockDeviceMgr CgBittorrentFileMgr;

typedef struct _CgBittorrentFileMgrData {
	char *dstDir;
} CgBittorrentFileMgrData;

/****************************************
* Function
****************************************/

/**
 * Create a new file manager.
 *
 * \return New file manager.
 */
CgBittorrentFileMgr *cg_bittorrent_filemgr_new(void);

/**
 * Destroy a filemgr.
 *
 * \param filemgr File manager to destroy.
 */
void cg_bittorrent_filemgr_delete(CgBittorrentFileMgr *filemgr);

/**
 * Return a filemgr type.
 *
 * \param filemgr File manager in question.
 *
 * \return FileMgr type.
 */
#define cg_bittorrent_filemgr_getdata(filemgr) ((CgBittorrentFileMgrData *)cg_bittorrent_blockdevicemgr_getuserdata(filemgr))

/**
 * Set a destination directory.
 *
 * \param filemgr File manager in question.
 * \param value Type to set.
 */
void cg_bittorrent_filemgr_setdestinationdirectory(CgBittorrentFileMgr *filemgr, char *value);

/**
 * Return a stored destination directory.
 *
 * \param filemgr File manager in question.
 *
 * \return Stored destination directory.
 */
char *cg_bittorrent_filemgr_getdestinationdirectory(CgBittorrentFileMgr *filemgr);

/* destinationdirectory */

#ifdef  __cplusplus
}
#endif

#endif
