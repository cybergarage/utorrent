# uTorrent for C (Under Development)

I was developing a library based on BitTorrent to study about the implementation of P2P networking before, but I stopped the development because I have no idea about the application which I want to create.

However I will might restart the development project because I would like to create some useful applications which are based on P2P such as Joost.

## Examples

### Client for BitTorrent

The following sample shows how to get the peers of the specified torrent using the current library.

```
int main(int argc, char* argv[])
{
 CgBittorrentMetainfo *cbm;
 CgBittorrentTracker *cbt;
 CgBittorrentPeer *cbp;
 int n;
 if (argc < 2) {
  printf(";Usage : printpeers <Torrent URL>\n";);
  return -1;
 }
 cbm = cg_bittorrent_metainfo_new();
 if (cg_bittorrent_metainfo_fetch(cbm, argv[1]) == FALSE) {
  printf(";Couldn't get the specified torrent file <%s>\n";, argv[1]);
  return -1;
 }

 cbt = cg_bittorrent_tracker_new();
 cg_bittorrent_tracker_load(
  cbt ,
  cbm,
  (unsigned char *)CDIST_TEST_TRACKER_PEERID,
  ";";,
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
  printf(";[%d] %s:%d\n";,
   n,
   cg_bittorrent_peer_getaddress(cbp),
   cg_bittorrent_peer_getport(cbp));
 }
 cg_bittorrent_tracker_delete(cbt);
 cg_bittorrent_metainfo_delete(cbm);
 return 0;
}
```

### Notice

To compile the sample, you have to install the latest CyberLinkForC from the SVN. Please use the following commands to check the simple sample if you want.

```
$ svn co https://cgbittorrent.svn.sourceforge.net/svnroot/cgbittorrent/trunk
$ cgbittorrent
$ cd cgbittorrent/
$ ./boostrap
$ ./configure
$ make
$ ./sample/printpeers/unix/printpeers http://torrent.fedoraproject.org/torrents/Zod-dvd-i386.torrent
[1] 80.xx3.x5x.x6:688x
[2] x4.x93.x03.8x:344x3
[3] x9x.x00.x5.x45:x88x
[4] x9.37.xxx.50:407
[5] 59.xx7.x70.x07:448xx
  ..........
[46] x43.88.x4.x40:x88x
[47] 85.8x.x59.x8x:x88x
[48] xx7.xx.x78.x7:x54xx
[49] 8x.8x.xx0.xx3:x7779
[50] x00.x0x.84.33:x88x
```

Currently, there are many implementations based on Bittorrent. I will implement the basic functions about [the BitTorrent specification](http://wiki.theory.org/BitTorrentSpecification) at first, then I will develop the uniqueness.
