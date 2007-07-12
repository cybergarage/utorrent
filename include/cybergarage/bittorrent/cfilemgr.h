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

#ifdef  __cplusplus
extern "C" {
#endif

/****************************************
* Data Type
****************************************/

typedef struct _CgBittorrentFileMgr {
	int test;
} CgBittorrentFileMgr;


/****************************************
* Function (FileMgr)
****************************************/

/**
 * Create a new filemgr.
 *
 * \return New filemgr.
 */
CgBittorrentFileMgr *cg_bittorrent_filemgr_new(void);

/**
 * Destroy a filemgr.
 *
 * \param dlmgr FileMgr to destroy.
 */
void cg_bittorrent_filemgr_delete(CgBittorrentFileMgr *dlmgr);

/**
 * Set a filemgr type.
 *
 * \param dlmgr FileMgr in question.
 * \param value Type to set.
 */
#define cg_bittorrent_filemgr_settype(dlmgr, value) (dlmgr->type = value)

/**
 * Return a filemgr type.
 *
 * \param dlmgr FileMgr in question.
 *
 * \return FileMgr type.
 */
#define cg_bittorrent_filemgr_gettype(dlmgr) (dlmgr->type)

#ifdef  __cplusplus
}
#endif

#endif
