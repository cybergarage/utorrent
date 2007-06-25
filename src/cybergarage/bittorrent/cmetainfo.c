/******************************************************************
*
*	CyberBittorrent for C
*
*	Copyright (C) Satoshi Konno 2007
*
*	File: cmetainfo.c
*
*	Revision:
*
*	01/30/07
*		- first revision
*
******************************************************************/

#include <cybergarage/bittorrent/cmetainfo.h>

/****************************************
* cg_bittorrent_metainfo_new
****************************************/

CgBittorrentMetainfo *cg_bittorrent_metainfo_new()
{
	CgBittorrentMetainfo *cbm;

	cbm = (CgBittorrentMetainfo *)malloc(sizeof(CgBittorrentMetainfo));
	if (!cbm)
		return NULL;

	cbm->dir = cg_bittorrent_dictionary_new();

	return cbm;
}

/****************************************
* cg_bittorrent_metainfo_delete
****************************************/

void cg_bittorrent_metainfo_delete(CgBittorrentMetainfo *cbm)
{
	if (!cbm)
		return;

	cg_bittorrent_dictionary_delete(cbm->dir);

	free(cbm);
}

/****************************************
* cg_bittorrent_metainfo_getinfohash
****************************************/

BOOL cg_bittorrent_metainfo_getinfohash(CgBittorrentMetainfo *cbm, unsigned char *infoHash)
{
	CgBittorrentBencoding *infoVal;

	if (!cbm)
		return FALSE;

	infoVal = cg_bittorrent_metainfo_getvaluebyname(cbm, CG_BITTORRENT_METAINFO_INFO);
	if (!infoVal)
		return FALSE;

	if (!cg_bittorrent_bencoding_tosha1(infoVal, infoHash))
		return FALSE;

	return TRUE;
}
