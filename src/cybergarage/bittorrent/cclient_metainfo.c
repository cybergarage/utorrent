/******************************************************************
*
*	CyberBittorrent for C
*
*	Copyright (C) Satoshi Konno 2007
*
*	File: cclient_download.c
*
*	Revision:
*
*	09/11/07
*		- first revision
*
******************************************************************/

#include <cybergarage/bittorrent/cclient.h>

/****************************************
* cg_bittorrent_client_addmetainfo
****************************************/

BOOL cg_bittorrent_client_addmetainfo(CgBittorrentClient *cbc, CgBittorrentMetainfo *cbm)
{
	if (!cg_bittorrent_client_isready(cbc))
		return FALSE;

	if (!cbc->httpServer)
		cg_http_server_start(cbc->httpServer);
	
	return TRUE;
}

/****************************************
* cg_bittorrent_client_removemetainfo
****************************************/

BOOL cg_bittorrent_client_removemetainfo(CgBittorrentClient *cbc, CgByte *infoHash)
{
	if (cbc->httpServer)
		cg_http_server_stop(cbc->httpServer);

	return TRUE;
}
