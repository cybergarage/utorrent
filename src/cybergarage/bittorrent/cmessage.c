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

	if (msg->payload)
		free(msg->payload);

	free(msg);
}

/****************************************
* cg_bittorrent_message_setpayload
****************************************/

void cg_bittorrent_message_setpayload(CgBittorrentMessage *msg, CgByte *value)
{
	if (!msg)
		return;

	if (msg->payload)
		free(msg->payload);

	msg->payload = value;
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

	if (cg_bittorrent_message_getlength(msg) <= index)
		return 0;

	intVal = (CgBittorrentInteger *)(msg->payload + index);

	return *intVal;
}
