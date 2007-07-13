/******************************************************************
*
*	CyberBittorrent for C
*
*	Copyright (C) Satoshi Konno 2007
*
*	File: cblockdevicemgr.h
*
*	Revision:
*
*	07/07/07
*		- first revision
*
******************************************************************/

#ifndef _CG_BITTORRENT_BLOCKDEVICEMGR_H_
#define _CG_BITTORRENT_BLOCKDEVICEMGR_H_

#include <cybergarage/bittorrent/ctracker.h>

#ifdef  __cplusplus
extern "C" {
#endif

/****************************************
* Data Type
****************************************/

typedef BOOL (*CG_BITTORRENT_BLOCKDEVICEMGR_READPIECE)(void *, CgBittorrentTracker *, int , CgByte **);
typedef BOOL (*CG_BITTORRENT_BLOCKDEVICEMGR_WRITEPIECE)(void *, CgBittorrentTracker *, int , CgByte *);
typedef BOOL (*CG_BITTORRENT_BLOCKDEVICEMGR_HAVEPIECE)(void *, CgBittorrentTracker *, int);

typedef struct _CgBittorrentBlockDeviceMgr {
	CG_BITTORRENT_BLOCKDEVICEMGR_READPIECE readPieceFunc;
	CG_BITTORRENT_BLOCKDEVICEMGR_WRITEPIECE writePieceFunc;
	CG_BITTORRENT_BLOCKDEVICEMGR_HAVEPIECE havePieceFunc;
	void *userData;
} CgBittorrentBlockDeviceMgr;

/****************************************
* Function (BlockDevMgr)
****************************************/

/**
 * Create a new blockdevicemgr.
 *
 * \return New blockdevicemgr.
 */
CgBittorrentBlockDeviceMgr *cg_bittorrent_blockdevicemgr_new(void);

/**
 * Destroy a blockdevicemgr.
 *
 * \param bdmgr BlockDevMgr to destroy.
 */
void cg_bittorrent_blockdevicemgr_delete(CgBittorrentBlockDeviceMgr *bdmgr);

/**
 * Set a read function.
 *
 * \param bdmgr Block device manager in question.
 * \param func Function to set.
 */
#define cg_bittorrent_blockdevicemgr_setreadpiecefunc(bdmgr, func) (bdmgr->readPieceFunc = func)

/**
 * Return a read function.
 *
 * \param bdmgr Block device manager in question.
 *
 * \return Read function
 */
#define cg_bittorrent_blockdevicemgr_getreadpiecefunc(bdmgr) (bdmgr->readPieceFunc)

/**
 * Set a write function.
 *
 * \param bdmgr Block device manager in question.
 * \param func Function to set.
 */
#define cg_bittorrent_blockdevicemgr_setwritepiecefunc(bdmgr, func) (bdmgr->writePieceFunc = func)

/**
 * Return a write function.
 *
 * \param bdmgr Block device manager in question.
 *
 * \return Read function
 */
#define cg_bittorrent_blockdevicemgr_getwritepiecefunc(bdmgr) (bdmgr->writePieceFunc)

/**
 * Set a have function.
 *
 * \param bdmgr Block device manager in question.
 * \param func Function to set.
 */
#define cg_bittorrent_blockdevicemgr_sethavepiecefunc(bdmgr, func) (bdmgr->havePieceFunc = func)

/**
 * Return a have function.
 *
 * \param bdmgr Block device manager in question.
 *
 * \return Read function
 */
#define cg_bittorrent_blockdevicemgr_gethavepiecefunc(bdmgr) (bdmgr->havePieceFunc)

/**
 * Set a user data.
 *
 * \param bdmgr Block device manager in question.
 * \param value User data to set.
 */
#define cg_bittorrent_blockdevicemgr_setuserdata(bdmgr, value) (bdmgr->userData = value)

/**
 * Get a user data.
 *
 * \param bdmgr Block device manager in question.
 *
 * \return User data
 */
#define cg_bittorrent_blockdevicemgr_getuserdata(bdmgr) (bdmgr->userData)

/**
 * Read a piece.
 *
 * \param bdmgr Block device manager in question.
 * \param tracker Tracker of the piece.
 * \param idx Index of the piece.
 * \param buf Pointer of a buffer to read the specifed piece. You have to free the pointer when you don't need.
 *
 * \return TRUE if the specifed piece is read normally, otherwise FALSE.
 */
#define cg_bittorrent_blockdevicemgr_readpiece(bdmgr, tracker, idx, buf) ((bdmgr->readPieceFunc) ? FALSE : bdmgr->readPieceFunc(tracker, idx, buf))

/**
 * Write a piece.
 *
 * \param bdmgr Block device manager in question.
 * \param tracker Tracker of the piece.
 * \param idx Index of the piece.
 * \param buf Buffer which has a piece data.
 *
 * \return TRUE if the specifed piece is worte normally, otherwise FALSE.
 */
#define cg_bittorrent_blockdevicemgr_writepiece(bdmgr, tracker, idx, buf) ((bdmgr->writePieceFunc) ? FALSE : bdmgr->writePieceFunc(tracker, idx, buf))

/**
 * Check a piece.
 *
 * \param bdmgr Block device manager in question.
 * \param tracker Tracker of the piece.
 * \param idx Index of the piece.
 *
 * \return TRUE if the specifed piece is available, otherwise FALSE.
 .
 */
#define cg_bittorrent_blockdevicemgr_havepiece(bdmgr, tracker, idx) ((bdmgr->havePieceFunc) ? FALSE : bdmgr->havePieceFunc(tracker, idx))


#ifdef  __cplusplus
}
#endif

#endif
