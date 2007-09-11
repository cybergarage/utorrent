/******************************************************************
*
*	CyberBittorrent for C
*
*	Copyright (C) Satoshi Konno 2007
*
*	File: cmetainfolist.c
*
*	Revision:
*
*	08/09/07
*		- first revision
*
******************************************************************/

#include <cybergarage/bittorrent/cmetainfo.h>

/****************************************
* cg_bittorrent_metainfolist_new
****************************************/

CgBittorrentMetainfoList *cg_bittorrent_metainfolist_new()
{
	CgBittorrentMetainfoList *minfoList;

	minfoList = (CgBittorrentMetainfoList *)malloc(sizeof(CgBittorrentMetainfoList));
	if (!minfoList)
		return NULL;

	cg_list_header_init((CgList *)minfoList);

	return minfoList;
}

/****************************************
* cg_bittorrent_metainfolist_delete
****************************************/

void cg_bittorrent_metainfolist_delete(CgBittorrentMetainfoList *minfoList)
{
	if (!minfoList)
		return;

	free(minfoList);
}

/****************************************
* cg_bittorrent_metainfolist_remove
****************************************/

BOOL cg_bittorrent_metainfolist_remove(CgBittorrentMetainfoList *cbmList, CgByte *infoHash)
{
	CgBittorrentMetainfo *cbm;
	CgByte cbmInfoHash[CG_BITTORRENT_METAINFO_INFOHASH_SIZE];

	if (!cbmList)
		return FALSE;

	for (cbm=cg_bittorrent_metainfolist_gets(cbmList); cbm; cbm=cg_bittorrent_metainfo_next(cbm)) {
		if (!cg_bittorrent_metainfo_getinfohash(cbm, cbmInfoHash))
			continue;
		if (memcmp(infoHash, cbmInfoHash, CG_BITTORRENT_METAINFO_INFOHASH_SIZE) == 0) {
			cg_bittorrent_metainfo_remove(cbm);
			return TRUE;
		}
	}

	return FALSE;
}
