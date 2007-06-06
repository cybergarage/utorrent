/******************************************************************
*
*	CyberBittorrent for C
*
*	Copyright (C) Satoshi Konno 2007
*
*	File: ctracker_parse.c
*
*	Revision:
*
*	03/20/07
*		- first revision
*
******************************************************************/

#include <cybergarage/bittorrent/ctracker.h>
#include <cybergarage/net/cinterface.h>

/****************************************
* cg_bittorrent_tracker_parse
****************************************/

BOOL cg_bittorrent_tracker_parse(CgBittorrentTracker *cbt, char *data, int dataLen)
{
	CgBittorrentDictionary *cbd;
	CgBittorrentBencoding *peerBen;
	CgBittorrentPeerList *peerList;
	CgBittorrentPeer *newPeer;
	unsigned char *peer;
	unsigned char addr[CG_NET_IPV4_ADDRSTRING_MAXSIZE];
	unsigned short *port;

	int offset;
	int peerNum;
	int n;

	if (!cbt)
		return FALSE;

	cbd = cg_bittorrent_tracker_getdictionary(cbt);
	if (!cbd)
		return FALSE;

	if (cg_bittorrent_dictionary_parse(cbd, data, &offset) == FALSE)
		return FALSE;

	peerBen = cg_bittorrent_tracker_getvaluebyname(cbt, CG_BITTORRENT_TRACKER_PEERS);
	if (!peerBen)
		return FALSE;

	peerList = cg_bittorrent_tracker_getpeerlist(cbt);

	peerNum = cg_bittorrent_bencoding_getlength(peerBen) / CG_BITTORRENT_TRACKER_PEERCOMPACT_SIZE;
	peer = cg_bittorrent_bencoding_getstring(peerBen);
	for (n=0; n<peerNum; n++) {
#if defined(HAVE_SNPRINTF)
		snprintf(addr, CG_BITTORRENT_TRACKER_PEERCOMPACT_IP_SIZE, "%d.%d.%d.%d", (int)peer[3], (int)peer[2], (int)peer[1], (int)peer[0]);
#else
		sprintf(addr, "%d.%d.%d.%d", (int)peer[0], (int)peer[1], (int)peer[2], (int)peer[3]);
#endif
		port = (unsigned short *)(peer + CG_BITTORRENT_TRACKER_PEERCOMPACT_IP_SIZE);
		newPeer = cg_bittorrent_peer_new();
		if (!newPeer)
			continue;
		cg_bittorrent_peer_setaddress(newPeer, addr);
		cg_bittorrent_peer_setport(newPeer, ntohs(*port));
		cg_bittorrent_peerlist_add(peerList, newPeer);
		peer += CG_BITTORRENT_TRACKER_PEERCOMPACT_SIZE;
	}

	return TRUE;
}
