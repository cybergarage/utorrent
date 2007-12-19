/******************************************************************
*
*	CyberBittorrent for C
*
*	Copyright (C) Satoshi Konno 2007
*
*	File: cmetainfo_statistics.c
*
*	Revision:
*
*	08/20/07
*		- first revision
*
******************************************************************/

#include <cybergarage/bittorrent/cmetainfo.h>

/****************************************
* cg_bittorrent_metainfo_getdownloadedpercentage
****************************************/

int cg_bittorrent_metainfo_getdownloadedpercentage(CgBittorrentMetainfo *cbm)
{
	int nTotalPieces;
	int downloadedPieces;
	int n;

	if (!cbm)
		return FALSE;

	nTotalPieces = cg_bittorrent_metainfo_gettotalpieces(cbm);
	if (nTotalPieces <= 0)
		return FALSE;
	
	downloadedPieces = 0;
	for (n=0; n<nTotalPieces; n++) {
		if (cg_bittorrent_metainfo_haspiece(cbm, n))
			downloadedPieces++;
	}

	return ((downloadedPieces * 100) / nTotalPieces);
}

