/******************************************************************
*
*	CyberBittorrent for C
*
*	Copyright (C) Satoshi Konno 2007
*
*	File: cpeerlist.c
*
*	Revision:
*
*	03/27/07
*		- first revision
*
******************************************************************/

#include <cybergarage/bittorrent/cpeer.h>

/****************************************
* cg_bittorrent_peerlist_new
****************************************/

CgBittorrentPeerList *cg_bittorrent_peerlist_new(void)
{
	CgBittorrentPeerList *peerList;

	peerList = (CgBittorrentPeerList *)malloc(sizeof(CgBittorrentPeerList));
	if (!peerList)
		return NULL;

	cg_list_header_init((CgList *)peerList);

	return peerList;
}

/****************************************
* cg_bittorrent_peerlist_delete
****************************************/

void cg_bittorrent_peerlist_delete(CgBittorrentPeerList *peerList)
{
	if (!peerList)
		return;

	free(peerList);
}
