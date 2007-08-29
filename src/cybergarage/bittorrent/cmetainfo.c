/******************************************************************
*
*	CyberBittorrent for C
*
*	Copyright (C) Satoshi Konno 2007
*
*	File: cmetainfo.c
*
*	Revision:
*
*	01/30/07
*		- first revision
*
******************************************************************/

#include <cybergarage/bittorrent/cmetainfo.h>

/****************************************
* cg_bittorrent_metainfo_new
****************************************/

CgBittorrentMetainfo *cg_bittorrent_metainfo_new()
{
	CgBittorrentMetainfo *cbm;

	cbm = (CgBittorrentMetainfo *)malloc(sizeof(CgBittorrentMetainfo));
	if (!cbm)
		return NULL;

	cbm->dir = cg_bittorrent_dictionary_new();
	cbm->url = cg_string_new();
	cbm->fileName = cg_string_new();
	cbm->id = cg_string_new();

	return cbm;
}

/****************************************
* cg_bittorrent_metainfo_delete
****************************************/

void cg_bittorrent_metainfo_delete(CgBittorrentMetainfo *cbm)
{
	if (!cbm)
		return;

	cg_bittorrent_dictionary_delete(cbm->dir);
	cg_string_delete(cbm->url);
	cg_string_delete(cbm->fileName);
	cg_string_delete(cbm->id);

	free(cbm);
}

/****************************************
* cg_bittorrent_metainfo_copy
****************************************/

BOOL cg_bittorrent_metainfo_copy(CgBittorrentMetainfo *destCbm, CgBittorrentMetainfo *srcCbm)
{
	CgString *buf;

	if (!destCbm || !srcCbm)
		return FALSE;

	buf = cg_string_new();
	if (!buf)
		return FALSE;

	if (!cg_bittorrent_metainfo_tostring(srcCbm, buf)) {
		cg_string_delete(buf);
		return FALSE;
	}

	if (!cg_bittorrent_metainfo_parse(destCbm, cg_string_getvalue(buf), cg_string_length(buf))) {
		cg_string_delete(buf);
		return FALSE;
	}

	cg_string_delete(buf);

	cg_string_setvalue(destCbm->url, cg_string_getvalue(srcCbm->url));
	cg_string_setvalue(destCbm->fileName, cg_string_getvalue(srcCbm->fileName));
	cg_string_setvalue(destCbm->id, cg_string_getvalue(srcCbm->id));

	return TRUE;
}

/****************************************
* cg_bittorrent_metainfo_tostring
****************************************/

BOOL cg_bittorrent_metainfo_tostring(CgBittorrentMetainfo *cbm, CgString *buf)
{
	CgBittorrentDictionary *dir;

	if (!cbm)
		return FALSE;

	dir = cg_bittorrent_metainfo_getdictionary(cbm);
	if (!cbm)
		return FALSE;

	cg_bittorrent_dictionary_tostring(dir, buf);

	return TRUE;
}

/****************************************
* cg_bittorrent_metainfo_getinfohash
****************************************/

BOOL cg_bittorrent_metainfo_getinfohash(CgBittorrentMetainfo *cbm, unsigned char *infoHash)
{
	CgBittorrentBencoding *infoVal;

	if (!cbm)
		return FALSE;

	infoVal = cg_bittorrent_metainfo_getvaluebyname(cbm, CG_BITTORRENT_METAINFO_INFO);
	if (!infoVal)
		return FALSE;

	if (!cg_bittorrent_bencoding_tosha1(infoVal, infoHash))
		return FALSE;

	return TRUE;
}

/****************************************
* cg_bittorrent_metainfo_getnfiles
****************************************/

int cg_bittorrent_metainfo_getnfiles(CgBittorrentMetainfo *cbm)
{
	CgBittorrentBencoding *file;
	int fileCnt;

	if (!cbm)
		return 0;

	if (cg_bittorrent_metainfo_issinglefilemode(cbm))
		return 1;

	fileCnt = 0;
	file = cg_bittorrent_metainfo_getinfofiles(cbm);
	while (file) {
		fileCnt++;
		file = cg_bittorrent_bencoding_next(file);
	}

	return fileCnt;
}

/****************************************
* cg_bittorrent_metainfo_getfileproperty
****************************************/

