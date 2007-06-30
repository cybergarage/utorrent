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
	if (cg_bittorrent_peer_getbitfieldlength(peer) < (unsigned int)bitfieldNum)
		return FALSE;
	return (peer->bitfield[bitfieldNum] & bitfieldMask) ? TRUE : FALSE;
}
