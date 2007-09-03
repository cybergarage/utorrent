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
	CgBittorrentStrategyMgr *stgMgr;

	stgMgr = (CgBittorrentStrategyMgr *)malloc(sizeof(CgBittorrentStrategyMgr));
	if (!stgMgr)
		return NULL;

	stgMgr->name = cg_string_new();

	cg_bittorrent_strategymgr_settype(stgMgr, 0);
	cg_bittorrent_strategymgr_setname(stgMgr, "");
	cg_bittorrent_strategymgr_setuserdata(stgMgr, NULL);

	return stgMgr;
}

/****************************************
* cg_bittorrent_strategymgr_delete
****************************************/

void cg_bittorrent_strategymgr_delete(CgBittorrentStrategyMgr *stgMgr)
{
	if (!stgMgr)
		return;

	if (stgMgr->name)
		cg_string_delete(stgMgr->name);

	free(stgMgr);
}

