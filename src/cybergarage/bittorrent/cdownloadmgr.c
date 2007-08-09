/******************************************************************
*
*	CyberBittorrent for C
*
*	Copyright (C) Satoshi Konno 2007
*
*	File: cdownloadmgr.c
*
*	Revision:
*
*	02/07/08
*		- first revision
*
******************************************************************/

#include <cybergarage/bittorrent/cdownloadmgr.h>
#include <cybergarage/bittorrent/csha1.h>

/****************************************
* cg_bittorrent_downloadmgr_new
****************************************/

CgBittorrentDownloadMgr *cg_bittorrent_downloadmgr_new()
{
	CgBittorrentDownloadMgr *dlmgr;

	dlmgr = (CgBittorrentDownloadMgr *)malloc(sizeof(CgBittorrentDownloadMgr));
	if (!dlmgr)
		return NULL;

	cg_bittorrent_downloadmgr_setfilemgr(dlmgr, NULL);
	cg_bittorrent_downloadmgr_setstrategymgr(dlmgr, NULL);

	return dlmgr;
}

/****************************************
* cg_bittorrent_downloadmgr_delete
****************************************/

void cg_bittorrent_downloadmgr_delete(CgBittorrentDownloadMgr *dlmgr)
{
	if (!dlmgr)
		return;

	cg_bittorrent_downloadmgr_clear(dlmgr);

	free(dlmgr);
}

/****************************************
* cg_bittorrent_downloadmgr_clear
****************************************/

void cg_bittorrent_downloadmgr_clear(CgBittorrentDownloadMgr *dlmgr)
{
	if (!dlmgr)
		return;
}

/****************************************
* cg_bittorrent_downloadmgr_initialize
****************************************/

BOOL cg_bittorrent_downloadmgr_initialize(CgBittorrentDownloadMgr *dlmgr)
{
	CgBittorrentFileMgr *filemgr;
	CgBittorrentStrategyMgr *stgmgr;

	if (!dlmgr)
		return FALSE;

	filemgr = cg_bittorrent_downloadmgr_getfilemgr(dlmgr);
	stgmgr = cg_bittorrent_downloadmgr_getstrategymgr(dlmgr);

	if (!filemgr ||!stgmgr)
		return FALSE;

	return TRUE;
}
