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
	CgBittorrentBlockDeviceMgr *bdmrg;

	bdmrg = (CgBittorrentBlockDeviceMgr *)malloc(sizeof(CgBittorrentBlockDeviceMgr));
	if (!bdmrg)
		return NULL;

	cg_bittorrent_blockdevicemgr_setreadpiecefunc(bdmrg, NULL);
	cg_bittorrent_blockdevicemgr_setwritepiecefunc(bdmrg, NULL);
	cg_bittorrent_blockdevicemgr_sethavepiecefunc(bdmrg, NULL);

	return bdmrg;
}

/****************************************
* cg_bittorrent_blockdevicemgr_delete
****************************************/

void cg_bittorrent_blockdevicemgr_delete(CgBittorrentBlockDeviceMgr *bdmrg)
{
	if (!bdmrg)
		return;

	free(bdmrg);
}

/****************************************
* cg_bittorrent_blockdevicemgr_getfileindex
****************************************/

BOOL cg_bittorrent_blockdevicemgr_getfileindex(CgBittorrentBlockDeviceMgr *bdmrg, CgBittorrentMetainfo *cbm, int pieceIdx, int *startFileIndex, int *endFileIndex)
{
	int cbmFileCnt;
	int pieceLength;
	CgInt64 pieceOffset;
	CgInt64 cbmFileOffset;
	CgInt64 cbmFileLength;
	CgInt64 fileLength;
	int cbmFileIndex;

	if (!bdmrg || !cbm)
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
			if (pieceOffset < (cbmFileOffset + fileLength)) {
				*startFileIndex = cbmFileIndex;
				break;
			}
			cbmFileOffset += fileLength;
		}

		for (; cbmFileIndex<cbmFileCnt; cbmFileIndex++) {
			cbmFileOffset += cg_bittorrent_metainfo_getinfofilelength(cbm, cbmFileIndex);
			if (pieceOffset <= cbmFileOffset) {
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