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

	/* Piece */
	cg_bittorrent_blockdevicemgr_setreadpiecefunc(bdmgr, NULL);
	cg_bittorrent_blockdevicemgr_setwritepiecefunc(bdmgr, NULL);
	cg_bittorrent_blockdevicemgr_sethavepiecefunc(bdmgr, NULL);

	/* File */
	cg_bittorrent_blockdevicemgr_setopenfilefunc(bdmgr, NULL);
	cg_bittorrent_blockdevicemgr_setreadfilefunc(bdmgr, NULL);
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

	/* Piece */
	if (!cg_bittorrent_blockdevicemgr_getreadpiecefunc(bdmgr))
		return FALSE;
	if (!cg_bittorrent_blockdevicemgr_getwritepiecefunc(bdmgr))
		return FALSE;
	if (!cg_bittorrent_blockdevicemgr_gethavepiecefunc(bdmgr))
		return FALSE;

	/* File */
	if (!cg_bittorrent_blockdevicemgr_getopenfilefunc(bdmgr))
		return FALSE;
	if (!cg_bittorrent_blockdevicemgr_getreadfilefunc(bdmgr))
		return FALSE;
	if (!cg_bittorrent_blockdevicemgr_getclosefilefunc(bdmgr))
		return FALSE;

	return TRUE;
}


/****************************************
* cg_bittorrent_blockdevicemgr_getfileindex
****************************************/

BOOL cg_bittorrent_blockdevicemgr_getfileindex(CgBittorrentBlockDeviceMgr *bdmgr, CgBittorrentMetainfo *cbm, int pieceIdx, int *startFileIndex, int *endFileIndex)
{
	int cbmFileCnt;
	int pieceLength;
	CgInt64 pieceOffset;
	CgInt64 cbmFileOffset;
	CgInt64 cbmFileLength;
	CgInt64 fileLength;
	int cbmFileIndex;

	if (!bdmgr || !cbm)
		return FALSE;

	pieceLength = cg_bittorrent_metainfo_getinfopiecelength(cbm);
	pieceOffset = (CgInt64)pieceIdx * (CgInt64)pieceLength;

	if (cg_bittorrent_metainfo_ismultiplefilemode(cbm)) {
		cbmFileCnt = cg_bittorrent_metainfo_getnfiles(cbm);
		if (cbmFileCnt < 0)
			return FALSE;

		*startFileIndex = *endFileIndex = 0;
		cbmFileOffset = 0;
		for (cbmFileIndex=0; cbmFileIndex<cbmFileCnt; cbmFileIndex++) { /* Info in Multiple File Mode */
			fileLength = cg_bittorrent_metainfo_getinfofilelength(cbm, cbmFileIndex);
			if ((cbmFileOffset <= pieceOffset) && (pieceOffset <= (cbmFileOffset + fileLength))) {
				*startFileIndex = cbmFileIndex;
				break;
			}
			cbmFileOffset += fileLength;
		}

		for (; cbmFileIndex<cbmFileCnt; cbmFileIndex++) {
			cbmFileOffset += cg_bittorrent_metainfo_getinfofilelength(cbm, cbmFileIndex);
			if ((pieceOffset + pieceLength) <= cbmFileOffset) {
				*endFileIndex = cbmFileIndex;
				break;
			}
		}
	}
	else { /* Info in Single File Mode */
		cbmFileLength = cg_bittorrent_metainfo_getinfolength(cbm);
		if (cbmFileLength < pieceOffset)
			return FALSE;
		*startFileIndex = *endFileIndex = 0;
	}

	if (*endFileIndex < *startFileIndex)
		return FALSE;

	return TRUE;
}