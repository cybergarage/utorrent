/******************************************************************
*
*	CyberBittorrent for C
*
*	Copyright (C) Satoshi Konno 2007
*
*	Strategy: csequential.h
*
*	Revision:
*
*	12/18/07
*		- first revision
*
******************************************************************/

#ifndef _CG_BITTORRENT_FILEMGR_SEQUENTIAL_H_
#define _CG_BITTORRENT_FILEMGR_SEQUENTIAL_H_

#include <cybergarage/bittorrent/cstrategymgr.h>

#ifdef  __cplusplus
extern "C" {
#endif

/****************************************
* Function (StrategyMgr)
****************************************/

/**
 * Create a new strategymgr.
 *
 * \return New strategymgr.
 */
CgBittorrentStrategyMgr *cg_bittorrent_sequential_strategymgr_new(void);

/**
 * Destroy a strategymgr.
 *
 * \param stgmgr Strategy manager to destroy.
 */
void cg_bittorrent_sequential_strategymgr_delete(CgBittorrentStrategyMgr *stgmgr);

#ifdef  __cplusplus
}
#endif

#endif
