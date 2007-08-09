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

/* Metainfo */
typedef BOOL (*CG_BITTORRENT_BLOCKDEVICEMGR_ADDMETAINFO)(void *cbdmgr, CgBittorrentMetainfo *cbm);
typedef BOOL (*CG_BITTORRENT_BLOCKDEVICEMGR_REMOVEMETAINFO)(void *cbdmgr, char *infoHash);
typedef BOOL (*CG_BITTORRENT_BLOCKDEVICEMGR_GETMETAINFOS)(void *cbdmgr, CgBittorrentMetainfoList *cbmList);
typedef BOOL (*CG_BITTORRENT_BLOCKDEVICEMGR_GETMETAINFO)(void *cbdmgr, char *infoHash, CgBittorrentMetainfo *cbm);

/* Piece */
typedef BOOL (*CG_BITTORRENT_BLOCKDEVICEMGR_READPIECE)(void *cbdmgr, CgBittorrentMetainfo *cbm, int pieceIdx , CgByte **pieceData, int *pieceLength);
typedef BOOL (*CG_BITTORRENT_BLOCKDEVICEMGR_WRITEPIECE)(void *cbdmgr, CgBittorrentMetainfo *cbm, int pieceIdx, CgByte *pieceData, int pieceLength);
typedef BOOL (*CG_BITTORRENT_BLOCKDEVICEMGR_HAVEPIECE)(void *cbdmgr, CgBittorrentMetainfo *cbm, int pieceIdx);
typedef BOOL (*CG_BITTORRENT_BLOCKDEVICEMGR_OPENFILE)(void *cbdmgr, CgBittorrentMetainfo *cbm, int fileIdx);
typedef int (*CG_BITTORRENT_BLOCKDEVICEMGR_READFILE)(void *cbdmgr, char *buf, int bufLen);
typedef BOOL (*CG_BITTORRENT_BLOCKDEVICEMGR_CLOSEFILE)(void *cbdmgr);

