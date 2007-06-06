/******************************************************************
*
*	CyberBittorrent for C
*
*	Copyright (C) Satoshi Konno 2007
*
*	File: cbencoding_print.c
*
*	Revision:
*
*	03/06/07
*		- first revision
*
******************************************************************/

#include <cybergarage/bittorrent/cbencoding.h>
#include <cybergarage/bittorrent/cdictionary.h>

/****************************************
* cg_bittorrent_bencoding_print
****************************************/

#if defined(DEBUG) || defined(_DEBUG) || defined(HAVE_PRINTF)
void cg_bittorrent_bencoding_print(CgBittorrentBencoding *cbb)
{
	CgBittorrentBencoding *cbbItem;
	char intBuf[CG_STRING_LONGLONG_BUFLEN];

	if (!cbb)
		return;

	switch (cbb->type) {
	case CG_BITTORRENT_BENCODING_STRING:
		{
			printf("%s ", cbb->data.sval);
		}
		break;
	case CG_BITTORRENT_BENCODING_INTEGER:
		{
			cg_longlong2str(cbb->data.ival, intBuf, sizeof(intBuf));
			printf("%s ", intBuf);
		}
		break;
	case CG_BITTORRENT_BENCODING_LIST:
		{
			for (cbbItem = cg_bittorrent_bencoding_getlists(cbb); cbbItem; cbbItem = cg_bittorrent_bencoding_next(cbbItem))
				cg_bittorrent_bencoding_print(cbbItem);
		}
		break;
	case CG_BITTORRENT_BENCODING_DICTIONARY:
		{
			cg_bittorrent_dictionary_print(cg_bittorrent_bencoding_getdictionary(cbb));
		}
		break;
	}
}
#endif
