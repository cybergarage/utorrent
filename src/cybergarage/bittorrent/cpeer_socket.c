/******************************************************************
*
*	CyberBittorrent for C
*
*	Copyright (C) Satoshi Konno 2007
*
*	File: cpeer_socket.c
*
*	Revision:
*
*	06/08/07
*		- first revision
*
******************************************************************/

#include <cybergarage/bittorrent/cpeer.h>
#include <cybergarage/util/cstring.h>

/****************************************
* cg_bittorrent_peer_connect
****************************************/

BOOL cg_bittorrent_peer_connect(CgBittorrentPeer *peer)
{
	char *addr;
	int port;
	int timeout;

	if (!peer)
		return FALSE;

	addr = cg_bittorrent_peer_getaddress(peer);
	port = cg_bittorrent_peer_getport(peer);

	if (cg_strlen(addr) <= 0 || port <= 0)
		return FALSE;

	if (!peer->sock)
		peer->sock = cg_socket_stream_new();

	cg_socket_close(peer->sock);

	if (!cg_socket_connect(peer->sock, addr, port))
		return FALSE;

	timeout = cg_bittorrent_peer_gettimeout(peer);
	if (0 < timeout)
		cg_socket_settimeout(peer->sock, timeout);

	return TRUE;
}

/****************************************
* cg_bittorrent_peer_open
****************************************/

BOOL cg_bittorrent_peer_open(CgBittorrentPeer *peer, CgByte *infoHash, CgByte *peerId)
{
	CgBittorrentHandshake *hsSend;
	CgBittorrentHandshake *hsRecv;
	BOOL isConnected;

	if (cg_bittorrent_peer_connect(peer) == FALSE)
		return FALSE;

	hsSend = cg_bittorrent_handshake_new();
	hsRecv = cg_bittorrent_handshake_new();
	cg_bittorrent_handshake_setinfohash(hsSend, infoHash);
	cg_bittorrent_handshake_setpeerid(hsSend, peerId);
	
	isConnected = cg_bittorrent_peer_handshake(peer, hsSend, hsRecv);

	cg_bittorrent_handshake_delete(hsSend);
	cg_bittorrent_handshake_delete(hsRecv);

	if (isConnected)
		cg_bittorrent_peer_setid(peer, cg_bittorrent_handshake_getpeerid(hsRecv));

	return isConnected;
}

/****************************************
* cg_bittorrent_peer_close
****************************************/

BOOL cg_bittorrent_peer_close(CgBittorrentPeer *peer)
{
	if (!peer)
		return FALSE;

	if (!peer->sock)
		return FALSE;

	return cg_socket_close(peer->sock);
}
