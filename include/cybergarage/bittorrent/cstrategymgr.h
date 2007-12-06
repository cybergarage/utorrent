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

#include <cybergarage/bittorrent/ctracker.h>

#ifdef  __cplusplus
extern "C" {
#endif

/****************************************
* Data Type
****************************************/

/* Metainfo */
typedef int (*CG_BITTORRENT_STRATEGYMGR_GETNEXTPIECEINDEX)(void *cbsm);
typedef CgBittorrentPeer *(*CG_BITTORRENT_STRATEGYMGR_GETPEER)(void *cbsm, CgBittorrentTracker *cbt, int pieceIdx);

/****************************************
* Data Type
****************************************/

typedef struct _CgBittorrentStrategyMgr {
	/* Basic */
	int type;
	CgString *name;
	/* Function */
	CG_BITTORRENT_STRATEGYMGR_GETNEXTPIECEINDEX nextPieceIndexFunc;
	CG_BITTORRENT_STRATEGYMGR_GETPEER getPeerFunc;
	/* User Data */
	void *userData;
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
 * \param stgmgr Strategy manager to destroy.
 */
void cg_bittorrent_strategymgr_delete(CgBittorrentStrategyMgr *stgmgr);

/**
 * Set a type.
 *
 * \param stgmgr Strategy manager to destroy.
 * \param value Type to set.
 */
#define cg_bittorrent_strategymgr_settype(stgmgr, value) (stgmgr->type = value)

/**
 * Return a stored type.
 *
 * \param stgmgr Strategy manager to destroy.
 *
 * \return Stored type.
 */
#define cg_bittorrent_strategymgr_gettype(stgmgr) (stgmgr->type)

/**
 * Set a name.
 *
 * \param stgmgr Strategy manager to destroy.
 * \param value Type to set.
 */
#define cg_bittorrent_strategymgr_setname(stgmgr, value) cg_string_setvalue(stgmgr->name, value)

/**
 * Return a stored name.
 *
 * \param stgmgr Strategy manager to destroy.
 *
 * \return Stored name.
 */
#define cg_bittorrent_strategymgr_getname(stgmgr) cg_string_getvalue(stgmgr->name)

/****************************************
* Function (User Data)
****************************************/

/**
 * Set a user data.
 *
 * \param stgmgr Strategy manager to destroy.
 * \param value User data to set.
 */
#define cg_bittorrent_strategymgr_setuserdata(stgmgr, value) (stgmgr->userData = value)

/**
 * Get a user data.
 *
 * \param stgmgr Strategy manager to destroy.
 *
 * \return User data
 */
#define cg_bittorrent_strategymgr_getuserdata(stgmgr) (stgmgr->userData)

/****************************************
* Function (User Data)
****************************************/

/**
 * Get a  a optimal peer to request.
 *
 * \param stgmgr Strategy manager to destroy.
 * \param tracker Metainfo of the file.
 *
 * \return TRUE if the specifed file is available, otherwise FALSE.
 . */
#define cg_bittorrent_strategymgr_getnextpeer(stgmgr, tracker, pieceIdx) ((stgmgr->getPeerFunc) ? stgmgr->getPeerFunc(stgmgr, tracker, pieceIdx) : FALSE)

#ifdef  __cplusplus
}
#endif

#endif
