/******************************************************************
*
*	CyberBittorrent for C
*
*	Copyright (C) Satoshi Konno 2007
*
*	File: cpeer_msg.c
*
*	Revision:
*
*	06/08/07
*		- first revision
*
******************************************************************/

#include <cybergarage/bittorrent/cpeer.h>
/****************************************
* cg_bittorrent_peer_message_new
****************************************/

CgBittorrentPeerMessage *cg_bittorrent_peer_message_new(void)
{
	CgBittorrentPeerMessage *msg;

	msg = (CgBittorrentPeerMessage *)malloc(sizeof(CgBittorrentPeerMessage));
	if (!msg)
		return NULL;

	return msg;
}

/****************************************
* cg_bittorrent_peer_message_delete
****************************************/

void cg_bittorrent_peer_message_delete(CgBittorrentPeerMessage *msg)
{
	if (!msg)
		return;

	free(msg);
}

