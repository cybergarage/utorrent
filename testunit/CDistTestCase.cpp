#include "CDistTestCase.h"

CPPUNIT_TEST_SUITE_REGISTRATION(CDistTestCase);

#if defined(WIN32) || defined(WINCE)
#define CDIST_TESTCASE_METAFILENAME "data\\Zod-dvd-i386.torrent"
#else
#define CDIST_TESTCASE_METAFILENAME "data/Zod-dvd-i386.torrent"
#endif

#define CDIST_TESTCASE_METAINFOURL "http://torrent.fedoraproject.org/torrents/Zod-dvd-i386.torrent"

#include <cybergarage/bittorrent/csha1.h>

////////////////////////////////////////
// setUp
////////////////////////////////////////

void CDistTestCase::setUp()
{
}

////////////////////////////////////////
// tearDown
////////////////////////////////////////

void CDistTestCase::tearDown()
{
}

////////////////////////////////////////
// testBencodingString
////////////////////////////////////////

#define CDIST_TEST_BENCODING_STRING "4:spam"

void CDistTestCase::testBencodingString()
{
	CgBittorrentBencoding *cbb = NULL;
	CgString *str;
	int offset;

	/**** Parse ****/
	CPPUNIT_ASSERT(cg_bittorrent_bencoding_parse(CDIST_TEST_BENCODING_STRING, &cbb, &offset) == TRUE);
	CPPUNIT_ASSERT(cbb);
	CPPUNIT_ASSERT(cg_bittorrent_bencoding_gettype(cbb) == CG_BITTORRENT_BENCODING_STRING);
	CPPUNIT_ASSERT(offset == 6);
	CPPUNIT_ASSERT(cg_streq(cg_bittorrent_bencoding_getstring(cbb), "spam"));

	/**** String ****/
	str = cg_string_new();
	cg_bittorrent_bencoding_tostring(cbb, str);
	CPPUNIT_ASSERT(cg_strlen(CDIST_TEST_BENCODING_STRING) == cg_string_length(str));
	CPPUNIT_ASSERT(cg_streq(CDIST_TEST_BENCODING_STRING, cg_string_getvalue(str)) == TRUE);
	cg_string_delete(str);

	cg_bittorrent_bencoding_delete(cbb);
}

////////////////////////////////////////
// testBencodingInteger
////////////////////////////////////////

#define CDIST_TEST_BENCODING_INTEGER "i123456e"

void CDistTestCase::testBencodingInteger()
{
	CgBittorrentBencoding *cbb = NULL;
	CgString *str;
	int offset;

	/**** Parse ****/
	CPPUNIT_ASSERT(cg_bittorrent_bencoding_parse(CDIST_TEST_BENCODING_INTEGER, &cbb, &offset) == TRUE);
	CPPUNIT_ASSERT(cbb);
	CPPUNIT_ASSERT(cg_bittorrent_bencoding_gettype(cbb) == CG_BITTORRENT_BENCODING_INTEGER);
	CPPUNIT_ASSERT(offset == 8);
	CPPUNIT_ASSERT(cg_bittorrent_bencoding_getinteger(cbb) == 123456);

	/**** String ****/
	str = cg_string_new();
	cg_bittorrent_bencoding_tostring(cbb, str);
	CPPUNIT_ASSERT(cg_strlen(CDIST_TEST_BENCODING_INTEGER) == cg_string_length(str));
	CPPUNIT_ASSERT(cg_streq(CDIST_TEST_BENCODING_INTEGER, cg_string_getvalue(str)) == TRUE);
	cg_string_delete(str);

	cg_bittorrent_bencoding_delete(cbb);
}

////////////////////////////////////////
// testBencodingList
////////////////////////////////////////

#define CDIST_TEST_BENCODING_LIST "l4:spam4:eggse"

