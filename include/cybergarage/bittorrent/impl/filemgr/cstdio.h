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

#ifndef _CG_BITTORRENT_FILEMGR_STDIO_H_
#define _CG_BITTORRENT_FILEMGR_STDIO_H_

#include <cybergarage/bittorrent/cblockdevmgr.h>

#ifdef  __cplusplus
extern "C" {
#endif

/****************************************
* Data Type
****************************************/

typedef struct _CgBittorrentStdioFileMgr {
	void *userData;
} CgBittorrentStdioFileMgr;

/****************************************
* Function (StrategyMgr)
****************************************/

/**
 * Create a new strategymgr.
 *
 * \return New strategymgr.
 */
CgBittorrentStdioFileMgr *cg_bittorrent_stdio_filemgr_new(void);

/**
 * Destroy a strategymgr.
 *
 * \param stgmgr Strategy manager to destroy.
 */
void cg_bittorrent_stdio_filemgr_delete(CgBittorrentStdioFileMgr *stgmgr);

/**
 * Set a type.
 *
 * \param stgmgr Strategy manager to destroy.
 * \param value Type to set.
 */
#define cg_bittorrent_stdio_filemgr_settype(stgmgr, value) (stgmgr->type = value)

/**
 * Return a stored type.
 *
 * \param stgmgr Strategy manager to destroy.
 *
 * \return Stored type.
 */
#define cg_bittorrent_stdio_filemgr_gettype(stgmgr) (stgmgr->type)

/**
 * Set a name.
 *
 * \param stgmgr Strategy manager to destroy.
 * \param value Type to set.
 */
#define cg_bittorrent_stdio_filemgr_setname(stgmgr, value) cg_string_setvalue(stgmgr->name, value)

/**
 * Return a stored name.
 *
 * \param stgmgr Strategy manager to destroy.
 *
 * \return Stored name.
 */
#define cg_bittorrent_stdio_filemgr_getname(stgmgr) cg_string_getvalue(stgmgr->name)

/****************************************
* Function (User Data)
****************************************/

/**
 * Set a user data.
 *
 * \param stgmgr Strategy manager to destroy.
 * \param value User data to set.
 */
#define cg_bittorrent_stdio_filemgr_setuserdata(stgmgr, value) (stgmgr->userData = value)

/**
 * Get a user data.
 *
 * \param stgmgr Strategy manager to destroy.
 *
 * \return User data
 */
#define cg_bittorrent_stdio_filemgr_getuserdata(stgmgr) (stgmgr->userData)

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
#define cg_bittorrent_stdio_filemgr_getnextpeer(stgmgr, tracker, pieceIdx) ((stgmgr->getPeerFunc) ? stgmgr->getPeerFunc(stgmgr, tracker, pieceIdx) : FALSE)

#ifdef  __cplusplus
}
#endif

#endif
