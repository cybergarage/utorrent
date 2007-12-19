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

BOOL cg_bittorrent_client_addmetainfo(CgBittorrentClient *cbc, CgBittorrentMetainfo *metainfo)
{
	CgBittorrentFileMgr *fileDevMgr;
	CgBittorrentMetainfoList *metainfoList;

	if (!metainfo)
		return FALSE;

	fileDevMgr = cg_bittorrent_client_getfilemgr(cbc);
	if (!fileDevMgr)
		return FALSE;

	if (!cg_bittorrent_filemgr_addmetainfo(fileDevMgr, metainfo))
		return FALSE;

	metainfoList = cg_bittorrent_client_getmetainfolist(cbc);
	if (!metainfoList)
		return FALSE;

	cg_bittorrent_client_lock(cbc);

	cg_bittorrent_metainfolist_add(metainfoList, metainfo);

	cg_bittorrent_client_unlock(cbc);

	return TRUE;
}

/****************************************
* cg_bittorrent_client_removemetainfo
****************************************/

BOOL cg_bittorrent_client_removemetainfo(CgBittorrentClient *cbc, CgByte *infoHash)
{
	CgBittorrentFileMgr *fileDevMgr;
	CgBittorrentMetainfoList *metainfoList;

	if (!cbc)
		return FALSE;

	fileDevMgr = cg_bittorrent_client_getfilemgr(cbc);
	if (!fileDevMgr)
		return FALSE;

	if (!cg_bittorrent_filemgr_removemetainfo(fileDevMgr, infoHash))
		return FALSE;

	metainfoList = cg_bittorrent_client_getmetainfolist(cbc);
	if (!metainfoList)
		return FALSE;

	cg_bittorrent_client_lock(cbc);

	cg_bittorrent_metainfolist_remove(metainfoList, infoHash);

	cg_bittorrent_client_unlock(cbc);

	return TRUE;
}

