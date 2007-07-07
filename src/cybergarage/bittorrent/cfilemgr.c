/******************************************************************
*
*	CyberBittorrent for C
*
*	Copyright (C) Satoshi Konno 2007
*
*	File: cfilemgr.c
*
*	Revision:
*
*	02/07/08
*		- first revision
*
******************************************************************/

#include <cybergarage/bittorrent/cfilemgr.h>

#include <stdlib.h>

/****************************************
* cg_bittorrent_filemgr_new
****************************************/

CgBittorrentFileMgr *cg_bittorrent_filemgr_new()
{
	CgBittorrentFileMgr *dlmgr;

	dlmgr = (CgBittorrentFileMgr *)malloc(sizeof(CgBittorrentFileMgr));
	if (!dlmgr)
		return NULL;

	return dlmgr;
}

/****************************************
* cg_bittorrent_filemgr_delete
****************************************/

void cg_bittorrent_filemgr_delete(CgBittorrentFileMgr *dlmgr)
{
	if (!dlmgr)
		return;

	free(dlmgr);
}
