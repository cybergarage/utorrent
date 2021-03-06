/******************************************************************
*
*	CyberBittorrent for C
*
*	Copyright (C) Satoshi Konno 2007
*
*	File: cpeer_request.c
*
*	Revision:
*
*	06/30/07
*		- first revision
*
******************************************************************/

#include <cybergarage/bittorrent/cpeer.h>
#include <cybergarage/bittorrent/cbencoding.h>

/****************************************
* cg_bittorrent_peer_singlemessage
****************************************/

static BOOL cg_bittorrent_peer_singlemessage(CgBittorrentPeer *peer, char msgId)
{
	CgBittorrentMessage *msg;
	BOOL resultFlag;
	
	if (!peer)
		return FALSE;

	msg = cg_bittorrent_message_new();
	if (!msg)
		return FALSE;

	cg_bittorrent_message_settype(msg, msgId);
	cg_bittorrent_message_setlength(msg, 1);

	resultFlag = cg_bittorrent_peer_sendmsg(peer, msg);

	cg_bittorrent_message_delete(msg);

	return resultFlag;
}

/****************************************
* cg_bittorrent_peer_choke
****************************************/

BOOL cg_bittorrent_peer_choke(CgBittorrentPeer *peer)
{
	return cg_bittorrent_peer_singlemessage(peer, CG_BITTORRENT_MESSAGE_CHOKE);
}

/****************************************
* cg_bittorrent_peer_unchoke
****************************************/

BOOL cg_bittorrent_peer_unchoke(CgBittorrentPeer *peer)
{
	return cg_bittorrent_peer_singlemessage(peer, CG_BITTORRENT_MESSAGE_UNCHOKE);
}

/****************************************
* cg_bittorrent_peer_interested
****************************************/

BOOL cg_bittorrent_peer_interested(CgBittorrentPeer *peer)
{
	return cg_bittorrent_peer_singlemessage(peer, CG_BITTORRENT_MESSAGE_INTERESTED);
}

/****************************************
* cg_bittorrent_peer_uninterested
****************************************/

BOOL cg_bittorrent_peer_notinterested(CgBittorrentPeer *peer)
{
	return cg_bittorrent_peer_singlemessage(peer, CG_BITTORRENT_MESSAGE_NOTINTERESTED);
}

/****************************************
* cg_bittorrent_peer_message_request
****************************************/

BOOL cg_bittorrent_peer_bitfield(CgBittorrentPeer *peer)
{
	CgBittorrentMessage *msg;
	BOOL resultFlag;
	unsigned int msgLength;

	if (!peer)
		return FALSE;

	msg = cg_bittorrent_message_new();
	if (!msg)
		return FALSE;

	resultFlag = FALSE;
	if (cg_bittorrent_peer_recvmsg(peer, msg)) {
		if (cg_bittorrent_message_gettype(msg) == CG_BITTORRENT_MESSAGE_BITFIELD) {
			msgLength = cg_bittorrent_message_getlength(msg);
			cg_bittorrent_peer_setbitfield(peer, cg_bittorrent_message_getpayload(msg), cg_bittorrent_message_getlength(msg));
			resultFlag = TRUE;
		}
	}
	cg_bittorrent_message_delete(msg);

	return resultFlag;
}


/****************************************
* cg_bittorrent_peer_message_request
****************************************/

BOOL cg_bittorrent_peer_request(CgBittorrentPeer *peer, int index, int begin, int length)
{
	CgBittorrentMessage *msg;
	BOOL resultFlag;
	CgBittorrentInteger payload[3];
	
	if (!peer)
		return FALSE;

	msg = cg_bittorrent_message_new();
	if (!msg)
		return FALSE;

	cg_bittorrent_message_settype(msg, CG_BITTORRENT_MESSAGE_REQUEST);
	cg_bittorrent_message_setlength(msg, 13);

	/* Payload */
	payload[0] = htonl(index);
	payload[1] = htonl(begin);
	payload[2] = htonl(length);
	cg_bittorrent_message_setpayload(msg, (CgByte *)&payload[0], sizeof(payload));

	resultFlag = cg_bittorrent_peer_sendmsg(peer, msg);

	cg_bittorrent_message_delete(msg);

	return resultFlag;
}
