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

#include <math.h>

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
	cbm->tracker = cg_bittorrent_tracker_new();
	cbm->pieceInfo = NULL;
	cbm->numPieceInfo = 0;
	cbm->bitfield = NULL;
	cbm->bitfieldLen = 0;

	return cbm;
}

/****************************************
* cg_bittorrent_metainfo_delete
****************************************/

void cg_bittorrent_metainfo_delete(CgBittorrentMetainfo *cbm)
{
	if (!cbm)
		return;

	cg_bittorrent_metainfo_freepieceinfo(cbm);

	cg_bittorrent_dictionary_delete(cbm->dir);
	cg_string_delete(cbm->url);
	cg_string_delete(cbm->fileName);
	cg_string_delete(cbm->id);
	cg_bittorrent_tracker_delete(cbm->tracker);
	cg_bittorrent_metainfo_freebitfield(cbm);

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

BOOL cg_bittorrent_metainfo_getinfohash(CgBittorrentMetainfo *cbm, CgByte *infoHash)
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
* cg_bittorrent_metainfo_allocpieceinfo
****************************************/

BOOL cg_bittorrent_metainfo_allocpieceinfo(CgBittorrentMetainfo *cbm, int num)
{
	int n;

	cg_bittorrent_metainfo_freepieceinfo(cbm);

	cbm->pieceInfo = (CgBittorrentPieceInfo **)malloc(sizeof(CgBittorrentPieceInfo*) * num);
	if (!cbm->pieceInfo)
		return FALSE;

	for (n=0; n<num; n++)
		cbm->pieceInfo[n] = cg_bittorrent_pieceinfo_new();
	
	cbm->numPieceInfo = num;
	
	return TRUE;
}

/****************************************
* cg_bittorrent_metainfo_freepieceinfo
****************************************/

BOOL cg_bittorrent_metainfo_freepieceinfo(CgBittorrentMetainfo *cbm)
{
	int n;

	if (cbm->numPieceInfo <= 0)
		return FALSE;

	for (n=0; n<cbm->numPieceInfo; n++)
		cg_bittorrent_pieceinfo_delete(cbm->pieceInfo[n]);
	
	free(cbm->pieceInfo);

	cbm->pieceInfo = NULL;
	cbm->numPieceInfo = 0;
	
	return TRUE;
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
* cg_bittorrent_metainfo_getinfototallength
****************************************/

CgInt64 cg_bittorrent_metainfo_getinfototallength(CgBittorrentMetainfo *cbm)
{
	int numFiles;
	CgInt64 totalFileLength;
	int n;

	if (!cbm)
		return FALSE;

	/* Info in Single File Mode */
	if (cg_bittorrent_metainfo_issinglefilemode(cbm)) 
		return cg_bittorrent_metainfo_getinfolength(cbm);

	/* Info in Multiple File Mode */
	numFiles = cg_bittorrent_metainfo_getnfiles(cbm);
	totalFileLength = 0;
	for (n=0; n<numFiles; n++)
		totalFileLength += cg_bittorrent_metainfo_getinfofilelength(cbm, n);

	return totalFileLength;
}

/****************************************
* cg_bittorrent_metainfo_numpieces
****************************************/

int cg_bittorrent_metainfo_numpieces(CgBittorrentMetainfo *cbm)
{
	CgInt64 pieceLength;
	CgInt64 totalFileLength;

	pieceLength = cg_bittorrent_metainfo_getinfopiecelength(cbm);
	if (pieceLength <= 0)
		return 0;

	totalFileLength = cg_bittorrent_metainfo_getinfototallength(cbm);

	return (int)ceil((double)(totalFileLength / pieceLength));
}

/****************************************
* cg_bittorrent_metainfo_numpieces
****************************************/

int cg_bittorrent_metainfo_getpiecelength(CgBittorrentMetainfo *cbm, int pieceIdx)
{
	int totalPieces;
	int pieceLength;
	CgInt64 totalLength;
	CgInt64 modLength;

	totalPieces = cg_bittorrent_metainfo_numpieces(cbm);
	if ((pieceIdx < 0) || totalPieces <= (pieceIdx))
		return 0;

	pieceLength = cg_bittorrent_metainfo_getinfopiecelength(cbm);
	if (pieceIdx < (totalPieces-1))
		return pieceLength;

	totalLength = cg_bittorrent_metainfo_getinfototallength(cbm);
	modLength = totalLength % pieceLength;

	return (int)modLength;
}

/****************************************
* cg_bittorrent_metainfo_allocateitfield
****************************************/

BOOL cg_bittorrent_metainfo_allocateitfield(CgBittorrentMetainfo *cbm)
{
	int nTotalPieces;
	int bitfieldLen;

	if (!cbm)
		return FALSE;

	nTotalPieces = cg_bittorrent_metainfo_numpieces(cbm);
	if (nTotalPieces <= 0)
		return FALSE;

	bitfieldLen = (nTotalPieces / 8) + ((nTotalPieces % 8) ? 1 : 0);
	
	cbm->bitfield = (CgByte *)calloc(sizeof(CgByte), bitfieldLen);
	if (!cbm->bitfield)
		return FALSE;

	cbm->bitfieldLen = bitfieldLen;

	return TRUE;
}

/****************************************
* cg_bittorrent_metainfo_freebitfield
****************************************/

BOOL cg_bittorrent_metainfo_freebitfield(CgBittorrentMetainfo *cbm)
{
	if (!cbm)
		return FALSE;

	if (cbm->bitfield) {
		free(cbm->bitfield);
		cbm->bitfield = NULL;
	}

	cbm->bitfieldLen = 0;

	return TRUE;
}

/****************************************
* cg_bittorrent_metainfo_updatetracker
****************************************/

BOOL cg_bittorrent_metainfo_updatetracker(
CgBittorrentMetainfo *cbm,
CgByte *peerId,
int port,
CgInt64 uploaded,
CgInt64 downloaded,
CgInt64 left,
char *eventStr,
int numwant)
{
	CgBittorrentTracker *cbt;
	char *announce;
	CgByte infoHash[CG_SHA1_HASH_SIZE];

	cbt = cg_bittorrent_metainfo_gettracker(cbm);

	announce = cg_bittorrent_metainfo_getannounce(cbm);
	if (cg_strlen(announce) <= 0)
		return FALSE;

	if (!cg_bittorrent_metainfo_getinfohash(cbm, infoHash))
		return FALSE;

	return cg_bittorrent_tracker_load(
		cbt,
		announce,
		infoHash,
		peerId,
		"",
		port,
		uploaded,
		downloaded,
		left,
		TRUE,
		eventStr,
		numwant
		);
}

/****************************************
* cg_bittorrent_metainfo_getfileindexbypieceindex
****************************************/

BOOL cg_bittorrent_metainfo_getfileindexbypieceindex(CgBittorrentMetainfo *cbm, int pieceIdx, int *startFileIndex, int *endFileIndex)
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
	if (pieceLength <= 0)
		return FALSE;

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

/****************************************
* cg_bittorrent_metainfo_getfilerangebypieceindex
****************************************/

BOOL cg_bittorrent_metainfo_getfileandpiecerangebypieceandfileindex(CgBittorrentMetainfo *cbm, int pieceIdx, int fileIdx, int *pieceOffset, CgInt64 *fileOffset, int *blockSize)
{
	int startFileIndex;
	int endFileIndex;
	int pieceLength;
	CgInt64 pieceStartOffset ;
	CgInt64 pieceEndOffset ;
	CgInt64 fileLength ;
	int fileMax;
	int n;
	CgInt64 prevAllFileOffset;
	CgInt64 targetAllFileOffset;

	if (!cbm)
		return FALSE;

	if (pieceIdx < 0)
		return FALSE;

	if (!cg_bittorrent_metainfo_getfileindexbypieceindex(cbm, pieceIdx, &startFileIndex, &endFileIndex))
		return FALSE;

	if (fileIdx < startFileIndex || endFileIndex < fileIdx)
		return FALSE;

	pieceLength = cg_bittorrent_metainfo_getinfopiecelength(cbm);
	if (pieceLength <= 0)
		return FALSE;
	
	pieceStartOffset = (CgInt64)pieceIdx * (CgInt64)pieceLength;
	pieceEndOffset = pieceStartOffset + (CgInt64)pieceLength;

	if (cg_bittorrent_metainfo_ismultiplefilemode(cbm)) { /* Info in Multiple File Mode */
		prevAllFileOffset = 0;
		fileMax = cg_bittorrent_metainfo_getnfiles(cbm);
		for (n=0; n < fileIdx; n++)
			prevAllFileOffset += cg_bittorrent_metainfo_getinfofilelength(cbm, n);
		targetAllFileOffset = prevAllFileOffset +  cg_bittorrent_metainfo_getinfofilelength(cbm, fileIdx);
		*pieceOffset = (int)((prevAllFileOffset < pieceStartOffset) ? 0 : (prevAllFileOffset - pieceStartOffset));
		*fileOffset = (pieceStartOffset < prevAllFileOffset) ? 0 : (pieceStartOffset - prevAllFileOffset);
		*blockSize = (int)(min(pieceEndOffset, targetAllFileOffset) - max(pieceStartOffset, prevAllFileOffset));
	}
	else { /* Info in Single File Mode */
		fileLength = cg_bittorrent_metainfo_getinfolength(cbm);
		if (fileLength < pieceStartOffset)
			return FALSE;
		*pieceOffset = 0;
		*fileOffset = pieceStartOffset;
		*blockSize = (int)(min(pieceEndOffset, fileLength ) - pieceStartOffset);
	}

	if (*pieceOffset < 0 || *fileOffset < 0 || *blockSize  <= 0)
		return FALSE;

	return TRUE;
}
