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
* cg_bittorrent_filemgr_getfilenameformetainfo
****************************************/

static BOOL cg_bittorrent_filemgr_getfilenameformetainfo(CgBittorrentFileMgr *filemgr, CgBittorrentMetainfo *cbm, CgString **buf)
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
* cg_bittorrent_filemgr_getfilenameforfile
****************************************/

static BOOL cg_bittorrent_filemgr_getfilenameforfile(CgBittorrentFileMgr *filemgr, CgBittorrentMetainfo *cbm, int fileIdx, CgString **buf)
{
	char *dstDir;
	CgFile *file;
	CgBittorrentBencoding *pathList;
	CgBittorrentBencoding *pathItem;

	dstDir = cg_bittorrent_filemgr_getdestinationdirectory(filemgr);
	if (cg_strlen(dstDir) <= 0)
		return FALSE;

	*buf = cg_string_new();
	if (!*buf)
		return FALSE;

	file = cg_file_new();
	if (!file)
		return FALSE;

	if (cg_bittorrent_metainfo_ismultiplefilemode(cbm)) { /* Info in Multiple File Mode */
		pathList = cg_bittorrent_metainfo_getinfofilepath(cbm, fileIdx);
		for (pathItem = cg_bittorrent_bencoding_getlists(pathList); pathItem; pathItem = cg_bittorrent_bencoding_next(pathItem))
			cg_file_addfilename(file, cg_bittorrent_metainfo_getinfoname(cbm));
	}
	else { /* Info in Single File Mode */
		cg_file_setpath(file, dstDir);
		cg_file_setfilename(file, cg_bittorrent_metainfo_getinfoname(cbm));
	}

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

	if (!cg_bittorrent_filemgr_getfilenameformetainfo(filemgr, cbm, &filename))
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

	if (!cg_bittorrent_filemgr_getfilenameformetainfo(filemgr, cbm, &filename))
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
* cg_bittorrent_filemgr_openfilefunc
****************************************/

static BOOL cg_bittorrent_filemgr_openfilefunc(CgBittorrentFileMgr *filemgr, CgBittorrentMetainfo *cbm, int fileIdx)
{
	CgString *filename;
	CgFile *file;
	BOOL isSuccess;

	file = cg_bittorrent_filemgr_getfile(filemgr);
	if (!file)
		return FALSE;

	if (!cg_bittorrent_filemgr_getfilenameforfile(filemgr, cbm, fileIdx, &filename))
		return FALSE;

	cg_file_setname(file, cg_string_getvalue(filename));
	cg_file_close(file);
	isSuccess = cg_file_open(file, CG_FILE_OPEN_CREATE);

	cg_string_delete(filename);

	return isSuccess;
}

/****************************************
* cg_bittorrent_filemgr_closefilefunc
****************************************/

static BOOL cg_bittorrent_filemgr_closefilefunc(CgBittorrentFileMgr *filemgr)
{
	CgString *filename;
	CgFile *file;
	BOOL isSuccess;

	file = cg_bittorrent_filemgr_getfile(filemgr);
	if (!file)
		return FALSE;

	isSuccess = cg_file_close(file);
	if (isSuccess)
		cg_file_setname(file, "");

	cg_string_delete(filename);

	return isSuccess;
}

/****************************************
* cg_bittorrent_filemgr_readpiece
****************************************/

static BOOL cg_bittorrent_filemgr_readpiecefunc(CgBittorrentFileMgr *filemgr, CgBittorrentMetainfo *cbm, int pieceIdx , CgByte **buf, int *bufLen)
{
	int startFileIdx, endFileIdx;
	CgInt64 fileFrom, fileTo;
	int fileIdx;
	CgString *filename;
	CgFile *file;

	if (!cg_bittorrent_metainfo_getfileindexbypieceindex(cbm, pieceIdx, &startFileIdx, &endFileIdx))
		return FALSE;

	for (fileIdx=startFileIdx; fileIdx <= endFileIdx; fileIdx++) {
		if (!cg_bittorrent_metainfo_getfilerangebypieceindex(cbm, pieceIdx, fileIdx, &fileFrom, &fileTo))
			return FALSE;
		if (!cg_bittorrent_filemgr_getfilenameforfile(filemgr, cbm, fileIdx, &filename))
			return FALSE;
		file = cg_file_new();
		if (!file)  {
			cg_string_delete(filename);
			return FALSE;
		}
		cg_file_setname(file, cg_string_getvalue(filename));
		cg_string_delete(filename);
		if (!cg_file_open(file, CG_FILE_OPEN_CREATE)) {
			cg_file_delete(file);
			return FALSE;
		}
		if (!cg_file_seek(file, fileFrom, CG_FILE_SEEK_SET)) {
			cg_file_delete(file);
			return FALSE;
		}
		// if (cg_file_write(file, CgByte *buf, int bufLen);
	}

	return TRUE;
}

/****************************************
* cg_bittorrent_filemgr_writepiece
****************************************/

static BOOL cg_bittorrent_filemgr_writepiecefunc(CgBittorrentFileMgr *filemgr, CgBittorrentMetainfo *cbm, int pieceIdx , CgByte *buf, int bufLen)
{
	return TRUE;
}

/****************************************
* cg_bittorrent_filemgr_havepiece
****************************************/

static BOOL cg_bittorrent_filemgr_havepiecefunc(CgBittorrentFileMgr *filemgr, CgBittorrentMetainfo *cbm, int pieceIdx)
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

	filemgrData->dstDir = cg_string_new();
	filemgrData->file = cg_file_new();

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

	cg_bittorrent_blockdevicemgr_setreadpiecefunc(filemgr, cg_bittorrent_filemgr_readpiecefunc);
	cg_bittorrent_blockdevicemgr_setwritepiecefunc(filemgr, cg_bittorrent_filemgr_writepiecefunc);
	cg_bittorrent_blockdevicemgr_sethavepiecefunc(filemgr, cg_bittorrent_filemgr_havepiecefunc);

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

	cg_string_delete(filemgrData->dstDir);
	cg_file_delete(filemgrData->file);

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
		cg_string_setvalue(filemgrData->dstDir, value);
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

	if (!filemgrData->dstDir)
		return NULL;

	return cg_string_getvalue(filemgrData->dstDir);
}

/****************************************
* cg_bittorrent_filemgr_getfile
****************************************/

CgFile *cg_bittorrent_filemgr_getfile(CgBittorrentFileMgr *filemgr)
{
	CgBittorrentFileMgrData *filemgrData;

	if (!filemgr)
		return NULL;

	filemgrData = cg_bittorrent_blockdevicemgr_getuserdata(filemgr);
	if (!filemgrData)
		return NULL;

	return filemgrData->file;
}
