/******************************************************************
*
*	CyberBittorrent for C
*
*	Copyright (C) Satoshi Konno 2007
*
*	Strategy: csequential.c
*
*	Revision:
*
*	12/18/07
*		- first revision
*
******************************************************************/

#include <cybergarage/bittorrent/impl/strategymgr/csequential.h>

/****************************************
* cg_bittorrent_sequential_strategymgr_new
****************************************/

int cg_bittorrent_sequential_strategymgr_getnextpieceindex(CgBittorrentStrategyMgr *stgMgr)
{
}

/****************************************
* cg_bittorrent_sequential_strategymgr_new
****************************************/

CgBittorrentPeer *cg_bittorrent_sequential_strategymgr_getpeer(CgBittorrentStrategyMgr *stgMgr, CgBittorrentTracker *cbt, int pieceIdx)
{
}

/****************************************
* cg_bittorrent_sequential_strategymgr_new
****************************************/

CgBittorrentStrategyMgr *cg_bittorrent_sequential_strategymgr_new(void)
{
	CgBittorrentStrategyMgr *stgMgr;
	
	stgMgr = cg_bittorrent_strategymgr_new();

	return stgMgr;
}

/****************************************
* cg_bittorrent_sequential_strategymgr_delete
****************************************/

void cg_bittorrent_sequential_strategymgr_delete(CgBittorrentStrategyMgr *stgMgr)
{
	cg_bittorrent_strategymgr_delete(stgMgr);
}

