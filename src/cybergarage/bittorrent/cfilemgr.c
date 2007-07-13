/******************************************************************
*
*	CyberBittorrent for C
*
*	Copyright (C) Satoshi Konno 2007
*
*	File: cfilemgr.c
*
*	Revision:
*
*	02/07/08
*		- first revision
*
******************************************************************/

#include <cybergarage/bittorrent/cfilemgr.h>
#include <cybergarage/util/cstring.h>

/****************************************
* cg_bittorrent_filemgr_readpiece
****************************************/

static BOOL cg_bittorrent_filemgr_readpiece(CgBittorrentFileMgr *filemgr, CgBittorrentTracker *tracker, int index, CgByte **buf)
{
	char *dstDir;

	dstDir = cg_bittorrent_filemgr_getdestinationdirectory(filemgr);
	if (cg_strlen(dstDir) <= 0)
		return FALSE;

	return TRUE;
}

/****************************************
* cg_bittorrent_filemgr_writepiece
****************************************/

static BOOL cg_bittorrent_filemgr_writepiece(CgBittorrentFileMgr *filemgr, CgBittorrentTracker *tracker, int index, CgByte *buf)
{
	return TRUE;
}

/****************************************
* cg_bittorrent_filemgr_havepiece
****************************************/

static BOOL cg_bittorrent_filemgr_havepiece(CgBittorrentFileMgr *filemgr, CgBittorrentTracker *tracker, int index)
{
	return TRUE;
}

/****************************************
* cg_bittorrent_filemgr_new
****************************************/

CgBittorrentFileMgr *cg_bittorrent_filemgr_new()
{
	CgBittorrentFileMgrData *filemgrData;
	CgBittorrentFileMgr *filemgr;


	filemgrData = (CgBittorrentFileMgrData *)malloc(sizeof(CgBittorrentFileMgrData));
	if (!filemgrData)
		return NULL;
	filemgrData->dstDir = NULL;

	filemgr = cg_bittorrent_blockdevicemgr_new();
	if (!filemgr) {
		free(filemgrData);
		return NULL;
	}

	cg_bittorrent_blockdevicemgr_setuserdata(filemgr, filemgrData);

	cg_bittorrent_blockdevicemgr_setreadpiecefunc(filemgr, cg_bittorrent_filemgr_readpiece);
	cg_bittorrent_blockdevicemgr_setwritepiecefunc(filemgr, cg_bittorrent_filemgr_writepiece);
	cg_bittorrent_blockdevicemgr_sethavepiecefunc(filemgr, cg_bittorrent_filemgr_havepiece);

	return filemgr;
}

/****************************************
* cg_bittorrent_filemgr_delete
****************************************/

void cg_bittorrent_filemgr_delete(CgBittorrentFileMgr *filemgr)
{
	CgBittorrentFileMgrData *filemgrData;

	if (!filemgr)
		return;

	filemgrData = cg_bittorrent_blockdevicemgr_getuserdata(filemgr);
	if (filemgrData)
		free(filemgrData);

	free(filemgr);
}

/****************************************
* cg_bittorrent_filemgr_setdestinationdirectory
****************************************/

void cg_bittorrent_filemgr_setdestinationdirectory(CgBittorrentFileMgr *filemgr, char *value)
{
	CgBittorrentFileMgrData *filemgrData;

	if (!filemgr)
		return;

	filemgrData = cg_bittorrent_blockdevicemgr_getuserdata(filemgr);
	if (!filemgrData)
		return;

	if (filemgrData->dstDir)
		free(filemgrData->dstDir);

	filemgrData->dstDir = cg_strdup(value);
}

/****************************************
* cg_bittorrent_filemgr_getdestinationdirectory
****************************************/

char *cg_bittorrent_filemgr_getdestinationdirectory(CgBittorrentFileMgr *filemgr)
{
	CgBittorrentFileMgrData *filemgrData;

	if (!filemgr)
		return NULL;

	filemgrData = cg_bittorrent_blockdevicemgr_getuserdata(filemgr);
	if (!filemgrData)
		return NULL;

	return filemgrData->dstDir;
}
