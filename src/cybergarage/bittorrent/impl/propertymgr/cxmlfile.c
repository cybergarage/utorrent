/******************************************************************
*
*	CyberBittorrent for C
*
*	Copyright (C) Satoshi Konno 2007
*
*	File: cxmlfile.c
*
*	Revision:
*
*	12/11/07
*		- first revision
*
******************************************************************/

#include <cybergarage/bittorrent/impl/propertymgr/cxmlfile.h>

#include <stdlib.h>

/****************************************
* cg_bittorrent_xmlfile_propertymgr_open
****************************************/

static BOOL cg_bittorrent_xmlfile_propertymgr_open(CgBittorrentPropertyMgr *propmgr)
{
	return TRUE;
}

/****************************************
* cg_bittorrent_xmlfile_propertymgr_close
****************************************/

static BOOL cg_bittorrent_xmlfile_propertymgr_close(CgBittorrentPropertyMgr *propmgr)
{
	return TRUE;
}

/****************************************
* cg_bittorrent_xmlfile_propertymgr_setvalue
****************************************/

static BOOL cg_bittorrent_xmlfile_propertymgr_setvalue(CgBittorrentPropertyMgr *propmgr, char *category, char *key, char *value)
{
	return TRUE;
}

/****************************************
* cg_bittorrent_xmlfile_propertymgr_getvalue
****************************************/

static BOOL cg_bittorrent_xmlfile_propertymgr_getvalue(CgBittorrentPropertyMgr *propmgr, char *category, char *key, char *buf, int bufSize)
{
	return TRUE;
}

/****************************************
* cg_bittorrent_xmlfile_propertymgr_new
****************************************/

CgBittorrentPropertyMgr *cg_bittorrent_xmlfile_propertymgr_new()
{
	CgBittorrentPropertyMgr *propmgr;
	CgBittorrentXmlFilePropertyMgrData *data;

	propmgr = cg_bittorrent_propertymgr_new();
	if (!propmgr)
		return NULL;

	data  = (CgBittorrentXmlFilePropertyMgrData *)malloc(sizeof(CgBittorrentXmlFilePropertyMgrData));
	if (!data) {
		free(propmgr);
		return NULL;
	}
	data->rootNode = cg_xml_nodelist_new();

	if (data->rootNode) {
		cg_bittorrent_xmlfile_propertymgr_delete(propmgr);
		return FALSE;
	}

	cg_bittorrent_propertymgr_setsetvaluefunc(propmgr, cg_bittorrent_xmlfile_propertymgr_setvalue);
	cg_bittorrent_propertymgr_setgetvaluefunc(propmgr, cg_bittorrent_xmlfile_propertymgr_getvalue);
	cg_bittorrent_propertymgr_setuserdata(propmgr, data);

	return propmgr;
}

/****************************************
* cg_bittorrent_xmlfile_propertymgr_delete
****************************************/

void cg_bittorrent_xmlfile_propertymgr_delete(CgBittorrentPropertyMgr *propmgr)
{
	CgBittorrentXmlFilePropertyMgrData *data;

	if (!propmgr)
		return;

	data = cg_bittorrent_xmlfile_propertymgr_getuserdata(propmgr);
	if (data->rootNode)
		cg_xml_nodelist_delete(data->rootNode);

	cg_bittorrent_xmlfile_propertymgr_delete(propmgr);
}