void CDistTestCase::testBencodingList()
{
	CgBittorrentBencoding *cbb = NULL;
	CgBittorrentBencoding *cbbItem = NULL;
	CgString *str;
	int offset;

	/**** Parse ****/
	CPPUNIT_ASSERT(cg_bittorrent_bencoding_parse(CDIST_TEST_BENCODING_LIST, &cbb, &offset) == TRUE);
	CPPUNIT_ASSERT(cbb);
	CPPUNIT_ASSERT(cg_bittorrent_bencoding_gettype(cbb) == CG_BITTORRENT_BENCODING_LIST);
	CPPUNIT_ASSERT(offset == 14);
	CPPUNIT_ASSERT(cg_bittorrent_bencoding_getlistsize(cbb) == 2);
	cbbItem = cg_bittorrent_bencoding_getlists(cbb);
	CPPUNIT_ASSERT(cbbItem);
	CPPUNIT_ASSERT(cg_streq(cg_bittorrent_bencoding_getstring(cbbItem), "spam"));
	cbbItem = cg_bittorrent_bencoding_next(cbbItem);
	CPPUNIT_ASSERT(cbbItem);
	CPPUNIT_ASSERT(cg_streq(cg_bittorrent_bencoding_getstring(cbbItem), "eggs"));

	/**** String ****/
	str = cg_string_new();
	cg_bittorrent_bencoding_tostring(cbb, str);
	CPPUNIT_ASSERT(cg_strlen(CDIST_TEST_BENCODING_LIST) == cg_string_length(str));
	CPPUNIT_ASSERT(cg_streq(CDIST_TEST_BENCODING_LIST, cg_string_getvalue(str)) == TRUE);
	cg_string_delete(str);

	cg_bittorrent_bencoding_delete(cbb);
}

////////////////////////////////////////
// testBencodingDictionary
////////////////////////////////////////

#define CDIST_TEST_BENCODING_DIR "d3:cow3:moo4:spam4:eggse"

void CDistTestCase::testBencodingDictionary()
{
	CgBittorrentBencoding *cbb = NULL;
	CgBittorrentDictionary *cbd = NULL;
	CgBittorrentDictionaryElement *cbdElem = NULL;
	CgString *str;
	int offset;

	/**** Parse ****/
	cbd = cg_bittorrent_dictionary_new();
	CPPUNIT_ASSERT(cbd);
	CPPUNIT_ASSERT(cg_bittorrent_dictionary_parse(cbd, CDIST_TEST_BENCODING_DIR, &offset) == TRUE);
	CPPUNIT_ASSERT(cbd);
	CPPUNIT_ASSERT(offset == 24);

	/* cow => moo */
	cbdElem = cg_bittorrent_dictionary_gets(cbd);
	CPPUNIT_ASSERT(cbdElem);
	cbb = cg_bittorrent_dictionary_element_getkey(cbdElem);
	CPPUNIT_ASSERT(cbb);
	CPPUNIT_ASSERT(cg_streq(cg_bittorrent_bencoding_getstring(cbb), "cow"));
	cbb = cg_bittorrent_dictionary_element_getvalue(cbdElem);
	CPPUNIT_ASSERT(cbb);
	CPPUNIT_ASSERT(cg_streq(cg_bittorrent_bencoding_getstring(cbb), "moo"));

	/* spam => eggs */
	cbdElem = cg_bittorrent_dictionary_element_next(cbdElem);
	CPPUNIT_ASSERT(cbdElem);
	cbb = cg_bittorrent_dictionary_element_getkey(cbdElem);
	CPPUNIT_ASSERT(cbb);
	CPPUNIT_ASSERT(cg_streq(cg_bittorrent_bencoding_getstring(cbb), "spam"));
	cbb = cg_bittorrent_dictionary_element_getvalue(cbdElem);
	CPPUNIT_ASSERT(cbb);
	CPPUNIT_ASSERT(cg_streq(cg_bittorrent_bencoding_getstring(cbb), "eggs"));

	/**** String ****/
	str = cg_string_new();
	cg_bittorrent_dictionary_tostring(cbd, str);
	CPPUNIT_ASSERT(cg_strlen(CDIST_TEST_BENCODING_DIR) == cg_string_length(str));
	CPPUNIT_ASSERT(cg_streq(CDIST_TEST_BENCODING_DIR, cg_string_getvalue(str)) == TRUE);
	cg_string_delete(str);

	cg_bittorrent_dictionary_delete(cbd);
}

////////////////////////////////////////
// testBencodingDictionary
////////////////////////////////////////

#define CDIST_TEST_BENCODING_DIR_NEST "d4:infod3:cow3:mooee"

