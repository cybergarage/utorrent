/******************************************************************
*
*	CyberBittorrent for C
*
*	Copyright (C) Satoshi Konno 2007
*
*	File: cbittorrent.h
*
*	Revision:
*
*	01/25/07
*		- first revision
*
******************************************************************/

#ifndef _CG_BITTORRENT_CLIENT_H_
#define _CG_BITTORRENT_CLIENT_H_

#ifdef  __cplusplus
extern "C" {
#endif

#include <cybergarage/http/chttp.h>
#include <cybergarage/net/csocket.h>
#include <cybergarage/util/cmutex.h>
#include <cybergarage/bittorrent/cmetainfo.h>
#include <cybergarage/bittorrent/cblockdevmgr.h>
#include <cybergarage/bittorrent/cstrategymgr.h>
#include <cybergarage/bittorrent/cpropertymgr.h>
#include <cybergarage/bittorrent/csha1.h>

/****************************************
* Define
****************************************/

#define CG_BITTORRENT_CLIENT_ID "CG"
#define CG_BITTORRENT_CLIENT_VER "0500"
#define CG_BITTORRENT_CLIENT_PEERID_SIZE CG_SHA1_HASH_SIZE

#define CG_BITTORRENT_CLIENT_REST_VERSION1 "V1"

#define CG_BITTORRENT_CLIENT_DEFAULT_HTTP_PORT 8188
#define CG_BITTORRENT_CLIENT_DEFAULT_SERVER_PORT 8288
#define CG_BITTORRENT_CLIENT_DEFAULT_MAX_UPLOAD_CONNECTIONS 5
#define CG_BITTORRENT_CLIENT_DEFAULT_MAX_DOWNLOAD_CONNECTIONS 5

#define CG_BITTORRENT_CLIENT_REST_PARAM_URL "url"
#define CG_BITTORRENT_CLIENT_REST_PARAM_TORRENTID "TorrentID"

#define CG_BITTORRENT_CLIENT_REST_PATH_ADDTORRENT "addTorrent"
#define CG_BITTORRENT_CLIENT_REST_PATH_GETTORRENTIDS "getTorrentIDs"
#define CG_BITTORRENT_CLIENT_REST_PATH_GETTORRENTINFO "getTorrentInfo"

#define CG_BITTORRENT_CLIENT_REST_STATUSCODE_OK 200
#define CG_BITTORRENT_CLIENT_REST_STATUSCODE_INVALIDARGS 402
#define CG_BITTORRENT_CLIENT_REST_STATUSCODE_ACTIONFAILED 501

/****************************************
* Data Type
****************************************/

typedef struct _CgBittorrentClient {
	CgBittorrentBlockDeviceMgr *blockDevMgr;
	CgBittorrentStrategyMgr *stgyMgr;
	CgBittorrentPropertyMgr *propMgr;
	CgBittorrentMetainfoList *metaInfoList;
	CgMutex *mutex;
	/* HTTP Server */
	CgHttpServer *httpServer;
	int httpServerPort;
	/* Socket Server */
	CgSocket* serverSock;
	int serverPort;
	int maxUploadConnections;
	int maxDownloadConnections;
	/* Thread */
	CgThread *acceptThread;
	CgThread *clientThreads;
} CgBittorrentClient;

/****************************************
* Function
****************************************/

/**
 * Create a new instance of the bittorrent client.
 *
 * \return New instance.
 */
CgBittorrentClient *cg_bittorrent_client_new();

/**
 * Destroy a instance of the bittorrent client.
 *
 * \param cbc Client to destory.
 */
void cg_bittorrent_client_delete(CgBittorrentClient *cbc);

/**
 * Lock the specified instance.
 *
 * \param cbc Client to destory.
 */
#define cg_bittorrent_client_lock(cbc) cg_mutex_lock(cbc->mutex);

/**
 * Unlock the specified instance.
 *
 * \param cbc Client to destory.
 */
#define cg_bittorrent_client_unlock(cbc) cg_mutex_unlock(cbc->mutex);

/**
 * Set a matainfo list.
 *
 * \param cbc  Client in question.
 * \param value matainfo list to set.
 */
#define cg_bittorrent_client_setmetainfolist(cbc, value) (cbc->metaInfoList = value)

/**
 * Return a  matainfo list of the specified download manager.
 *
 * \param cbc  Client in question.
 *
 * \return Stored matainfo list.
 */
#define cg_bittorrent_client_getmetainfolist(cbc) (cbc->metaInfoList)

/**
 * Set a block device manager.
 *
 * \param cbc  Client in question.
 * \param value Block device manager to set.
 */
#define cg_bittorrent_client_setblockdevicemgr(cbc, value) (cbc->blockDevMgr = value)

/**
 * Return a  blockdevice manager of the specified download manager.
 *
 * \param cbc  Client in question.
 *
 * \return Stored block device manager.
 */
#define cg_bittorrent_client_getblockdevicemgr(cbc) (cbc->blockDevMgr)

/**
 * Set a strategy manager of the specified download manager.
 *
 * \param cbc  Client in question.
 * \param value Strategy manager  to set.
 */
#define cg_bittorrent_client_setstrategymgr(cbc, value) (cbc->stgyMgr = value)

/**
 * Return a  strategy manager of the specified download manager.
 *
 * \param cbc Download manager in question.
 *
 * \return Stored strategy manager.
 */
#define cg_bittorrent_client_getstrategymgr(cbc) (cbc->stgyMgr)

/**
 * Set a property manager of the specified download manager.
 *
 * \param cbc  Client in question.
 * \param value Property manager  to set.
 */
#define cg_bittorrent_client_setpropertymgr(cbc, value) (cbc->propMgr = value)

/**
 * Return a  property manager of the specified download manager.
 *
 * \param cbc Download manager in question.
 *
 * \return Stored property manager.
 */
#define cg_bittorrent_client_getpropertymgr(cbc) (cbc->propMgr)

/**
 * Set a  port number for HTTP server
 *
 * \param cbc  Client in question.
 * \param value Port number
 *
 */
#define cg_bittorrent_client_sethttpserverport(cbc, value) (cbc->httpServerPort = value)

/**
 * Return a  port number for HTTP server
 *
 * \param cbc  Client in question.
 *
 * \return Stored port number.
 */
#define cg_bittorrent_client_gethttpserverport(cbc) (cbc->httpServerPort)

/**
 * Set a  port number for socket server
 *
 * \param cbc  Client in question.
 * \param value Port number
 *
 */
#define cg_bittorrent_client_setserverport(cbc, value) (cbc->serverPort = value)

/**
 * Return a  port number for socket server
 *
 * \param cbc  Client in question.
 *
 * \return Stored port number.
 */
#define cg_bittorrent_client_getserverport(cbc) (cbc->serverPort)

/**
 * Set a  port number for socket server
 *
 * \param cbc  Client in question.
 * \param value Port number
 *
 */
#define cg_bittorrent_client_setserverport(cbc, value) (cbc->serverPort = value)

/**
 * Return a  port number for socket server
 *
 * \param cbc  Client in question.
 *
 * \return Stored port number.
 */
#define cg_bittorrent_client_getserverport(cbc) (cbc->serverPort)

/**
 * Set a  max connections for upload
 *
 * \param cbc  Client in question.
 * \param value Max connections for upload
 *
 */
#define cg_bittorrent_client_setmaxuploadconnections(cbc, value) (cbc->maxUploadConnections = value)

/**
 * Return a  max connections for upload
 *
 * \param cbc  Client in question.
 *
 * \return Stored max connections for upload
 */
#define cg_bittorrent_client_getmaxuploadconnections(cbc) (cbc->maxUploadConnections)

/**
 * Set a  max connections for download
 *
 * \param cbc  Client in question.
 * \param value Max connections for download
 *
 */
#define cg_bittorrent_client_setmaxdownloadconnections(cbc, value) (cbc->maxDownloadConnections = value)

/**
 * Return a  max connections for download
 *
 * \param cbc  Client in question.
 *
 * \return Stored max connections for download
 */
#define cg_bittorrent_client_getmaxdownloadconnections(cbc) (cbc->maxDownloadConnections)

/**
 * Start the specified client.
 *
 * \param cbc Client to check.
 *
 * \return TRUE when the client is avairable, otherwise FALSE.
 */
BOOL cg_bittorrent_client_isready(CgBittorrentClient *cbc);

/**
 * Start the specified client.
 *
 * \param cbc Client to start.
 *
 * \return TRUE when the client is started normally, otherwise FALSE.
 */
BOOL cg_bittorrent_client_start(CgBittorrentClient *cbc);

/**
 * Stop the specified client.
  *
 * \param cbc Client to stop.
 *
 * \return TRUE when the client is stopped normally, otherwise FALSE.
 */
BOOL cg_bittorrent_client_stop(CgBittorrentClient *cbc);

/****************************************
* Function (Download)
****************************************/

BOOL cg_bittorrent_client_createpeerid(CgBittorrentClient *cbc, CgByte *peerid);
BOOL cg_bittorrent_client_addmetainfo(CgBittorrentClient *cbc, CgBittorrentMetainfo *cbm);
BOOL cg_bittorrent_client_removemetainfo(CgBittorrentClient *cbc, CgByte *infoHash);

/****************************************
* Function (Internal)
****************************************/

BOOL cg_bittorrent_client_server_start(CgBittorrentClient *cbc);
BOOL cg_bittorrent_client_server_stop(CgBittorrentClient *cbc);
#define cg_bittorrent_client_getserversocket(cbc) (cbc->serverSock)

#ifdef  __cplusplus
}
#endif

#endif

