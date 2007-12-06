/******************************************************************
*
*	CyberBittorrent for C
*
*	Copyright (C) Satoshi Konno 2007
*
*	File: ctracker.c
*
*	Revision:
*
*	03/12/07
*		- first revision
*
******************************************************************/

#include <cybergarage/bittorrent/ctracker.h>
#include <cybergarage/net/curi.h>

/****************************************
*  cg_bittorrent_tracker_new
****************************************/

CgBittorrentTracker *cg_bittorrent_tracker_new()
{
	CgBittorrentTracker *cbt;

	cbt = (CgBittorrentTracker *)malloc(sizeof(CgBittorrentTracker));
	if (!cbt)
		return NULL;

	cbt->dir = cg_bittorrent_dictionary_new();
	cbt->peerList = cg_bittorrent_peerlist_new();

	return cbt;
}

/****************************************
* cg_bittorrent_tracker_delete
****************************************/

void cg_bittorrent_tracker_delete(CgBittorrentTracker *cbt)
{
	if (!cbt)
		return;

	cg_bittorrent_dictionary_delete(cbt->dir);
	cg_bittorrent_peerlist_delete(cbt->peerList);

	free(cbt);
}

/****************************************
* cg_bittorrent_tracker_load
****************************************/

BOOL cg_bittorrent_tracker_load(
CgBittorrentTracker *cbt,
char *announceURL,
CgByte *info_hash,
CgByte *peer_id,
char *ip,
int port,
CgInt64 uploaded,
CgInt64 downloaded,
CgInt64 left,
BOOL isCompact,
char *eventStr,
int numwant
)
{
	CgBittorrentBencoding *infoVal;
	CgString *uri;
	CgString *escapedInfoValHash;
	CgString *escapedPeerID;
	char *announce;
	char intBuf[CG_STRING_LONGLONG_BUFLEN];
	BOOL ret;

	if (!cbt)
		return FALSE;

	if (cg_strlen(announceURL) <= 0)
		return FALSE;

	uri = cg_string_new();

	/**** announce ****/
	cg_string_addvalue(uri, announceURL);
	cg_string_addvalue(uri, CG_NET_URI_QUESTION_DELIM);

	/**** info_hash ****/
	cg_string_addvalue(uri, CG_BITTORRENT_TRACKER_QUERY_INFOHASH);
	cg_string_addvalue(uri, CG_NET_URI_EQ_DELIM);
	escapedInfoValHash = cg_string_new();
	cg_net_uri_escapestring(info_hash, CG_SHA1_HASH_SIZE, escapedInfoValHash);
	cg_string_addvalue(uri, cg_string_getvalue(escapedInfoValHash));
	cg_string_delete(escapedInfoValHash);
	cg_string_addvalue(uri, CG_NET_URI_AMP_DELIM);

	/**** peer_id ****/
	cg_string_addvalue(uri, CG_BITTORRENT_TRACKER_QUERY_PEERID);
	cg_string_addvalue(uri, CG_NET_URI_EQ_DELIM);
	escapedPeerID = cg_string_new();
	cg_net_uri_escapestring(peer_id, CG_SHA1_HASH_SIZE, escapedPeerID);
	cg_string_addvalue(uri, cg_string_getvalue(escapedPeerID));
	cg_string_delete(escapedPeerID);
	cg_string_addvalue(uri, CG_NET_URI_AMP_DELIM);

	/**** port ****/
	cg_string_addvalue(uri, CG_BITTORRENT_TRACKER_QUERY_PORT);
	cg_string_addvalue(uri, CG_NET_URI_EQ_DELIM);
	cg_longlong2str(port, intBuf, sizeof(intBuf));
	cg_string_addvalue(uri, intBuf);
	cg_string_addvalue(uri, CG_NET_URI_AMP_DELIM);

	/**** uploaded ****/
	cg_string_addvalue(uri, CG_BITTORRENT_TRACKER_QUERY_UPLOADED);
	cg_string_addvalue(uri, CG_NET_URI_EQ_DELIM);
	cg_longlong2str(uploaded, intBuf, sizeof(intBuf));
	cg_string_addvalue(uri, intBuf);
	cg_string_addvalue(uri, CG_NET_URI_AMP_DELIM);

	/**** downloaded ****/
	cg_string_addvalue(uri, CG_BITTORRENT_TRACKER_QUERY_DOWNLOADED);
	cg_string_addvalue(uri, CG_NET_URI_EQ_DELIM);
	cg_longlong2str(downloaded, intBuf, sizeof(intBuf));
	cg_string_addvalue(uri, intBuf);
	cg_string_addvalue(uri, CG_NET_URI_AMP_DELIM);

	/**** left ****/
	cg_string_addvalue(uri, CG_BITTORRENT_TRACKER_QUERY_LEFT);
	cg_string_addvalue(uri, CG_NET_URI_EQ_DELIM);
	cg_longlong2str(downloaded, intBuf, sizeof(intBuf));
	cg_string_addvalue(uri, intBuf);
	cg_string_addvalue(uri, CG_NET_URI_AMP_DELIM);

	/**** event ****/
	cg_string_addvalue(uri, CG_BITTORRENT_TRACKER_QUERY_EVENT);
	cg_string_addvalue(uri, CG_NET_URI_EQ_DELIM);
	cg_string_addvalue(uri, eventStr);
	cg_string_addvalue(uri, CG_NET_URI_AMP_DELIM);

	/**** ip ****/
	if (0 < cg_strlen(ip)) {
		cg_string_addvalue(uri, CG_BITTORRENT_TRACKER_QUERY_IP);
		cg_string_addvalue(uri, CG_NET_URI_EQ_DELIM);
		cg_string_addvalue(uri, ip);
		cg_string_addvalue(uri, CG_NET_URI_AMP_DELIM);
	}

	/**** numwant ****/
	if (0 < numwant) {
		cg_string_addvalue(uri, CG_BITTORRENT_TRACKER_QUERY_NUMWANT);
		cg_string_addvalue(uri, CG_NET_URI_EQ_DELIM);
		cg_longlong2str(numwant, intBuf, sizeof(intBuf));
		cg_string_addvalue(uri, intBuf);
		cg_string_addvalue(uri, CG_NET_URI_AMP_DELIM);
	}

	/**** compact ****/
	cg_string_addvalue(uri, CG_BITTORRENT_TRACKER_QUERY_COMPACT);
	cg_string_addvalue(uri, CG_NET_URI_EQ_DELIM);
	cg_string_addvalue(uri, (isCompact ? "1" : "0"));

	ret = cg_bittorrent_tracker_fetch(cbt, cg_string_getvalue(uri));
	
	cg_string_delete(uri);

	return ret;
}
