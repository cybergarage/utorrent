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

BOOL cg_bittorrent_peer_handshake(CgBittorrentPeer *peer, CgBittorrentHandshake *hsSend, CgBittorrentHandshake *hsRecv)
{
	if (!peer)
		return FALSE;

	/* Send Handshake message */
	if (cg_bittorrent_peer_write(peer, &hsSend->pstrlen, sizeof(hsSend->pstrlen)) != sizeof(hsSend->pstrlen))
		return FALSE;
	if (cg_bittorrent_peer_write(peer, hsSend->pstr, hsSend->pstrlen) != hsSend->pstrlen)
		return FALSE;
	if (cg_bittorrent_peer_write(peer, hsSend->reserved, sizeof(hsSend->reserved)) != sizeof(hsSend->reserved))
		return FALSE;
	if (cg_bittorrent_peer_write(peer, hsSend->infoHash, sizeof(hsSend->infoHash)) != sizeof(hsSend->infoHash))
		return FALSE;
	if (cg_bittorrent_peer_write(peer, hsSend->peerId, sizeof(hsSend->peerId)) != sizeof(hsSend->peerId))
		return FALSE;

	/* Read Handshake message */
	if (cg_bittorrent_peer_read(peer, &hsRecv->pstrlen, sizeof(hsRecv->pstrlen)) != sizeof(hsRecv->pstrlen))
		return FALSE;
	if (hsRecv->pstr)
		free(hsRecv->pstr);
	hsRecv->pstr = (char *)malloc(hsRecv->pstrlen);
	if (cg_bittorrent_peer_read(peer, hsRecv->pstr, hsRecv->pstrlen) != hsRecv->pstrlen)
		return FALSE;
	if (cg_bittorrent_peer_read(peer, hsRecv->reserved, sizeof(hsRecv->reserved)) != sizeof(hsRecv->reserved))
		return FALSE;
	if (cg_bittorrent_peer_read(peer, hsRecv->infoHash, sizeof(hsRecv->infoHash)) != sizeof(hsRecv->infoHash))
		return FALSE;
	if (cg_bittorrent_peer_read(peer, hsRecv->peerId, sizeof(hsRecv->peerId)) != sizeof(hsRecv->peerId))
		return FALSE;

	return TRUE;
}
