/******************************************************************
*
*	CyberBittorrent for C
*
*	Copyright (C) Satoshi Konno 2007
*
*	File: cblockdevicemgr.c
*
*	Revision:
*
*	07/12/08
*		- first revision
*
******************************************************************/

#include <cybergarage/bittorrent/cblockdevmgr.h>

#include <stdlib.h>

/****************************************
* cg_bittorrent_blockdevicemgr_new
****************************************/

CgBittorrentBlockDeviceMgr *cg_bittorrent_blockdevicemgr_new()
{
	CgBittorrentBlockDeviceMgr *bdmgr;

	bdmgr = (CgBittorrentBlockDeviceMgr *)malloc(sizeof(CgBittorrentBlockDeviceMgr));
	if (!bdmgr)
		return NULL;

	/* Metainfo */
	cg_bittorrent_blockdevicemgr_setaddmetainfofunc(bdmgr, NULL);
	cg_bittorrent_blockdevicemgr_setremovemetainfofunc(bdmgr, NULL);
	cg_bittorrent_blockdevicemgr_setgetmetainfosfunc(bdmgr, NULL);
	cg_bittorrent_blockdevicemgr_setgetmetainfofunc(bdmgr, NULL);

	/* File */
	cg_bittorrent_blockdevicemgr_setopenfilefunc(bdmgr, NULL);
	cg_bittorrent_blockdevicemgr_setseekfilefunc(bdmgr, NULL);
	cg_bittorrent_blockdevicemgr_setreadfilefunc(bdmgr, NULL);
	cg_bittorrent_blockdevicemgr_setwritefilefunc(bdmgr, NULL);
	cg_bittorrent_blockdevicemgr_setclosefilefunc(bdmgr, NULL);

	return bdmgr;
}

/****************************************
* cg_bittorrent_blockdevicemgr_delete
****************************************/

void cg_bittorrent_blockdevicemgr_delete(CgBittorrentBlockDeviceMgr *bdmgr)
{
	if (!bdmgr)
		return;

	free(bdmgr);
}

/****************************************
* cg_bittorrent_blockdevicemgr_getfileindex
****************************************/

BOOL cg_bittorrent_blockdevicemgr_isvalidated(CgBittorrentBlockDeviceMgr *bdmgr)
{
	/* Metainfo */
	if (!cg_bittorrent_blockdevicemgr_getaddmetainfofunc(bdmgr))
		return FALSE;
	if (!cg_bittorrent_blockdevicemgr_getremovemetainfofunc(bdmgr))
		return FALSE;
	if (!cg_bittorrent_blockdevicemgr_getgetmetainfosfunc(bdmgr))
		return FALSE;
	if (!cg_bittorrent_blockdevicemgr_getgetmetainfofunc(bdmgr))
		return FALSE;

	/* File */
	if (!cg_bittorrent_blockdevicemgr_getopenfilefunc(bdmgr))
		return FALSE;
	if (!cg_bittorrent_blockdevicemgr_getseekfilefunc(bdmgr))
		return FALSE;
	if (!cg_bittorrent_blockdevicemgr_getreadfilefunc(bdmgr))
		return FALSE;
	if (!cg_bittorrent_blockdevicemgr_getwritefilefunc(bdmgr))
		return FALSE;
	if (!cg_bittorrent_blockdevicemgr_getclosefilefunc(bdmgr))
		return FALSE;

	return TRUE;
}

/****************************************
* cg_bittorrent_bdmgr_readpiece
****************************************/

BOOL cg_bittorrent_blockdevicemgr_readpiecedata(CgBittorrentBlockDeviceMgr *bdmgr, CgBittorrentMetainfo *cbm, int pieceIdx , CgByte *buf, int bufLen, int *readLen)
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
		if (!cg_bittorrent_blockdevicemgr_openfile(bdmgr, cbm, pieceIdx))
			return FALSE;
		if (!cg_bittorrent_blockdevicemgr_seekfile(bdmgr, fileOffset)) {
			cg_bittorrent_blockdevicemgr_closefile(bdmgr);
			return FALSE;
		}
		readSize = cg_bittorrent_blockdevicemgr_readfile(bdmgr, (buf+pieceOffet), blockSize);
		cg_bittorrent_blockdevicemgr_closefile(bdmgr);
		if (readSize != blockSize)
			return FALSE;
		readLen += blockSize;
	}

	return TRUE;
}

/****************************************
* cg_bittorrent_bdmgr_writepiece
****************************************/

BOOL cg_bittorrent_blockdevicemgr_writepiecedata(CgBittorrentBlockDeviceMgr *bdmgr, CgBittorrentMetainfo *cbm, int pieceIdx , CgByte *buf, int bufLen)
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
		if (!cg_bittorrent_blockdevicemgr_openfile(bdmgr, cbm, pieceIdx))
			return FALSE;
		if (!cg_bittorrent_blockdevicemgr_seekfile(bdmgr, fileOffset)) {
			cg_bittorrent_blockdevicemgr_closefile(bdmgr);
			return FALSE;
		}
		worteRet = cg_bittorrent_blockdevicemgr_writefile(bdmgr, buf+pieceOffet, blockSize);
		cg_bittorrent_blockdevicemgr_closefile(bdmgr);
		if (!worteRet)
			return FALSE;
	}

	return TRUE;
}
