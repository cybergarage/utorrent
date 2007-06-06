#include <cybergarage/bittorrent/cbittorrent.h>

#define CDIST_TEST_TRACKER_PEERID "A9993E364706816ABA3E25717850C26C9CD0D89D"
#define CDIST_TEST_TRACKER_PORT 6889
#define CDIST_TEST_TRACKER_UPLOADED 0
#define CDIST_TEST_TRACKER_DOWNLOADED 0
#define CDIST_TEST_TRACKER_LEFT 0
#define CDIST_TEST_TRACKER_COMPACT TRUE
#define CDIST_TEST_TRACKER_NUMWANT 50

int main(int argc, char* argv[])
{
	CgBittorrentMetainfo *cbm;
	CgBittorrentTracker *cbt;
	CgBittorrentPeer *cbp;
	int n;

	if (argc < 2) {
		printf("Usage : printpeers <Torrent URL>\n");
		return -1;
	}

	cbm = cg_bittorrent_metainfo_new();
	if (cg_bittorrent_metainfo_fetch(cbm, argv[1]) == FALSE) {
		printf("Couldn't get the specified torrent file <%s>\n", argv[1]);
		return -1;
	}

	cbt = cg_bittorrent_tracker_new();
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

	n = 0;
	for (cbp = cg_bittorrent_tracker_getpeers(cbt); cbp; cbp = cg_bittorrent_peer_next(cbp)) {
		n++;
		printf("[%d] %s:%d\n",
			n,
			cg_bittorrent_peer_getaddress(cbp),
			cg_bittorrent_peer_getport(cbp));
	}

	cg_bittorrent_tracker_delete(cbt);
	cg_bittorrent_metainfo_delete(cbm);

	return 0;
}
