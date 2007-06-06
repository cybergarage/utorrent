/******************************************************************
*
*	CyberBittorrent for C
*
*	Copyright (C) Satoshi Konno 2007
*
*	File: cdictionary_string.c
*
*	Revision:
*
*	03/12/07
*		- first revision
*
******************************************************************/

#include <cybergarage/bittorrent/cdictionary.h>

/****************************************
* cg_bittorrent_dictionary_tostring
****************************************/

void cg_bittorrent_dictionary_tostring(CgBittorrentDictionary *cbd, CgString *str)
{
	CgBittorrentDictionaryElement *dirElem;
	CgBittorrentBencoding *benKey;
	CgBittorrentBencoding *benVal;
	char dirDelim[] = {CG_BITTORRENT_BENCODING_DICTIONARY_ID, '\0'};
	char endDelim[] = {CG_BITTORRENT_BENCODING_TRAIL_ID, '\0'};

	if (!cbd)
		return;

	cg_string_addvalue(str, dirDelim);

	for (dirElem=cg_bittorrent_dictionary_gets(cbd); dirElem; dirElem=cg_bittorrent_dictionary_element_next(dirElem)) {
		benKey = cg_bittorrent_dictionary_element_getkey(dirElem);
		benVal = cg_bittorrent_dictionary_element_getvalue(dirElem);
		if (!benKey || !benVal)
			continue;
		cg_bittorrent_bencoding_tostring(benKey, str);
		if (cg_bittorrent_bencoding_isdictionary(benVal)) {
			cg_bittorrent_dictionary_tostring(cg_bittorrent_bencoding_getdictionary(benVal), str);
		}
		else {
			cg_bittorrent_bencoding_tostring(benVal, str);
		}
	}

	cg_string_addvalue(str, endDelim);
}
