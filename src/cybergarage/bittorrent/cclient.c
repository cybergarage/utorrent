/******************************************************************
*
*	CyberBittorrent for C
*
*	Copyright (C) Satoshi Konno 2007
*
*	File: cbittorrent.c
*
*	Revision:
*
*	01/30/07
*		- first revision
*
******************************************************************/

#include <cybergarage/bittorrent/cclient.h>

/****************************************
* Prototype
*****************************************/

void cg_bittorrent_client_httplistener(CgHttpRequest *);

/****************************************
* cg_bittorrent_client_new
****************************************/

CgBittorrentClient *cg_bittorrent_client_new()
{
	CgBittorrentClient *cbc;

	cbc = (CgBittorrentClient *)malloc(sizeof(CgBittorrentClient));
	if (!cbc)
		return NULL;

	cbc->httpServer = cg_http_server_new();
	if (!cbc->httpServer) {
		free(cbc);
		return NULL;
	}
	cg_http_server_setlistener(cbc->httpServer, cg_bittorrent_client_httplistener);
	cg_http_server_setuserdata(cbc->httpServer, cbc);

	return cbc;
}

/****************************************
* cg_bittorrent_client_delete
****************************************/

void cg_bittorrent_client_delete(CgBittorrentClient *cbc)
{
	if (!cbc)
		return;

	if (cbc->httpServer)
		cg_http_server_delete(cbc->httpServer);

	free(cbc);
}

/****************************************
* cg_bittorrent_client_start
****************************************/

BOOL cg_bittorrent_client_start(CgBittorrentClient *cbc)
{
	if (cbc->httpServer)
		cg_http_server_start(cbc->httpServer);

	return TRUE;
}

/****************************************
* cg_bittorrent_client_stop
****************************************/

BOOL cg_bittorrent_client_stop(CgBittorrentClient *cbc)
{
	if (cbc->httpServer)
		cg_http_server_stop(cbc->httpServer);

	return TRUE;
}