typedef struct _CgBittorrentBlockDeviceMgr {
	/* Metainfo */
	CG_BITTORRENT_BLOCKDEVICEMGR_ADDMETAINFO addMetainfoFunc;
	CG_BITTORRENT_BLOCKDEVICEMGR_REMOVEMETAINFO removeMetainfoFunc;
	CG_BITTORRENT_BLOCKDEVICEMGR_GETMETAINFOS getMetainfosFunc;
	CG_BITTORRENT_BLOCKDEVICEMGR_GETMETAINFO getMetainfoFunc;

	/* Piece */
	CG_BITTORRENT_BLOCKDEVICEMGR_READPIECE readPieceFunc;
	CG_BITTORRENT_BLOCKDEVICEMGR_WRITEPIECE writePieceFunc;
	CG_BITTORRENT_BLOCKDEVICEMGR_HAVEPIECE havePieceFunc;
	CG_BITTORRENT_BLOCKDEVICEMGR_OPENFILE openFileFunc;
	CG_BITTORRENT_BLOCKDEVICEMGR_READFILE readFileFunc;
	CG_BITTORRENT_BLOCKDEVICEMGR_CLOSEFILE closeFileFunc;
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

/****************************************
* Function (Metainfo)
****************************************/

/****************************************
* Function (Piece)
****************************************/

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
 * Set a open function.
 *
 * \param bdmgr Block device manager in question.
 * \param func Function to set.
 */
#define cg_bittorrent_blockdevicemgr_setopenfilefunc(bdmgr, func) (bdmgr->openFileFunc = func)

/**
 * Return a open function.
 *
 * \param bdmgr Block device manager in question.
 *
 * \return Read function
 */
#define cg_bittorrent_blockdevicemgr_getopenfilefunc(bdmgr) (bdmgr->openFileFunc)

/**
 * Set a read function.
 *
 * \param bdmgr Block device manager in question.
 * \param func Function to set.
 */
#define cg_bittorrent_blockdevicemgr_setreadfilefunc(bdmgr, func) (bdmgr->readFileFunc = func)

/**
 * Return a read function.
 *
 * \param bdmgr Block device manager in question.
 *
 * \return Read function
 */
#define cg_bittorrent_blockdevicemgr_getreadfilefunc(bdmgr) (bdmgr->readFileFunc)

/**
 * Set a close function.
 *
 * \param bdmgr Block device manager in question.
 * \param func Function to set.
 */
#define cg_bittorrent_blockdevicemgr_setclosefilefunc(bdmgr, func) (bdmgr->closeFileFunc = func)

/**
 * Return a close function.
 *
 * \param bdmgr Block device manager in question.
 *
 * \return Read function
 */
#define cg_bittorrent_blockdevicemgr_getclosefilefunc(bdmgr) (bdmgr->closeFileFunc)

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
 * \param cbm Metainfo of the piece.
 * \param idx Index of the piece.
 * \param buf Pointer of a buffer to read the specifed piece. You have to free the pointer when you don't need.
 *
 * \return TRUE if the specifed piece is read normally, otherwise FALSE.
 */
#define cg_bittorrent_blockdevicemgr_readpiece(bdmgr, cbm, idx, buf) ((bdmgr->readPieceFunc) ? FALSE : bdmgr->readPieceFunc(cbm, idx, buf))

/**
 * Write a piece.
 *
 * \param bdmgr Block device manager in question.
 * \param cbm Metainfo of the piece.
 * \param idx Index of the piece.
 * \param buf Buffer which has a piece data.
 *
 * \return TRUE if the specifed piece is worte normally, otherwise FALSE.
 */
#define cg_bittorrent_blockdevicemgr_writepiece(bdmgr, cbm, idx, buf) ((bdmgr->writePieceFunc) ? FALSE : bdmgr->writePieceFunc(cbm, idx, buf))

/**
 * Check a piece.
 *
 * \param bdmgr Block device manager in question.
 * \param cbm Metainfo of the piece.
 * \param idx Index of the piece.
 *
 * \return TRUE if the specifed piece is available, otherwise FALSE.
 .
 */
#define cg_bittorrent_blockdevicemgr_havepiece(bdmgr, cbm, idx) ((bdmgr->havePieceFunc) ? FALSE : bdmgr->havePieceFunc(cbm, idx))

/**
 * Open a file.
 *
 * \param bdmgr Block device manager in question.
 * \param cbm Metainfo of the file.
 * \param idx Index of the file. Muse be zero when the file mode is single.
 *
 * \return TRUE if the specifed file is available, otherwise FALSE.
 .
 */
#define cg_bittorrent_blockdevicemgr_openfile(bdmgr, cbm, idx) ((bdmgr->openFileFunc) ? FALSE : bdmgr->openFileFunc(cbm, idx))

/**
 * Read a file.
 *
 * \param bdmgr Block device manager in question.
 * \param cbm Metainfo of the file.
 * \param buf Buffer to store the data.
 * \param bufLen Length of the buffer.
 *
 * \return TRUE if the specifed file is available, otherwise FALSE.
 .
 */
#define cg_bittorrent_blockdevicemgr_readfile(bdmgr, buf, bufLen) ((bdmgr->readFileFunc) ? FALSE : bdmgr->readFileFunc(cbm, buf, bufLen))

/**
 * Close a file.
 *
 * \param bdmgr Block device manager in question.
 * \param cbm Metainfo of the file.
 *
 * \return TRUE if the specifed file is available, otherwise FALSE.
 .
 */
#define cg_bittorrent_blockdevicemgr_closefile(bdmgr) ((bdmgr->closeFileFunc) ? FALSE : bdmgr->closeFileFunc(cbm, idx))

BOOL cg_bittorrent_blockdevicemgr_getfileindex(CgBittorrentBlockDeviceMgr *bdmrg, CgBittorrentMetainfo *cbm, int pieceIdx, int *startFileIndex, int *endFileIndex);

#ifdef  __cplusplus
}
#endif

#endif
