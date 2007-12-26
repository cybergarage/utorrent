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
* cg_bittorrent_sequential_strategymgr_getnextpieceindex
****************************************/

int cg_bittorrent_sequential_strategymgr_getnextpieceindex(CgBittorrentStrategyMgr *stgMgr, CgBittorrentMetainfo *cbm)
{
	int numPieces;
	int n;

	numPieces = cg_bittorrent_metainfo_numpieces(cbm);
	if (numPieces <= 0)
		return -1;
	
	for (n=0; n<numPieces; n++) {
		if (!cg_bittorrent_metainfo_haspiece(cbm, n))
			return n;
	}

	return -1;
}

/****************************************
* cg_bittorrent_sequential_strategymgr_getpeer
****************************************/

CgBittorrentPeer *cg_bittorrent_sequential_strategymgr_getpeer(CgBittorrentStrategyMgr *stgMgr, CgBittorrentMetainfo *cbm, int pieceIdx)
{
	CgBittorrentTracker *tracker;
	CgBittorrentPeer *peer;

	tracker = cg_bittorrent_metainfo_gettracker(cbm);
	if (!tracker)
		return NULL;

	for (peer=cg_bittorrent_tracker_getpeers(tracker); peer; peer=cg_bittorrent_peer_next(peer)) {
		if (0 < cg_bittorrent_peer_getnumfailed(peer))
			continue;
		if (cg_bittorrent_peer_isbound(peer))
			continue;
		if (cg_bittorrent_peer_hasbitfield(peer)) {
			if (cg_bittorrent_peer_haspiece(peer, pieceIdx))
				return peer;
		}
		return peer;
	}

	return NULL;
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

