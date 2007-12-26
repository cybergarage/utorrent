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
	peer->bitfieldLen = 0;
	peer->tracker = NULL;
	peer->timeout = 0;

	cg_bittorrent_peer_setnumsucceeded(peer, 0);
	cg_bittorrent_peer_setnumfailed(peer, 0);
	cg_bittorrent_peer_setdownloadedelapsedtime(peer, 0);
	cg_bittorrent_peer_setuploadedelapsedtime(peer, 0);
	cg_bittorrent_peer_setdownloadedbytes(peer, 0);
	cg_bittorrent_peer_setuploadedbytes(peer, 0);
	cg_bittorrent_peer_setdownloadingpercentages(peer, 0);

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

void cg_bittorrent_peer_setbitfield(CgBittorrentPeer *peer, CgByte *bitfield, int bitfieldLen)
{
	if (!peer)
		return;

	if (peer->bitfield) {
		free(peer->bitfield);
		peer->bitfield = NULL;
		peer->bitfieldLen = 0;
	}

	if (bitfield && 0 < bitfieldLen) {
		peer->bitfield = malloc(bitfieldLen);
		memcpy(peer->bitfield, bitfield, bitfieldLen);
		peer->bitfieldLen = bitfieldLen;
	}
}

/****************************************
* cg_bittorrent_peer_getpieceblock
****************************************/

BOOL cg_bittorrent_peer_getpieceblock(CgBittorrentPeer *peer, int pieceIdx, int pieceOffset, CgByte *buf, int bufLen)
{
	CgBittorrentMessage *msg;
	CgByte msgType;
	int readLen;

	if (!peer)
		return FALSE;

	if (cg_bittorrent_peer_hasbitfield(peer)) {
		if (cg_bittorrent_peer_haspiece(peer, pieceIdx) == FALSE)
			return FALSE;
	}

	msg = cg_bittorrent_message_new();
	if (!msg)
		return FALSE;

	readLen = 0;

	while (cg_bittorrent_peer_recvmsgheader(peer, msg)) {
		msgType = cg_bittorrent_message_gettype(msg);
		printf("msgType = %d\n", (int)msgType);
		if (msgType == CG_BITTORRENT_MESSAGE_PIECE) {
			readLen = cg_bittorrent_peer_recvmsgbody(peer, msg, buf, bufLen);
			break;
		}
		else {
			if (cg_bittorrent_peer_recvmsgbodynobuf(peer, msg) != cg_bittorrent_message_getpayloadlength(msg))
				continue;
			cg_bittorrent_message_print(msg);
			switch (msgType) {
			case CG_BITTORRENT_MESSAGE_BITFIELD:
				{
					if (cg_bittorrent_peer_hasbitfield(peer)) {
						if (cg_bittorrent_peer_haspiece(peer, pieceIdx) == FALSE) {
							cg_bittorrent_message_delete(msg);
							return FALSE;
						}
						if (!cg_bittorrent_peer_interested(peer))
							return FALSE;
						//if (!cg_bittorrent_peer_unchoke(peer))
						//	return FALSE;
					}
				}
				break;
			case CG_BITTORRENT_MESSAGE_UNCHOKE:
				{
					if (!cg_bittorrent_peer_request(peer, pieceIdx, pieceOffset, bufLen))
						return FALSE;
				}
				break;
			case CG_BITTORRENT_MESSAGE_CHOKE:
				return FALSE;
			}
		}
	}

	cg_bittorrent_message_delete(msg);

	return (bufLen == readLen) ? TRUE : FALSE;
}
