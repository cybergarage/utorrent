/******************************************************************
*
*	CyberBittorrent for C
*
*	Copyright (C) Satoshi Konno 2007
*
*	File: cxmlfile.h
*
*	Revision:
*
*	12/11/07
*		- first revision
*
******************************************************************/

#ifndef _CG_BITTORRENT_PROPERTYMGR_XMLFILE_H_
#define _CG_BITTORRENT_PROPERTYMGR_XMLFILE_H_

#include <cybergarage/xml/cxml.h>
#include <cybergarage/bittorrent/cpropertymgr.h>

#ifdef  __cplusplus
extern "C" {
#endif

/****************************************
* Define
****************************************/

#if defined(WIN32)
#define CG_BITTORRENT_PROPERTYMGR_XMLFILE_DIRECTORY
#else
#define CG_BITTORRENT_PROPERTYMGR_XMLFILE_DIRECTORY ".cgtorrent"
#endif

#define CG_BITTORRENT_PROPERTYMGR_XMLFILE_FILENAME "cgtorrent.properties"

/****************************************
* User Data
****************************************/

 typedef struct _CgBittorrentXmlFilePropertyMgrData {
	CgXmlNodeList *rootNode;
} CgBittorrentXmlFilePropertyMgrData;

/****************************************
* Function
****************************************/

/**
 * Create a new propertymgr.
 *
 * \return New propertymgr.
 */
CgBittorrentPropertyMgr *cg_bittorrent_xmlfile_propertymgr_new(void);

/**
 * Destroy a propertymgr.
 *
 * \param propMgr Property manager to destroy.
 */
void cg_bittorrent_xmlfile_propertymgr_delete(CgBittorrentPropertyMgr *propMgr);

/****************************************
* Macros
****************************************/

#define cg_bittorrent_xmlfile_propertymgr_getuserdata(propMgr) ((CgBittorrentXmlFilePropertyMgrData *)cg_bittorrent_propertymgr_getuserdata(propMgr))
#define cg_bittorrent_xmlfile_propertymgr_getrootnode(propMgr) (((CgBittorrentXmlFilePropertyMgrData *)cg_bittorrent_propertymgr_getuserdata(propMgr))->rootNode)

#ifdef  __cplusplus
}
#endif

#endif
