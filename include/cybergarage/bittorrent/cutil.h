/******************************************************************
*
*	CyberBittorrent for C
*
*	Copyright (C) Satoshi Konno 2007
*
*	File: cbittorrent.h
*
*	Revision:
*
*	01/25/07
*		- first revision
*
******************************************************************/

#ifndef _CG_BITTORRENT_H_
#define _CG_BITTORRENT_H_

#include <cybergarage/bittorrent/ctracker.h>
#include <cybergarage/bittorrent/cdownloadmgr.h>
#include <cybergarage/bittorrent/cclient.h>

#ifdef  __cplusplus
extern "C" {
#endif

/****************************************
* Define
****************************************/

/****************************************
* Data Type
****************************************/

/****************************************
* Function (Internal)
****************************************/

BOOL cg_bittorrent_getbitfieldparam(int pieceIdx, int *bitfieldNum, CgByte *bitfieldMask);
BOOL cg_bittorrent_haspiece(CgByte *bitfield, int bitfieldLen, int pieceIdx);


#ifdef  __cplusplus
}
#endif

#endif
