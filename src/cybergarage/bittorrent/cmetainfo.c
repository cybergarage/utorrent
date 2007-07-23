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

/****************************************
* cg_bittorrent_metainfo_getfilepropertyvalue
****************************************/

char *cg_bittorrent_metainfo_getfilepropertyvalue(CgBittorrentMetainfo *cbm, char *propName, int index)
{
	CgBittorrentBencoding *file;
	int n;

	if (!cbm)
		return NULL;

	if (cg_bittorrent_metainfo_issinglefilemode(cbm))
		return cg_bittorrent_dictionary_getstringbyname(cg_bittorrent_metainfo_getinfo(cbm), propName);

	file = cg_bittorrent_metainfo_getinfofiles(cbm);
	for(n=0; n<index; n++)
		file = cg_bittorrent_bencoding_next(file);

	if (!file)
		return NULL;

	return NULL;
}
