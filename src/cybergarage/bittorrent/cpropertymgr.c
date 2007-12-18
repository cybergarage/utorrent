/******************************************************************
*
*	CyberBittorrent for C
*
*	Copyright (C) Satoshi Konno 2007
*
*	File: cpropertymgr.c
*
*	Revision:
*
*	07/12/08
*		- first revision
*
******************************************************************/

#include <cybergarage/bittorrent/cpropertymgr.h>

#include <stdlib.h>

/****************************************
* cg_bittorrent_propertymgr_new
****************************************/

CgBittorrentPropertyMgr *cg_bittorrent_propertymgr_new()
{
	CgBittorrentPropertyMgr *propMgr;

	propMgr = (CgBittorrentPropertyMgr *)malloc(sizeof(CgBittorrentPropertyMgr));
	if (!propMgr)
		return NULL;

	/* Value */
	cg_bittorrent_propertymgr_setsetvaluefunc(propMgr, NULL);
	cg_bittorrent_propertymgr_setgetvaluefunc(propMgr, NULL);

	return propMgr;
}

/****************************************
* cg_bittorrent_propertymgr_delete
****************************************/

void cg_bittorrent_propertymgr_delete(CgBittorrentPropertyMgr *propMgr)
{
	if (!propMgr)
		return;

	free(propMgr);
}

/****************************************
* cg_bittorrent_propertymgr_isvalidated
****************************************/

BOOL cg_bittorrent_propertymgr_isvalidated(CgBittorrentPropertyMgr *propMgr)
{
	if (!propMgr)
		return FALSE;

	if (!cg_bittorrent_propertymgr_getsetvaluefunc(propMgr))
		return FALSE;
	if (!cg_bittorrent_propertymgr_getgetvaluefunc(propMgr))
		return FALSE;

	return TRUE;
}

/****************************************
* cg_bittorrent_propertymgr_getstringvalue
****************************************/

char *cg_bittorrent_propertymgr_getstringvalue(CgBittorrentPropertyMgr *propMgr, char *category, char *key, char *buf, int bufSize, char *defaultValue)
{
	if (!propMgr)
		return defaultValue;

	if (propMgr->getValueFunc) {
		if (propMgr->getValueFunc(propMgr, category, key, buf, bufSize))
			return buf;
	}

	return defaultValue;
}

/****************************************
* cg_bittorrent_propertymgr_isvalidated
****************************************/

BOOL cg_bittorrent_propertymgr_setintegervalue(CgBittorrentPropertyMgr *propMgr, char *category, char *key, int value)
{
	char buf[CG_STRING_INTEGER_BUFLEN];

	if (!propMgr)
		return FALSE;

	if (!cg_int2str(value, buf, (sizeof(buf)-1)))
		return FALSE;

	return  cg_bittorrent_propertymgr_setstringvalue(propMgr, category, key, buf);
}

/****************************************
* cg_bittorrent_propertymgr_isvalidated
****************************************/

int cg_bittorrent_propertymgr_getintegervalue(CgBittorrentPropertyMgr *propMgr, char *category, char *key, int defaultValue)
{
	char buf[CG_STRING_INTEGER_BUFLEN];

	if (!propMgr)
		return defaultValue;

	if (propMgr->getValueFunc) {
		if (propMgr->getValueFunc(propMgr, category, key, buf, (sizeof(buf)-1)))
			return cg_str2int(buf);
	}

	return defaultValue;
}
