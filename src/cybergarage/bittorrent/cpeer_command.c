/******************************************************************
*
*	CyberBittorrent for C
*
*	Copyright (C) Satoshi Konno 2007
*
*	File: cpeer_request.c
*
*	Revision:
*
*	06/30/07
*		- first revision
*
******************************************************************/

#include <cybergarage/bittorrent/cpeer.h>

/****************************************
* cg_bittorrent_peer_message_request
****************************************/

BOOL cg_bittorrent_peer_request(CgBittorrentPeer *peer, int index, int begin, int length)
{
	if (!peer)
		return FALSE;

/*
	CgBittorrentMetainfo *cbm = cg_bittorrent_metainfo_new();
	CPPUNIT_ASSERT(cg_bittorrent_metainfo_load(cbm, CDIST_TEST_METAINFO_FILE));
	cg_bittorrent_metainfo_print(cbm);
	CgBittorrentDictionary *info = cg_bittorrent_metainfo_getinfo(cbm);
	CPPUNIT_ASSERT(info);

	CPPUNIT_ASSERT(cg_bittorrent_metainfo_ismultiplefilemode(cbm) == TRUE);
	CgBittorrentBencodingList *filesList = cg_bittorrent_metainfo_getinfofileslist(cbm);
	CPPUNIT_ASSERT(filesList);
	CPPUNIT_ASSERT(cg_bittorrent_bencodinglist_size(filesList) == 2);
	for (CgBittorrentBencoding *ben = cg_bittorrent_metainfo_getinfofiles(cbm); ben; ben = cg_bittorrent_bencoding_next(ben)) {
		CPPUNIT_ASSERT(cg_bittorrent_bencoding_isdictionary(ben));
	}

	CgInt64 pieceLength = cg_bittorrent_metainfo_getinfopiecelength(cbm);

	CgBittorrentTracker *cbt = cg_bittorrent_tracker_new();
	cg_bittorrent_tracker_load(
		cbt , 
		cbm,
		(unsigned char *)CDIST_TEST_TRACKER_PEERID,
		"",
		CDIST_TEST_TRACKER_PORT,
		CDIST_TEST_TRACKER_UPLOADED,
		CDIST_TEST_TRACKER_DOWNLOADED,
		CDIST_TEST_TRACKER_LEFT,
		TRUE,
		CG_BITTORRENT_TRACKER_EVENT_STARTED,
		CDIST_TEST_TRACKER_NUMWANT
		);

	unsigned char infoValHash[CG_SHA1_HASH_SIZE];
	
	CPPUNIT_ASSERT(cg_bittorrent_metainfo_getinfohash(cbm, infoValHash));

	CgBittorrentPeer *cbp = cg_bittorrent_tracker_getpeers(cbt);
	CPPUNIT_ASSERT(cbp);

	CgBittorrentHandshake *hsIn = cg_bittorrent_handshake_new();
	CgBittorrentHandshake *hsOut = cg_bittorrent_handshake_new();
	cg_bittorrent_handshake_setinfohash(hsIn, infoValHash);
	cg_bittorrent_handshake_setpeerid(hsIn, CDIST_TEST_TRACKER_PEERID);
	while(cbp) {
		CPPUNIT_ASSERT(0< cg_strlen(cg_bittorrent_peer_getaddress(cbp)));
		CPPUNIT_ASSERT(0 < cg_bittorrent_peer_getport(cbp));
		if (cg_bittorrent_peer_connect(cbp) == FALSE)
			cbp = cg_bittorrent_peer_next(cbp);
		if (cg_bittorrent_peer_handshake(cbp, hsIn, hsOut) == TRUE)
			break;
		cbp = cg_bittorrent_peer_next(cbp);
	}
	cg_bittorrent_handshake_delete(hsIn);
	cg_bittorrent_handshake_delete(hsOut);

	CPPUNIT_ASSERT(cbp);

	CgBittorrentMessage *msg = cg_bittorrent_message_new();
	CPPUNIT_ASSERT(cg_bittorrent_peer_recvmsgheader(cbp, msg));
	char msgType = cg_bittorrent_message_gettype(msg);
	//CPPUNIT_ASSERT(msgType == CG_BITTORRENT_MESSAGE_BITFIELD);
	CPPUNIT_ASSERT(cg_bittorrent_peer_recvmsgbody(cbp, msg));
	CgInt64 msgLength = cg_bittorrent_message_getlength(msg);
	cg_bittorrent_peer_setbitfield(cbp, cg_bittorrent_message_getpayload(msg), cg_bittorrent_message_getlength(msg));

	// 3525195776 / 262144 / 8 = 1680.9443359375
	//msgLength = 1682;
	cg_bittorrent_message_delete(msg);

	CPPUNIT_ASSERT(cg_bittorrent_peer_close(cbp));

	cg_bittorrent_tracker_delete(cbt);
	cg_bittorrent_metainfo_delete(cbm);
*/

	return TRUE;
}

