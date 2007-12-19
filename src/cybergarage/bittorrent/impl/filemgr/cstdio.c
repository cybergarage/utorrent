/******************************************************************
*
*	CyberBittorrent for C
*
*	Copyright (C) Satoshi Konno 2007
*
*	Strategy: cstdio.c
*
*	Revision:
*
*	12/18/07
*		- first revision
*
******************************************************************/

#include <cybergarage/bittorrent/impl/filemgr/cstdio.h>
#include <cybergarage/util/cstring.h>
#include <cybergarage/io/cfile.h>

/****************************************
* cg_bittorrent_stdio_filemgr_getfilenameformetainfo
****************************************/

static BOOL cg_bittorrent_stdio_filemgr_getfilenameformetainfo(CgBittorrentFileMgr *filemgr, CgBittorrentMetainfo *cbm, CgString **buf)
{
	char *dstDir;
	char *id;
	CgFile *file;

	dstDir = cg_bittorrent_stdio_filemgr_getdestinationdirectory(filemgr);
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

	cg_file_setpath(file, cg_bittorrent_stdio_filemgr_getdestinationdirectory(filemgr));
	cg_file_setfilename(file, cg_bittorrent_metainfo_getid(cbm));

	cg_string_setvalue(*buf, cg_file_getname(file));
	
	cg_file_delete(file);

	return TRUE;
}

/****************************************
* cg_bittorrent_stdio_filemgr_getfilenameforfile
****************************************/

