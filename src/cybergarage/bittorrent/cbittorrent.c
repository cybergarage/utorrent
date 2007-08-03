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

#ifdef HAVE_CONFIG_H
#  include "config.h"
#endif

#include <cybergarage/bittorrent/cbittorrent.h>

#include <cybergarage/bittorrent/cbencoding.h>
#include <cybergarage/bittorrent/csha1.h>

/****************************************
* cg_bittorrent_new
****************************************/

CgBittorrent *cg_bittorrent_new()
{
	CgBittorrent *cb;

	cb = (CgBittorrent *)malloc(sizeof(CgBittorrent));
	if (!cb)
		return NULL;

	return cb;
}

/****************************************
* cg_bittorrent_delete
****************************************/

void cg_bittorrent_delete(CgBittorrent *cb)
{
	if (!cb)
		return;

	free(cb);
}
