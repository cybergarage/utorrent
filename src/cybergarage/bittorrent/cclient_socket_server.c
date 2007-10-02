/******************************************************************
*
*	CyberBittorrent for C
*
*	Copyright (C) Satoshi Konno 2007
*
*	File: cclient_socket_server.c
*
*	Revision:
*
*	08/04/07
*		- first revision
*
******************************************************************/

#include <cybergarage/bittorrent/cclient.h>

static void cg_bittorrent_client_accept_thread(CgThread *thread)
{
	CgBittorrentClient *cbc;

	cbc = (CgBittorrentClient *)cg_thread_getuserdata(thread);

	cg_bittorrent_client_lock(cbc);
	cg_thread_remove(thread);
	cg_bittorrent_client_unlock(cbc);

	cg_thread_delete(thread);
}

static void cg_bittorrent_client_server_thread(CgThread *thread)
{
	CgBittorrentClient *cbc;
	CgThread *clientThread;
	CgSocket *clientSock;

	cbc = (CgBittorrentClient *)cg_thread_getuserdata(thread);

	while (cg_thread_isrunnable(thread) == TRUE) {
		clientSock = cg_socket_stream_new();
		if (cg_socket_accept(cbc->serverSock, clientSock) == FALSE) {
			cg_socket_delete(clientSock);
			break;
		}

		clientThread = cg_thread_new();
		cg_thread_setaction(clientThread, cg_bittorrent_client_accept_thread);
		cg_thread_setuserdata(clientThread, cbc);
		
		cg_bittorrent_client_lock(cbc);
		cg_threadlist_add(cbc->clientThreads, clientThread);
		cg_bittorrent_client_unlock(cbc);

		cg_thread_start(clientThread);		
	}
	/*
	CgHttpServer *httpServer;
	CgThread *httpClientThread;
	CgHttpServerClientData *clientData;
	CgSocket *serverSock;
	CgSocket *clientSock;
			 
	cg_log_debug_l4("Entering...\n");

	httpServer = (CgHttpServer *)cg_thread_getuserdata(thread);
	
	if (cg_http_server_isopened(httpServer) == FALSE)
		return;
		
	serverSock = httpServer->sock;
	while (cg_thread_isrunnable(thread) == TRUE) {
		clientSock = cg_socket_stream_new();
		if (cg_socket_accept(serverSock, clientSock) == FALSE) {
			cg_socket_delete(clientSock);
			break;
		}
		cg_socket_settimeout(clientSock, cg_http_server_gettimeout(httpServer));
		clientData = cg_http_server_clientdata_new(httpServer, clientSock);
		httpClientThread = cg_thread_new();
		cg_thread_setaction(httpClientThread, cg_http_server_clientthread);
		cg_thread_setuserdata(httpClientThread, clientData);
		
		cg_threadlist_add(httpServer->clientThreads, httpClientThread);
		
		cg_thread_start(httpClientThread);		
	}

	cg_log_debug_l4("Leaving...\n");
*/
}

/****************************************
* cg_bittorrent_client_server_start
****************************************/

BOOL cg_bittorrent_client_server_start(CgBittorrentClient *cbc)
{
	CgSocket *sock;

	if (!cbc)
		return FALSE;

	cg_bittorrent_client_server_stop(cbc);

	sock = cg_bittorrent_client_getserversocket(cbc);
	if (!sock)
		return FALSE;

	if (!cg_socket_bind(sock, cg_bittorrent_client_getserverport(cbc), NULL, FALSE, FALSE))
		return FALSE;

	if (!cg_socket_listen(sock)) {
		cg_socket_close(sock);
		return FALSE;
	}

	/* Thread */
	cbc->acceptThread = cg_thread_new();
	cg_thread_setaction(cbc->acceptThread, cg_bittorrent_client_server_thread);
	cg_thread_setuserdata(cbc->acceptThread, cbc);
	cbc->clientThreads = cg_threadlist_new();
	if (cg_thread_start(cbc->acceptThread) == FALSE) {
		cg_thread_stop(cbc->acceptThread);
		cg_thread_delete(cbc->acceptThread);
		cbc->acceptThread = NULL;
		cg_threadlist_stop(cbc->clientThreads);
		cg_threadlist_delete(cbc->clientThreads);
		cbc->clientThreads = NULL;
		return FALSE;
	}

	return TRUE;
}

/****************************************
* cg_bittorrent_client_server_stop
****************************************/

BOOL cg_bittorrent_client_server_stop(CgBittorrentClient *cbc)
{
	CgSocket *sock;

	if (!cbc)
		return FALSE;

	sock = cg_bittorrent_client_getserversocket(cbc);
	if (!sock)
		return FALSE;

	cg_socket_close(sock);

	/* Thread */
	if (cbc->acceptThread != NULL) {
		cg_thread_stop(cbc->acceptThread);
		cg_thread_delete(cbc->acceptThread);
		cbc->acceptThread = NULL;
	}
	if (cbc->clientThreads != NULL) {
		cg_threadlist_stop(cbc->clientThreads);
		cg_threadlist_delete(cbc->clientThreads);
		cbc->clientThreads = NULL;
	}

	return TRUE;
}
