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
#include <cybergarage/bittorrent/cfilemgr.h>
#include <cybergarage/bittorrent/cstrategymgr.h>

#ifdef  __cplusplus
extern "C" {
#endif

/****************************************
* Data Type
****************************************/

typedef struct _CgBittorrentDownloadMgr {
	CgBittorrentFileMgr *filemgr;
	CgBittorrentStrategyMgr *stgmgr;
} CgBittorrentDownloadMgr;

/****************************************
* Function
****************************************/

/**
 * Create a new  downnload manager.
 *
 * \return New  downnload manager.
 */
CgBittorrentDownloadMgr *cg_bittorrent_downloadmgr_new(void);

/**
 * Destroy a downnload manager.
 *
 * \param dlmgr  Downnload manager to destroy.
 */
void cg_bittorrent_downloadmgr_delete(CgBittorrentDownloadMgr *dlmgr);

/**
 * Set a file manager of the specified download manager.
 *
 * \param dlmgr  Download manager in question.
 * \param trakcer File manager  to set.
 */
#define cg_bittorrent_downloadmgr_setfilemgr(dlmgr, value) (dlmgr->filemgr = value)

/**
 * Return a  file manager of the specified download manager.
 *
 * \param dlmgr Download manager in question.
 *
 * \return File manager of the specified download manager.
 */
#define cg_bittorrent_downloadmgr_getfilemgr(dlmgr) (dlmgr->filemgr)

/**
 * Set a strategy manager of the specified download manager.
 *
 * \param dlmgr  Download manager in question.
 * \param stgmgr Strategy manager  to set.
 */
#define cg_bittorrent_downloadmgr_setstrategymgr(dlmgr, value) (dlmgr->stgmgr = value)

/**
 * Return a  strategy manager of the specified download manager.
 *
 * \param dlmgr Download manager in question.
 *
 * \return Strategy manager of the specified download manager.
 */
#define cg_bittorrent_downloadmgr_getstrategymgr(dlmgr) (dlmgr->stgmgr)

/**
 * Start a downnload manager.
 *
 * \param dlmgr  Downnload manager to destroy.
 *
 * \return TRUE if the specified downalod manager is started normally, otherwise FALSE.
 */
BOOL cg_bittorrent_downloadmgr_start(CgBittorrentDownloadMgr *dlmgr);

/**
 * Stop a downnload manager.
 *
 * \param dlmgr  Downnload manager to destroy.
 *
 * \return TRUE if the specified downalod manager is stopped normally, otherwise FALSE.
 */
BOOL cg_bittorrent_downloadmgr_stop(CgBittorrentDownloadMgr *dlmgr);

/****************************************
* Function (Internal)
****************************************/

/**
 * Initialize the spceifiled downnload manager.
 *
 * \param dlmgr  Downnload manager to Initialize.
 *
 * \return TRUE if the specified downalod manager is Initialized normally, otherwise FALSE.
 */
BOOL cg_bittorrent_downloadmgr_initialize(CgBittorrentDownloadMgr *dlmgr);

/**
 * Free work areas in the spceifiled downnload manager.
 *
 * \param dlmgr  Downnload manager to Initialize.
 *
 */
void cg_bittorrent_downloadmgr_clear(CgBittorrentDownloadMgr *dlmgr);

#ifdef  __cplusplus
}
#endif

#endif