void CDistTestCase::testBencodingDictionaryNest()
{
	CgBittorrentBencoding *cbb = NULL;
	CgBittorrentDictionary *cbd = NULL;
	CgBittorrentDictionaryElement *cbdElem = NULL;
	CgString *str;
	int offset;

	/**** Parse ****/
	cbd = cg_bittorrent_dictionary_new();
	CPPUNIT_ASSERT(cbd);
	CPPUNIT_ASSERT(cg_bittorrent_dictionary_parse(cbd, CDIST_TEST_BENCODING_DIR_NEST, &offset) == TRUE);
	CPPUNIT_ASSERT(cbd);
	CPPUNIT_ASSERT(offset == 20);

	/**** String ****/
	str = cg_string_new();
	cg_bittorrent_dictionary_tostring(cbd, str);
	CPPUNIT_ASSERT(cg_strlen(CDIST_TEST_BENCODING_DIR_NEST) == cg_string_length(str));
	CPPUNIT_ASSERT(cg_streq(CDIST_TEST_BENCODING_DIR_NEST, cg_string_getvalue(str)) == TRUE);
	cg_string_delete(str);

	cg_bittorrent_dictionary_delete(cbd);
}

////////////////////////////////////////
// testMessageHasPiece
////////////////////////////////////////

#define CDIST_TEST_MESSAGE_HAS_PIECE_PAYLOAD_SIZE 32

void CDistTestCase::testMessageHasPiece()
{
	CgBittorrentPeer *peer = cg_bittorrent_peer_new();
	peer->bitfieldLength = CDIST_TEST_MESSAGE_HAS_PIECE_PAYLOAD_SIZE;
	peer->bitfield = (CgByte *)malloc(CDIST_TEST_MESSAGE_HAS_PIECE_PAYLOAD_SIZE);
	for (int n=0; n<32; n++)
		peer->bitfield[n] = 0xAA; // 10101010
	for (int i=0; i<(CDIST_TEST_MESSAGE_HAS_PIECE_PAYLOAD_SIZE*8); i++) {
		BOOL hasPiece = cg_bittorrent_peer_haspiece(peer, i);
		if (i % 2)
			CPPUNIT_ASSERT(!hasPiece);
		else
			CPPUNIT_ASSERT(hasPiece);
	}
	cg_bittorrent_peer_delete(peer);
}

////////////////////////////////////////
// testMetainfoFetch
////////////////////////////////////////

void CDistTestCase::testMetainfoFetch()
{
	CgBittorrentMetainfo *cbm = cg_bittorrent_metainfo_new();
	CPPUNIT_ASSERT(cbm);
	CPPUNIT_ASSERT(cg_bittorrent_metainfo_fetch(cbm, "http://torrent.fedoraproject.org/torrents/Zod-dvd-i386.torrent"));

	CPPUNIT_ASSERT(cg_streq(cg_bittorrent_metainfo_getannounce(cbm), "http://torrent.linux.duke.edu:6969/announce"));
	CPPUNIT_ASSERT(cg_bittorrent_metainfo_getcreationdate(cbm) == 1161640274);

	printf("\n");
	cg_bittorrent_metainfo_print(cbm);

	cg_bittorrent_metainfo_delete(cbm);
}

////////////////////////////////////////
// testMetainfoLoad
////////////////////////////////////////


#if defined(WIN32)
#define CDIST_TEST_METAINFO_FILE "..\\..\\data\\Zod-dvd-i386.torrent"
#else
#define CDIST_TEST_METAINFO_FILE "../data/Zod-dvd-i386.torrent"
#endif

void CDistTestCase::testMetainfoLoad()
{
	CgBittorrentMetainfo *cbm = cg_bittorrent_metainfo_new();
	CPPUNIT_ASSERT(cbm);
	CPPUNIT_ASSERT(cg_bittorrent_metainfo_load(cbm, CDIST_TEST_METAINFO_FILE));

	CPPUNIT_ASSERT(cg_streq(cg_bittorrent_metainfo_getannounce(cbm), "http://torrent.linux.duke.edu:6969/announce"));
	CPPUNIT_ASSERT(cg_bittorrent_metainfo_getcreationdate(cbm) == 1161640274);

	CgBittorrentBencoding *pathList;
	CgBittorrentBencoding *pathItem;
	CPPUNIT_ASSERT(cg_bittorrent_metainfo_getnfiles(cbm) == 2);
	CPPUNIT_ASSERT(cg_streq(cg_bittorrent_metainfo_getinfoname(cbm), "Zod-dvd-i386"));
	CPPUNIT_ASSERT(cg_bittorrent_metainfo_getinfopiecelength(cbm) == 262144);
	/* FC-6-i386-DVD.iso */
	pathList = cg_bittorrent_metainfo_getinfofilepath(cbm, 0);
	pathItem = cg_bittorrent_bencoding_getlists(pathList);
	CPPUNIT_ASSERT(cg_streq("FC-6-i386-DVD.iso", cg_bittorrent_bencoding_getstring(pathItem)));
	CPPUNIT_ASSERT(cg_bittorrent_metainfo_getinfofilelength(cbm, 0) == 3525195776);
	
	/* SHA1SUM */
	pathList = cg_bittorrent_metainfo_getinfofilepath(cbm, 1);
	pathItem = cg_bittorrent_bencoding_getlists(pathList);
	CPPUNIT_ASSERT(cg_streq("SHA1SUM", cg_bittorrent_bencoding_getstring(pathItem)));
	CPPUNIT_ASSERT(cg_bittorrent_metainfo_getinfofilelength(cbm, 1) == 671);
	//printf("\n");
	//cg_bittorrent_metainfo_print(cbm);

	CPPUNIT_ASSERT(cg_bittorrent_metainfo_save(cbm, CDIST_TEST_METAINFO_FILE ".copy"));

	cg_bittorrent_metainfo_delete(cbm);
}

