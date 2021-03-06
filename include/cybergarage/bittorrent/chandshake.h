/******************************************************************
*
*	CyberBittorrent for C
*
*	Copyright (C) Satoshi Konno 2007
*
*	File: chandshake.h
*
*	Revision:
*
*	06/11/07
*		- first revision
*
******************************************************************/

#ifndef _CG_BITTORRENT_HANDSHAKE_H_
#define _CG_BITTORRENT_HANDSHAKE_H_

#ifdef  __cplusplus
extern "C" {
#endif

#include <cybergarage/typedef.h>
#include <cybergarage/bittorrent/csha1.h>

/****************************************
* Define
****************************************/

#define CG_BITTORRENT_HANDSHAKE_PSTR "BitTorrent protocol"

/****************************************
* Data Type
****************************************/

typedef struct _CgBittorrentHandshake {
	CgByte pstrlen;
	char *pstr;
	CgByte reserved[8];
	CgByte infoHash[CG_SHA1_HASH_SIZE];
	CgByte peerId[CG_SHA1_HASH_SIZE];
} CgBittorrentHandshake;

/****************************************
* Function
****************************************/

/**
 * Create a new handshake.
 *
 * \return New handshake.
 */
CgBittorrentHandshake *cg_bittorrent_handshake_new(void);

/**
 * Destroy a peer.

 *
 * \param hs Handshake to destroy.
 */
void cg_bittorrent_handshake_delete(CgBittorrentHandshake *hs);

/**
 * Get a pstrlen of the specified handshake.
 *
 * \param hs Handshake in question.
 *
 * \return pstrlen of the handshake.
 */
#define cg_bittorrent_handshake_getpstrlen(hs) (hs->pstrlen)

/**
 * Get a pstr of the specified handshake.
 *
 * \param hs Handshake in question.
 *
 * \return pstr of the handshake.
 */
#define cg_bittorrent_handshake_getpstr(hs) (hs->pstr)

/**
 * Get a reserved of the specified handshake.
 *
 * \param hs Handshake in question.
 *
 * \return reserved of the handshake.
 */
#define cg_bittorrent_handshake_getreserved(hs) (hs->reserved)

/**
 * Set a info_hash of the specified handshake.
 *
 * \param hs Handshake in question.
 * \param value Info_hash to set.
 */
#define cg_bittorrent_handshake_setinfohash(hs, value) memcpy(hs->infoHash, value, sizeof(hs->infoHash))

/**
 * Get a info_hash of the specified handshake.
 *
 * \param hs Handshake in question.
 *
 * \return Info_hash of the handshake.
 */
#define cg_bittorrent_handshake_getinfohash(hs) (hs->infoHash)

/**
 * Set a peer_id of the specified handshake.
 *
 * \param hs Handshake in question.
 * \param value Peer_id to set.
 */
#define cg_bittorrent_handshake_setpeerid(hs, value) memcpy(hs->peerId, value, sizeof(hs->peerId))

/**
 * Get a peerid of the specified handshake.
 *
 * \param hs Handshake in question.
 *
 * \return Peer_id of the handshake.
 */
#define cg_bittorrent_handshake_getpeerid(hs) (hs->peerId)

#ifdef  __cplusplus
}
#endif

#endif
