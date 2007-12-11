/******************************************************************
*
*	CyberBittorrent for C
*
*	Copyright (C) Satoshi Konno 2007
*
*	File: cpropertymgr.h
*
*	Revision:
*
*	11/30/07
*		- first revision
*
******************************************************************/

#ifndef _CG_BITTORRENT_PROPERTYMGR_H_
#define _CG_BITTORRENT_PROPERTYMGR_H_

#include <cybergarage/bittorrent/ctracker.h>

#ifdef  __cplusplus
extern "C" {
#endif

/****************************************
* Define
****************************************/

#define CG_BITTORRENT_PROPERTYMGR_VALUE_MAXSIZE 512

#define CG_BITTORRENT_PROPERTYMGR_CATEGORY_MESSAGE "Message"
#define CG_BITTORRENT_PROPERTYMGR_KEY_REQUEST_UNIT "RequestUnit"
#define CG_BITTORRENT_PROPERTYMGR_KEY_REQUEST_AMOUNT_MAX "RequestAmountMax"
#define CG_BITTORRENT_PROPERTYMGR_KEY_REQUEST_RETRY_MAX "RequestRetryMax"
#define CG_BITTORRENT_PROPERTYMGR_KEY_REQUEST_TIMEOUT "RequestTimeout"

#define CG_BITTORRENT_PROPERTYMGR_KEY_REQUEST_UNIT_DEFAULT (16*1024)
#define CG_BITTORRENT_PROPERTYMGR_KEY_REQUEST_AMOUNT_MAX_DEFAULT (128*1024)
#define CG_BITTORRENT_PROPERTYMGR_KEY_REQUEST_RETRY_MAX_DEFAULT 20
#define CG_BITTORRENT_PROPERTYMGR_KEY_REQUEST_TIMEOUT_DEFAULT 5

/****************************************
* Data Type
****************************************/

/* Value */
typedef BOOL (*CG_BITTORRENT_PROPERTYMGR_SETVALUE)(void *propmgr, char *category, char *key, char *value);
typedef BOOL (*CG_BITTORRENT_PROPERTYMGR_GETVALUE)(void *propmgr, char *category, char *key, char *buf, int bufSize);

typedef struct _CgBittorrentPropertyMgr {
	/* Value */
	CG_BITTORRENT_PROPERTYMGR_SETVALUE setValueFunc;
	CG_BITTORRENT_PROPERTYMGR_GETVALUE getValueFunc;
	/* User Data */
	void *userData;
} CgBittorrentPropertyMgr;

/****************************************
* Function
****************************************/

/**
 * Create a new propertymgr.
 *
 * \return New propertymgr.
 */
CgBittorrentPropertyMgr *cg_bittorrent_propertymgr_new(void);

/**
 * Destroy a propertymgr.
 *
 * \param propmgr Property manager to destroy.
 */
void cg_bittorrent_propertymgr_delete(CgBittorrentPropertyMgr *propmgr);

/**
 * Check if the deveice is initialized normally.
 *
 * \param propmgr Property manager to check.
 *
 * \return TRUE if the specified block device manager is initialized normally.
 */
BOOL cg_bittorrent_propertymgr_isvalidated(CgBittorrentPropertyMgr *propmgr);

/****************************************
* Function
****************************************/

/**
 * Set a function to set a property,
 *
 * \param propmgr Property manager in question.
 * \param func Function to set.
 */
#define cg_bittorrent_propertymgr_setsetvaluefunc(propmgr, func) (propmgr->setValueFunc = func)

/**
 * Return a function to set a property,
 *
 * \param propmgr Property manager in question.
 *
 * \return Stored function
 */
#define cg_bittorrent_propertymgr_getsetvaluefunc(propmgr) (propmgr->setValueFunc)

/**
 * Set a function to get a property,
 *
 * \param propmgr Property manager in question.
 * \param func Function to set.
 */
#define cg_bittorrent_propertymgr_setgetvaluefunc(propmgr, func) (propmgr->getValueFunc = func)

/**
 * Return a function to get a property,
 *
 * \param propmgr Property manager in question.
 *
 * \return Stored function
 */
#define cg_bittorrent_propertymgr_getgetvaluefunc(propmgr) (propmgr->getValueFunc)

/****************************************
* Function (User Data)
****************************************/

/**
 * Set a user data.
 *
 * \param propmgr Property manager in question.
 * \param value User data to set.
 */
#define cg_bittorrent_propertymgr_setuserdata(propmgr, value) (propmgr->userData = value)

/**
 * Get a user data.
 *
 * \param propmgr Property manager in question.
 *
 * \return User data
 */
#define cg_bittorrent_propertymgr_getuserdata(propmgr) (propmgr->userData)

/****************************************
* Function
****************************************/

/**
 * Set a string value.
 *
 * \param propmgr Property manager in question.
 * \param category Category of the value to be set.
 * \param key Key of the value to be set.
 * \param value Value to be set.
 *
 * \return TRUE if the function succeeds, otherwise FALSE.
 */
#define cg_bittorrent_propertymgr_setstringvalue(propmgr, category, key, value) ((propmgr->setValueFunc) ? propmgr->setValueFunc(propmgr, category, key, value) : FALSE)

/**
 * Get a string value.
 *
 * \param propmgr Property manager in question.
 * \param category Category of the value to be set.
 * \param key Key of the value to be set.
 * \param buf Buffer to be set.
 * \param bufSize Size of the buffer.
 * \param defaultValue Default value when the method is failed.
 *
 * \return TRUE if the function succeeds, otherwise FALSE.
 */
char *cg_bittorrent_propertymgr_getstringvalue(CgBittorrentPropertyMgr *propmgr, char *category, char *key, char *buf, int bufSize, char *defaultValue);

/**
 * Set a integer value.
 *
 * \param propmgr Property manager in question.
 * \param category Category of the value to be set.
 * \param key Key of the value to be set.
 * \param value Value to be set.
 *
 * \return TRUE if the function succeeds, otherwise FALSE.
 */
BOOL cg_bittorrent_propertymgr_setintegervalue(CgBittorrentPropertyMgr *propmgr, char *category, char *key, int value);

/**
 * Get a integer value.
 *
 * \param propmgr Property manager in question.
 * \param category Category of the value to be set.
 * \param key Key of the value to be set.
 * \param defaultValue Default value when the method is failed.
 *
 * \return Stored value if the function succeeds, otherwise 0.
 */
int cg_bittorrent_propertymgr_getintegervalue(CgBittorrentPropertyMgr *propmgr, char *category, char *key, int defaultValue);

/****************************************
* Property
****************************************/

#define cg_bittorrent_propertymgr_message_setrequestunit(propmgr, value) cg_bittorrent_propertymgr_setintegervalue(propmgr, CG_BITTORRENT_PROPERTYMGR_CATEGORY_MESSAGE, CG_BITTORRENT_PROPERTYMGR_KEY_REQUEST_UNIT, value)
#define cg_bittorrent_propertymgr_message_getrequestunit(propmgr) cg_bittorrent_propertymgr_getintegervalue(propmgr, CG_BITTORRENT_PROPERTYMGR_CATEGORY_MESSAGE, CG_BITTORRENT_PROPERTYMGR_KEY_REQUEST_UNIT, CG_BITTORRENT_PROPERTYMGR_KEY_REQUEST_UNIT_DEFAULT)

#define cg_bittorrent_propertymgr_message_setrequestretrymax(propmgr, value) cg_bittorrent_propertymgr_setintegervalue(propmgr, CG_BITTORRENT_PROPERTYMGR_CATEGORY_MESSAGE, CG_BITTORRENT_PROPERTYMGR_KEY_REQUEST_RETRY_MAX, value)
#define cg_bittorrent_propertymgr_message_getrequestretrymax(propmgr) cg_bittorrent_propertymgr_getintegervalue(propmgr, CG_BITTORRENT_PROPERTYMGR_CATEGORY_MESSAGE, CG_BITTORRENT_PROPERTYMGR_KEY_REQUEST_RETRY_MAX, CG_BITTORRENT_PROPERTYMGR_KEY_REQUEST_RETRY_MAX_DEFAULT)

#define cg_bittorrent_propertymgr_message_setrequestamountmax(propmgr, value) cg_bittorrent_propertymgr_setintegervalue(propmgr, CG_BITTORRENT_PROPERTYMGR_CATEGORY_MESSAGE, CG_BITTORRENT_PROPERTYMGR_KEY_REQUEST_AMOUNT_MAX, value)
#define cg_bittorrent_propertymgr_message_getrequestamountmax(propmgr) cg_bittorrent_propertymgr_getintegervalue(propmgr, CG_BITTORRENT_PROPERTYMGR_CATEGORY_MESSAGE, CG_BITTORRENT_PROPERTYMGR_KEY_REQUEST_AMOUNT_MAX, CG_BITTORRENT_PROPERTYMGR_KEY_REQUEST_AMOUNT_MAX_DEFAULT)

#define cg_bittorrent_propertymgr_message_setrequesttimeout(propmgr, value) cg_bittorrent_propertymgr_setintegervalue(propmgr, CG_BITTORRENT_PROPERTYMGR_CATEGORY_MESSAGE, CG_BITTORRENT_PROPERTYMGR_KEY_REQUEST_TIMEOUT, value)
#define cg_bittorrent_propertymgr_message_getrequesttimeout(propmgr) cg_bittorrent_propertymgr_getintegervalue(propmgr, CG_BITTORRENT_PROPERTYMGR_CATEGORY_MESSAGE, CG_BITTORRENT_PROPERTYMGR_KEY_REQUEST_TIMEOUT, CG_BITTORRENT_PROPERTYMGR_KEY_REQUEST_TIMEOUT_DEFAULT)

#ifdef  __cplusplus
}
#endif

#endif
