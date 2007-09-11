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
BOOL cg_bittorrent_client_initialize(CgBittorrentClient *cbc);
BOOL cg_bittorrent_client_clean(CgBittorrentClient *cbc);

/****************************************
* cg_bittorrent_client_new
****************************************/

CgBittorrentClient *cg_bittorrent_client_new()
{
	CgBittorrentClient *cbc;
	CgBittorrentMetainfoList *cbmList;

	cbc = (CgBittorrentClient *)malloc(sizeof(CgBittorrentClient));
	if (!cbc)
		return NULL;

	/* Metainfo */
	cbmList = cg_bittorrent_metainfolist_new();
	if (!cbmList) {
		free(cbc);
		return NULL;
	}
	cg_bittorrent_client_setmetainfolist(cbc, cbmList);

	/* HTTP Server */
	cbc->httpServer = cg_http_server_new();
	if (!cbc->httpServer) {
		free(cbc);
		return NULL;
	}
	cg_http_server_setlistener(cbc->httpServer, cg_bittorrent_client_httplistener);
	cg_http_server_setuserdata(cbc->httpServer, cbc);

	/* Manager */
	cg_bittorrent_client_setblockdevicemgr(cbc, NULL);
	cg_bittorrent_client_setstrategymgr(cbc, NULL);

	return cbc;
}

/****************************************
* cg_bittorrent_client_delete
****************************************/

void cg_bittorrent_client_delete(CgBittorrentClient *cbc)
{
	if (!cbc)
		return;

	cg_bittorrent_client_stop(cbc);
	cg_bittorrent_client_clean(cbc);

	if (cbc->httpServer)
		cg_http_server_delete(cbc->httpServer);

	free(cbc);
}

/****************************************
* cg_bittorrent_client_isready
****************************************/

static BOOL cg_bittorrent_client_isready(CgBittorrentClient *cbc)
{
	if (!cbc->blockDevMgr)
		return FALSE;

	if (!cg_bittorrent_blockdevicemgr_isvalidated(cbc->blockDevMgr))
		return FALSE;

	if (!cbc->stgyMgr)
		return FALSE;

	if (!cbc->httpServer)
		return FALSE;

	return TRUE;
}

/****************************************
* cg_bittorrent_client_initialize
****************************************/

static BOOL cg_bittorrent_client_initialize(CgBittorrentClient *cbc)
{
	CgBittorrentMetainfoList *cbmList;
	CgBittorrentBlockDeviceMgr *blockDevMgr;

	if (!cg_bittorrent_client_isready(cbc))
		return FALSE;

	if (!cg_bittorrent_client_clean(cbc))
		return FALSE;

	cbmList = cg_bittorrent_client_getmetainfolist(cbc);
	if (!cbmList)
		return FALSE;

	blockDevMgr = cg_bittorrent_client_getblockdevicemgr(cbc);
	if (!blockDevMgr)
		return FALSE;

	cg_bittorrent_blockdevicemgr_getmetainfos(blockDevMgr, &cbmList);

	return TRUE;
}

/****************************************
* cg_bittorrent_client_clean
****************************************/

static BOOL cg_bittorrent_client_clean(CgBittorrentClient *cbc)
{
	CgBittorrentMetainfoList *cbmList;

	if (!cbc)
		return FALSE;

	/* Metainfo */
	cbmList = cg_bittorrent_client_getmetainfolist(cbc);
	if (!cbmList)
		return FALSE;
	cg_bittorrent_metainfolist_clear(cbmList);

	return TRUE;
}

/****************************************
* cg_bittorrent_client_start
****************************************/

BOOL cg_bittorrent_client_start(CgBittorrentClient *cbc)
{
	if (!cg_bittorrent_client_isready(cbc))
		return FALSE;

	if (!cbc->httpServer)
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
