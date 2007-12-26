/******************************************************************
*
*	CyberBittorrent for C
*
*	Copyright (C) Satoshi Konno 2007
*
*	File: cmetainfo_parse.c
*
*	Revision:
*
*	02/07/07
*		- first revision
*
******************************************************************/

#include <cybergarage/bittorrent/cmetainfo.h>

/****************************************
* cg_bittorrent_metainfo_parse
****************************************/

BOOL cg_bittorrent_metainfo_parse(CgBittorrentMetainfo *cbm, char *data, int dataLen)
{
	CgBittorrentDictionary *cbd;
	int offset;
	int numPieces;

	if (!cbm)
		return FALSE;

	cbd = cg_bittorrent_metainfo_getdictionary(cbm);
	if (!cbd)
		return FALSE;

	if (cg_bittorrent_dictionary_parse(cbd, data, &offset) == FALSE)
		return FALSE;

	/* Initialize Piece Infos */
	numPieces = cg_bittorrent_metainfo_numpieces(cbm);
	cg_bittorrent_metainfo_allocpieceinfo(cbm, numPieces);

	if (!cg_bittorrent_metainfo_allocateitfield(cbm))
		return FALSE;

	return TRUE;
}
