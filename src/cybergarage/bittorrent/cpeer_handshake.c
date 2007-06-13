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
	if (!peer)
		return FALSE;

	/* Send Handshake message */
	if (cg_bittorrent_peer_write(peer, &hsIn->pstrlen, sizeof(hsIn->pstrlen)) != sizeof(hsIn->pstrlen))
		return FALSE;
	if (cg_bittorrent_peer_write(peer, hsIn->pstr, hsIn->pstrlen) != hsIn->pstrlen)
		return FALSE;
	if (cg_bittorrent_peer_write(peer, hsIn->reserved, sizeof(hsIn->reserved)) != sizeof(hsIn->reserved))
		return FALSE;
	if (cg_bittorrent_peer_write(peer, hsIn->infoHash, sizeof(hsIn->infoHash)) != sizeof(hsIn->infoHash))
		return FALSE;
	if (cg_bittorrent_peer_write(peer, hsIn->peerId, sizeof(hsIn->peerId)) != sizeof(hsIn->peerId))
		return FALSE;

	/* Read Handshake message */
	if (cg_bittorrent_peer_read(peer, &hsOut->pstrlen, sizeof(hsOut->pstrlen)) != sizeof(hsOut->pstrlen))
		return FALSE;
	if (hsOut->pstr)
		free(hsOut->pstr);
	hsOut->pstr = (char *)malloc(hsOut->pstrlen);
	if (cg_bittorrent_peer_read(peer, hsOut->pstr, hsOut->pstrlen) != hsOut->pstrlen)
		return FALSE;
	if (cg_bittorrent_peer_read(peer, hsOut->reserved, sizeof(hsOut->reserved)) != sizeof(hsOut->reserved))
		return FALSE;
	if (cg_bittorrent_peer_read(peer, hsOut->infoHash, sizeof(hsOut->infoHash)) != sizeof(hsOut->infoHash))
		return FALSE;
	if (cg_bittorrent_peer_read(peer, hsOut->peerId, sizeof(hsOut->peerId)) != sizeof(hsOut->peerId))
		return FALSE;

	return TRUE;
}
