/******************************************************************
*
*	CyberBittorrent for C
*
*	Copyright (C) Satoshi Konno 2007
*
*	File: cpeer_handshake.c
*
*	Revision:
*
*	06/12/07
*		- first revision
*
******************************************************************/

#include <cybergarage/bittorrent/cpeer.h>

/****************************************
* cg_bittorrent_peer_handshake
****************************************/

BOOL cg_bittorrent_peer_handshake(CgBittorrentPeer *peer, CgBittorrentHandshake *hsIn, CgBittorrentHandshake *hsOut)
{
	unsigned int pstrlen;
	unsigned int npstrlen;
	int test = sizeof(hsIn->infoHash);

	if (!peer)
		return FALSE;

	/* Send Handshake message */
	pstrlen = cg_bittorrent_handshake_getpstrlen(hsIn);
	npstrlen = htonl(pstrlen);
	if (cg_bittorrent_peer_write(peer, (char *)&npstrlen, sizeof(npstrlen)) < sizeof(npstrlen))
		return FALSE;
	if (cg_bittorrent_peer_write(peer, hsIn->pstr, pstrlen) < (int)pstrlen)
		return FALSE;
	if (cg_bittorrent_peer_write(peer, hsIn->reserved, sizeof(hsIn->reserved)) < sizeof(hsIn->reserved))
		return FALSE;
	if (cg_bittorrent_peer_write(peer, hsIn->infoHash, sizeof(hsIn->infoHash)) < sizeof(hsIn->infoHash))
		return FALSE;
	if (cg_bittorrent_peer_write(peer, hsIn->peerId, sizeof(hsIn->peerId)) < sizeof(hsIn->peerId))
		return FALSE;

	/* Read Handshake message */
	if (cg_bittorrent_peer_read(peer, (char *)&npstrlen, sizeof(npstrlen)) <= 0)
		return FALSE;
	hsOut->pstrlen = ntohl(npstrlen);
	if (hsOut->pstr)
		free(hsOut->pstr);
	hsOut->pstr = (char *)malloc(hsOut->pstrlen);
	if (cg_bittorrent_peer_read(peer, hsOut->pstr, pstrlen) <= 0)
		return FALSE;
	if (cg_bittorrent_peer_read(peer, hsOut->reserved, sizeof(hsOut->reserved)) <= 0)
		return FALSE;
	if (cg_bittorrent_peer_read(peer, hsOut->infoHash, sizeof(hsOut->infoHash)) <= 0)
		return FALSE;
	if (cg_bittorrent_peer_read(peer, hsOut->peerId, sizeof(hsOut->peerId)) <= 0)
		return FALSE;

	return TRUE;
}
