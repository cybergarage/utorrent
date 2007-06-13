/******************************************************************
*
*	CyberBittorrent for C
*
*	Copyright (C) Satoshi Konno 2007
*
*	File: chandshake.c
*
*	Revision:
*
*	06/11/07
*		- first revision
*
******************************************************************/

#include <cybergarage/bittorrent/chandshake.h>
#include <cybergarage/util/cstring.h>

/****************************************
* cg_bittorrent_handshake_new
****************************************/

CgBittorrentHandshake *cg_bittorrent_handshake_new(void)
{
	CgBittorrentHandshake *hs;

	hs = (CgBittorrentHandshake *)malloc(sizeof(CgBittorrentHandshake));
	if (!hs)
		return NULL;

	hs->pstrlen =cg_strlen(CG_BITTORRENT_HANDSHAKE_PSTR);
	hs->pstr = cg_strdup(CG_BITTORRENT_HANDSHAKE_PSTR);
	memset(hs->reserved, 0, sizeof(hs->reserved));
	memset(hs->infoHash, 0, sizeof(hs->infoHash));
	memset(hs->peerId, 0, sizeof(hs->peerId));

	return hs;
}

/****************************************
* cg_bittorrent_handshake_delete
****************************************/

void cg_bittorrent_handshake_delete(CgBittorrentHandshake *hs)
{
	if (!hs)
		return;

	if (hs->pstr)
		free(hs->pstr);

	free(hs);
}
