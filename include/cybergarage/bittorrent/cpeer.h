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

#include <cybergarage/typedef.h>
#include <cybergarage/util/clist.h>
#include <cybergarage/net/csocket.h>
#include <cybergarage/bittorrent/chandshake.h>
#include <cybergarage/bittorrent/cmessage.h>
#include <cybergarage/bittorrent/csha1.h>

#ifdef  __cplusplus
extern "C" {
#endif

/****************************************
* Define
****************************************/

#define CG_BITTORRENT_PEERID_SIZE CG_SHA1_HASH_SIZE
#define CG_BITTORRENT_PIECE_MAX_SIZE (1<<14)

/****************************************
* Data Type
****************************************/

typedef struct _CgBittorrentPeer {
	BOOL headFlag;
	struct _CgBittorrentPeer *prev;
	struct _CgBittorrentPeer *next;
	void *tracker;
	char *addr;
	int port;
	CgSocket *sock;
	CgByte id[CG_BITTORRENT_PEERID_SIZE];
	CgByte *bitfield;
	int bitfieldLength;
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
 * Set a parent tracker.
 *
 * \param peer Peer in question.
 * \param value Tracker to set.
 */
#define cg_bittorrent_peer_settracker(peer, value)  (peer->tracker = value)

/**
 * Get a parent tracker.
 *
 * \param peer Peer in question.
 *
 * \return Tracker of the peer.
 */
#define cg_bittorrent_peer_gettracker(peer) (CgBittorrentTracker *)(peer->tracker)

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
 * Set a peer peerid.
 *
 * \param peer Peer in question.
 * \param peerid Peer id to set.
 */
#define cg_bittorrent_peer_setid(peer, value) memcpy(peer->id, value, CG_BITTORRENT_PEERID_SIZE)

 /**
 * Get a peer peerid.
 *
 * \param peer Peer in question.
 *
 * \return Peed id of the peer.
 */
#define cg_bittorrent_peer_getid(peer) (peer->id)

/**
 * Set a peer bitfield.
 *
 * \param peer Peer in question.
 * \param value Bitfield to set.
 * \param value Length of the bitfield to set.
 */
void cg_bittorrent_peer_setbitfield(CgBittorrentPeer *peer, CgByte *bitfield, int bitfieldLength);

 /**
 * Get a peer bitfield.
 *
 * \param peer Peer in question.
 *
 * \return Bitfield of the peer.
 */
#define cg_bittorrent_peer_getbitfield(peer) (peer->bitfield)

 /**
 * Check a peer bitfield.
 *
 * \param peer Peer in question.
 *
 * \return TRUE when the peer has a bitfield, otherwise FALSE.
 */
#define cg_bittorrent_peer_hasbitfield(peer) ((peer->bitfield) ? TRUE : FALSE)

 /**
 * Get a length of the bitfield.
 *
 * \param peer Peer in question.
 *
 * \return Length of the bitfield.
 */
#define cg_bittorrent_peer_getbitfieldlength(peer) (peer->bitfieldLength)

 /**
 * Connect the specified peer.
 *
 * \param peer Peer in question.
 *
 * \return TRUE when the connection is succeeded, otherwise FALSE.
 */
BOOL cg_bittorrent_peer_connect(CgBittorrentPeer *peer);

 /**
 * Connect the specified peer.
 *
 * \param peer Peer in question.
 * \param infoHash InfoHash in question.
 * \param peerid Peer id in question.
 *
 * \return TRUE when the connection is succeeded, otherwise FALSE.
 */
BOOL cg_bittorrent_peer_open(CgBittorrentPeer *peer, CgByte *infoHash, CgByte *peerid);

 /**
 * Close a connection of the specified peer.
 *
 * \param peer Peer in question.
 *
 * \return TRUE when the connection is closed normally, otherwise FALSE.
 */
BOOL cg_bittorrent_peer_close(CgBittorrentPeer *peer);

 /**
 * Read data from the specified peer.
 *
 * \param peer Peer in question.
 * \param buffer Buffer to read.
 * \param bufferLen Length of the buffer.
 *
 * \return a number of read data.
 */

#define cg_bittorrent_peer_read(peer, buffer, bufferLen) cg_socket_read(peer->sock, buffer, bufferLen)

 /**
 * Write data to the specified peer.
 *
 * \param peer Peer in question.
 * \param buffer Buffer to write.
 * \param bufferLen Length of the buffer.
 *
 * \return a number of wrote data.
 */

#define cg_bittorrent_peer_write(peer, buffer, bufferLen) cg_socket_write(peer->sock, buffer, bufferLen)

 /**
 * Handshake with the current peer.
 *
 * \param peer Peer in question.
 * \param hsSend Handshake infomation of the client.
 * \param hsRecv Handshake infomation of the connected peer.
 *
 * \return TRUE when the connection is closed normally, otherwise FALSE.
 */
BOOL cg_bittorrent_peer_handshake(CgBittorrentPeer *peer, CgBittorrentHandshake *hsSend, CgBittorrentHandshake *hsRecv);

/**
 * Check if a peer has the specfied piece.
 *
 * \param peer Peer in question.
 * \param index Index of the piece.
 *
 * \return TRUE if the peer has the specified piece, otherwise FALSE.
 */
BOOL cg_bittorrent_peer_haspiece(CgBittorrentPeer *peer, int index);

/**
 * Check if a peer has the specfied piece.
 *
 * \param peer Peer in question.
 * \param index Index of the piece.
 *
 * \return TRUE if the peer has the specified piece, otherwise FALSE.
 */
BOOL cg_bittorrent_peer_getpieceblock(CgBittorrentPeer *peer, int pieceIdx, int pieceOffset, CgByte *buf, int bufLen);

/**
 * Request the specfied piece.
 *
 * \param peer Peer in question.
 * \param index Index of the piece.
 * \param begin Offset of the piece.
 * \param length Length of the piece.
 *
 * \return TRUE if the request is successful, otherwise FALSE.
 */
BOOL cg_bittorrent_peer_request(CgBittorrentPeer *peer, int index, int begin, int length);

BOOL cg_bittorrent_peer_recvmsgheader(CgBittorrentPeer *peer, CgBittorrentMessage *msg);
int cg_bittorrent_peer_recvmsgbody(CgBittorrentPeer *peer, CgBittorrentMessage *msg, CgByte *buf, int bufLen);
#define cg_bittorrent_peer_recvmsgbodynobuf(peer, msg) cg_bittorrent_peer_recvmsgbody(peer, msg, NULL, 0)
int cg_bittorrent_peer_recvmsgbodyasync(CgBittorrentPeer *peer, CgBittorrentMessage *msg, CG_BITTORRENT_MESSAGE_READ_FUNC func, void *userData, char *buf, int bufSize);
BOOL cg_bittorrent_peer_recvmsg(CgBittorrentPeer *peer, CgBittorrentMessage *msg);
BOOL cg_bittorrent_peer_sendmsg(CgBittorrentPeer *peer, CgBittorrentMessage *msg);

BOOL cg_bittorrent_peer_choke(CgBittorrentPeer *peer);
BOOL cg_bittorrent_peer_unchoke(CgBittorrentPeer *peer);
BOOL cg_bittorrent_peer_interested(CgBittorrentPeer *peer);
BOOL cg_bittorrent_peer_notinterested(CgBittorrentPeer *peer);

#ifdef  __cplusplus
}
#endif

#endif
