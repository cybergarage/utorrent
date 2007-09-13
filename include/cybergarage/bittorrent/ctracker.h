/******************************************************************
*
*	CyberBittorrent for C
*
*	Copyright (C) Satoshi Konno 2007
*
*	File: ctracker.h
*
*	Revision:
*
*	03/12/07
*		- first revision
*
******************************************************************/

#ifndef _CG_BITTORRENT_TRACKER_H_
#define _CG_BITTORRENT_TRACKER_H_

#include <cybergarage/bittorrent/cmetainfo.h>
#include <cybergarage/bittorrent/csha1.h>
#include <cybergarage/bittorrent/cpeer.h>

#ifdef  __cplusplus
extern "C" {
#endif

/****************************************
* Define
****************************************/

#define CG_BITTORRENT_TRACKER_QUERY_INFOHASH "info_hash"
#define CG_BITTORRENT_TRACKER_QUERY_PEERID "peer_id"
#define CG_BITTORRENT_TRACKER_QUERY_PORT "port"
#define CG_BITTORRENT_TRACKER_QUERY_UPLOADED "uploaded"
#define CG_BITTORRENT_TRACKER_QUERY_DOWNLOADED "downloaded"
#define CG_BITTORRENT_TRACKER_QUERY_LEFT "left"
#define CG_BITTORRENT_TRACKER_QUERY_COMPACT "compact"
#define CG_BITTORRENT_TRACKER_QUERY_EVENT "event"
#define CG_BITTORRENT_TRACKER_QUERY_IP "ip"
#define CG_BITTORRENT_TRACKER_QUERY_LOCALIP "localip"
#define CG_BITTORRENT_TRACKER_QUERY_NUMWANT "numwant"

#define CG_BITTORRENT_TRACKER_EVENT_STARTED "started"
#define CG_BITTORRENT_TRACKER_EVENT_STOPPED "stopped"
#define CG_BITTORRENT_TRACKER_EVENT_COMPLETED "completed"

/****************************************
* Data Type
****************************************/

typedef struct _CgBittorrentTracker {
	CgBittorrentDictionary *dir;
	CgBittorrentPeerList *peerList;
} CgBittorrentTracker;

/****************************************
* Function
****************************************/

/**
 * Create a new tracker.
 *
 * \return Tracker.
 */
CgBittorrentTracker *cg_bittorrent_tracker_new();

/**
 * Destroy a tracker.
 *
 * \param cbt Tracker to destory.
 */
void cg_bittorrent_tracker_delete(CgBittorrentTracker *cbt);

/**
 * Get a dictionary.
 *
 * \param cbt Tracker in question.
 *
 * \return Stored dictionary.
 */
#define cg_bittorrent_tracker_getdictionary(cbt) (cbt->dir)

/**
 * Get a peer list.
 *
 * \param cbt Tracker in question.
 *
 * \return Stored peer list.
 */
#define cg_bittorrent_tracker_getpeerlist(cbt) (cbt->peerList)

/**
 * Get a first peer of the list.
 *
 * \param cbt Tracker in question.
 *
 * \return First peer.
 */
#define cg_bittorrent_tracker_getpeers(cbt) cg_bittorrent_peerlist_gets(cbt->peerList)

/**
 * Return a dictionary element by name.
 *
 * \param cbt Tracker in question.
 * \param name Name of the dictionary.
 *
 * \return Dictionary element if the specified name is found, otherwise NULL.
 */
#define  cg_bittorrent_tracker_getelementbyname(cbt, name) cg_bittorrent_dictionary_getelementbyname(cbt->dir, name)

/**
 * Return a dictionary element by name.
 *
 * \param cbt Tracker in question.
 * \param name Name of the dictionary.
 *
 * \return Bencording if the specified name is found, otherwise NULL.
 */
#define cg_bittorrent_tracker_getvaluebyname(cbt, name) cg_bittorrent_dictionary_getvaluebyname(cbt->dir, name)

/**
 * Return a dictionary string by name.
 *
 * \param cbt Tracker in question.
 * \param name Name of the dictionary.
 *
 * \return String of the dictionary if the specified name is found and the type is integer, otherwise NULL.
 */
#define cg_bittorrent_tracker_getstringbyname(cbt, name) cg_bittorrent_dictionary_getstringbyname(cbt->dir, name)

/**
 * Return a dictionary integer by name.
 *
 * \param cbt Tracker in question.
 * \param name Name of the dictionary.
 *
 * \return Value of the dictionary if the specified name is found and the type is integer, otherwise 0.
 */
#define cg_bittorrent_tracker_getintegerbyname(cbt, name) cg_bittorrent_dictionary_getintegerbyname(cbt->dir, name)

/**
 * Return a dictionary list by name.
 *
 * \param cbt Tracker in question.
 * \param name Name of the dictionary.
 *
 * \return List of the dictionary if the specified name is found and the type is list, otherwise NULL.
 */
#define cg_bittorrent_tracker_getlistbyname(cbt, name) cg_bittorrent_dictionary_getlistbyname(cbt->dir, name)

/****************************************
* Function (Internal)
****************************************/

BOOL cg_bittorrent_tracker_parse(CgBittorrentTracker *cbt, char *data, int dataLen);
BOOL cg_bittorrent_tracker_fetch(CgBittorrentTracker *cbt, char *url);

BOOL cg_bittorrent_tracker_load(
CgBittorrentTracker *cbt,
CgBittorrentMetainfo *cbm,
CgByte *peer_id,
char *ip,
int port,
CgInt64 uploaded,
CgInt64 downloaded,
CgInt64 left,
BOOL isCompact,
char *eventStr,
int numwant);

/****************************************
* Macros
****************************************/

#define CG_BITTORRENT_TRACKER_FAILUREREASON "failure reason"
#define CG_BITTORRENT_TRACKER_WARNINGMESSAGE "warning message"
#define CG_BITTORRENT_TRACKER_INTERVAL "interval"
#define CG_BITTORRENT_TRACKER_MININTERVAL "min interval"
#define CG_BITTORRENT_TRACKER_TRACKERID "tracker id"
#define CG_BITTORRENT_TRACKER_COMPLETE "complete"
#define CG_BITTORRENT_TRACKER_INCOMPLETE "incomplete"
#define CG_BITTORRENT_TRACKER_PEERS "peers"
#define CG_BITTORRENT_TRACKER_PEERSID "peer id"
#define CG_BITTORRENT_TRACKER_IP "ip"
#define CG_BITTORRENT_TRACKER_PORT "port"

#define CG_BITTORRENT_TRACKER_PEERCOMPACT_SIZE (4+2)
#define CG_BITTORRENT_TRACKER_PEERCOMPACT_IP_SIZE 4
#define CG_BITTORRENT_TRACKER_PEERCOMPACT_PORT_SIZE 2

#define cg_bittorrent_tracker_getfailurereason(cbt) cg_bittorrent_tracker_getstringbyname(cbt, CG_BITTORRENT_TRACKER_FAILUREREASON)
#define cg_bittorrent_tracker_getwarningmessage(cbt) cg_bittorrent_tracker_getstringbyname(cbt, CG_BITTORRENT_TRACKER_WARNINGMESSAGE)
#define cg_bittorrent_tracker_getinterval(cbt) cg_bittorrent_tracker_getintegerbyname(cbt, CG_BITTORRENT_TRACKER_INTERVAL)
#define cg_bittorrent_tracker_getmininterval(cbt) cg_bittorrent_tracker_getintegerbyname(cbt, CG_BITTORRENT_TRACKER_MININTERVAL)
#define cg_bittorrent_tracker_gettrackerid(cbt) cg_bittorrent_tracker_getintegerbyname(cbt,CG_BITTORRENT_TRACKER_TRACKERID)
#define cg_bittorrent_tracker_getcomplete(cbt) cg_bittorrent_tracker_getintegerbyname(cbt, CG_BITTORRENT_TRACKER_COMPLETE)
#define cg_bittorrent_tracker_getincomplete(cbt) cg_bittorrent_tracker_getintegerbyname(cbt, CG_BITTORRENT_TRACKER_INCOMPLETE)
/*
#define cg_bittorrent_tracker_getpeers(cbt) cg_bittorrent_tracker_getstringbyname(cbt, CG_BITTORRENT_TRACKER_PEERS)
*/

#ifdef  __cplusplus
}
#endif

#endif