static BOOL cg_bittorrent_stdio_filemgr_getfilenameforfile(CgBittorrentFileMgr *filemgr, CgBittorrentMetainfo *cbm, int fileIdx, CgString **buf)
{
	char *dstDir;
	CgFile *file;
	CgBittorrentBencoding *pathList;
	CgBittorrentBencoding *pathItem;

	dstDir = cg_bittorrent_stdio_filemgr_getdestinationdirectory(filemgr);
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
* cg_bittorrent_stdio_filemgr_addmetainfofunc
****************************************/

static BOOL cg_bittorrent_stdio_filemgr_addmetainfofunc(CgBittorrentFileMgr *filemgr, CgBittorrentMetainfo *cbm)
{
	CgString *filename;
	BOOL isSaved;

	if (!cg_bittorrent_stdio_filemgr_getfilenameformetainfo(filemgr, cbm, &filename))
		return FALSE;

	isSaved = cg_bittorrent_metainfo_save(cbm, cg_string_getvalue(filename));

	cg_string_delete(filename);

	return isSaved;
}

/****************************************
* cg_bittorrent_stdio_filemgr_getmetainfosfunc
****************************************/

static int cg_bittorrent_stdio_filemgr_getmetainfosfunc(CgBittorrentFileMgr *filemgr, CgBittorrentMetainfoList **cbmList)
{
	char *dstDir;
	CgFile *dstFile;
	CgFileList *fileList;
	CgFile *cbmFile;
	CgFile *file;
	CgBittorrentMetainfo *cbm;

	dstDir = cg_bittorrent_stdio_filemgr_getdestinationdirectory(filemgr);
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
* cg_bittorrent_stdio_filemgr_getmetainfofunc
****************************************/

static BOOL cg_bittorrent_stdio_filemgr_getmetainfofunc(CgBittorrentFileMgr *filemgr, unsigned char *infoHash, CgBittorrentMetainfo **cbm)
{
	CgBittorrentMetainfoList *dstCbmList;
	CgBittorrentMetainfoList *dstCbm;
	unsigned char dstCbmInfoHash[CG_SHA1_HASH_SIZE];
	BOOL compFlag;
	int n;

	if (cg_bittorrent_stdio_filemgr_getmetainfos(filemgr, &dstCbmList) <= 0)
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
* cg_bittorrent_stdio_filemgr_removemetainfofunc
****************************************/

static BOOL cg_bittorrent_stdio_filemgr_removemetainfofunc(CgBittorrentFileMgr *filemgr, unsigned char *infoHash)
{
	CgBittorrentMetainfo *cbm;
	CgString *filename;
	BOOL isRemoved;
	CgFile *file;

	if (!cg_bittorrent_stdio_filemgr_getmetainfo(filemgr, infoHash, &cbm))
		return FALSE;

	if (!cg_bittorrent_stdio_filemgr_getfilenameformetainfo(filemgr, cbm, &filename))
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
* cg_bittorrent_stdio_filemgr_openfilefunc
****************************************/

static BOOL cg_bittorrent_stdio_filemgr_openfilefunc(CgBittorrentFileMgr *filemgr, CgBittorrentMetainfo *cbm, int fileIdx)
{
	CgString *filename;
	CgFile *file;
	BOOL isSuccess;

	file = cg_bittorrent_stdio_filemgr_getfile(filemgr);
	if (!file)
		return FALSE;

	if (!cg_bittorrent_stdio_filemgr_getfilenameforfile(filemgr, cbm, fileIdx, &filename))
		return FALSE;

	cg_file_setname(file, cg_string_getvalue(filename));
	cg_file_close(file);
	isSuccess = cg_file_open(file, CG_FILE_OPEN_CREATE);

	cg_string_delete(filename);

	return isSuccess;
}

/****************************************
* cg_bittorrent_stdio_filemgr_closefilefunc
****************************************/

static BOOL cg_bittorrent_stdio_filemgr_closefilefunc(CgBittorrentFileMgr *filemgr)
{
	CgString *filename;
	CgFile *file;
	BOOL isSuccess;

	file = cg_bittorrent_stdio_filemgr_getfile(filemgr);
	if (!file)
		return FALSE;

	isSuccess = cg_file_close(file);
	if (isSuccess)
		cg_file_setname(file, "");

	cg_string_delete(filename);

	return isSuccess;
}

/****************************************
* cg_bittorrent_stdio_filemgr_havepiece
****************************************/

static BOOL cg_bittorrent_stdio_filemgr_havepiecefunc(CgBittorrentFileMgr *filemgr, CgBittorrentMetainfo *cbm, int pieceIdx)
{
	return TRUE;
}

/****************************************
* cg_bittorrent_stdio_filemgr_new
****************************************/

CgBittorrentFileMgr *cg_bittorrent_stdio_filemgr_new()
{
	CgBittorrentFileMgrData *filemgrData;
	CgBittorrentFileMgr *filemgr;


	filemgrData = (CgBittorrentFileMgrData *)malloc(sizeof(CgBittorrentFileMgrData));
	if (!filemgrData)
		return NULL;

	filemgrData->dstDir = cg_string_new();
	filemgrData->file = cg_file_new();

	filemgr = cg_bittorrent_filemgr_new();
	if (!filemgr) {
		free(filemgrData);
		return NULL;
	}

	cg_bittorrent_filemgr_setuserdata(filemgr, filemgrData);

	cg_bittorrent_filemgr_setaddmetainfofunc(filemgr, cg_bittorrent_stdio_filemgr_addmetainfofunc);
	cg_bittorrent_filemgr_setremovemetainfofunc(filemgr, cg_bittorrent_stdio_filemgr_removemetainfofunc);
	cg_bittorrent_filemgr_setgetmetainfosfunc(filemgr, cg_bittorrent_stdio_filemgr_getmetainfosfunc);
	cg_bittorrent_filemgr_setgetmetainfofunc(filemgr, cg_bittorrent_stdio_filemgr_getmetainfofunc);

	return filemgr;
}

/****************************************
* cg_bittorrent_stdio_filemgr_delete
****************************************/

void cg_bittorrent_stdio_filemgr_delete(CgBittorrentFileMgr *filemgr)
{
	CgBittorrentFileMgrData *filemgrData;

	if (!filemgr)
		return;

	filemgrData = cg_bittorrent_filemgr_getuserdata(filemgr);
	if (filemgrData) {
		cg_string_delete(filemgrData->dstDir);
		cg_file_delete(filemgrData->file);
		free(filemgrData);
	}

	free(filemgr);
}

/****************************************
* cg_bittorrent_stdio_filemgr_setdestinationdirectory
****************************************/

void cg_bittorrent_stdio_filemgr_setdestinationdirectory(CgBittorrentFileMgr *filemgr, char *value)
{
	CgBittorrentFileMgrData *filemgrData;

	if (!filemgr)
		return;

	filemgrData = cg_bittorrent_filemgr_getuserdata(filemgr);
	if (!filemgrData)
		return;

	if (filemgrData->dstDir)
		cg_string_setvalue(filemgrData->dstDir, value);
}

/****************************************
* cg_bittorrent_stdio_filemgr_getdestinationdirectory
****************************************/

char *cg_bittorrent_stdio_filemgr_getdestinationdirectory(CgBittorrentFileMgr *filemgr)
{
	CgBittorrentFileMgrData *filemgrData;

	if (!filemgr)
		return NULL;

	filemgrData = cg_bittorrent_filemgr_getuserdata(filemgr);
	if (!filemgrData)
		return NULL;

	if (!filemgrData->dstDir)
		return NULL;

	return cg_string_getvalue(filemgrData->dstDir);
}

/****************************************
* cg_bittorrent_stdio_filemgr_getfile
****************************************/

CgFile *cg_bittorrent_stdio_filemgr_getfile(CgBittorrentFileMgr *filemgr)
{
	CgBittorrentFileMgrData *filemgrData;

	if (!filemgr)
		return NULL;

	filemgrData = cg_bittorrent_filemgr_getuserdata(filemgr);
	if (!filemgrData)
		return NULL;

	return filemgrData->file;
}

/****************************************
* cg_bittorrent_fileMgr_writepiece
****************************************/

/*
BOOL cg_bittorrent_filemgr_writepiecedata(CgBittorrentFileMgr *fileMgr, CgBittorrentMetainfo *cbm, int pieceIdx , CgByte *buf, int bufLen)
{
	int startFileIdx, endFileIdx;
	int pieceOffet, pieceSize;
	CgInt64 fileOffset, fileSize;
	int fileIdx;
	CgString *filename;
	int wroteSize;

	if (!cg_bittorrent_metainfo_getfileindexbypieceindex(cbm, pieceIdx, &startFileIdx, &endFileIdx))
		return FALSE;

	for (fileIdx=startFileIdx; fileIdx <= endFileIdx; fileIdx++) {
		if (!cg_bittorrent_metainfo_getfileandpiecerangebypieceandfileindex(cbm, pieceIdx, fileIdx, &pieceOffet, &pieceSize, &fileOffset, &fileSize))
			return FALSE;
		if (bufLen < (fileSize-fileOffset))
			return FALSE;
		if (!cg_bittorrent_fileMgr_getfilenameforfile(fileMgr, cbm, fileIdx, &filename))
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
		if (!cg_file_seek(file, fileOffset, CG_FILE_SEEK_SET)) {
			cg_file_delete(file);
			return FALSE;
		}
		wroteSize = cg_file_write(file, buf+fileOffset, pieceSize);
		cg_file_close(file);
		if (wroteSize != pieceSize)
			return FALSE;
	}

	return TRUE;
}
*/

