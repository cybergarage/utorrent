/******************************************************************
*
*	CyberBittorrent for C
*
*	Copyright (C) Satoshi Konno 2007
*
*	File: cmetainfo_fetch.c
*
*	Revision:
*
*	03/20/07
*		- first revision
*
******************************************************************/

#include <cybergarage/bittorrent/cmetainfo.h>
#include <cybergarage/bittorrent/chttp.h>

/****************************************
* cg_bittorrent_metainfo_fetch
****************************************/

BOOL cg_bittorrent_metainfo_fetch(CgBittorrentMetainfo *cbm, char *url)
{
	CgString *dataStr;
	int	dataLen;
	char	*data;
	BOOL parseResult;

	dataStr = cg_string_new();
	if (!dataStr)
		return FALSE;

	if (!cg_bittorrent_http_fetch(url, dataStr)) {
		cg_string_delete(dataStr);
		return FALSE;
	}

	dataLen = cg_string_length(dataStr);

	data = (char *)malloc(dataLen+1);
	if (!data) {
		cg_string_delete(dataStr);
		return FALSE;
	}

	memcpy(data, cg_string_getvalue(dataStr), dataLen);
	data[dataLen] = '\0';

	cg_string_delete(dataStr);

	parseResult = cg_bittorrent_metainfo_parse(cbm, data, dataLen);

	free(data);

	if (parseResult) {
		cg_bittorrent_metainfo_seturl(cbm, url);
		cg_bittorrent_metainfo_setfilename(cbm, "");
		cg_bittorrent_metainfo_setidfromname(cbm, url);
	}

	return parseResult;
}
