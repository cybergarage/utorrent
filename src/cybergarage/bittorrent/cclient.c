/******************************************************************
*
*	CyberBittorrent for C
*
*	Copyright (C) Satoshi Konno 2007
*
*	File: cbittorrent.c
*
*	Revision:
*
*	01/30/07
*		- first revision
*
******************************************************************/

#include <cybergarage/bittorrent/cclient.h>
#include <cybergarage/net/cinterface.h>

/****************************************
* Prototype
*****************************************/

void cg_bittorrent_client_httplistener(CgHttpRequest *);
BOOL cg_bittorrent_client_initialize(CgBittorrentClient *cbc);
BOOL cg_bittorrent_client_clean(CgBittorrentClient *cbc);

/****************************************
* cg_bittorrent_client_new
****************************************/

CgBittorrentClient *cg_bittorrent_client_new()
{
	CgBittorrentClient *cbc;
	CgBittorrentMetainfoList *cbmList;

	cbc = (CgBittorrentClient *)malloc(sizeof(CgBittorrentClient));
	if (!cbc)
		return NULL;

	/* Mutex */
	cbc->mutex = cg_mutex_new();
	if (!cbc->mutex) {
		free(cbc);
		return NULL;
	}

	/* Metainfo */
	cbmList = cg_bittorrent_metainfolist_new();
	if (!cbmList) {
		free(cbc);
		return NULL;
	}
	cg_bittorrent_client_setmetainfolist(cbc, cbmList);

	/* Socket Server */
	cbc->serverSock = cg_socket_stream_new();
	if (!cbc->serverSock) {
		free(cbc);
		return NULL;
	}
	cg_bittorrent_client_setserverport(cbc, CG_BITTORRENT_CLIENT_DEFAULT_SERVER_PORT);

	/* HTTP Server */
	cbc->httpServer = cg_http_server_new();
	if (!cbc->httpServer) {
		free(cbc);
		cg_socket_delete(cbc->serverSock );
		return NULL;
	}
	cg_http_server_setlistener(cbc->httpServer, cg_bittorrent_client_httplistener);
	cg_http_server_setuserdata(cbc->httpServer, cbc);
	cg_bittorrent_client_sethttpserverport(cbc, CG_BITTORRENT_CLIENT_DEFAULT_HTTP_PORT);

	/* Manager */
	cg_bittorrent_client_setfilemgr(cbc, NULL);
	cg_bittorrent_client_setstrategymgr(cbc, NULL);

	/* Other Settings */
	cg_bittorrent_client_setmaxuploadconnections(cbc, CG_BITTORRENT_CLIENT_DEFAULT_MAX_UPLOAD_CONNECTIONS);
	cg_bittorrent_client_setmaxdownloadconnections(cbc, CG_BITTORRENT_CLIENT_DEFAULT_MAX_DOWNLOAD_CONNECTIONS);

	/* Thread */
	cbc->acceptThread = NULL;
	cbc->clientThreads = NULL;

	return cbc;
}

/****************************************
* cg_bittorrent_client_delete
****************************************/

void cg_bittorrent_client_delete(CgBittorrentClient *cbc)
{
	if (!cbc)
		return;

	cg_bittorrent_client_stop(cbc);
	cg_bittorrent_client_clean(cbc);

	/* Mutex */
	if (cbc->mutex)
		cg_mutex_delete(cbc->mutex);

	/* Socket Server */
	if (cbc->serverSock)
		cg_socket_delete(cbc->serverSock );

	/* HTTP Server */
	if (cbc->httpServer)
		cg_http_server_delete(cbc->httpServer);

	free(cbc);
}

/****************************************
* cg_bittorrent_client_isready
****************************************/

static BOOL cg_bittorrent_client_isready(CgBittorrentClient *cbc)
{
	if (!cbc->fileDevMgr)
		return FALSE;

	if (!cg_bittorrent_filemgr_isvalidated(cbc->fileDevMgr))
		return FALSE;

	if (!cbc->stgyMgr)
		return FALSE;

	if (!cbc->httpServer)
		return FALSE;

	return TRUE;
}

/****************************************
* cg_bittorrent_client_initialize
****************************************/

static BOOL cg_bittorrent_client_initialize(CgBittorrentClient *cbc)
{
	CgBittorrentMetainfoList *metainfoList;
	CgBittorrentFileMgr *blkDevMgr;
	CgBittorrentMetainfoList *blkDevMetainfoList;
	CgByte infoHash[CG_BITTORRENT_METAINFO_INFOHASH_SIZE];
	CgBittorrentMetainfo *metainfo, *cbm;

	if (!cg_bittorrent_client_isready(cbc))
		return FALSE;

	if (!cg_bittorrent_client_clean(cbc))
		return FALSE;

	metainfoList = cg_bittorrent_client_getmetainfolist(cbc);
	if (!metainfoList)
		return FALSE;

	blkDevMgr = cg_bittorrent_client_getfilemgr(cbc);
	if (!blkDevMgr)
		return FALSE;

	/* Loading Metainfos */
	if (!cg_bittorrent_filemgr_getmetainfos(blkDevMgr, &blkDevMetainfoList))
		return FALSE;

	for (cbm=cg_bittorrent_metainfolist_gets(blkDevMetainfoList); cbm; cbm=cg_bittorrent_metainfo_next(cbm)) {
		if (!cg_bittorrent_metainfo_getinfohash(cbm, infoHash))
			continue;
		if (!cg_bittorrent_filemgr_getmetainfo(blkDevMgr, infoHash, &metainfo))
			continue;
		cg_bittorrent_client_addmetainfo(cbc, metainfo);
	}

	return TRUE;
}

