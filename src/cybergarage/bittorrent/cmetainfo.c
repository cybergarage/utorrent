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
* cg_bittorrent_metainfo_getnfiles
****************************************/

int cg_bittorrent_metainfo_getnfiles(CgBittorrentMetainfo *cbm)
{
	CgBittorrentBencoding *file;
	int fileCnt;

	if (!cbm)
		return 0;

	if (cg_bittorrent_metainfo_issinglefilemode(cbm))
		return 1;

	fileCnt = 0;
	file = cg_bittorrent_metainfo_getinfofiles(cbm);
	while (file) {
		fileCnt++;
		file = cg_bittorrent_bencoding_next(file);
	}

	return fileCnt;
}

/****************************************
* cg_bittorrent_metainfo_getfileproperty
****************************************/

CgBittorrentBencoding *cg_bittorrent_metainfo_getfileproperty(CgBittorrentMetainfo *cbm, char *propName, int index)
{
	CgBittorrentBencoding *file;
	int n;
	CgBittorrentDictionary *cbd;

	if (!cbm)
		return NULL;

	if (cg_bittorrent_metainfo_issinglefilemode(cbm))
		return cg_bittorrent_dictionary_getvaluebyname(cg_bittorrent_metainfo_getinfo(cbm), propName);

	file = cg_bittorrent_metainfo_getinfofiles(cbm);
	for(n=0; n<index; n++)
		file = cg_bittorrent_bencoding_next(file);

	if (!file || !cg_bittorrent_bencoding_isdictionary(file))
		return NULL;

	cbd = cg_bittorrent_bencoding_getdictionary(file);
	if (!cbd)
		return NULL;

	return cg_bittorrent_dictionary_getvaluebyname(cbd, propName);
}

/****************************************
* cg_bittorrent_metainfo_getfilepropertystring
****************************************/

char *cg_bittorrent_metainfo_getfilepropertystring(CgBittorrentMetainfo *cbm, char *propName, int index)
{
	CgBittorrentBencoding *cbb;
	
	cbb = cg_bittorrent_metainfo_getfileproperty(cbm, propName, index);
	if (!cbb)
		return NULL;

	return cg_bittorrent_bencoding_getstring(cbb);
}

/****************************************
* cg_bittorrent_metainfo_getfilepropertyinteger
****************************************/

CgInt64 cg_bittorrent_metainfo_getfilepropertyinteger(CgBittorrentMetainfo *cbm, char *propName, int index)
{
	CgBittorrentBencoding *cbb;
	
	cbb = cg_bittorrent_metainfo_getfileproperty(cbm, propName, index);
	if (!cbb)
		return 0;

	return cg_bittorrent_bencoding_getinteger(cbb);
}

