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

#include <cybergarage/bittorrent/cmetainfo.h>

#ifdef  __cplusplus
extern "C" {
#endif

/****************************************
* Data Type
****************************************/

/* Metainfo */
typedef BOOL (*CG_BITTORRENT_FILEMGR_ADDMETAINFO)(void *cfileMgr, CgBittorrentMetainfo *cbm);
typedef BOOL (*CG_BITTORRENT_FILEMGR_REMOVEMETAINFO)(void *cfileMgr, CgByte *infoHash);
typedef int (*CG_BITTORRENT_FILEMGR_GETMETAINFOS)(void *cfileMgr, CgBittorrentMetainfoList **cbmList);
typedef BOOL (*CG_BITTORRENT_FILEMGR_GETMETAINFO)(void *cfileMgr, CgByte *infoHash, CgBittorrentMetainfo **cbm);

/* Input */
typedef BOOL (*CG_BITTORRENT_FILEMGR_OPENFILE)(void *cfileMgr, CgBittorrentMetainfo *cbm, int fileIdx);
typedef int (*CG_BITTORRENT_FILEMGR_SEEKFILE)(void *cfileMgr, CgInt64 offset);
typedef int (*CG_BITTORRENT_FILEMGR_READFILE)(void *cfileMgr, char *buf, int bufLen);
typedef int (*CG_BITTORRENT_FILEMGR_WRITEFILE)(void *cfileMgr, char *buf, int bufLen);
typedef BOOL (*CG_BITTORRENT_FILEMGR_CLOSEFILE)(void *cfileMgr);

typedef struct _CgBittorrentFileMgr {
	/* Metainfo */
	CG_BITTORRENT_FILEMGR_ADDMETAINFO addMetainfoFunc;
	CG_BITTORRENT_FILEMGR_REMOVEMETAINFO removeMetainfoFunc;
	CG_BITTORRENT_FILEMGR_GETMETAINFOS getMetainfosFunc;
	CG_BITTORRENT_FILEMGR_GETMETAINFO getMetainfoFunc;
	/* File */
	CG_BITTORRENT_FILEMGR_OPENFILE openFileFunc;
	CG_BITTORRENT_FILEMGR_SEEKFILE seekFileFunc;
	CG_BITTORRENT_FILEMGR_READFILE readFileFunc;
	CG_BITTORRENT_FILEMGR_WRITEFILE writeFileFunc;
	CG_BITTORRENT_FILEMGR_CLOSEFILE closeFileFunc;
	/* User Data */
	void *userData;
} CgBittorrentFileMgr;

/****************************************
* Function (BlockDevMgr)
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
 * \param fileMgr Block device manager to destroy.
 */
void cg_bittorrent_filemgr_delete(CgBittorrentFileMgr *fileMgr);

/**
 * Check if the deveice is initialized normally.
 *
 * \param fileMgr Block device manager to check.
 *
 * \return TRUE if the specified block device manager is initialized normally.
 */
BOOL cg_bittorrent_filemgr_isvalidated(CgBittorrentFileMgr *fileMgr);

/****************************************
* Function (Metainfo)
****************************************/

/**
 * Set a function to add a metainfo.
 *
 * \param fileMgr Block device manager in question.
 * \param func Function to set.
 */
#define cg_bittorrent_filemgr_setaddmetainfofunc(fileMgr, func) (fileMgr->addMetainfoFunc = func)

/**
 * Return a function to add a metainfo.
 *
 * \param fileMgr Block device manager in question.
 *
 * \return Specifided function
 */
#define cg_bittorrent_filemgr_getaddmetainfofunc(fileMgr) (fileMgr->addMetainfoFunc)

/**
 * Set a function to remove a metainfo.
 *
 * \param fileMgr Block device manager in question.
 * \param func Function to set.
 */
#define cg_bittorrent_filemgr_setremovemetainfofunc(fileMgr, func) (fileMgr->removeMetainfoFunc = func)

/**
 * Return a function to remove a metainfo.
 *
 * \param fileMgr Block device manager in question.
 *
 * \return Specifided function
 */
#define cg_bittorrent_filemgr_getremovemetainfofunc(fileMgr) (fileMgr->removeMetainfoFunc)

/**
 * Set a function to get a metainfo list.
 *
 * \param fileMgr Block device manager in question.
 * \param func Function to set.
 */
#define cg_bittorrent_filemgr_setgetmetainfosfunc(fileMgr, func) (fileMgr->getMetainfosFunc = func)

/**
 * Return a function to get a metainfo list.
 *
 * \param fileMgr Block device manager in question.
 *
 * \return Specifided function
 */
#define cg_bittorrent_filemgr_getgetmetainfosfunc(fileMgr) (fileMgr->getMetainfosFunc)

/**
 * Set a function to get a metainfo.
 *
 * \param fileMgr Block device manager in question.
 * \param func Function to set.
 */
#define cg_bittorrent_filemgr_setgetmetainfofunc(fileMgr, func) (fileMgr->getMetainfoFunc = func)

/**
 * Return a function to get a metainfo.
 *
 * \param fileMgr Block device manager in question.
 *
 * \return Specifided function
 */
#define cg_bittorrent_filemgr_getgetmetainfofunc(fileMgr) (fileMgr->getMetainfoFunc)

/****************************************
* Function (File)
****************************************/

/**
 * Set a open function.
 *
 * \param fileMgr Block device manager in question.
 * \param func Function to set.
 */
#define cg_bittorrent_filemgr_setopenfilefunc(fileMgr, func) (fileMgr->openFileFunc = func)

/**
 * Return a open function.
 *
 * \param fileMgr Block device manager in question.
 *
 * \return Read function
 */
#define cg_bittorrent_filemgr_getopenfilefunc(fileMgr) (fileMgr->openFileFunc)

/**
 * Set a seek function.
 *
 * \param fileMgr Block device manager in question.
 * \param func Function to set.
 */
#define cg_bittorrent_filemgr_setseekfilefunc(fileMgr, func) (fileMgr->seekFileFunc = func)

/**
 * Return a seek function.
 *
 * \param fileMgr Block device manager in question.
 *
 * \return Read function
 */
#define cg_bittorrent_filemgr_getseekfilefunc(fileMgr) (fileMgr->seekFileFunc)

/**
 * Set a read function.
 *
 * \param fileMgr Block device manager in question.
 * \param func Function to set.
 */
#define cg_bittorrent_filemgr_setreadfilefunc(fileMgr, func) (fileMgr->readFileFunc = func)

/**
 * Return a read function.
 *
 * \param fileMgr Block device manager in question.
 *
 * \return Read function
 */
#define cg_bittorrent_filemgr_getreadfilefunc(fileMgr) (fileMgr->readFileFunc)

/**
 * Set a write function.
 *
 * \param fileMgr Block device manager in question.
 * \param func Function to set.
 */
#define cg_bittorrent_filemgr_setwritefilefunc(fileMgr, func) (fileMgr->writeFileFunc = func)

/**
 * Return a write function.
 *
 * \param fileMgr Block device manager in question.
 *
 * \return Read function
 */
#define cg_bittorrent_filemgr_getwritefilefunc(fileMgr) (fileMgr->writeFileFunc)

/**
 * Set a close function.
 *
 * \param fileMgr Block device manager in question.
 * \param func Function to set.
 */
#define cg_bittorrent_filemgr_setclosefilefunc(fileMgr, func) (fileMgr->closeFileFunc = func)

/**
 * Return a close function.
 *
 * \param fileMgr Block device manager in question.
 *
 * \return Read function
 */
#define cg_bittorrent_filemgr_getclosefilefunc(fileMgr) (fileMgr->closeFileFunc)

/****************************************
* Function (User Data)
****************************************/

/**
 * Set a user data.
 *
 * \param fileMgr Block device manager in question.
 * \param value User data to set.
 */
#define cg_bittorrent_filemgr_setuserdata(fileMgr, value) (fileMgr->userData = value)

/**
 * Get a user data.
 *
 * \param fileMgr Block device manager in question.
 *
 * \return User data
 */
#define cg_bittorrent_filemgr_getuserdata(fileMgr) (fileMgr->userData)

/****************************************
* Function (Metainfo)
****************************************/

/**
 * Add a metainfo.
 *
 * \param fileMgr Block device manager in question.
 * \param cbm Metainfo to add.
 *
 * \return TRUE if the specifed metainfo is added normally, otherwise FALSE.
 */
#define cg_bittorrent_filemgr_addmetainfo(fileMgr, cbm) ((fileMgr->addMetainfoFunc) ? fileMgr->addMetainfoFunc(fileMgr, cbm) : FALSE)

/**
 * Remove a specified metainfo.
 *
 * \param fileMgr Block device manager in question.
 * \param infoHash Info_hash of a metainfo to delete.
 *
 * \return TRUE if the specifed metainfo is removed normally, otherwise FALSE.
 */
#define cg_bittorrent_filemgr_removemetainfo(fileMgr, infoHash) ((fileMgr->removeMetainfoFunc) ? fileMgr->removeMetainfoFunc(fileMgr, infoHash) : FALSE)

/**
 * Get a metainfo list.
 *
 * \param fileMgr Block device manager in question.
 * \param cbmList Metainfo list to store.
 *
 * \return Number of the stored mateinfos.
 */
#define cg_bittorrent_filemgr_getmetainfos(fileMgr, cbmList) ((fileMgr->getMetainfosFunc) ? fileMgr->getMetainfosFunc(fileMgr, cbmList) : FALSE)

/**
 * Get a metainfo.
 *
 * \param fileMgr Block device manager in question.
 * \param infoHash Info_hash of a metainfo to get.
 * \param cbm Metainfo to store.
 *
 * \return TRUE if the specifed metainfo is stored normally, otherwise FALSE.
 */
#define cg_bittorrent_filemgr_getmetainfo(fileMgr, infoHash, cbm) ((fileMgr->getMetainfoFunc) ? fileMgr->getMetainfoFunc(fileMgr, infoHash, cbm) : FALSE)

/****************************************
* Function (Piece)
****************************************/

/**
 * Read a piece.
 *
 * \param fileMgr Block device manager in question.
 * \param cbm Metainfo of the piece.
 * \param idx Index of the piece.
 * \param buf Pointer of a buffer to read the specifed piece. You have to free the pointer when you don't need.
 *
 * \return TRUE if the specifed piece is read normally, otherwise FALSE.
 */
#define cg_bittorrent_filemgr_readpiece(fileMgr, cbm, idx, buf) ((fileMgr->readPieceFunc) ? fileMgr->readPieceFunc(fileMgr, cbm, idx, buf) : FALSE)

/**
 * Write a piece.
 *
 * \param fileMgr Block device manager in question.
 * \param cbm Metainfo of the piece.
 * \param idx Index of the piece.
 * \param buf Buffer which has a piece data.
 *
 * \return TRUE if the specifed piece is worte normally, otherwise FALSE.
 */
#define cg_bittorrent_filemgr_writepiece(fileMgr, cbm, idx, buf) ((fileMgr->writePieceFunc) ? fileMgr->writePieceFunc(fileMgr, cbm, idx, buf) : FALSE)

/**
 * Check a piece.
 *
 * \param fileMgr Block device manager in question.
 * \param cbm Metainfo of the piece.
 * \param idx Index of the piece.
 *
 * \return TRUE if the specifed piece is available, otherwise FALSE.
 .
 */
#define cg_bittorrent_filemgr_havepiece(fileMgr, cbm, idx) ((fileMgr->havePieceFunc) ? fileMgr->havePieceFunc(fileMgr, cbm, idx) : FALSE)

/****************************************
* Function (File)
****************************************/

/**
 * Open a file.
 *
 * \param fileMgr Block device manager in question.
 * \param cbm Metainfo of the file.
 * \param idx Index of the file. Muse be zero when the file mode is single.
 *
 * \return TRUE if the specifed file is available, otherwise FALSE.
 .
 */
#define cg_bittorrent_filemgr_openfile(fileMgr, cbm, idx) ((fileMgr->openFileFunc) ? fileMgr->openFileFunc(fileMgr, cbm, idx) : FALSE)

/**
 * Seek a file.
 *
 * \param fileMgr Block device manager in question.
 * \param cbm Metainfo of the file.
 * \param offset Offset to seek.
 *
 * \return TRUE if the specifed file is available, otherwise FALSE.
 .
 */
#define cg_bittorrent_filemgr_seekfile(fileMgr, offset) ((fileMgr->seekFileFunc) ? fileMgr->seekFileFunc(fileMgr, offset) : FALSE)

/**
 * Read a file.
 *
 * \param fileMgr Block device manager in question.
 * \param cbm Metainfo of the file.
 * \param buf Buffer to read the data.
 * \param bufLen Length of the buffer.
 *
 * \return TRUE if the specifed file is available, otherwise FALSE.
 .
 */
#define cg_bittorrent_filemgr_readfile(fileMgr, buf, bufLen) ((fileMgr->readFileFunc) ? fileMgr->readFileFunc(fileMgr, buf, bufLen) : FALSE)

/**
 * Write a file.
 *
 * \param fileMgr Block device manager in question.
 * \param cbm Metainfo of the file.
 * \param buf Buffer to write the data.
 * \param bufLen Length of the buffer.
 *
 * \return TRUE if the specifed file is available, otherwise FALSE.
 .
 */
#define cg_bittorrent_filemgr_writefile(fileMgr, buf, bufLen) ((fileMgr->writeFileFunc) ? fileMgr->writeFileFunc(fileMgr, buf, bufLen) : FALSE)

/**
 * Close a file.
 *
 * \param fileMgr Block device manager in question.
 * \param cbm Metainfo of the file.
 *
 * \return TRUE if the specifed file is available, otherwise FALSE.
 .
 */
#define cg_bittorrent_filemgr_closefile(fileMgr) ((fileMgr->closeFileFunc) ? fileMgr->closeFileFunc(fileMgr) : FALSE)

/****************************************
* Function (File)
****************************************/

/**
 * Write a piece to the file.
 *
 * \param fileMgr Block device manager in question.
 * \param cbm Metainfo of the file.
 * \param pieceIdx Index of the piece.
 * \param buf Data to write.
 * \param bufLen Length of the data.
 *
 * \return TRUE if the specifed file is available, otherwise FALSE.
 */
BOOL cg_bittorrent_filemgr_writepiecedata(CgBittorrentFileMgr *fileMgr, CgBittorrentMetainfo *cbm, int pieceIdx , CgByte *buf, int bufLen);

/**
 * Read a piece from the file.
 *
 * \param fileMgr Block device manager in question.
 * \param cbm Metainfo of the file.
 * \param pieceIdx Index of the piece.
 * \param buf Data to store.
 * \param bufLen Length of the data.
 * \param readLen Length of the data to read.
 *
 * \return TRUE if the specifed file is available, otherwise FALSE.
 */
BOOL cg_bittorrent_filemgr_readpiecedata(CgBittorrentFileMgr *fileMgr, CgBittorrentMetainfo *cbm, int pieceIdx , CgByte *buf, int bufLen, int *readLen);

#ifdef  __cplusplus
}
#endif

#endif
