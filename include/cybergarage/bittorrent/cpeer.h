/******************************************************************
*
*	CyberBittorrent for C
*
*	Copyright (C) Satoshi Konno 2007
*
*	File: cpeer.h
*
*	Revision:
*
*	03/27/07
*		- first revision
*
******************************************************************/

#ifndef _CG_BITTORRENT_PEER_H_
#define _CG_BITTORRENT_PEER_H_

#ifdef  __cplusplus
extern "C" {
#endif

#include <cybergarage/typedef.h>
#include <cybergarage/util/clist.h>
#include <cybergarage/net/csocket.h>

/****************************************
* Define
****************************************/

/****************************************
* Data Type
****************************************/

typedef struct _CgBittorrentPeer {
	BOOL headFlag;
	struct _CgBittorrentPeer *prev;
	struct _CgBittorrentPeer *next;
	char *addr;
	int port;
	CgSocket *sock;
} CgBittorrentPeer, CgBittorrentPeerList;

/****************************************
* Function (Peer List)
****************************************/

/**
 * Create a new peer list.
 *
 * \return Peer list.
 */
CgBittorrentPeerList *cg_bittorrent_peerlist_new(void);

/**
 * Destroy a peer list.
 *
 * \param peerList Peer list to destory.
 */
void cg_bittorrent_peerlist_delete(CgBittorrentPeerList *peerList);

/**
 * Clear all items of a peer list.
 *
 * \param peerList Peer list to clear.
 */
#define cg_bittorrent_peerlist_clear(peerList) cg_list_clear((CgList *)peerList, (CG_LIST_DESTRUCTORFUNC)cg_bittorrent_peer_delete)

/**
 * Get the size of a peer list.
 *
 * \param peerList Peer list in question.
 *
 * \return Size of the peer list.
 */
#define cg_bittorrent_peerlist_size(peerList) cg_list_size((CgList *)peerList)

/**
 * Get the first item from a peer list.
 *
 * \param peerList Peer list in question.
 *
 * \return First Peer of the list, otherwise NULL if the list has no items.
 */
#define cg_bittorrent_peerlist_gets(peerList) (CgBittorrentPeer *)cg_list_next((CgList *)peerList)

/**
 * Add a peer into a peer list.
 *
 * \param peerList Peer list in question.
 * \param peer Peer to add to the list.
 */
#define cg_bittorrent_peerlist_add(peerList, peer) cg_list_add((CgList *)peerList, (CgList *)peer)

/****************************************
* Function (Peer)
****************************************/

/**
 * Create a new peer.
 *
 * \return New peer.
 */
CgBittorrentPeer *cg_bittorrent_peer_new(void);

/**
 * Destroy a peer.
 *
 * \param peer Peer to destroy.
 */
void cg_bittorrent_peer_delete(CgBittorrentPeer *peer);

/**
 * Get the next item from the peer list.
 *
 * \param peer Peer in question.
 *
 * \return Next Peer of the list, otherwise NULL if the list has no items.
 */
#define cg_bittorrent_peer_next(peer) (CgBittorrentPeer *)cg_list_next((CgList *)peer)

/**
 * Set a peer address.
 *
 * \param peer Peer in question.
 * \param value Type to set.
 */
void cg_bittorrent_peer_setaddress(CgBittorrentPeer *peer, char *addr);

/**
 * Get a peer address.
 *
 * \param peer Peer in question.
 *
 * \return Address of the peer.
 */
#define cg_bittorrent_peer_getaddress(peer) (peer->addr)

/**
 * Set a peer port.
 *
 * \param peer Peer in question.
 * \param port Port to set.
 */
#define cg_bittorrent_peer_setport(peer, value) (peer->port = value)

 /**
 * Get a peer port.
 *
 * \param peer Peer in question.
 *
 * \return Port of the peer.
 */
#define cg_bittorrent_peer_getport(peer) (peer->port)

 /**
 * Connect the specified peer.
 *
 * \param peer Peer in question.
 *
 * \return TRUE when the connection is succeeded, otherwise FALSE.
 */
BOOL cg_bittorrent_peer_connect(CgBittorrentPeer *peer);

 /**
 * Close a connection of the specified peer.
 *
 * \param peer Peer in question.
 *
 * \return TRUE when the connection is closed normally, otherwise FALSE.
 */
BOOL cg_bittorrent_peer_close(CgBittorrentPeer *peer);

#ifdef  __cplusplus
}
#endif

#endif
