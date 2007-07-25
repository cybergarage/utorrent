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
* cg_bittorrent_filemgr_readpiece
****************************************/

static char *cg_bittorrent_filemgr_getfilename(CgBittorrentFileMgr *filemgr, CgBittorrentMetainfo *cbm, CgString *filename)
{
	char *dstDir;
	int dstDirLen;

	if (!filemgr || !filename || !cbm)
		return NULL;

	dstDir = cg_bittorrent_filemgr_getdestinationdirectory(filemgr);
	dstDirLen = cg_strlen(dstDir);
	if (dstDirLen <= 0)
		return NULL;
	
	cg_string_addvalue(filename, dstDir);

/*
	CgBittorrentMetainfo *cbm = cg_bittorrent_metainfo_new();
	CPPUNIT_ASSERT(cbm);
	CPPUNIT_ASSERT(cg_bittorrent_metainfo_load(cbm, CDIST_TEST_METAINFO_FILE));

	CPPUNIT_ASSERT(cg_streq(cg_bittorrent_metainfo_getannounce(cbm), "http://torrent.linux.duke.edu:6969/announce"));
	CPPUNIT_ASSERT(cg_bittorrent_metainfo_getcreationdate(cbm) == 1161640274);

	CgBittorrentBencoding *pathList;
	CgBittorrentBencoding *pathItem;
	CPPUNIT_ASSERT(cg_bittorrent_metainfo_getnfiles(cbm) == 2);
	CPPUNIT_ASSERT(cg_streq(cg_bittorrent_metainfo_getinfoname(cbm), "Zod-dvd-i386"));
	CPPUNIT_ASSERT(cg_bittorrent_metainfo_getinfopiecelength(cbm) == 262144);
	pathList = cg_bittorrent_metainfo_getinfofilepath(cbm, 0);
	pathItem = cg_bittorrent_bencoding_getlists(pathList);
	CPPUNIT_ASSERT(cg_streq("FC-6-i386-DVD.iso", cg_bittorrent_bencoding_getstring(pathItem)));
	CPPUNIT_ASSERT(cg_bittorrent_metainfo_getinfofilelength(cbm, 0) == 3525195776);
*/

	return cg_string_getvalue(filename);
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
