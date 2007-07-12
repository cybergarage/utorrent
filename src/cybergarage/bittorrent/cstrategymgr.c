/******************************************************************
*
*	CyberBittorrent for C
*
*	Copyright (C) Satoshi Konno 2007
*
*	Strategy: cstrategymgr.c
*
*	Revision:
*
*	07/12/08
*		- first revision
*
******************************************************************/

#include <cybergarage/bittorrent/cstrategymgr.h>

#include <stdlib.h>

/****************************************
* cg_bittorrent_strategymgr_new
****************************************/

CgBittorrentStrategyMgr *cg_bittorrent_strategymgr_new()
{
	CgBittorrentStrategyMgr *stgMrg;

	stgMrg = (CgBittorrentStrategyMgr *)malloc(sizeof(CgBittorrentStrategyMgr));
	if (!stgMrg)
		return NULL;

	return stgMrg;
}

/****************************************
* cg_bittorrent_strategymgr_delete
****************************************/

void cg_bittorrent_strategymgr_delete(CgBittorrentStrategyMgr *stgMrg)
{
	if (!stgMrg)
		return;

	free(stgMrg);
}
