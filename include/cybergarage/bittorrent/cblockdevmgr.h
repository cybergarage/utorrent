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

typedef BOOL (*CG_BITTORRENT_BLOCKDEVICEMGR_READ)(CgBittorrentTracker *, int pieceIndex, CgByte **);
typedef BOOL (*CG_BITTORRENT_BLOCKDEVICEMGR_WRITE)(CgBittorrentTracker *, int pieceIndex, CgByte *);
typedef BOOL (*CG_BITTORRENT_BLOCKDEVICEMGR_HAVE)(CgBittorrentTracker *, int pieceIndex);

typedef struct _CgBittorrentBlockDeviceMgr {
	CG_BITTORRENT_BLOCKDEVICEMGR_READ readFunc;
	CG_BITTORRENT_BLOCKDEVICEMGR_WRITE writeFunc;
	CG_BITTORRENT_BLOCKDEVICEMGR_HAVE haveFunc;
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
#define cg_bittorrent_blockdevicemgr_setreadfunc(bdmgr, func) (bdmgr->readFunc = func)

/**
 * Return a read function.
 *
 * \param bdmgr Block device manager in question.
 *
 * \return Read function
 .
 */
#define cg_bittorrent_blockdevicemgr_getreadfunc(bdmgr) (bdmgr->readFunc)

/**
 * Set a write function.
 *
 * \param bdmgr Block device manager in question.
 * \param func Function to set.
 */
#define cg_bittorrent_blockdevicemgr_setwritefunc(bdmgr, func) (bdmgr->writeFunc = func)

/**
 * Return a write function.
 *
 * \param bdmgr Block device manager in question.
 *
 * \return Read function
 .
 */
#define cg_bittorrent_blockdevicemgr_getwritefunc(bdmgr) (bdmgr->writeFunc)

/**
 * Set a have function.
 *
 * \param bdmgr Block device manager in question.
 * \param func Function to set.
 */
#define cg_bittorrent_blockdevicemgr_sethavefunc(bdmgr, func) (bdmgr->haveFunc = func)

/**
 * Return a have function.
 *
 * \param bdmgr Block device manager in question.
 *
 * \return Read function
 .
 */
#define cg_bittorrent_blockdevicemgr_gethavefunc(bdmgr) (bdmgr->haveFunc)

#ifdef  __cplusplus
}
#endif

#endif
