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

/****************************************
* Define
****************************************/

#define CG_BITTORRENT_HANDSHAKE_PSTR "BitTorrent protocol"



/****************************************
* Data Type
****************************************/

typedef struct _CgBittorrentHandshake {
	unsigned int pstrlen;
	char *pstr;
	unsigned char reserved[8];
	unsigned char infoHash[20];
	unsigned char peerId[20];
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
#define cg_bittorrent_handshake_getinfohash(peer) (hs->infoHash)

/**
 * Set a peer_id of the specified handshake.
 *
 * \param hs Handshake in question.
 * \param value Peer_id to set.
 */
#define cg_bittorrent_handshake_setpeerid(hs, value) memcpy(hs->peerid, value, sizeof(hs->peerid))

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
