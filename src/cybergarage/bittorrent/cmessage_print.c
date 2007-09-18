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

	msgType = cg_bittorrent_message_gettype(msg);

	printf("%d : ", cg_bittorrent_message_getlength(msg));

	switch (msgType) {
	case CG_BITTORRENT_MESSAGE_CHOKE:
		printf("choke : "); break;
	case CG_BITTORRENT_MESSAGE_UNCHOKE:
		printf("unchoke : "); break;
	case CG_BITTORRENT_MESSAGE_INTERESTED:
		printf("intersted : "); break;
	case CG_BITTORRENT_MESSAGE_NOT_INTERESTED:
		printf("not interested : "); break;
	case CG_BITTORRENT_MESSAGE_HAVE:
		printf("have : "); break;
	case CG_BITTORRENT_MESSAGE_BITFIELD:
		printf("bitfield : "); break;
	case CG_BITTORRENT_MESSAGE_REQUEST:
		printf("request : "); break;
	case CG_BITTORRENT_MESSAGE_PIECE:
		printf("piece : "); break;
	case CG_BITTORRENT_MESSAGE_PORT:
		printf("port : "); break;
	}

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