////////////////////////////////////////
// testTrackerLoad
////////////////////////////////////////

#define CDIST_TEST_TRACKER_PEERID "A9993E364706816ABA3E25717850C26C9CD0D89D"
#define CDIST_TEST_TRACKER_PORT 6889
#define CDIST_TEST_TRACKER_UPLOADED 0
#define CDIST_TEST_TRACKER_DOWNLOADED 0
#define CDIST_TEST_TRACKER_LEFT 0
#define CDIST_TEST_TRACKER_COMPACT TRUE
#define CDIST_TEST_TRACKER_NUMWANT 50

void CDistTestCase::testTrackerLoad()
{
	CgBittorrentMetainfo *cbm = cg_bittorrent_metainfo_new();
	CPPUNIT_ASSERT(cbm);
#if defined(WIN32)
	CPPUNIT_ASSERT(cg_bittorrent_metainfo_load(cbm, "..\\..\\data\\Zod-dvd-i386.torrent"));
#else
	CPPUNIT_ASSERT(cg_bittorrent_metainfo_load(cbm, "../data/Zod-dvd-i386.torrent"));
#endif

	CgBittorrentTracker *cbt = cg_bittorrent_tracker_new();
	CPPUNIT_ASSERT(cbt);
	CPPUNIT_ASSERT(
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
		));

	CPPUNIT_ASSERT(0 < cg_bittorrent_tracker_getcomplete(cbt));
	CPPUNIT_ASSERT(0 < cg_bittorrent_tracker_getincomplete(cbt));
	CPPUNIT_ASSERT(0 < cg_bittorrent_tracker_getinterval(cbt));
	cg_bittorrent_tracker_delete(cbt);
}

////////////////////////////////////////
// testSHA1
////////////////////////////////////////

#define TEST1   "abc"
#define TEST2a  "abcdbcdecdefdefgefghfghighijhi"

#define TEST2b  "jkijkljklmklmnlmnomnopnopq"
#define TEST2   TEST2a TEST2b
#define TEST3   "a"
#define TEST4a  "01234567012345670123456701234567"
#define TEST4b  "01234567012345670123456701234567"
    /* an exact multiple of 512 bits */

#define TEST4   TEST4a TEST4b
char *testarray[4] =
{
    TEST1,
    TEST2,
    TEST3,
    TEST4
};
long int repeatcount[4] = { 1, 1, 1000000, 10 };
char *resultarray[4] =
{
"A9993E364706816ABA3E25717850C26C9CD0D89D",
"84983E441C3BD26EBAAE4AA1F95129E5E54670F1",
"34AA973CD4C4DAA4F61EEB2BDBAD27316534016F",
"DEA356A2CDDD90C7A7ECEDC5EBB563934F460452"
};

