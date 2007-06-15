/******************************************************************
*
*	CyberBittorrent for C
*
*	Copyright (C) Satoshi Konno 2007
*
*	File: cpeer_message.c
*
*	Revision:
*
*	06/12/07
*		- first revision
*
******************************************************************/

#include <cybergarage/bittorrent/cpeer.h>

/****************************************
* cg_bittorrent_peer_readmessage
****************************************/

int cg_bittorrent_peer_recvmsg(CgBittorrentPeer *peer, CgBittorrentMessage *msg)
{
	unsigned int pstrlen;
	unsigned int npstrlen;

	if (!peer)
		return 0;

	/* Recv a message*/
	if (cg_bittorrent_peer_read(peer, (char *)&npstrlen, sizeof(npstrlen)) != sizeof(npstrlen))
		return FALSE;
	pstrlen = ntohl(npstrlen);
	cg_bittorrent_message_setlength(msg, pstrlen);

	if (cg_bittorrent_peer_read(peer, &msg->type, sizeof(msg->type)) != sizeof(msg->type))
		return FALSE;

	if (msg->payload) {
		free(msg->payload);
		msg->payload = NULL;
	}

	if (0 < pstrlen) {
		msg->payload = (char *)malloc(pstrlen);
		if (cg_bittorrent_peer_read(peer, &msg->payload, pstrlen) != pstrlen)
			return FALSE;
	}

	return TRUE;
}

/****************************************
* cg_bittorrent_peer_writemessage
****************************************/

int cg_bittorrent_peer_sendmsg(CgBittorrentPeer *peer, CgBittorrentMessage *msg)
{
	unsigned int pstrlen;
	unsigned int npstrlen;

	if (!peer)
		return 0;

	/* Send message */
	pstrlen = cg_bittorrent_message_getlength(msg);
	npstrlen = htonl(pstrlen);
	if (cg_bittorrent_peer_write(peer, (char *)&npstrlen, sizeof(npstrlen)) != sizeof(npstrlen))
		return FALSE;
	if (cg_bittorrent_peer_write(peer, &msg->type, sizeof(msg->type)) != sizeof(msg->type))
		return FALSE;
	if (0 < pstrlen && msg->payload) {
		if (cg_bittorrent_peer_write(peer, msg->payload, pstrlen) != pstrlen)
			return FALSE;
	}

	return TRUE;
}
