/******************************************************************
*
*	CyberBittorrent for C
*
*	Copyright (C) Satoshi Konno 2007
*
*	File: cbencoding_parse.c
*
*	Revision:
*
*	02/13/07
*		- first revision
*
******************************************************************/

#include <cybergarage/bittorrent/cdictionary.h>

/****************************************
* cg_bittorrent_bencoding_char2type
****************************************/

static int cg_bittorrent_bencoding_char2type(char c)
{
	switch (c) {
	case CG_BITTORRENT_BENCODING_INTEGER_ID:
		return CG_BITTORRENT_BENCODING_INTEGER;
	case CG_BITTORRENT_BENCODING_LIST_ID:
		return CG_BITTORRENT_BENCODING_LIST;
	case CG_BITTORRENT_BENCODING_DICTIONARY_ID:
		return CG_BITTORRENT_BENCODING_DICTIONARY;
	}
	if ('0' <= c && c <= '9')
		return CG_BITTORRENT_BENCODING_STRING;
	return CG_BITTORRENT_BENCODING_NONE;
}

/****************************************
* cg_bittorrent_bencoding_parse
****************************************/

BOOL cg_bittorrent_bencoding_parse(char *data, CgBittorrentBencoding **cbb, int *offset)
{
	int dataType;
	char intValBuf[CG_STRING_LONG_BUFLEN+1];
	int strLen;
	char delimStr[] = {CG_BITTORRENT_BENCODING_DELIM, '\0'};
	char trailStr[] = {CG_BITTORRENT_BENCODING_TRAIL_ID, '\0'};
	int delimIdx;
	int trailIdx;
	int listOffset;
	CgBittorrentBencoding *listItem;
	CgBittorrentDictionary *cbd;

	if (!data)
		return FALSE;

	*offset = -1;

	*cbb = cg_bittorrent_bencoding_new();
	if (!*cbb)
		return FALSE;

	dataType = cg_bittorrent_bencoding_char2type(data[0]);
	switch (dataType) {
	case CG_BITTORRENT_BENCODING_STRING:
		{
			delimIdx = cg_strstr(data, delimStr);
			if (delimIdx < 0 || CG_STRING_INTEGER_BUFLEN < delimIdx)
				break;
			memcpy(intValBuf, data, delimIdx);
			intValBuf[delimIdx] = '\0';
			strLen = cg_str2int(intValBuf);
			cg_bittorrent_bencoding_setstring(*cbb, (data+delimIdx+1), strLen);
			cg_bittorrent_bencoding_setlength((*cbb), strLen);
			*offset = delimIdx + strLen + 1;
		}
		break;
	case CG_BITTORRENT_BENCODING_INTEGER:
		{
			trailIdx = cg_strstr(data, trailStr);
			if (trailIdx < 1 || CG_STRING_INTEGER_BUFLEN < trailIdx)
				break;
			memcpy(intValBuf, (data+1), (trailIdx-1));
			intValBuf[(trailIdx-1)] = '\0';
			#if defined(CG_USE_INT64)
			cg_bittorrent_bencoding_setinteger(*cbb, cg_str2longlong(intValBuf));
			#else
			cg_bittorrent_bencoding_setinteger(*cbb, cg_str2long(intValBuf));
			#endif
			cg_bittorrent_bencoding_setlength((*cbb), sizeof(CgInt64));
			*offset = trailIdx + 1;
		}
		break;
	case CG_BITTORRENT_BENCODING_LIST:
		{
			cg_bittorrent_bencoding_setlist(*cbb);
			cg_bittorrent_bencoding_setlength((*cbb), 0);
			*offset = 1;
			while (data[*offset] !=  CG_BITTORRENT_BENCODING_TRAIL_ID && data[*offset] !=  '\0') {
				if (cg_bittorrent_bencoding_parse(data + *offset, &listItem, &listOffset) == FALSE) {
					*offset = -1;
					break;
				}
				cg_bittorrent_bencodinglist_add(*cbb, listItem);
				*offset += listOffset;
			}
			*offset += 1;
		}
		break;
	case CG_BITTORRENT_BENCODING_DICTIONARY:
		{
			cbd = cg_bittorrent_dictionary_new();
			if (!cbd) {
				*offset = -1;
				break;
			}
			if (cg_bittorrent_dictionary_parse(cbd, data, &listOffset) == FALSE) {
				*offset = -1;
				break;
			}
			cg_bittorrent_bencoding_setdictionary(*cbb, cbd);
			cg_bittorrent_bencoding_setlength((*cbb), 0);
			*offset += listOffset;
			*offset += 1;
		}
		break;
	}

	if (*offset < 0)
		cg_bittorrent_bencoding_delete(*cbb);

	return (0 <= *offset) ? TRUE : FALSE;
}

