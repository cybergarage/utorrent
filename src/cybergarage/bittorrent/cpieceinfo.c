/******************************************************************
*
*	CyberBittorrent for C
*
*	Copyright (C) Satoshi Konno 2007
*
*	File: cpieceinfo.c
*
*	Revision:
*
*	12/05/07
*		- first revision
*
******************************************************************/

#include <cybergarage/bittorrent/cpieceinfo.h>

/****************************************
* cg_bittorrent_pieceinfo_new
****************************************/

CgBittorrentPieceInfo *cg_bittorrent_pieceinfo_new()
{
	CgBittorrentPieceInfo *cbpi;

	cbpi = (CgBittorrentPieceInfo *)malloc(sizeof(CgBittorrentPieceInfo));
	if (!cbpi)
		return NULL;

	cg_bittorrent_pieceinfo_setdownloaded(cbpi, FALSE);

	return cbpi;
}

/****************************************
* cg_bittorrent_pieceinfo_delete
****************************************/

void cg_bittorrent_pieceinfo_delete(CgBittorrentPieceInfo *cbpi)
{
	if (!cbpi)
		return;

	free(cbpi);
}
