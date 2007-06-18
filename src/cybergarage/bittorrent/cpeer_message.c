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

#include <cybergarage/bittorrent/cmessage.h>

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

	if (cg_bittorrent_peer_read(peer, &msg->type, sizeof(msg->type)) != sizeof(msg->type))
		return FALSE;

	return TRUE;
}

/****************************************
* cg_bittorrent_peer_recvmsgbody
****************************************/

int cg_bittorrent_peer_recvmsgbody(CgBittorrentPeer *peer, CgBittorrentMessage *msg)
{
	int pstrlen;
	int readlen;
	int nread;

	if (!peer || !msg)
		return 0;

	if (msg->payload) {
		free(msg->payload);
		msg->payload = NULL;
	}

	pstrlen = cg_bittorrent_message_getlength(msg);
	if (pstrlen <=0)
		return 0;

	msg->payload = (char *)malloc(pstrlen);

	readlen = 0;
	while (readlen < pstrlen) {
		nread = cg_bittorrent_peer_read(peer, (msg->payload + readlen), (pstrlen - readlen));
		if (nread <= 0)
			return readlen;
		readlen += nread;
	}

	return readlen;
}

/****************************************
* cg_bittorrent_peer_recvmsgbodyasync
****************************************/

int cg_bittorrent_peer_recvmsgbodyasync(CgBittorrentPeer *peer, CgBittorrentMessage *msg, CG_BITTORRENT_MESSAGE_READ_FUNC func, void *userData, char *buf, int bufSize)
{
	int pstrlen;
	int readlen;
	int nread;

	if (!peer || !msg || !func)
		return 0;

	if (msg->payload) {
		free(msg->payload);
		msg->payload = NULL;
	}

	pstrlen = cg_bittorrent_message_getlength(msg);
	if (pstrlen <=0)
		return 0;

	readlen = 0;
	while (readlen < pstrlen) {
		nread = pstrlen - readlen;
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
* cg_bittorrent_peer_writemessage
****************************************/

int cg_bittorrent_peer_sendmsg(CgBittorrentPeer *peer, CgBittorrentMessage *msg)
{
	unsigned int pstrlen;
	unsigned int npstrlen;

	if (!peer)
		return 0;

	/* Send message */
	pstrlen = cg_bittorrent_message_getlength(msg);
	npstrlen = htonl(pstrlen);
	if (cg_bittorrent_peer_write(peer, (char *)&npstrlen, sizeof(npstrlen)) != sizeof(npstrlen))
		return FALSE;
	if (cg_bittorrent_peer_write(peer, &msg->type, sizeof(msg->type)) != sizeof(msg->type))
		return FALSE;
	if (0 < pstrlen && msg->payload) {
		if (cg_bittorrent_peer_write(peer, msg->payload, pstrlen) != pstrlen)
			return FALSE;
	}

	return TRUE;
}
