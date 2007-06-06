/******************************************************************
*
*	CyberBittorrent for C
*
*	Copyright (C) Satoshi Konno 2007
*
*	File: cbencoding_string.c
*
*	Revision:
*

*	03/12/07
*		- first revision
*
******************************************************************/

#include <cybergarage/bittorrent/cbencoding.h>
#include <cybergarage/bittorrent/cdictionary.h>

/****************************************
* cg_bittorrent_bencoding_tostring
****************************************/

int cg_bittorrent_bencoding_tostring(CgBittorrentBencoding *cbb, CgString *str)
{
	CgBittorrentBencoding *cbbItem;

	char intBuf[CG_STRING_LONGLONG_BUFLEN];
	char benDelim[] = {CG_BITTORRENT_BENCODING_DELIM, '\0'};
	char intDelim[] = {CG_BITTORRENT_BENCODING_INTEGER_ID, '\0'};
	char listDelim[] = {CG_BITTORRENT_BENCODING_LIST_ID, '\0'};
	char endDelim[] = {CG_BITTORRENT_BENCODING_TRAIL_ID, '\0'};
	
	if (!cbb)
		return 0;

	switch (cbb->type) {
	case CG_BITTORRENT_BENCODING_STRING:
		{
			cg_int2str(cg_bittorrent_bencoding_getlength(cbb), intBuf, CG_STRING_INTEGER_BUFLEN);
			cg_string_addvalue(str, intBuf);
			cg_string_addvalue(str, benDelim);
			cg_string_naddvalue(str, cbb->data.sval, cg_bittorrent_bencoding_getlength(cbb));
		}
		break;
	case CG_BITTORRENT_BENCODING_INTEGER:
		{
			cg_string_addvalue(str, intDelim);
			cg_longlong2str(cbb->data.ival, intBuf, sizeof(intBuf));
			cg_string_addvalue(str, intBuf);
			cg_string_addvalue(str, endDelim);
		}
		break;
	case CG_BITTORRENT_BENCODING_LIST:
		{
			cg_string_addvalue(str, listDelim);
			for (cbbItem = cg_bittorrent_bencoding_getlists(cbb); cbbItem; cbbItem = cg_bittorrent_bencoding_next(cbbItem))
				cg_bittorrent_bencoding_tostring(cbbItem, str);
			cg_string_addvalue(str, endDelim);
		}
		break;
	case CG_BITTORRENT_BENCODING_DICTIONARY:
		{
			cg_bittorrent_dictionary_tostring(cg_bittorrent_bencoding_getdictionary(cbb), str);
		}
		break;
	}

	return cg_string_length(str);
}
