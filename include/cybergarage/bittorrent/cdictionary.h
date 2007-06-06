/******************************************************************
*
*	CyberBittorrent for C
*
*	Copyright (C) Satoshi Konno 2007
*
*	File: cdictionary.h
*
*	Revision:
*
*	01/25/07
*		- first revision
*
******************************************************************/

#ifndef _CG_BITTORRENT_DICTIONARY_H_
#define _CG_BITTORRENT_DICTIONARY_H_

#include <cybergarage/bittorrent/cbencoding.h>

#ifdef  __cplusplus
extern "C" {
#endif

/****************************************
* Define
****************************************/

/****************************************
* Data Type
****************************************/

typedef struct _CgBittorrentDictionary {
	BOOL headFlag;
	struct _CgBittorrentDictionary *prev;
	struct _CgBittorrentDictionary *next;
	CgBittorrentBencoding *key;
	CgBittorrentBencoding *value;
} CgBittorrentDictionary, CgBittorrentDictionaryElement;

/****************************************
* Function (Dictionary)
****************************************/

/**
 * Create a new dictionary element.
 *
 * \return New dictionary element.
 */
CgBittorrentDictionaryElement *cg_bittorrent_dictionary_element_new(void);

/**
 * Destroy a dictionary element.
 *
 * \param dictionary Dictionary element to destroy.
 */
void cg_bittorrent_dictionary_element_delete(CgBittorrentDictionaryElement *cbdm);

/**
 * Return a next dictionary.
 *
 * \param cbdm Dictionary element in question.
 *
 * \return Next dictionary element if the current element has a next item, otherwise NULL.
 */
#define cg_bittorrent_dictionary_element_next(cbdm) (CgBittorrentDictionaryElement *)cg_list_next((CgList *)cbdm)

/**
 * Set a bencoded key.
 *
 * \param cbdm Dictionary element in question.
 * \param cbb Bencoding including a key to set.
 */
void cg_bittorrent_dictionary_element_setkey(CgBittorrentDictionaryElement *cbdm, CgBittorrentBencoding *cbb);

/**
 * Return a bencoded key.
 *
 * \param cbdm Dictionary element in question.
 *
 * \return Bencoding including a key.
 */
#define cg_bittorrent_dictionary_element_getkey(cbdm) (cbdm->key)

/**
 * Set a bencoded value.
 *
 * \param cbdm Dictionary element in question.
 * \param cbb Bencoding including a value to set.
 */
void cg_bittorrent_dictionary_element_setvalue(CgBittorrentDictionary *cbdm, CgBittorrentBencoding *cbb);

/**
 * Return a bencoded value.
 *
 * \param cbdm Dictionary in question.
 *
 * \return Bencoding including a value.
 */
#define cg_bittorrent_dictionary_element_getvalue(cbdm) (cbdm->value)

/****************************************
* Function (Dictionary)
****************************************/

/**
 * Create a new dictionary.
 *
 * \return Dictionary.
 */
CgBittorrentDictionary *cg_bittorrent_dictionary_new();

/**
 * Destroy a dictionary.
 *
 * \param cbd Dictionary to destory.
 */
void cg_bittorrent_dictionary_delete(CgBittorrentDictionary *cbd);

/**
 * Clear all items of a dictionary.
 *
 * \param cbd Dictionary to clear.
 */
#define cg_bittorrent_dictionary_clear(cbd) cg_list_clear((CgList *)cbd, (CG_LIST_DESTRUCTORFUNC)cg_bittorrent_dictionary_element_delete)

/**
 * Get the size of a dictionary.
 *
 * \param cbd Dictionary in question.
 *
 * \return Size of the dictionary list.
 */
#define cg_bittorrent_dictionary_size(cbd) cg_list_size((CgList *)cbd)

/**
 * Get the first item from a dictionary.
 *
 * \param cbd Dictionary in question.
 *
 * \return First Dictionary element of the directory, otherwise NULL if the list has no elements.
 */
#define cg_bittorrent_dictionary_gets(cbd) (CgBittorrentDictionaryElement *)cg_list_next((CgList *)cbd)

/**
 * Add a dictionary into a dictionary list.
 *
 * \param cbd Dictionary in question.
 * \param cbdm Dictionary element to add to the dictionary.
 */
#define cg_bittorrent_dictionary_add(cbd, cbdm) cg_list_add((CgList *)cbd, (CgList *)cbdm)

/**
 * Return a dictionary element by name.
 *
 * \param cbm Dictionary in question.
 * \param name Name of the dictionary.
 *
 * \return Dictionary element if the specified name is found, otherwise NULL.
 */
CgBittorrentDictionaryElement *cg_bittorrent_dictionary_getelementbyname(CgBittorrentDictionary *cbd, char *name);

/**
 * Return a dictionary element by name.
 *
 * \param cbm Dictionary in question.
 * \param name Name of the dictionary.
 *
 * \return Bencording if the specified name is found, otherwise NULL.
 */
CgBittorrentBencoding *cg_bittorrent_dictionary_getvaluebyname(CgBittorrentDictionary *cbd, char *name);

/**
 * Return a dictionary string by name.
 *
 * \param cbm Dictionary in question.
 * \param name Name of the dictionary.
 *
 * \return String of the dictionary if the specified name is found and the type is integer, otherwise NULL.
 */
char *cg_bittorrent_dictionary_getstringbyname(CgBittorrentDictionary *cbd, char *name);

/**
 * Return a dictionary integer by name.
 *
 * \param cbm Dictionary in question.
 * \param name Name of the dictionary.
 *
 * \return Value of the dictionary if the specified name is found and the type is integer, otherwise 0.
 */
CgInt64 cg_bittorrent_dictionary_getintegerbyname(CgBittorrentDictionary *cbd, char *name);

/**
 * Return a dictionary list by name.
 *
 * \param cbm Dictionary in question.
 * \param name Name of the dictionary.
 *
 * \return List of the dictionary if the specified name is found and the type is list, otherwise NULL.
 */
CgBittorrentBencodingList *cg_bittorrent_dictionary_getlistbyname(CgBittorrentDictionary *cbd, char *name);

/****************************************
* Function (Internal)
****************************************/

BOOL cg_bittorrent_dictionary_parse(CgBittorrentDictionary *cbd, char *data, int *offset);
void cg_bittorrent_dictionary_print(CgBittorrentDictionary *cbd);
void cg_bittorrent_dictionary_setprintindent(int indent);
void cg_bittorrent_dictionary_tostring(CgBittorrentDictionary *cbd, CgString *str);

#ifdef  __cplusplus
}
#endif

#endif
