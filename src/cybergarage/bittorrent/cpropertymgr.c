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
	CgBittorrentPropertyMgr *propmgr;

	propmgr = (CgBittorrentPropertyMgr *)malloc(sizeof(CgBittorrentPropertyMgr));
	if (!propmgr)
		return NULL;

	/* Value */
	cg_bittorrent_propertymgr_setsetvaluefunc(propmgr, NULL);
	cg_bittorrent_propertymgr_setgetvaluefunc(propmgr, NULL);

	return propmgr;
}

/****************************************
* cg_bittorrent_propertymgr_delete
****************************************/

void cg_bittorrent_propertymgr_delete(CgBittorrentPropertyMgr *propmgr)
{
	if (!propmgr)
		return;

	free(propmgr);
}

/****************************************
* cg_bittorrent_propertymgr_isvalidated
****************************************/

BOOL cg_bittorrent_propertymgr_isvalidated(CgBittorrentPropertyMgr *propmgr)
{
	if (!cg_bittorrent_propertymgr_getsetvaluefunc(propmgr))
		return FALSE;
	if (!cg_bittorrent_propertymgr_getgetvaluefunc(propmgr))
		return FALSE;
	return TRUE;
}

/****************************************
* cg_bittorrent_propertymgr_getstringvalue
****************************************/

char *cg_bittorrent_propertymgr_getstringvalue(CgBittorrentPropertyMgr *propmgr, char *category, char *key, char *buf, int bufSize, char *defaultValue)
{
	if (propmgr->getValueFunc) {
		if (propmgr->getValueFunc(propmgr, category, key, buf, bufSize))
			return buf;
	}

	return defaultValue;
}

/****************************************
* cg_bittorrent_propertymgr_isvalidated
****************************************/

BOOL cg_bittorrent_propertymgr_setintegervalue(CgBittorrentPropertyMgr *propmgr, char *category, char *key, int value)
{
	char buf[CG_STRING_INTEGER_BUFLEN];

	if (!cg_int2str(value, buf, (sizeof(buf)-1)))
		return FALSE;

	return  cg_bittorrent_propertymgr_setstringvalue(propmgr, category, key, buf);
}

/****************************************
* cg_bittorrent_propertymgr_isvalidated
****************************************/

int cg_bittorrent_propertymgr_getintegervalue(CgBittorrentPropertyMgr *propmgr, char *category, char *key, int defaultValue)
{
	char buf[CG_STRING_INTEGER_BUFLEN];

	if (propmgr->getValueFunc) {
		if (propmgr->getValueFunc(propmgr, category, key, buf, (sizeof(buf)-1)))
			return cg_str2int(buf);
	}

	return defaultValue;
}
