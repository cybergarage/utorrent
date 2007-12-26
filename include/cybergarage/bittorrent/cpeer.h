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
	/* Socket */
	CgSocket *sock;
	CgByte id[CG_BITTORRENT_PEERID_SIZE];
	int timeout;
	/* Bitfield */
	CgByte *bitfield;
	int bitfieldLength;
	/* Statistics */
	int numSucceeded;
	int numFailed;
	int downloadedElapsedTime;
	int uploadedElapsedTime;
	int downloadedBytes;
	int uploadedBytes;
	int downloadingPercentage;
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
 * Set a peer timeout.
 *
 * \param peer Peer in question.
 * \param value value of the timeout to set.
 */
#define cg_bittorrent_peer_settimeout(peer, value) (peer->timeout = value)

 /**
 * Get a peer timeout.
 *
 * \param peer Peer in question.
 *
 * \return Value of the timeout.
 */
#define cg_bittorrent_peer_gettimeout(peer) (peer->timeout)

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
 * Check if the specified peer is connected.
 *
 * \param peer Peer in question.
 *
 * \return TRUE when the peer is connected, otherwise FALSE.
 */
#define cg_bittorrent_peer_isbound(peer) cg_socket_isbound(peer->sock)

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

/****************************************
* Function (Statics)
****************************************/

/**
 * Set a count of the succeeded connections.
 *
 * \param peer Peer in question.
 * \param value Count of the succeeded connections.
 */
#define cg_bittorrent_peer_setnumsucceeded(peer, value) (peer->numSucceeded = value)

 /**
 * Get the count of the succeeded connections.
 *
 * \param peer Peer in question.
 *
 * \return Count of the succeeded connections.
 */
#define cg_bittorrent_peer_getnumsucceeded(peer) (peer->numSucceeded)

 /**
 * Increment the a count of the succeeded connections.
 *
 * \param peer Peer in question.
 *
 */
#define cg_bittorrent_peer_incrementnumsucceeded(peer) (peer->numSucceeded++)

/**
 * Set a count of the failed connections.
 *
 * \param peer Peer in question.
 * \param value Count of the failed connections.
 */
#define cg_bittorrent_peer_setnumfailed(peer, value) (peer->numFailed = value)

 /**
 * Get the count of the failed connections.
 *
 * \param peer Peer in question.
 *
 * \return Count of the failed connections.
 */
#define cg_bittorrent_peer_getnumfailed(peer) (peer->numFailed)

 /**
 * Increment the a count of the failed connections.
 *
 * \param peer Peer in question.
 *
 */
#define cg_bittorrent_peer_incrementnumfailed(peer) (peer->numFailed++)

/**
 * Set a elapsed time.
 *
 * \param peer Peer in question.
 * \param value to set.
 */
#define cg_bittorrent_peer_setdownloadedelapsedtime(peer, value) (peer->downloadedElapsedTime = value)

 /**
 * Get the elapsed time.
 *
 * \param peer Peer in question.
 *
 * \return Elapsed time.
 */
#define cg_bittorrent_peer_getdownloadedelapsedtime(peer) (peer->downloadedElapsedTime)

 /**
 * Add a time into the current elapsed time.
 *
 * \param peer Peer in question.
 * \value Value to add.
 *
 */
#define cg_bittorrent_peer_adddownloadedelapsedtime(peer, value) (peer->downloadedElapsedTime += value)

/**
 * Set a elapsed time.
 *
 * \param peer Peer in question.
 * \param value to set.
 */
#define cg_bittorrent_peer_setuploadedelapsedtime(peer, value) (peer->uploadedElapsedTime = value)

 /**
 * Get the elapsed time.
 *
 * \param peer Peer in question.
 *
 * \return Elapsed time.
 */
#define cg_bittorrent_peer_getuploadedelapsedtime(peer) (peer->uploadedElapsedTime)

 /**
 * Add a time into the current elapsed time.
 *
 * \param peer Peer in question.
 * \value Value to add.
 *
 */
#define cg_bittorrent_peer_adduploadedelapsedtime(peer, value) (peer->uploadedElapsedTime += value)

/**
 * Set a downloaded bytes.
 *
 * \param peer Peer in question.
 * \param value to set.
 */
#define cg_bittorrent_peer_setdownloadedbytes(peer, value) (peer->downloadedBytes = value)

 /**
 * Get the downloaded bytes.
 *
 * \param peer Peer in question.
 *
 * \return Elapsed bytes.
 */
#define cg_bittorrent_peer_getdownloadedbytes(peer) (peer->downloadedBytes)

 /**
 * Add a bytes into the current downloaded bytes.
 *
 * \param peer Peer in question.
 * \value Value to add.
 *
 */
#define cg_bittorrent_peer_adddownloadedbytes(peer, value) (peer->downloadedBytes += value)

/**
 * Set a uploaded bytes.
 *
 * \param peer Peer in question.
 * \param value to set.
 */
#define cg_bittorrent_peer_setuploadedbytes(peer, value) (peer->uploadedBytes = value)

 /**
 * Get the uploaded bytes.
 *
 * \param peer Peer in question.
 *
 * \return Elapsed bytes.
 */
#define cg_bittorrent_peer_getuploadedbytes(peer) (peer->uploadedBytes)

 /**
 * Add a bytes into the current uploaded bytes.
 *
 * \param peer Peer in question.
 * \value Value to add.
 *
 */
#define cg_bittorrent_peer_adduploadedbytes(peer, value) (peer->uploadedBytes += value)

/**
 * Set a downloaded percentages.
 *
 * \param peer Peer in question.
 * \param value to set.
 */
#define cg_bittorrent_peer_setdownloadingpercentages(peer, value) (peer->downloadingPercentage = value)

 /**
 * Get the downloaded percentages.
 *
 * \param peer Peer in question.
 *
 * \return Elapsed percentages.
 */
#define cg_bittorrent_peer_getdownloadingpercentages(peer) (peer->downloadingPercentage)

/****************************************
* Function (Other)
****************************************/

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
