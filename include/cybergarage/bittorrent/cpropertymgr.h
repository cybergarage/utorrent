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
* Function (BlockDevMgr)
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
* Function (Metainfo)
****************************************/

/**
 * Set a function to add a metainfo.
 *
 * \param propmgr Property manager in question.
 * \param func Function to set.
 */
#define cg_bittorrent_propertymgr_setaddmetainfofunc(propmgr, func) (propmgr->setValueFunc = func)

/**
 * Return a function to add a metainfo.
 *
 * \param propmgr Property manager in question.
 *
 * \return Specifided function
 */
#define cg_bittorrent_propertymgr_getaddmetainfofunc(propmgr) (propmgr->setValueFunc)

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
* Function (Metainfo)
****************************************/

/**
 * Set a value.
 *
 * \param propmgr Property manager in question.
 * \param category Category of the value to be set.
 * \param key Key of the value to be set.
 * \param value Value to be set.
 *
 * \return TRUE if the function succeeds, otherwise FALSE.
 */
#define cg_bittorrent_propertymgr_setvalue(propmgr, category, key, value) ((propmgr->setValueFunc) ? propmgr->setValueFunc(propmgr, category, key, value) : FALSE)

/**
 * Get a value.
 *
 * \param propmgr Property manager in question.
 * \param category Category of the value to be set.
 * \param key Key of the value to be set.
 * \param buf Buffer to be set.
 * \param bufSize Size of the buffer.
 *
 * \return TRUE if the function succeeds, otherwise FALSE.
 */
#define cg_bittorrent_propertymgr_getvalue(propmgr, category, key, buf, bufSize) ((propmgr->getValueFunc) ? propmgr->getValueFunc(propmgr, category, key, buf, bufSize) : FALSE)

#ifdef  __cplusplus
}
#endif

#endif
