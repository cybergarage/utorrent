/******************************************************************
*
*	CyberBittorrent for C
*
*	Copyright (C) Satoshi Konno 2007
*
*	File: cbencodinglist.c
*
*	Revision:
*
*	02/09/07
*		- first revision
*
******************************************************************/

#include <cybergarage/bittorrent/cbencoding.h>

/****************************************
* cg_bittorrent_bencodinglist_new
****************************************/

CgBittorrentBencodingList *cg_bittorrent_bencodinglist_new()
{
	CgBittorrentBencodingList *cbbList;

	cbbList = (CgBittorrentBencodingList *)malloc(sizeof(CgBittorrentBencodingList));
	if (!cbbList)
		return NULL;

	cg_list_header_init((CgList *)cbbList);

	return cbbList;
}

/****************************************
* cg_bittorrent_bencodinglist_delete
****************************************/

void cg_bittorrent_bencodinglist_delete(CgBittorrentBencodingList *cbbList)
{
	if (!cbbList)
		return;

	free(cbbList);
}
