/******************************************************************
*
*	CyberBittorrent for C
*
*	Copyright (C) Satoshi Konno 2007
*
*	File: cbencoding.c
*
*	Revision:
*
*	02/09/07
*		- first revision
*
******************************************************************/

#include <cybergarage/bittorrent/cbencoding.h>
#include <cybergarage/bittorrent/csha1.h>

/****************************************
* cg_bittorrent_bencoding_new
****************************************/

CgBittorrentBencoding *cg_bittorrent_bencoding_new()
{
	CgBittorrentBencoding *cbb;

	cbb = (CgBittorrentBencoding *)malloc(sizeof(CgBittorrentBencoding));
	if (!cbb)
		return NULL;

	cg_list_node_init((CgList *)cbb);

	cg_bittorrent_bencoding_settype(cbb, CG_BITTORRENT_BENCODING_NONE);
	cg_bittorrent_bencoding_setlength(cbb, 0);

	return cbb;
}

/****************************************
* cg_bittorrent_bencoding_delete
****************************************/

void cg_bittorrent_bencoding_delete(CgBittorrentBencoding *cbb)
{
	if (!cbb)
		return;

	cg_bittorrent_bencoding_clear(cbb);

	free(cbb);
}

/****************************************
* cg_bittorrent_bencoding_clear
****************************************/

void cg_bittorrent_bencoding_clear(CgBittorrentBencoding *cbb)
{
	if (!cbb)
		return;

	switch (cbb->type) {
	case CG_BITTORRENT_BENCODING_STRING:
		{
			if (cbb->data.sval)
				free(cbb->data.sval);
		}
		break;
	case CG_BITTORRENT_BENCODING_LIST:
		{
			cg_bittorrent_bencodinglist_clear(cbb);
		}
		break;
	}

	cbb->type = CG_BITTORRENT_BENCODING_NONE;
}

/****************************************
* cg_bittorrent_bencoding_setstring
****************************************/

void cg_bittorrent_bencoding_setstring(CgBittorrentBencoding *cbb, char *value, int valSize)
{
	int n;

	if (!cbb)
		return;

	cg_bittorrent_bencoding_clear(cbb);

	cbb->data.sval = (char *)malloc((valSize+1) * sizeof(char));
	if (!cbb->data.sval)
		return;

	for (n=0; n<valSize; n++)
		cbb->data.sval[n] = '\0';
	memcpy(cbb->data.sval, value, valSize);
	cbb->data.sval[valSize] = '\0';

	cbb->type = CG_BITTORRENT_BENCODING_STRING;
}

/****************************************
* cg_bittorrent_bencoding_setinteger
****************************************/

void cg_bittorrent_bencoding_setinteger(CgBittorrentBencoding *cbb, CgInt64 value)
{
	if (!cbb)
		return;

	cg_bittorrent_bencoding_clear(cbb);

	cbb->data.ival = value;

	cbb->type = CG_BITTORRENT_BENCODING_INTEGER;
}

/****************************************
* cg_bittorrent_bencoding_setlist
****************************************/

void cg_bittorrent_bencoding_setlist(CgBittorrentBencoding *cbb)
{
	if (!cbb)
		return;

	cg_bittorrent_bencoding_clear(cbb);

	cg_list_header_init((CgList *)cbb);

	cbb->type = CG_BITTORRENT_BENCODING_LIST;
}

/****************************************
* cg_bittorrent_bencoding_setdictionary
****************************************/

void cg_bittorrent_bencoding_setdictionary(CgBittorrentBencoding *cbb, void *value)
{
	if (!cbb)
		return;

	cg_bittorrent_bencoding_clear(cbb);

	cbb->data.dval = value;

	cbb->type = CG_BITTORRENT_BENCODING_DICTIONARY;
}

/****************************************
* cg_bittorrent_bencoding_tosha1
****************************************/

BOOL cg_bittorrent_bencoding_tosha1(CgBittorrentBencoding *cbb, CgByte *buf)
{
	CgString *str;
	CgSHA1Context sha;
	int err;

	str = cg_string_new();
	if (cg_bittorrent_bencoding_tostring(cbb, str) <=0) {
		cg_string_delete(str);
		return FALSE;
	}

	err = cg_sha1_reset(&sha);
	if (!err) {
		err = cg_sha1_input(&sha, cg_string_getvalue(str), cg_string_length(str));
		if (!err)
			err = cg_sha1_result(&sha, buf);
	}

	cg_string_delete(str);

	return (err ? FALSE : TRUE);
}

