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
	CgBittorrentBlockDeviceMgr *bdmrg;

	bdmrg = (CgBittorrentBlockDeviceMgr *)malloc(sizeof(CgBittorrentBlockDeviceMgr));
	if (!bdmrg)
		return NULL;

	cg_bittorrent_blockdevicemgr_setreadfunc(bdmrg, NULL);
	cg_bittorrent_blockdevicemgr_setwritefunc(bdmrg, NULL);
	cg_bittorrent_blockdevicemgr_sethavefunc(bdmrg, NULL);

	return bdmrg;
}

/****************************************
* cg_bittorrent_blockdevicemgr_delete
****************************************/

void cg_bittorrent_blockdevicemgr_delete(CgBittorrentBlockDeviceMgr *bdmrg)
{
	if (!bdmrg)
		return;

	free(bdmrg);
}