CgBittorrentBencoding *cg_bittorrent_metainfo_getfileproperty(CgBittorrentMetainfo *cbm, char *propName, int index)
{
	CgBittorrentBencoding *file;
	int n;
	CgBittorrentDictionary *cbd;

	if (!cbm)
		return NULL;

	if (cg_bittorrent_metainfo_issinglefilemode(cbm))
		return cg_bittorrent_dictionary_getvaluebyname(cg_bittorrent_metainfo_getinfo(cbm), propName);

	file = cg_bittorrent_metainfo_getinfofiles(cbm);
	for(n=0; n<index; n++)
		file = cg_bittorrent_bencoding_next(file);

	if (!file || !cg_bittorrent_bencoding_isdictionary(file))
		return NULL;

	cbd = cg_bittorrent_bencoding_getdictionary(file);
	if (!cbd)
		return NULL;

	return cg_bittorrent_dictionary_getvaluebyname(cbd, propName);
}

/****************************************
* cg_bittorrent_metainfo_getfilepropertystring
****************************************/

char *cg_bittorrent_metainfo_getfilepropertystring(CgBittorrentMetainfo *cbm, char *propName, int index)
{
	CgBittorrentBencoding *cbb;
	
	cbb = cg_bittorrent_metainfo_getfileproperty(cbm, propName, index);
	if (!cbb)
		return NULL;

	return cg_bittorrent_bencoding_getstring(cbb);
}

/****************************************
* cg_bittorrent_metainfo_getfilepropertyinteger
****************************************/

CgInt64 cg_bittorrent_metainfo_getfilepropertyinteger(CgBittorrentMetainfo *cbm, char *propName, int index)
{
	CgBittorrentBencoding *cbb;
	
	cbb = cg_bittorrent_metainfo_getfileproperty(cbm, propName, index);
	if (!cbb)
		return 0;

	return cg_bittorrent_bencoding_getinteger(cbb);
}

/****************************************
* cg_bittorrent_metainfo_setidfromname
****************************************/

BOOL cg_bittorrent_metainfo_setidfromname(CgBittorrentMetainfo *cbm, char *name)
{
	int delimIdx;

	if (cg_strlen(name) <= 0)
		return FALSE;

	delimIdx = cg_strrchr(name, CG_BITTORRENT_METAINFO_ID_DELIM, cg_strlen(CG_BITTORRENT_METAINFO_ID_DELIM));
	if (0 < delimIdx)
		cg_bittorrent_metainfo_setid(cbm, name + delimIdx + 1);
	else
		cg_bittorrent_metainfo_setid(cbm, name);

	return TRUE;
}

/****************************************
* cg_bittorrent_metainfo_getfileindexrange
****************************************/

BOOL cg_bittorrent_metainfo_getfileindexrange(CgBittorrentMetainfo *cbm, int pieceIdx, int *startFileIndex, int *endFileIndex)
{
	int cbmFileCnt;
	int pieceLength;
	CgInt64 pieceStartOffset;
	CgInt64 pieceEndOffset;
	CgInt64 cbmFileOffset;
	CgInt64 cbmFileLength;
	CgInt64 fileLength;
	int cbmFileIndex;

	if (!cbm)
		return FALSE;

	if (pieceIdx < 0)
		return FALSE;

	pieceLength = cg_bittorrent_metainfo_getinfopiecelength(cbm);
	pieceStartOffset = (CgInt64)pieceIdx * (CgInt64)pieceLength;

	if (cg_bittorrent_metainfo_ismultiplefilemode(cbm)) { /* Info in Multiple File Mode */
		cbmFileCnt = cg_bittorrent_metainfo_getnfiles(cbm);
		if (cbmFileCnt <= 0)
			return FALSE;

		*startFileIndex = *endFileIndex = 0;
		cbmFileOffset = 0;
		for (cbmFileIndex=0; cbmFileIndex<cbmFileCnt; cbmFileIndex++) { 
			fileLength = cg_bittorrent_metainfo_getinfofilelength(cbm, cbmFileIndex);
			if ((cbmFileOffset <= pieceStartOffset) && (pieceStartOffset <= (cbmFileOffset + fileLength))) {
				*startFileIndex = cbmFileIndex;
				break;
			}
			cbmFileOffset += fileLength;
		}

		pieceEndOffset = pieceStartOffset +  (CgInt64)pieceLength;
		for (; cbmFileIndex<cbmFileCnt; cbmFileIndex++) {
			*endFileIndex = cbmFileIndex;
			cbmFileOffset += cg_bittorrent_metainfo_getinfofilelength(cbm, cbmFileIndex);
			if (pieceEndOffset <= cbmFileOffset)
				break;
		}
	}
	else { /* Info in Single File Mode */
		cbmFileLength = cg_bittorrent_metainfo_getinfolength(cbm);
		if (cbmFileLength < pieceStartOffset)
			return FALSE;
		*startFileIndex = *endFileIndex = 0;
	}

	if (*endFileIndex < *startFileIndex)
		return FALSE;

	return TRUE;
}