/******************************************************************
*
*	CyberBittorrent for C
*
*	Copyright (C) Satoshi Konno 2007
*
*	File: cmetainfo.h
*
*	Revision:
*
*	01/25/07
*		- first revision
*
******************************************************************/

#ifndef _CG_BITTORRENT_METAINFO_H_
#define _CG_BITTORRENT_METAINFO_H_

#include <cybergarage/net/curl.h>
#include <cybergarage/util/cstring.h>
#include <cybergarage/bittorrent/cdictionary.h>
#include <cybergarage/bittorrent/csha1.h>

#ifdef  __cplusplus
extern "C" {
#endif

/****************************************
* Define
****************************************/

#define CG_BITTORRENT_METAINFO_INFO "info"
#define CG_BITTORRENT_METAINFO_ANNOUNCE "announce"
#define CG_BITTORRENT_METAINFO_ANNOUNCELIST "announce-list"
#define CG_BITTORRENT_METAINFO_CREATIONDATE "creation date"
#define CG_BITTORRENT_METAINFO_COMMENT "comment"
#define CG_BITTORRENT_METAINFO_CREATEDBY "created by"
#define CG_BITTORRENT_METAINFO_PIECE_LENGTH "piece length"
#define CG_BITTORRENT_METAINFO_PIECES "pieces"
#define CG_BITTORRENT_METAINFO_PRIVATE "private"
#define CG_BITTORRENT_METAINFO_NAME "name"
#define CG_BITTORRENT_METAINFO_LENGTH "length"
#define CG_BITTORRENT_METAINFO_MD5SUM "md5sum"
#define CG_BITTORRENT_METAINFO_FILES "files"
#define CG_BITTORRENT_METAINFO_PATH "path"

#define CG_BITTORRENT_METAINFO_ID_DELIM "\\/"

#define CG_BITTORRENT_METAINFO_INFOHASH_SIZE CG_SHA1_HASH_SIZE

/****************************************
* Data Type
****************************************/

typedef struct _CgBittorrentMetainfo {
	BOOL headFlag;
	struct _CgBittorrentMetainfo *prev;
	struct _CgBittorrentMetainfo *next;
	CgBittorrentDictionary *dir;
	CgString *url;
	CgString *fileName;
	CgString *id;
} CgBittorrentMetainfo, CgBittorrentMetainfoList;

/****************************************
* Function (Metainfo List)
****************************************/

/**
 * Create a new metainfo list.
 *
 * \return Metainfo list.
 */
CgBittorrentMetainfoList *cg_bittorrent_metainfolist_new();

/**
 * Destroy a metainfo list.
 *
 * \param cbmList Metainfo list to destory.
 */
void cg_bittorrent_metainfolist_delete(CgBittorrentMetainfoList *cbmList);

/**
 * Clear all items of a metainfo list.
 *
 * \param cbmList Metainfo list to clear.
 */
#define cg_bittorrent_metainfolist_clear(cbmList) cg_list_clear((CgList *)cbmList, (CG_LIST_DESTRUCTORFUNC)cg_bittorrent_metainfo_delete)

/**
 * Get the size of a metainfo list.
 *
 * \param cbmList Metainfo list in question.
 *
 * \return Size of the metainfo list.
 */
#define cg_bittorrent_metainfolist_size(cbmList) cg_list_size((CgList *)cbmList)

/**
 * Get the first item from a metainfo list.
 *
 * \param cbmList Metainfo list in question.
 *
 * \return First Metainfo of the list, otherwise NULL if the list has no items.
 */
#define cg_bittorrent_metainfolist_gets(cbmList) (CgBittorrentMetainfo *)cg_list_next((CgList *)cbmList)

/**
 * Add a metainfo into a metainfo list.
 *
 * \param cbmList Metainfo list in question.
 * \param cbm Metainfo to add to the list.
 */
#define cg_bittorrent_metainfolist_add(cbmList, cbm) cg_list_add((CgList *)cbmList, (CgList *)cbm)

/**
 * Remove a metainfo from the specifeid list.
 *
 * \param cbmList Metainfo list to destory.
 * \param hashInfo HashInfo of the metainfo to remove.
 *
 * \return TRUE when the specified metainfo is removed normally, othrewise FALSE;
*/
BOOL cg_bittorrent_metainfolist_remove(CgBittorrentMetainfoList *cbmList, CgByte *infoHash);

/****************************************
* Function (Metainfo)
****************************************/

/**
 * Create a metainfo
 *
 * \return New Metainfo
 */
CgBittorrentMetainfo *cg_bittorrent_metainfo_new();

/**
 * Delete a metainfo
 *
 * \param cbm Metainfo to delete.
 */
void cg_bittorrent_metainfo_delete(CgBittorrentMetainfo *cbm);

/**
 * Get a next metainfo.
 *
 * \param cbm Metainfo in question.
 *
 * \return Next metainfo if the current metainfo has a next item, otherwise NULL.
 */
#define cg_bittorrent_metainfo_next(cbm) (CgBittorrentMetainfo *)cg_list_next((CgList *)cbm)

/**
 * Remove the specified matainfo form the list.
 *
 * \param cbm Metainfo in question.
 *
 * \return TRUE when the specified metainfo is removed norrmally, otherwise FALSE.
 */
#define cg_bittorrent_metainfo_remove(cbm) cg_list_remove((CgList *)cbm)

/**
 * Load the metainfo from a file.
 *
 * \param destCbm Destination metainfo in question.
 * \param destCbm Source metainfo in question.
 *
 * \return TRUE if the task was successful, otherwise FALSE.
 */
BOOL cg_bittorrent_metainfo_copy(CgBittorrentMetainfo *destCbm, CgBittorrentMetainfo *srcCbm);

/**
 * Load the metainfo from a file.
 *
 * \param cbm Metainfo in question.
 * \param buf Buffer to store.
 *
 * \return TRUE if the task was successful, otherwise FALSE.
 */
BOOL cg_bittorrent_metainfo_tostring(CgBittorrentMetainfo *cbm, CgString *buf);

/**
 * Get a dictionary.
 *
 * \param cbm Metainfo in question.
 *
 * \return Stored dictionary.
 */
#define cg_bittorrent_metainfo_getdictionary(cbm) (cbm->dir)

/**
 * Load the metainfo from a file.
 *
 * \param cbm Metainfo in question.
 * \param fileName The file name containing the metainfo.
 *
 * \return TRUE if the loading was successful, otherwise FALSE.
 */
BOOL cg_bittorrent_metainfo_load(CgBittorrentMetainfo *cbm, char *fileName);

/**
 * Load the metainfo from a URL.
 *
 * \param cbm Metainfo in question
 * \param url The url containing the metainfo
 *
 * \return TRUE, if the loading was successful; otherwise FALSE.
 */
BOOL cg_bittorrent_metainfo_fetch(CgBittorrentMetainfo *cbm, char *url);

/**
 * Return a dictionary element by name.
 *
 * \param cbm Metainfo in question.
 * \param name Name of the dictionary.
 *
 * \return Dictionary element if the specified name is found, otherwise NULL.
 */
#define  cg_bittorrent_metainfo_getelementbyname(cbm, name) cg_bittorrent_dictionary_getelementbyname(cbm->dir, name)

/**
 * Return a dictionary element by name.
 *
 * \param cbm Metainfo in question.
 * \param name Name of the dictionary.
 *
 * \return Bencording if the specified name is found, otherwise NULL.
 */
#define cg_bittorrent_metainfo_getvaluebyname(cbm, name) cg_bittorrent_dictionary_getvaluebyname(cbm->dir, name)

/**
 * Return a dictionary string by name.
 *
 * \param cbm Metainfo in question.
 * \param name Name of the dictionary.
 *
 * \return String of the dictionary if the specified name is found and the type is integer, otherwise NULL.
 */
#define cg_bittorrent_metainfo_getstringbyname(cbm, name) cg_bittorrent_dictionary_getstringbyname(cbm->dir, name)

/**
 * Return a dictionary integer by name.
 *
 * \param cbm Metainfo in question.
 * \param name Name of the dictionary.
 *
 * \return Value of the dictionary if the specified name is found and the type is integer, otherwise 0.
 */
#define cg_bittorrent_metainfo_getintegerbyname(cbm, name) cg_bittorrent_dictionary_getintegerbyname(cbm->dir, name)

/**
 * Return a dictionary list by name.
 *
 * \param cbm Metainfo in question.
 * \param name Name of the dictionary.
 *
 * \return List of the dictionary if the specified name is found and the type is list, otherwise NULL.
 */
#define cg_bittorrent_metainfo_getlistbyname(cbm, name) cg_bittorrent_dictionary_getlistbyname(cbm->dir, name)

/**
 * Return a dictionary by name.
 *
 * \param cbm Metainfo in question.
 * \param name Name of the dictionary.
 *
 * \return Dictionary of the dictionary if the specified name is found and the type is list, otherwise NULL.
 */
#define cg_bittorrent_metainfo_getdictionarybyname(cbm, name) cg_bittorrent_dictionary_getdictionarybyname(cbm->dir, name)

/**
 * Print the metainfo to console.
*
 * \param cbm Metainfo in question
 */
void cg_bittorrent_metainfo_print(CgBittorrentMetainfo *cbm);

/**
 * Get the info hash.
 *
 * \param cbm Metainfo in question.
 * \param infoHash Buffer to store the info hash.
 *
 * \return TRUE when the info hash was generated normally, otherwise NULL.
 */
BOOL cg_bittorrent_metainfo_getinfohash(CgBittorrentMetainfo *cbm, CgByte *infoHash);

/**
 * Set a URL.
 *
 * \param cbm Metainfo in question.
 * \param value URL to store.
 *
 */
#define cg_bittorrent_metainfo_seturl(cbm, value) cg_string_setvalue(cbm->url, value)

/**
 * Get a stored URL.
 *
 * \param cbm Metainfo in question.
 *
 * \return Stored URL.
 */
#define cg_bittorrent_metainfo_geturl(cbm) cg_string_getvalue(cbm->url)

/**
 * Set a file name.
 *
 * \param cbm Metainfo in question.
 * \param value File name to store.
 *
 */
#define cg_bittorrent_metainfo_setfilename(cbm, value) cg_string_setvalue(cbm->fileName, value)

/**
 * Get a stored file name.
 *
 * \param cbm Metainfo in question.
 *
 * \return Stored file name.
 */
#define cg_bittorrent_metainfo_getfilename(cbm) cg_string_getvalue(cbm->fileName)

/**
 * Set a ID.
 *
 * \param cbm Metainfo in question.
 * \param value ID to store.
 *
 */
#define cg_bittorrent_metainfo_setid(cbm, value) cg_string_setvalue(cbm->id, value)

/**
 * Get a stored ID.
 *
 * \param cbm Metainfo in question.
 *
 * \return Stored ID.
 */
#define cg_bittorrent_metainfo_getid(cbm) cg_string_getvalue(cbm->id)

/****************************************
* Macros
****************************************/

#define cg_bittorrent_metainfo_getinfo(cbm) cg_bittorrent_metainfo_getdictionarybyname(cbm, CG_BITTORRENT_METAINFO_INFO)
#define cg_bittorrent_metainfo_getannounce(cbm) cg_bittorrent_metainfo_getstringbyname(cbm, CG_BITTORRENT_METAINFO_ANNOUNCE)
#define cg_bittorrent_metainfo_getannouncelist(cbm) cg_bittorrent_metainfo_getstringbyname(cbm, CG_BITTORRENT_METAINFO_ANNOUNCELIST)
#define cg_bittorrent_metainfo_getcreationdate(cbm) cg_bittorrent_metainfo_getintegerbyname(cbm,CG_BITTORRENT_METAINFO_CREATIONDATE)
#define cg_bittorrent_metainfo_getcomment(cbm) cg_bittorrent_metainfo_getstringbyname(cbm, CG_BITTORRENT_METAINFO_COMMENT)
#define cg_bittorrent_metainfo_getcreateby(cbm) cg_bittorrent_metainfo_getstringbyname(cbm, CG_BITTORRENT_METAINFO_CREATEDBY)

#define cg_bittorrent_metainfo_getinfopiecelength(cbm) (int)cg_bittorrent_dictionary_getintegerbyname(cg_bittorrent_metainfo_getinfo(cbm), CG_BITTORRENT_METAINFO_PIECE_LENGTH)
#define cg_bittorrent_metainfo_getinfopieces(cbm) cg_bittorrent_dictionary_getstringbyname(cg_bittorrent_metainfo_getinfo(cbm), CG_BITTORRENT_METAINFO_PIECES)
#define cg_bittorrent_metainfo_getinfoprivate(cbm) cg_bittorrent_dictionary_getintegerbyname(cg_bittorrent_metainfo_getinfo(cbm), CG_BITTORRENT_METAINFO_PRIVATE)
#define cg_bittorrent_metainfo_getinfoname(cbm) cg_bittorrent_dictionary_getstringbyname(cg_bittorrent_metainfo_getinfo(cbm), CG_BITTORRENT_METAINFO_NAME)
#define cg_bittorrent_metainfo_getinfolength(cbm) cg_bittorrent_dictionary_getintegerbyname(cg_bittorrent_metainfo_getinfo(cbm), CG_BITTORRENT_METAINFO_LENGTH)
#define cg_bittorrent_metainfo_getinfomd5sum(cbm) cg_bittorrent_dictionary_getstringbyname(cg_bittorrent_metainfo_getinfo(cbm), CG_BITTORRENT_METAINFO_MD5SUM)
#define cg_bittorrent_metainfo_getinfofileslist(cbm) cg_bittorrent_dictionary_getlistbyname(cg_bittorrent_metainfo_getinfo(cbm), CG_BITTORRENT_METAINFO_FILES)
#define cg_bittorrent_metainfo_getinfofiles(cbm) cg_bittorrent_bencodinglist_gets(cg_bittorrent_metainfo_getinfofileslist(cbm))
#define cg_bittorrent_metainfo_getinfofilepath(cbm, index) cg_bittorrent_metainfo_getfileproperty(cbm, CG_BITTORRENT_METAINFO_PATH, index)
#define cg_bittorrent_metainfo_getinfofilelength(cbm, index) cg_bittorrent_metainfo_getfilepropertyinteger(cbm, CG_BITTORRENT_METAINFO_LENGTH, index)
#define cg_bittorrent_metainfo_getinfofilemd5sum(cbm, index) cg_bittorrent_metainfo_getfilepropertystring(cbm, CG_BITTORRENT_METAINFO_MD5SUM, index)

/****************************************
* Macros (Metainfo)
****************************************/

/**
 * Check the file mode.
 *
 * \param cbm Metainfo in question.
 *
 * \return TRUE when the file mode is multiple.
 */
#define cg_bittorrent_metainfo_ismultiplefilemode(cbm) (cg_bittorrent_metainfo_getinfofiles(cbm) ? TRUE : FALSE)

/**
 * Check the file mode.
 *
 * \param cbm Metainfo in question.
 *
 * \return TRUE when the file mode is single.
 */
#define cg_bittorrent_metainfo_issinglefilemode(cbm) (!cg_bittorrent_metainfo_ismultiplefilemode(cbm))

/****************************************
* Function (Internal)
****************************************/

int cg_bittorrent_metainfo_getnfiles(CgBittorrentMetainfo *cbm);

CgBittorrentBencoding *cg_bittorrent_metainfo_getfileproperty(CgBittorrentMetainfo *cbm, char *propName, int index);
char *cg_bittorrent_metainfo_getfilepropertystring(CgBittorrentMetainfo *cbm, char *propName, int index);
CgInt64 cg_bittorrent_metainfo_getfilepropertyinteger(CgBittorrentMetainfo *cbm, char *propName, int index);

BOOL cg_bittorrent_metainfo_parse(CgBittorrentMetainfo *cbm, char *data, int dataLen);
BOOL cg_bittorrent_metainfo_save(CgBittorrentMetainfo *cbm, char *fileName);

BOOL cg_bittorrent_metainfo_setidfromname(CgBittorrentMetainfo *cbm, char *name);

/****************************************
* Function (Metainfo)
****************************************/

BOOL cg_bittorrent_metainfo_getfileindexbypieceindex(CgBittorrentMetainfo *cbm, int pieceIdx, int *startFileIndex, int *endFileIndex);
BOOL cg_bittorrent_metainfo_getfileandpiecerangebypieceandfileindex(CgBittorrentMetainfo *cbm, int pieceIdx, int fileIdx, int *pieceOffset, int *pieceSize, CgInt64 *fileOffset, CgInt64 *fileSize);

#ifdef  __cplusplus
}
#endif

#endif
