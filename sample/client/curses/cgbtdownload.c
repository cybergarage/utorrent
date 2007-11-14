/******************************************************************
*
*	CyberBittorrent for C
*
*	Copyright (C) Satoshi Konno 2007
*
*	File: cgbtdownload.c
*
*	Revision:
*
*	11/15/07
*		- first revision
*
******************************************************************/

#include <curses.h>
#include <cybergarage/util/ctime.h>
#include <cybergarage/bittorrent/cbittorrent.h>

/****************************************
* Define
****************************************/

#define CGBTDOWNLOAD_LEFT_ROW 2
#define CGBTDOWNLOAD_URL_LINE 1

/****************************************
* Usage
****************************************/

void print_usage()
{
	printf("Usage: cgbtdownload [OPTIONS] [TORRENTFILE]\n");
}

/****************************************
* main
****************************************/

int main( int argc, char *argv[] )
{
	int i;
	int wx, wy;
	WINDOW *win;
	char *torrentURL;
	CgBittorrentMetainfo *cbm;

	if (argc < 2) {
		print_usage();
		exit(1);
	}

	torrentURL = argv[argc-1];

	cbm = cg_bittorrent_metainfo_new();
	if (!cg_bittorrent_metainfo_fetch(cbm, torrentURL)) {
		printf("Couldn't get %s\n", torrentURL);
		cg_bittorrent_metainfo_delete(cbm);
		exit(1);
	}
	//CgBittorrentDictionary *info = cg_bittorrent_metainfo_getinfo(cbm);

	win = initscr();
	getmaxyx(win, wy, wx);
	border(0, 0, 0, 0, 0, 0, 0, 0);
	
	/**** URL ****/
	move(CGBTDOWNLOAD_URL_LINE, CGBTDOWNLOAD_LEFT_ROW);
	printw("url: %s", torrentURL);

  for(i=0; i<5 ; i++){
    mvprintw(20-i%20, 5, "d", i);
	cg_sleep(1000);
    refresh();
  }
  endwin();

  return 0;
}

