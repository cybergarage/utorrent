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
* cg_bittorrent_propertymgr_getfileindex
****************************************/

BOOL cg_bittorrent_propertymgr_isvalidated(CgBittorrentPropertyMgr *propmgr)
{
	/* Metainfo */
	if (!cg_bittorrent_propertymgr_getsetvaluefunc(propmgr))
		return FALSE;
	if (!cg_bittorrent_propertymgr_getgetvaluefunc(propmgr))
		return FALSE;
	return TRUE;
}
