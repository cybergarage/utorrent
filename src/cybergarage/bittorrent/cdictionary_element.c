/******************************************************************
*
*	CyberBittorrent for C
*
*	Copyright (C) Satoshi Konno 2007
*
*	File: cdictionary.c
*
*	Revision:
*
*	02/09/07
*		- first revision
*
******************************************************************/

#include <cybergarage/bittorrent/cdictionary.h>

/****************************************
* cg_bittorrent_dictionary_element_new
****************************************/

CgBittorrentDictionaryElement *cg_bittorrent_dictionary_element_new()
{
	CgBittorrentDictionaryElement *cbdm;

	cbdm = (CgBittorrentDictionaryElement *)calloc(sizeof(char), sizeof(CgBittorrentDictionaryElement));
	if (!cbdm)
		return NULL;

	cg_list_node_init((CgList *)cbdm);

	cbdm->key = NULL;
	cbdm->value = NULL;

	return cbdm;
}

/****************************************
* cg_bittorrent_dictionary_element_delete
****************************************/

void cg_bittorrent_dictionary_element_delete(CgBittorrentDictionaryElement *cbdm)
{
	if (!cbdm)
		return;

	if (cbdm->key)
		cg_bittorrent_bencoding_delete(cbdm->key);
	if (cbdm->value)
		cg_bittorrent_bencoding_delete(cbdm->value);

	free(cbdm);
}

/****************************************
* cg_bittorrent_dictionary_element_setkey
****************************************/

void cg_bittorrent_dictionary_element_setkey(CgBittorrentDictionaryElement *cbdm, CgBittorrentBencoding *cbb)
{
	if (cbdm->key)
		cg_bittorrent_bencoding_delete(cbdm->key);
	cbdm->key = cbb;
}

/****************************************

* cg_bittorrent_dictionary_element_setvalue
****************************************/

void cg_bittorrent_dictionary_element_setvalue(CgBittorrentDictionaryElement *cbdm, CgBittorrentBencoding *cbb)
{
	if (cbdm->value)
		cg_bittorrent_bencoding_delete(cbdm->value);
	cbdm->value = cbb;
}
