/******************************************************************
*
*	CyberBittorrent for C
*
*	Copyright (C) Satoshi Konno 2007
*
*	File: cblockdevicemgr.c
*
*	Revision:
*
*	07/12/08
*		- first revision
*
******************************************************************/

#include <cybergarage/bittorrent/cblockdevmgr.h>

#include <stdlib.h>

/****************************************
* cg_bittorrent_blockdevicemgr_new
****************************************/

CgBittorrentBlockDeviceMgr *cg_bittorrent_blockdevicemgr_new()
{
	CgBittorrentBlockDeviceMgr *bdmgr;

	bdmgr = (CgBittorrentBlockDeviceMgr *)malloc(sizeof(CgBittorrentBlockDeviceMgr));
	if (!bdmgr)
		return NULL;

	/* Metainfo */
	cg_bittorrent_blockdevicemgr_setaddmetainfofunc(bdmgr, NULL);
	cg_bittorrent_blockdevicemgr_setremovemetainfofunc(bdmgr, NULL);
	cg_bittorrent_blockdevicemgr_setgetmetainfosfunc(bdmgr, NULL);
	cg_bittorrent_blockdevicemgr_setgetmetainfofunc(bdmgr, NULL);

	/* File */
	cg_bittorrent_blockdevicemgr_setopenfilefunc(bdmgr, NULL);
	cg_bittorrent_blockdevicemgr_setseekfilefunc(bdmgr, NULL);
	cg_bittorrent_blockdevicemgr_setreadfilefunc(bdmgr, NULL);
	cg_bittorrent_blockdevicemgr_setwritefilefunc(bdmgr, NULL);
	cg_bittorrent_blockdevicemgr_setclosefilefunc(bdmgr, NULL);

	return bdmgr;
}

/****************************************
* cg_bittorrent_blockdevicemgr_delete
****************************************/

void cg_bittorrent_blockdevicemgr_delete(CgBittorrentBlockDeviceMgr *bdmgr)
{
	if (!bdmgr)
		return;

	free(bdmgr);
}

/****************************************
* cg_bittorrent_blockdevicemgr_getfileindex
****************************************/

BOOL cg_bittorrent_blockdevicemgr_isvalidated(CgBittorrentBlockDeviceMgr *bdmgr)
{
	/* Metainfo */
	if (!cg_bittorrent_blockdevicemgr_getaddmetainfofunc(bdmgr))
		return FALSE;
	if (!cg_bittorrent_blockdevicemgr_getremovemetainfofunc(bdmgr))
		return FALSE;
	if (!cg_bittorrent_blockdevicemgr_getgetmetainfosfunc(bdmgr))
		return FALSE;
	if (!cg_bittorrent_blockdevicemgr_getgetmetainfofunc(bdmgr))
		return FALSE;

	/* File */
	if (!cg_bittorrent_blockdevicemgr_getopenfilefunc(bdmgr))
		return FALSE;
	if (!cg_bittorrent_blockdevicemgr_getseekfilefunc(bdmgr))
		return FALSE;
	if (!cg_bittorrent_blockdevicemgr_getreadfilefunc(bdmgr))
		return FALSE;
	if (!cg_bittorrent_blockdevicemgr_getwritefilefunc(bdmgr))
		return FALSE;
	if (!cg_bittorrent_blockdevicemgr_getclosefilefunc(bdmgr))
		return FALSE;

	return TRUE;
}


