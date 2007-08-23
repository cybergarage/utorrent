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


/****************************************
* Macros
****************************************/

#define cg_bittorrent_filemgr_isvalidated(filemgr) cg_bittorrent_blockdevicemgr_isvalidated(filemgr)

#define cg_bittorrent_filemgr_addmetainfo(bdmgr, cbm) cg_bittorrent_blockdevicemgr_addmetainfo(bdmgr, cbm)
#define cg_bittorrent_filemgr_removemetainfo(bdmgr, infoHash) cg_bittorrent_blockdevicemgr_removemetainfo(bdmgr, infoHash)
#define cg_bittorrent_filemgr_getmetainfos(bdmgr, cbmList) cg_bittorrent_blockdevicemgr_getmetainfos(bdmgr, cbmList)
#define cg_bittorrent_filemgr_getmetainfo(bdmgr, infoHash, cbm) cg_bittorrent_blockdevicemgr_getmetainfo(bdmgr, infoHash, cbm)

#ifdef  __cplusplus
}
#endif

#endif
