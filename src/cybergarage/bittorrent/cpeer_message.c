/******************************************************************
*
*	CyberBittorrent for C
*
*	Copyright (C) Satoshi Konno 2007
*
*	File: cpeer_message.c
*
*	Revision:
*
*	06/12/07
*		- first revision
*
******************************************************************/

#include <cybergarage/bittorrent/cpeer.h>

/****************************************
* cg_bittorrent_peer_recvmsgheader
****************************************/

BOOL cg_bittorrent_peer_recvmsgheader(CgBittorrentPeer *peer, CgBittorrentMessage *msg)
{
	unsigned int pstrlen;
	unsigned int npstrlen;

	if (!peer || !msg)
		return FALSE;

	/* Recv a message*/
	if (cg_bittorrent_peer_read(peer, (char *)&npstrlen, sizeof(npstrlen)) != sizeof(npstrlen))
		return FALSE;
	pstrlen = ntohl(npstrlen);
	cg_bittorrent_message_setlength(msg, pstrlen);

	if (pstrlen < 0)
		return FALSE;

	if (pstrlen == 0) {
		cg_bittorrent_message_settype(msg, CG_BITTORRENT_BENCODING_KEEP_ALIVE);
		return TRUE;
	}

	if (cg_bittorrent_peer_read(peer, &msg->type, sizeof(msg->type)) != sizeof(msg->type))
		return FALSE;

	return TRUE;
}

/****************************************
* cg_bittorrent_peer_recvmsgbody
****************************************/

int cg_bittorrent_peer_recvmsgbody(CgBittorrentPeer *peer, CgBittorrentMessage *msg, CgByte *buf, int bufLen)
{
	int payloadLen;
	int readlen;
	int nread;
	int skiplen;
	CgByte skipBuf[32];

	if (!peer || !msg)
		return 0;

	cg_bittorrent_message_freepayload(msg);

	if (msg->payload) {
		free(msg->payload);
		msg->payload = NULL;
	}

	payloadLen = cg_bittorrent_message_getpayloadlength(msg);
	if (payloadLen <=0)
		return 0;

	if (!buf || bufLen < 0) {
		if (!cg_bittorrent_message_allocatepayload(msg, payloadLen))
			return 0;
		buf = cg_bittorrent_message_getpayload(msg);
		bufLen = payloadLen;
	}

	readlen = 0;
	while ((readlen < bufLen) && (readlen < payloadLen)) {
		nread = cg_bittorrent_peer_read(peer, (buf + readlen), min((bufLen - readlen),  (readlen < payloadLen)));
		if (nread <= 0)
			readlen;
		readlen += nread;
	}
	skiplen = 0;
	while ((readlen +  skiplen)< payloadLen) {
		nread = cg_bittorrent_peer_read(peer, skipBuf, (sizeof(skipBuf) < (payloadLen - readlen- skiplen)) ? sizeof(skipBuf) : (payloadLen - readlen- skiplen));
		if (nread <= 0)
			break;
		skiplen += nread;
	}

	switch (cg_bittorrent_message_gettype(msg)) {
	case CG_BITTORRENT_MESSAGE_BITFIELD:
		{
				cg_bittorrent_peer_setbitfield(peer, cg_bittorrent_message_getpayload(msg), cg_bittorrent_message_getpayloadlength(msg));
		}
		break;
	}

	return readlen;
}

/****************************************
* cg_bittorrent_peer_recvmsgbodyasync
****************************************/

int cg_bittorrent_peer_recvmsgbodyasync(CgBittorrentPeer *peer, CgBittorrentMessage *msg, CG_BITTORRENT_MESSAGE_READ_FUNC func, void *userData, char *buf, int bufSize)
{
	/* Not implemented yet */

	int payloadLen;
	int readlen;
	int nread;

	if (!peer || !msg || !func)
		return 0;

	if (msg->payload) {
		free(msg->payload);
		msg->payload = NULL;
	}

	payloadLen = cg_bittorrent_message_getlength(msg);
	if (payloadLen <=0)
		return 0;

	readlen = 0;
	while (readlen < payloadLen) {
		nread = payloadLen - readlen;
		if (bufSize < nread)
			nread = bufSize;
		nread = cg_bittorrent_peer_read(peer, buf, nread);
		if (nread <= 0)
			return readlen;
		func(userData, buf, nread);
		readlen += nread;
	}

	return readlen;
}

/****************************************
* cg_bittorrent_peer_recvmsg
****************************************/

BOOL cg_bittorrent_peer_recvmsg(CgBittorrentPeer *peer, CgBittorrentMessage *msg)
{
	if (cg_bittorrent_peer_recvmsgheader(peer, msg) == FALSE)
		return FALSE;
	if (cg_bittorrent_peer_recvmsgbodynobuf(peer, msg) != cg_bittorrent_message_getlength(msg))
		return FALSE;
	return TRUE;
}

/****************************************
* cg_bittorrent_peer_writemessage
****************************************/

BOOL cg_bittorrent_peer_sendmsg(CgBittorrentPeer *peer, CgBittorrentMessage *msg)
{
	unsigned int pstrlen;
	unsigned int npstrlen;
	unsigned int payloadLen;

	if (!peer)
		return FALSE;

	/* Send message */
	pstrlen = cg_bittorrent_message_getlength(msg);
	npstrlen = htonl(pstrlen);
	if (cg_bittorrent_peer_write(peer, (char *)&npstrlen, sizeof(npstrlen)) != sizeof(npstrlen))
		return FALSE;
	if (cg_bittorrent_peer_write(peer, &msg->type, sizeof(msg->type)) != sizeof(msg->type))
		return FALSE;
	payloadLen = cg_bittorrent_message_getpayloadlength(msg);
	if (msg->payload && 0 < payloadLen) {
		if (cg_bittorrent_peer_write(peer, msg->payload, payloadLen) != payloadLen)
			return FALSE;
	}

	return TRUE;
}