/****************************************
* cg_bittorrent_client_clean
****************************************/

static BOOL cg_bittorrent_client_clean(CgBittorrentClient *cbc)
{
	CgBittorrentMetainfoList *cbmList;

	if (!cbc)
		return FALSE;

	/* Metainfo */
	cbmList = cg_bittorrent_client_getmetainfolist(cbc);
	if (!cbmList)
		return FALSE;
	cg_bittorrent_metainfolist_clear(cbmList);

	return TRUE;
}

/****************************************
* cg_bittorrent_client_start
****************************************/

BOOL cg_bittorrent_client_start(CgBittorrentClient *cbc)
{
	if (!cg_bittorrent_client_isready(cbc))
		return FALSE;

	if (!cbc->httpServer)
		cg_http_server_start(cbc->httpServer);
	
	return TRUE;
}

/****************************************
* cg_bittorrent_client_stop
****************************************/

BOOL cg_bittorrent_client_stop(CgBittorrentClient *cbc)
{
	if (cbc->httpServer)
		cg_http_server_stop(cbc->httpServer);

	if (cbc->acceptThread) {
		cg_thread_stop(cbc->acceptThread);
		cg_thread_delete(cbc->acceptThread);
		cbc->acceptThread = NULL;
	}

	if (cbc->clientThreads) {
		cg_threadlist_stop(cbc->clientThreads);
		cg_threadlist_delete(cbc->clientThreads);
		cbc->clientThreads = NULL;
	}

	return TRUE;
}

/****************************************
* cg_bittorrent_client_createpeerid
****************************************/

BOOL cg_bittorrent_client_createpeerid(CgBittorrentClient *cbc, CgByte *peerId)
{
	CgNetworkInterfaceList *netIfList;
	CgNetworkInterface *netIf;
	char hostName[CG_HTTP_SEVERNAME_MAXLEN];
	CgByte hostNameHash[CG_SHA1_HASH_SIZE];
	CgSHA1Context sha;
	int err;

	memset(peerId, 0, CG_BITTORRENT_CLIENT_PEERID_SIZE);

	/* Client ID/Vertion */
	peerId[0] = '-';
	memcpy(peerId + 1, CG_BITTORRENT_CLIENT_ID, 2);
	memcpy(peerId + 3, CG_BITTORRENT_CLIENT_VER, 4);

	/* Host Name */
	cg_http_getservername(hostName, CG_HTTP_SEVERNAME_MAXLEN);
	err = cg_sha1_reset(&sha);
	if (!err) {
		err = cg_sha1_input(&sha, hostName, cg_strlen(hostName));
		if (!err)
			err = cg_sha1_result(&sha, hostNameHash);
	}
	if (err)
		return FALSE;
	memcpy(peerId + 7, hostNameHash, 7);
	
	/* Mac Address */
	netIfList = cg_net_interfacelist_new();
	if (!netIfList)
		return FALSE;
	cg_net_gethostinterfaces(netIfList);
	netIf =cg_net_interfacelist_gets(netIfList);
	if (!netIf) {
		cg_net_interfacelist_delete(netIfList);
		return FALSE;
	}
	cg_net_interface_getmacaddress(netIf, (peerId + 14));
	cg_net_interfacelist_delete(netIfList);

	return FALSE;
}

/****************************************
* cg_bittorrent_client_getpiece
****************************************/

