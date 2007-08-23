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

	*buf = cg_string_new();
	if (!*buf)
		return FALSE;

	file = cg_file_new();
	if (!file)
		return FALSE;

	cg_file_setpath(file, cg_bittorrent_filemgr_getdestinationdirectory(filemgr));
	cg_file_setfilename(file, cg_bittorrent_metainfo_getid(cbm));

	cg_string_setvalue(*buf, cg_file_getname(file));
	
	cg_file_delete(file);

	return TRUE;
}

/****************************************
* cg_bittorrent_filemgr_addmetainfofunc
****************************************/

static BOOL cg_bittorrent_filemgr_addmetainfofunc(CgBittorrentFileMgr *filemgr, CgBittorrentMetainfo *cbm)
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
* cg_bittorrent_filemgr_getmetainfosfunc
****************************************/

static int cg_bittorrent_filemgr_getmetainfosfunc(CgBittorrentFileMgr *filemgr, CgBittorrentMetainfoList **cbmList)
{
	char *dstDir;
	CgFile *dstFile;
	CgFileList *fileList;
	CgFile *cbmFile;
	CgFile *file;
	CgBittorrentMetainfo *cbm;

	dstDir = cg_bittorrent_filemgr_getdestinationdirectory(filemgr);
	if (cg_strlen(dstDir) <= 0)
		return 0;

	dstFile = cg_file_new();
	cg_file_setname(dstFile, dstDir);
	fileList = cg_filelist_new();
	if (cg_file_listfiles(dstFile, fileList) <= 0) {
		cg_file_delete(dstFile);
		cg_filelist_delete(fileList);
		return 0;
	}

	*cbmList = cg_bittorrent_metainfolist_new();

	cbmFile = cg_file_new();
	for (file = cg_filelist_gets(fileList); file; file = cg_file_next(file)) {
		cg_file_setpath(cbmFile, dstDir);
		cg_file_setfilename(cbmFile, cg_file_getname(file));
		cbm = cg_bittorrent_metainfo_new();
		if (!cbm)
			continue;
		if (!cg_bittorrent_metainfo_load(cbm, cg_file_getname(cbmFile))) {
			cg_bittorrent_metainfo_delete(cbm);
			continue;
		}
		cg_bittorrent_metainfo_setfilename(cbm, cg_file_getname(cbmFile));
		cg_bittorrent_metainfo_setid(cbm, cg_file_getname(file));
		cg_bittorrent_metainfolist_add(*cbmList, cbm);
	}
	cg_file_delete(cbmFile);

	return cg_bittorrent_metainfolist_size(*cbmList);
}

/****************************************
* cg_bittorrent_filemgr_getmetainfofunc
****************************************/

static BOOL cg_bittorrent_filemgr_getmetainfofunc(CgBittorrentFileMgr *filemgr, unsigned char *infoHash, CgBittorrentMetainfo **cbm)
{
	CgBittorrentMetainfoList *dstCbmList;
	CgBittorrentMetainfoList *dstCbm;
	unsigned char dstCbmInfoHash[CG_SHA1_HASH_SIZE];
	BOOL compFlag;
	int n;

	if (cg_bittorrent_filemgr_getmetainfos(filemgr, &dstCbmList) <= 0)
		return FALSE;

	for (dstCbm = cg_bittorrent_metainfolist_gets(dstCbmList); dstCbm; dstCbm = cg_bittorrent_metainfo_next(dstCbm)) {
		if (!cg_bittorrent_metainfo_getinfohash(dstCbm, dstCbmInfoHash))
			continue;
		compFlag = TRUE;
		for (n=0; n<CG_SHA1_HASH_SIZE; n++) {
			if (dstCbmInfoHash[n] != infoHash[n]) {
				compFlag = FALSE;
				break;
			}
		}
		if (!compFlag)
			continue;
		*cbm = cg_bittorrent_metainfo_new();
		if (!*cbm)
			return FALSE;
		if (!cg_bittorrent_metainfo_copy(*cbm, dstCbm))
			return FALSE;
		return TRUE;
	}

	return FALSE;
}

/****************************************
* cg_bittorrent_filemgr_removemetainfofunc
****************************************/

static BOOL cg_bittorrent_filemgr_removemetainfofunc(CgBittorrentFileMgr *filemgr, unsigned char *infoHash)
{
	CgBittorrentMetainfo *cbm;
	CgString *filename;
	BOOL isRemoved;
	CgFile *file;

	if (!cg_bittorrent_filemgr_getmetainfo(filemgr, infoHash, &cbm))
		return FALSE;

	if (!cg_bittorrent_filemgr_getfilename(filemgr, cbm, &filename))
		return FALSE;
	
	cg_bittorrent_metainfo_delete(cbm);

	file = cg_file_new();
	if (!file)
		return FALSE;
	cg_file_setname(file, cg_string_getvalue(filename));
	isRemoved = cg_file_remove(file);
	cg_file_delete(file);
	cg_string_delete(filename);

	return isRemoved;
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

	cg_bittorrent_blockdevicemgr_setaddmetainfofunc(filemgr, cg_bittorrent_filemgr_addmetainfofunc);
	cg_bittorrent_blockdevicemgr_setremovemetainfofunc(filemgr, cg_bittorrent_filemgr_removemetainfofunc);
	cg_bittorrent_blockdevicemgr_setgetmetainfosfunc(filemgr, cg_bittorrent_filemgr_getmetainfosfunc);
	cg_bittorrent_blockdevicemgr_setgetmetainfofunc(filemgr, cg_bittorrent_filemgr_getmetainfofunc);

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
