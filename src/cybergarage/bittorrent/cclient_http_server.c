/******************************************************************
*
*	CyberBittorrent for C
*
*	Copyright (C) Satoshi Konno 2007
*
*	File: cclient_http_server.c
*
*	Revision:
*
*	08/04/07
*		- first revision
*
******************************************************************/

#include <cybergarage/bittorrent/cclient.h>
#include <cybergarage/soap/csoap.h>

/****************************************
* cg_bittorrent_client_getrequestrecieved
****************************************/

static void cg_bittorrent_client_badrequestrecieved(CgBittorrentClient *cbc, CgHttpRequest *httpReq)
{
	CgSoapResponse *soapRes;
	CgHttpResponse *httpRes;
/*
	httpReq = cg_soap_request_gethttprequest(soapReq);
	
	soapRes = cg_soap_response_new();
	cg_upnp_control_soap_response_setfaultresponse(soapRes, code, cg_upnp_status_code2string(code));
	httpRes = cg_soap_response_gethttpresponse(soapRes);
	cg_http_request_postresponse(httpReq, httpRes);
	cg_soap_response_delete(soapRes);
*/
}

/****************************************
* cg_bittorrent_client_getrequestrecieved
****************************************/

static void cg_bittorrent_client_getrequestrecieved(CgBittorrentClient *cbc, CgHttpRequest *httpReq)
{
	CgNetURL *url;
	char *urlStr;
	char *urlPath;

	urlStr = cg_http_request_geturi(httpReq);

	if (cg_strlen(urlStr) <= 0) {
		cg_http_request_postbadrequest(httpReq);
		return;
	}

	url = cg_net_url_new();
	cg_net_url_set(url, urlStr);
	urlPath = cg_net_url_getpath(url);
	if (cg_strlen(urlPath) <= 0) {
		cg_net_url_delete(url);
		cg_http_request_postbadrequest(httpReq);
		return;
	}

	/*
	CgString *descStr;
	char *url;
	char *ifAddr;
	CgUpnpService *embService;
	CgUpnpDevice *embDev;
	CgHttpResponse *httpRes;
	
	cg_log_debug_l4("Entering...\n");

	url = cg_http_request_geturi(httpReq);
	if (cg_strlen(url) <= 0) {
		cg_http_request_postbadrequest(httpReq);
		return;
	}

	descStr = cg_string_new();	
	ifAddr = cg_http_request_getlocaladdress(httpReq);

	cg_log_debug_s("Requested: |%s|, description: |%s|\n", url, cg_string_getvalue(dev->descriptionURI));
	if (cg_upnp_device_isdescriptionuri(dev, url) == TRUE) {
		cg_upnp_device_getdescription(dev, ifAddr, descStr);
	}
	else if ((embService = cg_upnp_device_getservicebyscpdurl(dev, url)) != NULL) {
		cg_upnp_service_getdescription(embService, descStr);
	}
	else if ((embDev = cg_upnp_device_getdevicebydescriptionuri(dev, url)) != NULL) {
		cg_upnp_device_getdescription(embDev, ifAddr, descStr);
	} else {
		cg_http_request_poststatuscode(httpReq, CG_HTTP_STATUS_NOT_FOUND);
		cg_string_delete(descStr);
		return;
	}
	
	httpRes = cg_http_response_new();
	cg_http_response_setstatuscode(httpRes, CG_HTTP_STATUS_OK);
	cg_http_response_setcontenttype(httpRes, CG_XML_CONTENT_TYPE);
	cg_http_response_setcontent(httpRes, cg_string_getvalue(descStr));
	cg_http_response_setcontentlength(httpRes, cg_string_length(descStr));
	
	if (cg_http_request_isheadrequest(httpReq) == TRUE)
	{
		cg_http_response_setcontent(httpRes, NULL);
	}
	
	cg_http_response_print(httpRes);
	
	cg_http_request_postresponse(httpReq, httpRes);
	cg_http_response_delete(httpRes);	

	cg_string_delete(descStr);	

	cg_log_debug_l4("Leaving...\n");
*/
	cg_net_url_delete(url);

}

/****************************************
* cg_bittorrent_client_httplistener
****************************************/

void cg_bittorrent_client_httplistener(CgHttpRequest *httpReq)
{
	CgBittorrentClient *cbc;
	CgString *unescapedUrl;
	char *url;
	
	cbc = (CgBittorrentClient *)cg_http_request_getuserdata(httpReq);
	if (!cbc) {
		cg_http_request_postbadrequest(httpReq);
		return;
	}

	/* Unescape URI */
	url = cg_http_request_geturi(httpReq);
	if (0 < cg_strlen(url)) {
		unescapedUrl = cg_string_new();
		cg_net_uri_unescapestring(url, 0, unescapedUrl);
		if (0 < cg_string_length(unescapedUrl))
			cg_http_request_seturi(httpReq, cg_string_getvalue(unescapedUrl));
		cg_string_delete(unescapedUrl);
	}

	if (cg_http_request_isgetrequest(httpReq) == TRUE) {
		cg_bittorrent_client_getrequestrecieved(cbc, httpReq);
		return;
	}

	cg_http_request_postbadrequest(httpReq);
}

