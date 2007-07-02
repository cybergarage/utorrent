/******************************************************************
*
*	CyberBittorrent for C
*
*	Copyright (C) Satoshi Konno 2007
*
*	File: cbencoding.h
*
*	Revision:
*
*	01/25/07
*		- first revision
*
******************************************************************/

#ifndef _CG_BITTORRENT_BENCODING_H_
#define _CG_BITTORRENT_BENCODING_H_

#include <cybergarage/typedef.h>
#include <cybergarage/util/cstring.h>
#include <cybergarage/util/clist.h>
#include <cybergarage/util/cthread.h>
#include <cybergarage/util/ctime.h>
#include <cybergarage/net/csocket.h>
#include <cybergarage/net/curl.h>

#ifdef  __cplusplus
extern "C" {
#endif

/****************************************
* Define
****************************************/

#define CG_BITTORRENT_BENCODING_NONE 0x00
#define CG_BITTORRENT_BENCODING_STRING	0x01
#define CG_BITTORRENT_BENCODING_INTEGER 0x02
#define CG_BITTORRENT_BENCODING_LIST	0x04
#define CG_BITTORRENT_BENCODING_DICTIONARY 0x10

#define CG_BITTORRENT_BENCODING_DICTIONARY_ID 'd'
#define CG_BITTORRENT_BENCODING_INTEGER_ID 'i'
#define CG_BITTORRENT_BENCODING_LIST_ID 'l'
#define CG_BITTORRENT_BENCODING_TRAIL_ID 'e'
#define CG_BITTORRENT_BENCODING_DELIM ':'

typedef unsigned int CgBittorrentInteger;

/****************************************
* Data Type
****************************************/

typedef struct _CgBittorrentBencoding {
	BOOL headFlag;
	struct _CgBittorrentBencoding *prev;
	struct _CgBittorrentBencoding *next;
	int type;
	union _data {
		char *sval;
		CgInt64 ival;
		void *dval;
	} data;
	int len;
} CgBittorrentBencoding, CgBittorrentBencodingList;

/****************************************
* Function (Bencoding List)
****************************************/

/**
 * Create a new bencoding list.
 *
 * \return Bencoding list.
 */
CgBittorrentBencodingList *cg_bittorrent_bencodinglist_new();

/**
 * Destroy a bencoding list.
 *
 * \param cbbList Bencoding list to destory.
 */
void cg_bittorrent_bencodinglist_delete(CgBittorrentBencodingList *cbbList);

/**
 * Clear all items of a bencoding list.
 *
 * \param cbbList Bencoding list to clear.
 */
#define cg_bittorrent_bencodinglist_clear(cbbList) cg_list_clear((CgList *)cbbList, (CG_LIST_DESTRUCTORFUNC)cg_bittorrent_bencoding_delete)

/**
 * Get the size of a bencoding list.
 *
 * \param cbbList Bencoding list in question.
 *
 * \return Size of the bencoding list.
 */
#define cg_bittorrent_bencodinglist_size(cbbList) cg_list_size((CgList *)cbbList)

/**
 * Get the first item from a bencoding list.
 *
 * \param cbbList Bencoding list in question.
 *
 * \return First Bencoding of the list, otherwise NULL if the list has no items.
 */
#define cg_bittorrent_bencodinglist_gets(cbbList) (CgBittorrentBencoding *)cg_list_next((CgList *)cbbList)

/**
 * Add a bencoding into a bencoding list.
 *
 * \param cbbList Bencoding list in question.
 * \param cbb Bencoding to add to the list.
 */
#define cg_bittorrent_bencodinglist_add(cbbList, cbb) cg_list_add((CgList *)cbbList, (CgList *)cbb)

/****************************************
* Function (Bencoding)
****************************************/

/**
 * Create a new bencoding.
 *
 * \return New bencoding.
 */
CgBittorrentBencoding *cg_bittorrent_bencoding_new(void);

/**
 * Destroy a bencoding.
 *
 * \param cbb Bencoding to destroy.
 */
void cg_bittorrent_bencoding_delete(CgBittorrentBencoding *cbb);

/**
 * Clear a data of a bencoding.
 *
 * \param cbb Bencoding to clear.
 */
void cg_bittorrent_bencoding_clear(CgBittorrentBencoding *cbb);

/**
 * Set a bencoding type.
 *
 * \param cbb Bencoding in question.
 * \param value Type to set.
 */
#define cg_bittorrent_bencoding_settype(cbb, value) (cbb->type = value)

/**
 * Return a bencoding type.
 *
 * \param cbb Bencoding in question.
 *
 * \return Bencoding type.
 */
#define cg_bittorrent_bencoding_gettype(cbb) (cbb->type)

/**
 * Check bencoding type as string.
 *
 * \param cbb Bencoding in question.
 *
 * \return TRUE if the bencoding type as string.
 */
#define cg_bittorrent_bencoding_isstring(cbb) ((cbb->type == CG_BITTORRENT_BENCODING_STRING) ? TRUE : FALSE)

/**
 * Check bencoding type as integer.
 *
 * \param cbb Bencoding in question.
 *
 * \return TRUE if the bencoding type as integer.
 */
#define cg_bittorrent_bencoding_isinteger(cbb) ((cbb->type == CG_BITTORRENT_BENCODING_INTEGER) ? TRUE : FALSE)

/**
 * Check bencoding type as list.
 *
 * \param cbb Bencoding in question.
 *
 * \return TRUE if the bencoding type as list.
 */
#define cg_bittorrent_bencoding_islist(cbb) ((cbb->type == CG_BITTORRENT_BENCODING_LIST) ? TRUE : FALSE)

/**
 * Check bencoding type as dictionary.
 *
 * \param cbb Bencoding in question.
 *
 * \return TRUE if the bencoding type as dictionary.
 */
#define cg_bittorrent_bencoding_isdictionary(cbb) ((cbb->type == CG_BITTORRENT_BENCODING_DICTIONARY) ? TRUE : FALSE)

/**
 * Set a bencoding length.
 *
 * \param cbb Bencoding in question.
 * \param value Length to set.
 */
#define cg_bittorrent_bencoding_setlength(cbb, value) (cbb->len = value)

/**
 * Return a bencoding length.
 *
 * \param cbb Bencoding in question.
 *
 * \return Bencoding length.
 */
#define cg_bittorrent_bencoding_getlength(cbb) (cbb->len)

/**
 * Return a next bencoding.
 *
 * \param cbb Bencoding in question.
 *
 * \return Next bencoding if the current bencording has a next item, otherwise NULL.
 */
#define cg_bittorrent_bencoding_next(cbb) (CgBittorrentBencoding *)cg_list_next((CgList *)cbb)

/**
 * Set a string.
 *
 * \param cbb Bencoding in question.
 * \param value Stringe to set.
 * \param value Size of the string.
 */
void cg_bittorrent_bencoding_setstring(CgBittorrentBencoding *cbb, char *value, int valSize);

/**
 * Return a stored string.
 *
 * \param cbb Bencoding in question.
 *
 * \return Stored string if the type is CG_BITTORRENT_BENCODING_STRING, otherwise NULL.
 */
#define cg_bittorrent_bencoding_getstring(cbb) ((cbb->type == CG_BITTORRENT_BENCODING_STRING) ? cbb->data.sval : NULL)

/**
 * Set a integer.
 *
 * \param cbb Bencoding in question.
 * \param value Integer to set.
 */
void cg_bittorrent_bencoding_setinteger(CgBittorrentBencoding *cbb, CgInt64 value);

/**
 * Return a stored integer.
 *
 * \param cbb Bencoding in question.
 *
 * \return Stored integer if the type is CG_BITTORRENT_BENCODING_INTEGER, otherwise 0.
 */
#define cg_bittorrent_bencoding_getinteger(cbb) ((cbb->type == CG_BITTORRENT_BENCODING_INTEGER) ? cbb->data.ival : 0)

/**
 * Set a bencoding as a list head.
 *
 * \param cbb Bencoding in question.
 */
void cg_bittorrent_bencoding_setlist(CgBittorrentBencoding *cbb);

/**
 * Return a stored list.
 *
 * \param cbb Bencoding in question.
 *
 * \return List if the type is CG_BITTORRENT_BENCODING_LIST, otherwise NULL.
 */
#define cg_bittorrent_bencoding_getlist(cbb) ((cbb->type == CG_BITTORRENT_BENCODING_LIST) ? cbb : NULL)

/**
 * Return a stored list items.
 *
 * \param cbb Bencoding in question.
 *
 * \return First item of the list if the type is CG_BITTORRENT_BENCODING_LIST, otherwise NULL.
 */
#define cg_bittorrent_bencoding_getlists(cbb) ((cbb->type == CG_BITTORRENT_BENCODING_LIST) ? cg_bittorrent_bencodinglist_gets(cbb) : NULL)

/**
 * Return a size of a stored list .
 *
 * \param cbb Bencoding in question.
 *
 * \return Size of the list if the type is CG_BITTORRENT_BENCODING_LIST, otherwise 0.
 */
#define cg_bittorrent_bencoding_getlistsize(cbb) ((cbb->type == CG_BITTORRENT_BENCODING_LIST) ? cg_bittorrent_bencodinglist_size(cbb) : NULL)

/**
 * Set a bencoding as a dictionary head.
 *
 * \param cbb Bencoding in question.
 * \param value Dictionary to set.
 */
void cg_bittorrent_bencoding_setdictionary(CgBittorrentBencoding *cbb, void *value);

/**
 * Return a stored dictionary.
 *
 * \param cbb Bencoding in question.
 *
 * \return List if the type is CG_BITTORRENT_BENCODING_DICTIONARY, otherwise NULL.
 */
#define cg_bittorrent_bencoding_getdictionary(cbb) ((CgBittorrentDictionary *)((cbb->type == CG_BITTORRENT_BENCODING_DICTIONARY) ? cbb->data.dval : NULL))

/****************************************
* Function (Internal)
****************************************/

BOOL cg_bittorrent_bencoding_parse(char *data, CgBittorrentBencoding **cbb, int *offset);
void cg_bittorrent_bencoding_print(CgBittorrentBencoding *cbb);
int cg_bittorrent_bencoding_tostring(CgBittorrentBencoding *cbb, CgString *str);
BOOL cg_bittorrent_bencoding_tosha1(CgBittorrentBencoding *cbb, unsigned char *buf);

#ifdef  __cplusplus
}
#endif

#endif