BOOL cg_bittorrent_client_getpiece(CgBittorrentClient *cbc,  CgBittorrentMetainfo *cbm, int pieceIdx, CgByte *buf, int bufLen)
{
	CgBittorrentStrategyMgr *stgMgr;
	CgBittorrentPropertyMgr *propMgr;
	CgBittorrentTracker *cbt;
	CgBittorrentPeer *peer;
	CgByte infoValHash[CG_SHA1_HASH_SIZE];
	CgByte peerId[CG_SHA1_HASH_SIZE];
	int pieceLength;
	int pieceOffset;
	int numFailed;
	int reqBlockLength;
	int reqRetryMax;
	int reqBlockLen;
	int reqAmountMax;
	int recvBlockLen;
	int reqTimeout;

	stgMgr = cg_bittorrent_client_getstrategymgr(cbc);
	if (!stgMgr)
		return FALSE;

	propMgr = cg_bittorrent_client_getpropertymgr(cbc);
	if (!propMgr)
		return FALSE;

	cbt = cg_bittorrent_metainfo_gettracker(cbm);
	if (!cbt)
		return FALSE;

	pieceLength = cg_bittorrent_metainfo_getinfopiecelength(cbm);
	if (pieceLength <= 0)
		return FALSE;
	
	reqBlockLength = cg_bittorrent_propertymgr_message_getrequestunit(propMgr);
	reqRetryMax = cg_bittorrent_propertymgr_message_getrequestretrymax(propMgr);
	reqAmountMax = cg_bittorrent_propertymgr_message_getrequestamountmax(propMgr);
	reqTimeout = cg_bittorrent_propertymgr_message_getrequesttimeout(propMgr);
	if ((reqBlockLength <= 0) || (reqRetryMax <= 0) || (reqRetryMax <= 0) || (reqTimeout <= 0))
		return FALSE;

	if (!cg_bittorrent_client_createpeerid(cbc, peerId))
		return FALSE;

	if (!cg_bittorrent_metainfo_getinfohash(cbm, infoValHash))
		return FALSE;

	pieceOffset = 0;
	numFailed = 0;
	recvBlockLen = 0;

	while (pieceOffset < bufLen && numFailed < reqRetryMax) {
		peer = cg_bittorrent_strategymgr_getnextpeer(stgMgr, cbm, pieceIdx);
		if (!peer)
			break;

		if (0 < reqTimeout)
			cg_bittorrent_peer_settimeout(peer, reqTimeout);

		if (!cg_bittorrent_peer_open(peer, infoValHash, peerId)) {
			numFailed++;
			continue;
		}

		if (!cg_bittorrent_peer_haspiece(peer, pieceIdx)) {
			cg_bittorrent_peer_close(peer);
			continue;
		}

		recvBlockLen = 0;
		while (recvBlockLen < reqAmountMax) {
			reqBlockLen = min((pieceLength - pieceOffset), reqBlockLength);
			if (!cg_bittorrent_peer_getpieceblock(peer, pieceIdx, 0, (buf + pieceOffset), reqBlockLength))
				break;
			pieceOffset += reqBlockLength;
			recvBlockLen += reqBlockLength;
		}

		cg_bittorrent_peer_close(peer);
	}

	return (pieceOffset == bufLen) ? TRUE : FALSE;
}

/****************************************
* cg_bittorrent_client_downloadpiece
****************************************/

BOOL cg_bittorrent_client_downloadpiece(CgBittorrentClient *cbc,  CgBittorrentMetainfo *cbm, int pieceIdx)
{
	CgBittorrentFileMgr *fileDevMgr;
	int pieceLength;
	CgByte *pieceBuf;
	BOOL wroteRes;

	if (cg_bittorrent_metainfo_haspiece(cbm, pieceIdx))
		return TRUE;

	fileDevMgr = cg_bittorrent_client_getfilemgr(cbc);
	if (!fileDevMgr)
		return FALSE;

	pieceLength = cg_bittorrent_metainfo_getpiecelength(cbm, pieceIdx);
	if (pieceLength <= 0)
		return FALSE;
	
	pieceBuf = (CgByte *)malloc(sizeof(CgByte) * pieceLength);
	if (!pieceBuf)
		return FALSE;

	if (!cg_bittorrent_client_getpiece(cbc,  cbm, pieceIdx, pieceBuf, pieceLength)) {
		free(pieceBuf);
		return FALSE;
	}

	wroteRes = cg_bittorrent_filemgr_writepiecedata(fileDevMgr, cbm, pieceIdx , pieceBuf, pieceLength);

	free(pieceBuf);

	if (wroteRes) {
		if (!cg_bittorrent_metainfo_setbitfield(cbm, pieceIdx, FALSE))
			return FALSE;
	}

	return wroteRes;
}

/****************************************
* cg_bittorrent_client_downloadpiece
****************************************/

BOOL cg_bittorrent_client_downloadpieces(CgBittorrentClient *cbc,  CgBittorrentMetainfo *cbm)
{
	CgBittorrentStrategyMgr *stgMgr;
	int totalPieceNum;
	int nextPieceIdx;

	if (!cbm)
		return FALSE;

	stgMgr = cg_bittorrent_client_getstrategymgr(cbc);
	if (!stgMgr)
		return FALSE;

	totalPieceNum = cg_bittorrent_metainfo_gettotalpieces(cbm);
	if (totalPieceNum <= 0)
		return FALSE;

	while (!cg_bittorrent_metainfo_isdownloaded(cbm)) {
		nextPieceIdx = cg_bittorrent_strategymgr_getnextpieceindex(stgMgr, cbm);
		cg_bittorrent_client_downloadpiece(cbc, cbm, nextPieceIdx);
	}

	return TRUE;
}
