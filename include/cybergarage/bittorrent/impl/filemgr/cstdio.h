/******************************************************************
*
*	CyberBittorrent for C
*
*	Copyright (C) Satoshi Konno 2007
*
*	File: stdio.h
*
*	Revision:
*
*	12/18/07
*		- first revision
*
******************************************************************/

#ifndef _CG_BITTORRENT_FILEMGR_STDIO_H_
#define _CG_BITTORRENT_FILEMGR_STDIO_H_

#include <cybergarage/bittorrent/cfilemgr.h>
#include <cybergarage/util/cstring.h>
#include <cybergarage/io/cfile.h>

#ifdef  __cplusplus
extern "C" {
#endif

/****************************************
* Data Type
****************************************/

typedef CgBittorrentFileMgr CgBittorrentFileMgr;

typedef struct _CgBittorrentFileMgrData {
	CgString *dstDir;
	CgFile *file;
} CgBittorrentFileMgrData;

/****************************************
* Function
****************************************/

/**
 * Create a new file manager.
 *
 * \return New file manager.
 */
CgBittorrentFileMgr *cg_bittorrent_stdio_filemgr_new(void);

/**
 * Destroy a filemgr.
 *
 * \param filemgr File manager to destroy.
 */
void cg_bittorrent_stdio_filemgr_delete(CgBittorrentFileMgr *filemgr);

/**
 * Return a filemgr type.
 *
 * \param filemgr File manager in question.
 *
 * \return FileMgr type.
 */
#define cg_bittorrent_stdio_filemgr_getdata(filemgr) ((CgBittorrentFileMgrData *)cg_bittorrent_filemgr_getuserdata(filemgr))

/**
 * Set a destination directory.
 *
 * \param filemgr File manager in question.
 * \param value Type to set.
 */
void cg_bittorrent_stdio_filemgr_setdestinationdirectory(CgBittorrentFileMgr *filemgr, char *value);

/**
 * Return a stored destination directory.
 *
 * \param filemgr File manager in question.
 *
 * \return Stored destination directory.
 */
char *cg_bittorrent_stdio_filemgr_getdestinationdirectory(CgBittorrentFileMgr *filemgr);

/**
 * Return a stored file.
 *
 * \param filemgr File manager in question.
 *
 * \return Stored file.
 */
CgFile *cg_bittorrent_stdio_filemgr_getfile(CgBittorrentFileMgr *filemgr);

/****************************************
* Macros
****************************************/

#define cg_bittorrent_stdio_filemgr_isvalidated(filemgr) cg_bittorrent_filemgr_isvalidated(filemgr)

#define cg_bittorrent_stdio_filemgr_addmetainfo(fileMgr, cbm) cg_bittorrent_filemgr_addmetainfo(fileMgr, cbm)
#define cg_bittorrent_stdio_filemgr_removemetainfo(fileMgr, infoHash) cg_bittorrent_filemgr_removemetainfo(fileMgr, infoHash)
#define cg_bittorrent_stdio_filemgr_getmetainfos(fileMgr, cbmList) cg_bittorrent_filemgr_getmetainfos(fileMgr, cbmList)
#define cg_bittorrent_stdio_filemgr_getmetainfo(fileMgr, infoHash, cbm) cg_bittorrent_filemgr_getmetainfo(fileMgr, infoHash, cbm)

#ifdef  __cplusplus
}
#endif

#endif
