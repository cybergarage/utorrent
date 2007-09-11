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
	CgBittorrentBlockDeviceMgr *blockDevMgr;
	CgBittorrentMetainfoList *metainfoList;

	if (!metainfo)
		return FALSE;

	blockDevMgr = cg_bittorrent_client_getblockdevicemgr(cbc);
	if (!blockDevMgr)
		return FALSE;

	if (!cg_bittorrent_blockdevicemgr_addmetainfo(blockDevMgr, metainfo))
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
	CgBittorrentBlockDeviceMgr *blockDevMgr;
	CgBittorrentMetainfoList *metainfoList;

	if (!cbc)
		return FALSE;

	blockDevMgr = cg_bittorrent_client_getblockdevicemgr(cbc);
	if (!blockDevMgr)
		return FALSE;

	if (!cg_bittorrent_blockdevicemgr_removemetainfo(blockDevMgr, infoHash))
		return FALSE;

	metainfoList = cg_bittorrent_client_getmetainfolist(cbc);
	if (!metainfoList)
		return FALSE;

	cg_bittorrent_client_lock(cbc);

	cg_bittorrent_metainfolist_remove(metainfoList, infoHash);

	cg_bittorrent_client_unlock(cbc);

	return TRUE;
}

