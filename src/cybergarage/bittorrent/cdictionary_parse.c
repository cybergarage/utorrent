/******************************************************************
*
*	CyberBittorrent for C
*
*	Copyright (C) Satoshi Konno 2007
*
*	File: cdictionary_parse.c
*
*	Revision:
*
*	02/13/07
*		- first revision
*
******************************************************************/

#include <cybergarage/bittorrent/cdictionary.h>

/****************************************
* cg_bittorrent_dictionary_element_parse
****************************************/

BOOL cg_bittorrent_dictionary_parse(CgBittorrentDictionary *cbd, char *data, int *offset)
{
	CgBittorrentDictionaryElement *cbdElem;
	CgBittorrentBencoding *cbbKey;
	CgBittorrentBencoding *cbbValue;
	int benOffset;

	if (!data)
		return FALSE;

	if (data[0] !=  CG_BITTORRENT_BENCODING_DICTIONARY_ID)
		return FALSE;

	*offset = 1;
	while (data[*offset] !=  CG_BITTORRENT_BENCODING_TRAIL_ID) {
		cbdElem = cg_bittorrent_dictionary_element_new();
		if (!cbdElem) {
			*offset = -1;
			break;
		}
		if (cg_bittorrent_bencoding_parse(data + *offset, &cbbKey, &benOffset) == FALSE) {
			*offset = -1;
			break;
		}
		if (cg_bittorrent_bencoding_isstring(cbbKey) == FALSE) {
			cg_bittorrent_bencoding_delete(cbbKey);
			*offset = -1;
			break;
		}
		cg_bittorrent_dictionary_element_setkey(cbdElem, cbbKey);
		*offset += benOffset;
		if (cg_bittorrent_bencoding_parse(data + *offset, &cbbValue, &benOffset) == FALSE) {
			*offset = -1;
			break;
		}
		cg_bittorrent_dictionary_element_setvalue(cbdElem, cbbValue);
		*offset += benOffset;
		cg_bittorrent_dictionary_add(cbd, cbdElem);
	}

	if (0 < *offset) {
		if (data[*offset] ==  CG_BITTORRENT_BENCODING_TRAIL_ID)
			*offset += 1;
	}
	return (0 < *offset) ? TRUE : FALSE;
}

