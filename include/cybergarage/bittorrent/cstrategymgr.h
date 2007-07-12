/******************************************************************
*
*	CyberBittorrent for C
*
*	Copyright (C) Satoshi Konno 2007
*
*	Strategy: cstrategymgr.h
*
*	Revision:
*
*	07/12/07
*		- first revision
*
******************************************************************/

#ifndef _CG_BITTORRENT_STRATEGYMGR_H_
#define _CG_BITTORRENT_STRATEGYMGR_H_

#ifdef  __cplusplus
extern "C" {
#endif

/****************************************
* Data Type
****************************************/

typedef struct _CgBittorrentStrategyMgr {
	int test;
} CgBittorrentStrategyMgr;

/****************************************
* Function (StrategyMgr)
****************************************/

/**
 * Create a new strategymgr.
 *
 * \return New strategymgr.
 */
CgBittorrentStrategyMgr *cg_bittorrent_strategymgr_new(void);

/**
 * Destroy a strategymgr.
 *
 * \param dlmgr StrategyMgr to destroy.
 */
void cg_bittorrent_strategymgr_delete(CgBittorrentStrategyMgr *dlmgr);

/**
 * Set a strategymgr type.
 *
 * \param dlmgr StrategyMgr in question.
 * \param value Type to set.
 */
#define cg_bittorrent_strategymgr_settype(dlmgr, value) (dlmgr->type = value)

/**
 * Return a strategymgr type.
 *
 * \param dlmgr StrategyMgr in question.
 *
 * \return StrategyMgr type.
 */
#define cg_bittorrent_strategymgr_gettype(dlmgr) (dlmgr->type)

#ifdef  __cplusplus
}
#endif

#endif
