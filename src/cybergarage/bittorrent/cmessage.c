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

