/******************************************************************
*
*	CyberBittorrent for C
*
*	Copyright (C) Satoshi Konno 2007
*
*	File: cmessage_print.c
*
*	Revision:
*
*	09/09/07
*		- first revision
*
******************************************************************/

#include <cybergarage/bittorrent/cmessage.h>

/****************************************
* cg_bittorrent_metainfo_print
****************************************/

#if defined(DEBUG) || defined(_DEBUG) || defined(HAVE_PRINTF)

void cg_bittorrent_message_print(CgBittorrentMessage *msg)
{
	CgByte msgType;

	if (!msg)
		return;

	printf("%d : %d : ", 
		cg_bittorrent_message_getlength(msg),
		(int)cg_bittorrent_message_gettype(msg)
		);

	msgType = cg_bittorrent_message_gettype(msg);
	switch (msgType) {
	case CG_BITTORRENT_MESSAGE_HAVE:
		{
			printf("%d", cg_bittorrent_message_getpayloadinteger(msg, 0));
		}
		break;
	}

	printf("\n");
}

#endif
