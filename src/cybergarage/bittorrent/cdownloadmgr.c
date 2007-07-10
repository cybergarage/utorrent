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

	cg_bittorrent_downloadmgr_settrakcer(dlmgr, NULL);
	cg_bittorrent_downloadmgr_setfilemgr(dlmgr, NULL);

	return dlmgr;
}

/****************************************
* cg_bittorrent_downloadmgr_delete
****************************************/

void cg_bittorrent_downloadmgr_delete(CgBittorrentDownloadMgr *dlmgr)
{
	if (!dlmgr)
		return;

	free(dlmgr);
}
