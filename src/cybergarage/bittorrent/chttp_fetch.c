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
*	01/30/07
*		- first revision
*
******************************************************************/

#include <cybergarage/bittorrent/ctracker.h>

#include <cybergarage/http/chttp.h>
#include <sys/stat.h>

/************************************************************
* cg_bittorrent_http_fetch
************************************************************/

#define CG_BITTORRENT_HTTP_URLLEN_MAX 512

BOOL cg_bittorrent_http_fetch(char *url, CgString *str)
{
	CgNetURL *netUrl;
	CgHttpRequest *httpReq;
	CgHttpResponse *httpRes;
	int statusCode;
	char *content;
	long contentLen;
	char path[CG_BITTORRENT_HTTP_URLLEN_MAX];

	netUrl = cg_net_url_new();
	cg_net_url_set(netUrl, url);

	httpReq = cg_http_request_new();
	cg_http_request_setmethod(httpReq, CG_HTTP_GET);
	
	cg_strncpy(path, cg_net_url_getpath(netUrl), (CG_BITTORRENT_HTTP_URLLEN_MAX-1));
	if (cg_net_url_getquery(netUrl) != NULL) {
		cg_strncat(path, "?", (CG_BITTORRENT_HTTP_URLLEN_MAX-cg_strlen(path)-1));
		cg_strncat(path, cg_net_url_getquery(netUrl), (CG_BITTORRENT_HTTP_URLLEN_MAX-cg_strlen(path)-1));
	}
	
	cg_http_request_seturi(httpReq, path);
	cg_http_request_setcontentlength(httpReq, 0);
	httpRes = cg_http_request_post(httpReq, cg_net_url_gethost(netUrl), cg_net_url_getport(netUrl));
	
	statusCode = cg_http_response_getstatuscode(httpRes);

	if (statusCode != CG_HTTP_STATUS_OK) {
		cg_net_url_delete(netUrl);
		cg_http_request_delete(httpReq);
		return FALSE;
	}
	
	contentLen = (long)cg_http_response_getcontentlength(httpRes);
	content = (char *)malloc(contentLen * sizeof(char));
	memcpy(content, cg_http_response_getcontent(httpRes), contentLen);
	cg_string_setpointervalue(str, content, contentLen);

	cg_http_request_delete(httpReq);
	cg_net_url_delete(netUrl);

	return TRUE;
}
