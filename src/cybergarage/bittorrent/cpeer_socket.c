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

	if (!peer)
		return FALSE;

	addr = cg_bittorrent_peer_getaddress(peer);
	port = cg_bittorrent_peer_getport(peer);

	if (cg_strlen(addr) <= 0 || port <= 0)
		return FALSE;

	if (!peer->sock)
		peer->sock = cg_socket_stream_new();

	cg_socket_close(peer->sock);

	return cg_socket_connect(peer->sock, addr, port);
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
