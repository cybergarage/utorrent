/******************************************************************
*
*	CyberBittorrent for C
*
*	Copyright (C) Satoshi Konno 2007
*
*	File: cmetainfo_print.c
*
*	Revision:
*
*	02/07/07
*		- first revision
*
******************************************************************/

#include <cybergarage/bittorrent/cmetainfo.h>

/****************************************
* cg_bittorrent_metainfo_print
****************************************/

#if defined(DEBUG) || defined(_DEBUG) || defined(HAVE_PRINTF)
void cg_bittorrent_metainfo_print(CgBittorrentMetainfo *cbm)
{
	if (!cbm)
		return;

	cg_bittorrent_dictionary_setprintindent(-1);
	cg_bittorrent_dictionary_print(cg_bittorrent_metainfo_getdictionary(cbm));
}
#endif
