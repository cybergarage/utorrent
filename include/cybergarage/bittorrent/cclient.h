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

/****************************************
* Define
****************************************/

#define CG_BITTORRENT_CLIENT_REST_VERSION1 "V1"

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
	CgHttpServer *httpServer;
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

#ifdef  __cplusplus
}
#endif

#endif
