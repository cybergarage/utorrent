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
#include <cybergarage/io/cfile.h>

/****************************************
* cg_bittorrent_filemgr_checkparam
****************************************/

static BOOL cg_bittorrent_filemgr_getfilename(CgBittorrentFileMgr *filemgr, CgBittorrentMetainfo *cbm, CgString **buf)
{
	char *dstDir;
	char *id;
	CgFile *file;

	dstDir = cg_bittorrent_filemgr_getdestinationdirectory(filemgr);
	if (cg_strlen(dstDir) <= 0)
		return FALSE;

	id = cg_bittorrent_metainfo_getid(cbm);
	if (cg_strlen(dstDir) <= 0)
		return FALSE;

	file = cg_file_new();
	if (!file)
		return FALSE;

	cg_file_setpath(file, cg_bittorrent_filemgr_getdestinationdirectory(filemgr));
	cg_file_setfilename(file, cg_bittorrent_metainfo_getid(cbm));

	*buf = cg_string_new();
	cg_string_setvalue(*buf, cg_file_getname(file));
	
	cg_file_delete(file);

	return TRUE;
}

/****************************************
* cg_bittorrent_filemgr_addmetainfo
****************************************/

BOOL cg_bittorrent_filemgr_addmetainfo(CgBittorrentFileMgr *filemgr, CgBittorrentMetainfo *cbm)
{
	CgString *filename;
	BOOL isSaved;

	if (!cg_bittorrent_filemgr_getfilename(filemgr, cbm, &filename))
		return FALSE;

	isSaved = cg_bittorrent_metainfo_save(cbm, cg_string_getvalue(filename));

	cg_string_delete(filename);

	return isSaved;
}

/****************************************
* cg_bittorrent_filemgr_removemetainfo
****************************************/

BOOL cg_bittorrent_filemgr_removemetainfo(CgBittorrentFileMgr *filemgr, char *infoHash)
{
	char *dstDir;

	dstDir = cg_bittorrent_filemgr_getdestinationdirectory(filemgr);
	if (cg_strlen(dstDir) <= 0)
		return FALSE;
}

/****************************************
* cg_bittorrent_filemgr_getmetainfos
****************************************/

int cg_bittorrent_filemgr_getmetainfos(CgBittorrentFileMgr *filemgr, CgBittorrentMetainfoList *cbmList)
{
	char *dstDir;

	dstDir = cg_bittorrent_filemgr_getdestinationdirectory(filemgr);
	if (cg_strlen(dstDir) <= 0)
		return 0;
}

/****************************************
* cg_bittorrent_filemgr_getmetainfo
****************************************/

BOOL cg_bittorrent_filemgr_getmetainfo(CgBittorrentFileMgr *filemgr, char *infoHash, CgBittorrentMetainfo *cbm)
{
	char *dstDir;

	dstDir = cg_bittorrent_filemgr_getdestinationdirectory(filemgr);
	if (cg_strlen(dstDir) <= 0)
		return FALSE;
}

/****************************************
* cg_bittorrent_filemgr_readpiece
****************************************/

static BOOL cg_bittorrent_filemgr_openfile(CgBittorrentFileMgr *filemgr, CgBittorrentMetainfo *cbm, int mode, CgFile **file)
{
	char *dstDir;

	dstDir = cg_bittorrent_filemgr_getdestinationdirectory(filemgr);
	if (cg_strlen(dstDir) <= 0)
		return FALSE;

	return TRUE;
}

/****************************************
* cg_bittorrent_filemgr_readpiece
****************************************/

static BOOL cg_bittorrent_filemgr_readpiece(CgBittorrentFileMgr *filemgr, CgBittorrentMetainfo *cbm, int pieceIdx , CgByte **buf, int *bufLen)
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

static BOOL cg_bittorrent_filemgr_writepiece(CgBittorrentFileMgr *filemgr, CgBittorrentMetainfo *cbm, int pieceIdx , CgByte *buf, int bufLen)
{
	return TRUE;
}

/****************************************
* cg_bittorrent_filemgr_havepiece
****************************************/

static BOOL cg_bittorrent_filemgr_havepiece(CgBittorrentFileMgr *filemgr, CgBittorrentMetainfo *cbm, int pieceIdx)
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

	cg_bittorrent_blockdevicemgr_setaddmetainfofunc(filemgr, cg_bittorrent_filemgr_addmetainfo);
	cg_bittorrent_blockdevicemgr_setremovemetainfofunc(filemgr, cg_bittorrent_filemgr_removemetainfo);
	cg_bittorrent_blockdevicemgr_setgetmetainfosfunc(filemgr, cg_bittorrent_filemgr_getmetainfos);
	cg_bittorrent_blockdevicemgr_setgetmetainfofunc(filemgr, cg_bittorrent_filemgr_getmetainfo);

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
