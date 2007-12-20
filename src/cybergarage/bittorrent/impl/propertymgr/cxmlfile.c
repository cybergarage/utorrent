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
#include <cybergarage/io/cfile.h>

#include <stdlib.h>

/****************************************
* cg_bittorrent_xmlfile_propertymgr_getpath
****************************************/

static char *cg_bittorrent_xmlfile_propertymgr_getpath(CgBittorrentPropertyMgr *propMgr, CgString *buf)
{
	return cg_string_getvalue(buf);
}

/****************************************
* cg_bittorrent_xmlfile_propertymgr_load
****************************************/

static BOOL cg_bittorrent_xmlfile_propertymgr_load(CgBittorrentPropertyMgr *propMgr)
{
	CgXmlNode *rootNode;
	CgString *buf;
	CgFile *file;
	BOOL loadRes;
	CgXmlParser *xmlParser;
	BOOL parseRes;

	rootNode = cg_bittorrent_xmlfile_propertymgr_getrootnode(propMgr);
	if (!rootNode)
		return FALSE;

	file = cg_file_new();
	if (!file)
		return FALSE;

	buf = cg_string_new();
	if (!buf)
		return FALSE;
	cg_file_setname(file, cg_bittorrent_xmlfile_propertymgr_getpath(propMgr, buf));
	cg_file_delete(file);
	loadRes = cg_file_load(file);

	cg_string_delete(buf);

	if (!loadRes) {
		cg_file_delete(file);
		return FALSE;
	}

	xmlParser = cg_xml_parser_new();
	if (!xmlParser) {
		cg_file_delete(file);
		return FALSE;
	}
	parseRes = cg_xml_parse(xmlParser, rootNode, cg_file_getcontent(file), cg_file_getlength(file));
	cg_xml_parser_delete(xmlParser);

	cg_file_delete(file);

	return parseRes;
}

/****************************************
* cg_bittorrent_xmlfile_propertymgr_save
****************************************/

static BOOL cg_bittorrent_xmlfile_propertymgr_save(CgBittorrentPropertyMgr *propMgr)
{
	CgString *buf;
	CgXmlNode *rootNode;
	CgFile *file;
	BOOL saveRes;

	rootNode = cg_bittorrent_xmlfile_propertymgr_getrootnode(propMgr);
	if (!rootNode)
		return FALSE;

	buf = cg_string_new();
	if (!buf)
		return FALSE;

	cg_xml_node_tostring(rootNode, TRUE, buf);

	file = cg_file_new();
	if (!file) {
		cg_string_delete(buf);
		return FALSE;
	}
	cg_file_setcontent(file, cg_string_getvalue(buf));
	cg_file_setname(file, cg_bittorrent_xmlfile_propertymgr_getpath(propMgr, buf));
	saveRes = cg_file_save(file);
	cg_file_delete(file);

	cg_string_delete(buf);

	return saveRes;
}

/****************************************
* cg_bittorrent_xmlfile_propertymgr_setvalue
****************************************/

static BOOL cg_bittorrent_xmlfile_propertymgr_setvalue(CgBittorrentPropertyMgr *propMgr, char *category, char *key, char *value)
{
	return TRUE;
}

/****************************************
* cg_bittorrent_xmlfile_propertymgr_getvalue
****************************************/

static BOOL cg_bittorrent_xmlfile_propertymgr_getvalue(CgBittorrentPropertyMgr *propMgr, char *category, char *key, char *buf, int bufSize)
{
	return TRUE;
}

/****************************************
* cg_bittorrent_xmlfile_propertymgr_new
****************************************/

CgBittorrentPropertyMgr *cg_bittorrent_xmlfile_propertymgr_new()
{
	CgBittorrentPropertyMgr *propMgr;
	CgBittorrentXmlFilePropertyMgrData *data;

	propMgr = cg_bittorrent_propertymgr_new();
	if (!propMgr)
		return NULL;

	data  = (CgBittorrentXmlFilePropertyMgrData *)malloc(sizeof(CgBittorrentXmlFilePropertyMgrData));
	if (!data) {
		free(propMgr);
		return NULL;
	}
	data->rootNode = cg_xml_nodelist_new();
	data->directory = cg_string_new();
	data->filename = cg_string_new();

	if (!data->rootNode || !data->directory || !data->filename) {
		cg_bittorrent_xmlfile_propertymgr_delete(propMgr);
		return FALSE;
	}

	cg_bittorrent_propertymgr_setsetvaluefunc(propMgr, cg_bittorrent_xmlfile_propertymgr_setvalue);
	cg_bittorrent_propertymgr_setgetvaluefunc(propMgr, cg_bittorrent_xmlfile_propertymgr_getvalue);
	cg_bittorrent_propertymgr_setuserdata(propMgr, data);

	return propMgr;
}

/****************************************
* cg_bittorrent_xmlfile_propertymgr_delete
****************************************/

void cg_bittorrent_xmlfile_propertymgr_delete(CgBittorrentPropertyMgr *propMgr)
{
	CgBittorrentXmlFilePropertyMgrData *data;

	if (!propMgr)
		return;

	data = cg_bittorrent_xmlfile_propertymgr_getuserdata(propMgr);
	if (data->rootNode)
		cg_xml_nodelist_delete(data->rootNode);

	cg_bittorrent_xmlfile_propertymgr_delete(propMgr);
}
