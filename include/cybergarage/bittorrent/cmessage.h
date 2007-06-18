/******************************************************************
*
*	CyberBittorrent for C
*
*	Copyright (C) Satoshi Konno 2007
*
*	File: cmessage.h
*
*	Revision:
*
*	06/08/07
*		- first revision
*
******************************************************************/

#ifndef _CG_BITTORRENT_MESSAGE_H_
#define _CG_BITTORRENT_MESSAGE_H_

#ifdef  __cplusplus
extern "C" {
#endif

#include <cybergarage/bittorrent/cpeer.h>

/****************************************
* Define
****************************************/

/* keep-alive: <len=0000>*/
#define CG_BITTORRENT_BENCODING_KEEP_ALIVE 

/* choke: <len=0001><id=0>*/
#define CG_BITTORRENT_MESSAGE_CHOKE '0'

/* unchoke: <len=0001><id=1> */
#define CG_BITTORRENT_MESSAGE_UNCHOKE '1'

/* interested: <len=0001><id=2> */
#define CG_BITTORRENT_MESSAGE_INTERESTED '2'

/* not interested: <len=0001><id=3> */
#define CG_BITTORRENT_MESSAGE_NOT_INTERESTED '3'

/* have: <len=0005><id=4><piece index> */
#define CG_BITTORRENT_MESSAGE_NOT_HAVE '4'

/* bitfield: <len=0001+X><id=5><bitfield> */
#define CG_BITTORRENT_MESSAGE_BITFIELD '5'

/* request: <len=0013><id=6><index><begin><length> */
#define CG_BITTORRENT_MESSAGE_REQUEST '6'

/* piece: <len=0009+X><id=7><index><begin><block> */
#define CG_BITTORRENT_MESSAGE_PIECE '7'

/* cancel: <len=0013><id<=8><index><begin><length> */
#define CG_BITTORRENT_MESSAGE_CANCEL '8'

/* port: <len=0003><id=9><listen-port> */
#define CG_BITTORRENT_MESSAGE_PORT '9'

/****************************************
* Data Type
****************************************/

typedef struct _CgBittorrentMessage {
	unsigned int length;
	unsigned char type;
	char *payload;
} CgBittorrentMessage;

/****************************************
* Function Type
****************************************/

/**
 * Prototype for reading a peer message
 *
 */
typedef void (*CG_BITTORRENT_MESSAGE_READ_FUNC)(void *, char *, int);

/****************************************
* Function
****************************************/

/**
 * Create a new message.
 *
 * \return New message.
 */
CgBittorrentMessage *cg_bittorrent_message_new(void);

/**
 * Destroy a peer.

 *
 * \param msg Message to destroy.
 */
void cg_bittorrent_message_delete(CgBittorrentMessage *msg);

/**
 * Set a length of the specified message.
 *
 * \param msg Message in question.
 * \param value Length to set.
 */
#define cg_bittorrent_message_setlength(msg, value) (msg->length = value)

/**
 * Get a length of the specified message.
 *
 * \param msg Message in question.
 *
 * \return Length of the message.
 */
#define cg_bittorrent_message_getlength(msg) (msg->length)

/**
 * Set a type of the specified message.
 *
 * \param msg Message in question.
 * \param value Type to set.
 */
#define cg_bittorrent_message_settype(msg, value) (msg->type = value)

/**
 * Get a type of the specified message.
 *
 * \param msg Message in question.
 *
 * \return Type of the message.
 */
#define cg_bittorrent_message_gettype(msg) (msg->type)

/****************************************
* Message
****************************************/

#ifdef  __cplusplus
}
#endif

#endif
