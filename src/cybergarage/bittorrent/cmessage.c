/******************************************************************
*
*	CyberBittorrent for C
*
*	Copyright (C) Satoshi Konno 2007
*
*	File: cmessage.c
*
*	Revision:
*
*	06/08/07
*		- first revision
*
******************************************************************/

#include <cybergarage/bittorrent/cmessage.h>

/****************************************
* cg_bittorrent_message_new
****************************************/

CgBittorrentMessage *cg_bittorrent_message_new(void)
{
	CgBittorrentMessage *msg;

	msg = (CgBittorrentMessage *)malloc(sizeof(CgBittorrentMessage));
	if (!msg)
		return NULL;

	msg->length = 0;
	msg->type = 0;
	msg->payload = NULL;

	return msg;
}

/****************************************
* cg_bittorrent_message_delete
****************************************/

void cg_bittorrent_message_delete(CgBittorrentMessage *msg)
{
	if (!msg)
		return;

	cg_bittorrent_message_freepayload(msg);

	free(msg);
}

/****************************************
* cg_bittorrent_message_setpayload
****************************************/

void cg_bittorrent_message_setpayload(CgBittorrentMessage *msg, CgByte *value)
{
	if (!msg)
		return;

	cg_bittorrent_message_freepayload(msg);

	msg->payload = value;
}

/****************************************
* cg_bittorrent_message_freepayload
****************************************/

BOOL cg_bittorrent_message_allocpayload(CgBittorrentMessage *msg, int size)
{
	if (!msg)
		return FALSE;
	
	if (size < 0)
		return FALSE;

	cg_bittorrent_message_freepayload(msg);

	msg->payload = (CgByte *)malloc(size);

	return (msg->payload) ? TRUE : FALSE;
}

/****************************************
* cg_bittorrent_message_freepayload
****************************************/

void cg_bittorrent_message_freepayload(CgBittorrentMessage *msg)
{
	if (!msg)
		return;

	if (msg->payload)
		free(msg->payload);

	msg->payload = NULL;
}

/****************************************
* cg_bittorrent_message_getpayloadinteger
****************************************/

CgBittorrentInteger cg_bittorrent_message_getpayloadinteger(CgBittorrentMessage *msg, int index)
{
	CgBittorrentInteger *intVal;

	if (!msg)
		return 0;

	if (!msg->payload)
		return 0;

	if (cg_bittorrent_message_getlength(msg) <= (CgBittorrentInteger)index)
		return 0;

	intVal = (CgBittorrentInteger *)(msg->payload + index);

	return *intVal;
}
