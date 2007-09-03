/******************************************************************
*
*	CyberBittorrent for C
*
*	Copyright (C) Satoshi Konno 2007
*
*	File: cpeer.c
*
*	Revision:
*
*	03/27/07
*		- first revision
*
******************************************************************/

#include <cybergarage/bittorrent/cpeer.h>
#include <cybergarage/util/cstring.h>

/****************************************
* cg_bittorrent_peer_new
****************************************/

CgBittorrentPeer *cg_bittorrent_peer_new(void)
{
	CgBittorrentPeer *peer;
	int n;

	peer = (CgBittorrentPeer *)malloc(sizeof(CgBittorrentPeer));
	if (!peer)
		return NULL;

	cg_list_node_init((CgList *)peer);

	peer->addr = NULL;
	peer->port = 0;
	peer->sock = NULL;
	peer->bitfield = NULL;
	peer->bitfieldLength = 0;
	peer->tracker = NULL;

	for (n=0; n<CG_BITTORRENT_PEERID_SIZE; n++)
		peer->id[n] = 0;

	return peer;
}

/****************************************
* cg_bittorrent_peer_delete
****************************************/

void cg_bittorrent_peer_delete(CgBittorrentPeer *peer)
{
	if (!peer)
		return;

	cg_bittorrent_peer_setaddress(peer, NULL);
	cg_bittorrent_peer_setbitfield(peer, NULL, 0);

	if (peer->sock)
		cg_socket_delete(peer->sock);

	free(peer);
}

/****************************************
* cg_bittorrent_peer_setaddr
****************************************/

void cg_bittorrent_peer_setaddress(CgBittorrentPeer *peer, char *addr)
{
	if (!peer)
		return;

	if (peer->addr) {
		free(peer->addr);
		peer->addr = NULL;
	}

	if (addr)
		peer->addr = cg_strdup(addr);
}

/****************************************
* cg_bittorrent_peer_setbitfield
****************************************/

void cg_bittorrent_peer_setbitfield(CgBittorrentPeer *peer, CgByte *bitfield, int bitfieldLength)
{
	if (!peer)
		return;

	if (peer->bitfield) {
		free(peer->bitfield);
		peer->bitfield = NULL;
		peer->bitfieldLength = 0;
	}

	if (bitfield && 0 < bitfieldLength) {
		peer->bitfield = malloc(bitfieldLength);
		memcpy(peer->bitfield, bitfield, bitfieldLength);
		peer->bitfieldLength = bitfieldLength;
	}
}

/****************************************
* cg_bittorrent_peer_haspiece
****************************************/

BOOL cg_bittorrent_peer_haspiece(CgBittorrentPeer *peer, int index)
{
	int bitfieldNum;
	int bitfieldOffset;
	CgByte bitfieldMask;
	bitfieldNum = index / 8;
	bitfieldOffset = index % 8;
	bitfieldMask = 1 << (7 - bitfieldOffset); 
	if (cg_bittorrent_peer_getbitfieldlength(peer) < (CgBittorrentInteger)bitfieldNum)
		return FALSE;
	return (peer->bitfield[bitfieldNum] & bitfieldMask) ? TRUE : FALSE;
}

/****************************************
* cg_bittorrent_peer_getpiece
****************************************/

BOOL cg_bittorrent_peer_getpiece(CgBittorrentPeer *peer, char *infoHash, char *peerId, int index, int offset, CgByte *buf, int bufLen)
{
	CgBittorrentHandshake *hsSend;
	CgBittorrentHandshake *hsRecv;
	CgBittorrentMessage *msg;
	char *msgType;

	if (cg_strlen(cg_bittorrent_peer_getaddress(peer)) <= 0)
		return FALSE;

	if (cg_bittorrent_peer_getport(peer) <= 0)
		return FALSE;

	if (cg_bittorrent_peer_hasbitfield(peer)) {
		if (cg_bittorrent_peer_haspiece(peer, index) == FALSE)
			return FALSE;
	}

	if (cg_bittorrent_peer_connect(peer) == FALSE)
		return FALSE;

	/* Hand Shake */
	hsSend = cg_bittorrent_handshake_new();
	cg_bittorrent_handshake_setinfohash(hsSend, infoHash);
	cg_bittorrent_handshake_setpeerid(hsSend, peerId);
	hsRecv = cg_bittorrent_handshake_new();
	if (cg_bittorrent_peer_handshake(peer, hsSend, hsRecv) == TRUE) {
		cg_bittorrent_peer_close(peer);
		return FALSE;
	}
	cg_bittorrent_handshake_delete(hsSend);
	cg_bittorrent_handshake_delete(hsRecv);

	/* Bitfield */
	msg = cg_bittorrent_message_new();
	cg_bittorrent_peer_recvmsgheader(peer, msg);
	msgType = cg_bittorrent_message_gettype(msg);
/*
	//CPPUNIT_ASSERT(msgType == CG_BITTORRENT_MESSAGE_BITFIELD);
	CPPUNIT_ASSERT(cg_bittorrent_peer_recvmsgbody(cbp, msg));
	CgInt64 msgLength = cg_bittorrent_message_getlength(msg);
	cg_bittorrent_peer_setbitfield(cbp, cg_bittorrent_message_getpayload(msg), cg_bittorrent_message_getlength(msg));

	while (cg_bittorrent_peer_recvmsgheader(cbp, msg)) {
		switch (cg_bittorrent_message_gettype(msg)) {
			default:
				{
					cg_bittorrent_peer_recvmsgbody(cbp, msg);
					int msgType = cg_bittorrent_message_gettype(msg);
				}
				break;
		}
	}
	// 3525195776 / 262144 / 8 = 1680.9443359375
	//msgLength = 1682;
	cg_bittorrent_message_delete(msg);
*/

	return FALSE;
}

