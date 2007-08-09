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
