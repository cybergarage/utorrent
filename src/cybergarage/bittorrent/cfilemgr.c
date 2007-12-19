/******************************************************************
*
*	CyberBittorrent for C
*
*	Copyright (C) Satoshi Konno 2007
*
*	File: cfilemgr.c
*
*	Revision:
*
*	07/12/08
*		- first revision
*
******************************************************************/

#include <cybergarage/bittorrent/cfilemgr.h>

#include <stdlib.h>

/****************************************
* cg_bittorrent_filemgr_new
****************************************/

CgBittorrentFileMgr *cg_bittorrent_filemgr_new()
{
	CgBittorrentFileMgr *fileMgr;

	fileMgr = (CgBittorrentFileMgr *)malloc(sizeof(CgBittorrentFileMgr));
	if (!fileMgr)
		return NULL;

	/* Metainfo */
	cg_bittorrent_filemgr_setaddmetainfofunc(fileMgr, NULL);
	cg_bittorrent_filemgr_setremovemetainfofunc(fileMgr, NULL);
	cg_bittorrent_filemgr_setgetmetainfosfunc(fileMgr, NULL);
	cg_bittorrent_filemgr_setgetmetainfofunc(fileMgr, NULL);

	/* File */
	cg_bittorrent_filemgr_setopenfilefunc(fileMgr, NULL);
	cg_bittorrent_filemgr_setseekfilefunc(fileMgr, NULL);
	cg_bittorrent_filemgr_setreadfilefunc(fileMgr, NULL);
	cg_bittorrent_filemgr_setwritefilefunc(fileMgr, NULL);
	cg_bittorrent_filemgr_setclosefilefunc(fileMgr, NULL);

	return fileMgr;
}

/****************************************
* cg_bittorrent_filemgr_delete
****************************************/

void cg_bittorrent_filemgr_delete(CgBittorrentFileMgr *fileMgr)
{
	if (!fileMgr)
		return;

	free(fileMgr);
}

/****************************************
* cg_bittorrent_filemgr_getfileindex
****************************************/

BOOL cg_bittorrent_filemgr_isvalidated(CgBittorrentFileMgr *fileMgr)
{
	/* Metainfo */
	if (!cg_bittorrent_filemgr_getaddmetainfofunc(fileMgr))
		return FALSE;
	if (!cg_bittorrent_filemgr_getremovemetainfofunc(fileMgr))
		return FALSE;
	if (!cg_bittorrent_filemgr_getgetmetainfosfunc(fileMgr))
		return FALSE;
	if (!cg_bittorrent_filemgr_getgetmetainfofunc(fileMgr))
		return FALSE;

	/* File */
	if (!cg_bittorrent_filemgr_getopenfilefunc(fileMgr))
		return FALSE;
	if (!cg_bittorrent_filemgr_getseekfilefunc(fileMgr))
		return FALSE;
	if (!cg_bittorrent_filemgr_getreadfilefunc(fileMgr))
		return FALSE;
	if (!cg_bittorrent_filemgr_getwritefilefunc(fileMgr))
		return FALSE;
	if (!cg_bittorrent_filemgr_getclosefilefunc(fileMgr))
		return FALSE;

	return TRUE;
}

/****************************************
* cg_bittorrent_fileMgr_readpiece
****************************************/

BOOL cg_bittorrent_filemgr_readpiecedata(CgBittorrentFileMgr *fileMgr, CgBittorrentMetainfo *cbm, int pieceIdx , CgByte *buf, int bufLen, int *readLen)
{
	int startFileIdx, endFileIdx;
	int pieceOffet, blockSize;

	CgInt64 fileOffset;
	int fileIdx;
	int readSize;

	if (!cg_bittorrent_metainfo_getfileindexbypieceindex(cbm, pieceIdx, &startFileIdx, &endFileIdx))
		return FALSE;

	*readLen = 0;

	for (fileIdx=startFileIdx; fileIdx <= endFileIdx; fileIdx++) {
		if (!cg_bittorrent_metainfo_getfileandpiecerangebypieceandfileindex(cbm, pieceIdx, fileIdx, &pieceOffet, &fileOffset, &blockSize))
			return FALSE;
		if (!cg_bittorrent_filemgr_openfile(fileMgr, cbm, pieceIdx))
			return FALSE;
		if (!cg_bittorrent_filemgr_seekfile(fileMgr, fileOffset)) {
			cg_bittorrent_filemgr_closefile(fileMgr);
			return FALSE;
		}
		readSize = cg_bittorrent_filemgr_readfile(fileMgr, (buf+pieceOffet), blockSize);
		cg_bittorrent_filemgr_closefile(fileMgr);
		if (readSize != blockSize)
			return FALSE;
		readLen += blockSize;
	}

	return TRUE;
}

/****************************************
* cg_bittorrent_fileMgr_writepiece
****************************************/

BOOL cg_bittorrent_filemgr_writepiecedata(CgBittorrentFileMgr *fileMgr, CgBittorrentMetainfo *cbm, int pieceIdx , CgByte *buf, int bufLen)
{
	int startFileIdx, endFileIdx;
	int pieceOffet, blockSize;
	CgInt64 fileOffset;
	int fileIdx;
	BOOL worteRet;

	if (!cg_bittorrent_metainfo_getfileindexbypieceindex(cbm, pieceIdx, &startFileIdx, &endFileIdx))
		return FALSE;

	for (fileIdx=startFileIdx; fileIdx <= endFileIdx; fileIdx++) {
		if (!cg_bittorrent_metainfo_getfileandpiecerangebypieceandfileindex(cbm, pieceIdx, fileIdx, &pieceOffet, &fileOffset, &blockSize))
			return FALSE;
		if (!cg_bittorrent_filemgr_openfile(fileMgr, cbm, pieceIdx))
			return FALSE;
		if (!cg_bittorrent_filemgr_seekfile(fileMgr, fileOffset)) {
			cg_bittorrent_filemgr_closefile(fileMgr);
			return FALSE;
		}
		worteRet = cg_bittorrent_filemgr_writefile(fileMgr, buf+pieceOffet, blockSize);
		cg_bittorrent_filemgr_closefile(fileMgr);
		if (!worteRet)
			return FALSE;
	}

	return TRUE;
}
