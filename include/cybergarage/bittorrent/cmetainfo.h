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

#include <cybergarage/bittorrent/cdictionary.h>

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

/****************************************
* Data Type
****************************************/

typedef struct _CgBittorrentMetainfo {
	CgBittorrentDictionary *dir;
} CgBittorrentMetainfo;

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
 * \return TRUE, if the loading was successful; otherwise FALSE.
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
BOOL cg_bittorrent_metainfo_getinfohash(CgBittorrentMetainfo *cbm, unsigned char *infoHash);

/****************************************
* Macros
****************************************/

#define cg_bittorrent_metainfo_getinfo(cbb) cg_bittorrent_metainfo_getdictionarybyname(cbb, CG_BITTORRENT_METAINFO_INFO)
#define cg_bittorrent_metainfo_getannounce(cbb) cg_bittorrent_metainfo_getstringbyname(cbb, CG_BITTORRENT_METAINFO_ANNOUNCE)
#define cg_bittorrent_metainfo_getannouncelist(cbb) cg_bittorrent_metainfo_getstringbyname(cbb, CG_BITTORRENT_METAINFO_ANNOUNCELIST)
#define cg_bittorrent_metainfo_getcreationdate(cbb) cg_bittorrent_metainfo_getintegerbyname(cbb,CG_BITTORRENT_METAINFO_CREATIONDATE)
#define cg_bittorrent_metainfo_getcomment(cbb) cg_bittorrent_metainfo_getstringbyname(cbb, CG_BITTORRENT_METAINFO_COMMENT)
#define cg_bittorrent_metainfo_getcreateby(cbb) cg_bittorrent_metainfo_getstringbyname(cbb, CG_BITTORRENT_METAINFO_CREATEDBY)

#define cg_bittorrent_metainfo_getinfopiecelength(cbb) cg_bittorrent_dictionary_getintegerbyname(cg_bittorrent_metainfo_getinfo(cbb), CG_BITTORRENT_METAINFO_PIECE_LENGTH)
#define cg_bittorrent_metainfo_getinfopieces(cbb) cg_bittorrent_metainfo_getstringbyname(cg_bittorrent_metainfo_getinfo(cbb), CG_BITTORRENT_METAINFO_PIECES)
#define cg_bittorrent_metainfo_getinfoprivate(cbb) cg_bittorrent_dictionary_getintegerbyname(cg_bittorrent_metainfo_getinfo(cbb), CG_BITTORRENT_METAINFO_PRIVATE)
#define cg_bittorrent_metainfo_getinfoname(cbb) cg_bittorrent_dictionary_getstringbyname(cg_bittorrent_metainfo_getinfo(cbb), CG_BITTORRENT_METAINFO_NAME)
#define cg_bittorrent_metainfo_getinfolength(cbb) cg_bittorrent_dictionary_getintegerbyname(cg_bittorrent_metainfo_getinfo(cbb), CG_BITTORRENT_METAINFO_LENGTH)
#define cg_bittorrent_metainfo_getinfomd5sum(cbb) cg_bittorrent_dictionary_getstringbyname(cg_bittorrent_metainfo_getinfo(cbb), CG_BITTORRENT_METAINFO_MD5SUM)
#define cg_bittorrent_metainfo_getinfofileslist(cbb) cg_bittorrent_dictionary_getlistbyname(cg_bittorrent_metainfo_getinfo(cbb), CG_BITTORRENT_METAINFO_FILES)
#define cg_bittorrent_metainfo_getinfofiles(cbb) cg_bittorrent_bencodinglist_gets(cg_bittorrent_metainfo_getinfofileslist(cbb))

/****************************************
* Function (Metainfo)
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

BOOL cg_bittorrent_metainfo_parse(CgBittorrentMetainfo *cbm, char *data, int dataLen);
BOOL cg_bittorrent_metainfo_save(CgBittorrentMetainfo *cbm, char *fileName);

#ifdef  __cplusplus
}
#endif

#endif
