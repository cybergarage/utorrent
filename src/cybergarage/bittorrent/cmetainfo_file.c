/******************************************************************
*
*	CyberBittorrent for C
*
*	Copyright (C) Satoshi Konno 2007
*
*	File: cmetainfo_file.c
*
*	Revision:
*
*	01/30/07
*		- first revision
*
******************************************************************/

#include <cybergarage/bittorrent/cmetainfo.h>

#include <sys/stat.h>

/****************************************
* cg_bittorrent_metainfo_load
****************************************/

BOOL cg_bittorrent_metainfo_load(CgBittorrentMetainfo *cbm, char *fileName)
{
	struct stat fileStat;
	size_t fileSize;
	FILE *fp;
	size_t nRead;
	size_t nTotalRead;
	char *dataBuf;
#if (defined(WIN32) && defined(WINCE)) || defined(UNICODE)
	TCHAR wFileName[MAX_PATH];
#endif
	BOOL parseResult;

	if (!cbm)
		return FALSE;
#if (defined(WIN32) && defined(WINCE)) || defined(UNICODE)
	MultiByteToWideChar(CP_UTF8, 0, fileName, -1, wFileName, (MAX_PATH-1));
#endif

	if(stat(fileName, &fileStat ) == -1)
		return FALSE;
	
	fileSize = (size_t)fileStat.st_size;
	if (fileSize <= 0)
		return FALSE;

	dataBuf = malloc(fileSize+1);
	if (!dataBuf)
		return FALSE;

	fp = fopen(fileName, "rb");
	if (fp == NULL) {
		free(dataBuf);
		return FALSE;
	}

	nTotalRead = 0;
	nRead = fread(dataBuf, sizeof(char), fileSize, fp);
	while (0 < nRead && (nTotalRead + nRead) <= fileSize) {
		nTotalRead += nRead;
		nRead = fread((dataBuf + nTotalRead), sizeof(char), (fileSize - nTotalRead), fp);
	}
	fclose(fp);

	if (fileSize != nTotalRead) {
		free(dataBuf);
		return FALSE;
	}
	
	dataBuf[fileSize] = '\0';
	parseResult = cg_bittorrent_metainfo_parse(cbm, dataBuf, fileSize);
	free(dataBuf);

	return parseResult;
}

/****************************************
* cg_bittorrent_metainfo_save
****************************************/

BOOL cg_bittorrent_metainfo_save(CgBittorrentMetainfo *cbm, char *fileName)
{
	FILE *fp;
	CgString *str;
	CgBittorrentDictionary *dir;

	if (!cbm)
		return FALSE;

	dir = cg_bittorrent_metainfo_getdictionary(cbm);
	if (!cbm)
		return FALSE;

	str = cg_string_new();
	cg_bittorrent_dictionary_tostring(dir, str);

	fp = fopen(fileName, "wb");
	if (fp) {
		fwrite(cg_string_getvalue(str), sizeof(char), cg_string_length(str), fp);
		fclose(fp);
	}

	cg_string_delete(str);

	return (fp ? TRUE : FALSE);
}