void CDistTestCase::testSHA1()
{
    CgSHA1Context sha;
    int i, j, err;
    uint8_t Message_Digest[20];
    char Message_Digest_Str[20*2+1];

    for(j = 0; j < 4; ++j)
    {
        err = cg_sha1_reset(&sha);
		CPPUNIT_ASSERT(!err);

        for(i = 0; i < repeatcount[j]; ++i)
        {

            err = cg_sha1_input(&sha,
                  (const unsigned char *) testarray[j],
                  strlen(testarray[j]));
			CPPUNIT_ASSERT(!err);
        }

        err = cg_sha1_result(&sha, Message_Digest);
		CPPUNIT_ASSERT(!err);
        if (!err) {
            for(i = 0; i < 20 ; ++i)
            {
                sprintf((Message_Digest_Str+(i*2)), "%02X", Message_Digest[i]);
            }
        }
		CPPUNIT_ASSERT(cg_streq(Message_Digest_Str, resultarray[j]));
    }

    /* Test some error returns */
	/*
    err = cg_sha1_input(&sha,(const unsigned char *) testarray[1], 1);
    printf ("\nError %d. Should be %d.\n", err, shaStateError );
    err = cg_sha1_reset(0);
    printf ("\nError %d. Should be %d.\n", err, shaNull );
	*/
}

////////////////////////////////////////
// testPeerSocket
////////////////////////////////////////

void CDistTestCase::testBlockDevice()
{
	CgBittorrentMetainfo *cbm = cg_bittorrent_metainfo_new();
	CPPUNIT_ASSERT(cbm);
	CPPUNIT_ASSERT(cg_bittorrent_metainfo_load(cbm, CDIST_TEST_METAINFO_FILE));

	int pieceLength = cg_bittorrent_metainfo_getinfopiecelength(cbm);

	CgBittorrentBlockDeviceMgr *blockDev = cg_bittorrent_blockdevicemgr_new();

	if (cg_bittorrent_metainfo_ismultiplefilemode(cbm)) {
		int cbmFileCnt = cg_bittorrent_metainfo_getnfiles(cbm);
		CPPUNIT_ASSERT(0 < cbmFileCnt);
		CgInt64 cbmFileOffset = 0;
		int startFileIndex;
		int endFileIndex;
		for (int n=0; n<cbmFileCnt; n++) { /* Info in Multiple File Mode */
			cbmFileOffset += cg_bittorrent_metainfo_getinfofilelength(cbm, n);
			float pieceIdx = (float)cbmFileOffset / (float)pieceLength;
			cg_bittorrent_blockdevicemgr_getfileindex(blockDev, cbm, (int)pieceIdx, &startFileIndex, &endFileIndex);
			CPPUNIT_ASSERT(startFileIndex == n);
			CPPUNIT_ASSERT(endFileIndex == n);
		}
	}
	else { /* Info in Single File Mode */
	}

	cg_bittorrent_blockdevicemgr_delete(blockDev);
	cg_bittorrent_metainfo_delete(cbm);
}

////////////////////////////////////////
// testPeerSocket
////////////////////////////////////////

void CDistTestCase::testPeerHandshake()
{
	CgBittorrentMetainfo *cbm = cg_bittorrent_metainfo_new();
	CPPUNIT_ASSERT(cg_bittorrent_metainfo_load(cbm, CDIST_TEST_METAINFO_FILE));
	cg_bittorrent_metainfo_print(cbm);
	CgBittorrentDictionary *info = cg_bittorrent_metainfo_getinfo(cbm);
	CPPUNIT_ASSERT(info);

	/* Info */
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

	/* Handshake */
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

	/* Bitfield */
	CgBittorrentMessage *msg = cg_bittorrent_message_new();
	CPPUNIT_ASSERT(cg_bittorrent_peer_recvmsgheader(cbp, msg));
	char msgType = cg_bittorrent_message_gettype(msg);
	//CPPUNIT_ASSERT(msgType == CG_BITTORRENT_MESSAGE_BITFIELD);
	CPPUNIT_ASSERT(cg_bittorrent_peer_recvmsgbody(cbp, msg));
	CgInt64 msgLength = cg_bittorrent_message_getlength(msg);
	cg_bittorrent_peer_setbitfield(cbp, cg_bittorrent_message_getpayload(msg), cg_bittorrent_message_getlength(msg));

	/*
	while (cg_bittorrent_peer_recvmsgheader(cbp, msg)) {
		switch (cg_bittorrent_message_gettype(msg)) {
			default:
				{
					cg_bittorrent_peer_recvmsgbody(cbp, msg);
					int msgType = cg_bittorrent_message_gettype(msg);
				}
				break;
		}
	}
*/
	// 3525195776 / 262144 / 8 = 1680.9443359375
	//msgLength = 1682;
	cg_bittorrent_message_delete(msg);

	CPPUNIT_ASSERT(cg_bittorrent_peer_close(cbp));

	cg_bittorrent_tracker_delete(cbt);
	cg_bittorrent_metainfo_delete(cbm);
}
