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
* cg_bittorrent_message_delete
****************************************/

BOOL cg_bittorrent_message_haspiece(CgBittorrentMessage *msg, int index)
{
	int bitfieldNum;
	int bitfieldOffset;
	CgByte bitfieldMask;
	if (cg_bittorrent_message_gettype(msg) != CG_BITTORRENT_MESSAGE_BITFIELD)
		return FALSE;
	bitfieldNum = index / 8;
	bitfieldOffset = index % 8;
	bitfieldMask = 1 << (7 - bitfieldOffset); 
	if (cg_bittorrent_message_getlength(msg) < bitfieldNum)
		return FALSE;
	return (msg->payload[bitfieldNum] & bitfieldMask) ? TRUE : FALSE;
}
