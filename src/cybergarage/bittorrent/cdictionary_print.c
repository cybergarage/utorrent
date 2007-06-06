/******************************************************************
*
*	CyberBittorrent for C
*
*	Copyright (C) Satoshi Konno 2007
*
*	File: cdictionary_print.c
*
*	Revision:
*
*	03/06/07
*		- first revision
*
******************************************************************/

#include <cybergarage/bittorrent/cdictionary.h>

/****************************************
* cg_bittorrent_dictionary_print
****************************************/

static int gDictionaryIndent;

#if defined(DEBUG) || defined(_DEBUG) || defined(HAVE_PRINTF)
void cg_bittorrent_dictionary_print(CgBittorrentDictionary *cbd)
{
	CgBittorrentDictionaryElement *dirElem;
	CgBittorrentBencoding *benKey;
	CgBittorrentBencoding *benVal;
	int n;

	if (!cbd)
		return;

	gDictionaryIndent++;

	for (dirElem=cg_bittorrent_dictionary_gets(cbd); dirElem; dirElem=cg_bittorrent_dictionary_element_next(dirElem)) {
		benKey = cg_bittorrent_dictionary_element_getkey(dirElem);
		benVal = cg_bittorrent_dictionary_element_getvalue(dirElem);
		if (!benKey || !benVal)
			continue;
		for (n=0; n<gDictionaryIndent; n++)
			printf("\t");
		cg_bittorrent_bencoding_print(benKey); printf(" ");
		if (cg_bittorrent_bencoding_isdictionary(benVal)) {
			printf("\n");
			cg_bittorrent_dictionary_print(cg_bittorrent_bencoding_getdictionary(benVal));
		}
		else {
			cg_bittorrent_bencoding_print(benVal);
			printf("\n");
		}
	}

	gDictionaryIndent--;
}
#endif

/****************************************
* cg_bittorrent_dictionary_setprintindent
****************************************/

void cg_bittorrent_dictionary_setprintindent(int indent)
{
	gDictionaryIndent = indent;
}
