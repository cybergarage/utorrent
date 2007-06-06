/******************************************************************
*
*	CyberBittorrent for C
*
*	Copyright (C) Satoshi Konno 2007
*
*	File: cdictionarylist.c
*
*	Revision:
*
*	02/09/07
*		- first revision
*
******************************************************************/

#include <cybergarage/bittorrent/cdictionary.h>

/****************************************
* cg_bittorrent_dictionary_new
****************************************/

CgBittorrentDictionary *cg_bittorrent_dictionary_new()
{
	CgBittorrentDictionary *cbdList;

	cbdList = (CgBittorrentDictionary *)malloc(sizeof(CgBittorrentDictionary));
	if (!cbdList)
		return NULL;

	cg_list_header_init((CgList *)cbdList);

	return cbdList;
}

/****************************************
* cg_bittorrent_dictionary_delete
****************************************/

void cg_bittorrent_dictionary_delete(CgBittorrentDictionary *cbdList)
{
	if (!cbdList)
		return;

	free(cbdList);
}

/****************************************
* cg_bittorrent_dictionary_getelementbyname
****************************************/

CgBittorrentDictionaryElement *cg_bittorrent_dictionary_getelementbyname(CgBittorrentDictionary *cbd, char *name)
{
	CgBittorrentDictionaryElement *dirElem;

	if (!cbd)
		return NULL;

	if (!name)
		return NULL;

	for (dirElem=cg_bittorrent_dictionary_gets(cbd); dirElem; dirElem=cg_bittorrent_dictionary_element_next(dirElem)) {
		CgBittorrentBencoding *benKey = cg_bittorrent_dictionary_element_getkey(dirElem);
		if (!benKey)
			continue;
		if (cg_bittorrent_bencoding_isstring(benKey) == FALSE)
			continue;
		if (cg_streq(name, cg_bittorrent_bencoding_getstring(benKey)))
			return dirElem;
	}

	return NULL;
}

/****************************************
* cg_bittorrent_dictionary_getvaluebyname
****************************************/

CgBittorrentBencoding *cg_bittorrent_dictionary_getvaluebyname(CgBittorrentDictionary *cbd, char *name)
{
	CgBittorrentDictionary *dirElem;

	if (!cbd)
		return NULL;
	
	dirElem =cg_bittorrent_dictionary_getelementbyname(cbd, name);
	if (!dirElem)
		return NULL;
	
	return cg_bittorrent_dictionary_element_getvalue(dirElem);
}

/****************************************
* cg_bittorrent_dictionary_getstringbyname
****************************************/

char *cg_bittorrent_dictionary_getstringbyname(CgBittorrentDictionary *cbd, char *name)
{
	CgBittorrentBencoding *benElem;

	benElem = cg_bittorrent_dictionary_getvaluebyname(cbd, name);
	if (!benElem)
		return NULL;
	
	return cg_bittorrent_bencoding_getstring(benElem);
}

/****************************************
* cg_bittorrent_dictionary_getintegerbyname
****************************************/

CgInt64 cg_bittorrent_dictionary_getintegerbyname(CgBittorrentDictionary *cbd, char *name)
{
	CgBittorrentBencoding *benElem;

	benElem = cg_bittorrent_dictionary_getvaluebyname(cbd, name);
	if (!benElem)
		return 0;
	
	return cg_bittorrent_bencoding_getinteger(benElem);
}

/****************************************
* cg_bittorrent_dictionary_getlistbyname
****************************************/

CgBittorrentBencodingList *cg_bittorrent_dictionary_getlistbyname(CgBittorrentDictionary *cbd, char *name)
{
	CgBittorrentBencoding *benElem;

	benElem = cg_bittorrent_dictionary_getvaluebyname(cbd, name);
	if (!benElem)
		return NULL;
	
	return cg_bittorrent_bencoding_getlist(benElem);
}
