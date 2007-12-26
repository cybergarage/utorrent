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

#ifndef _CG_BITTORRENT_UTIL_H_
#define _CG_BITTORRENT_UTIL_H_

#include <cybergarage/typedef.h>

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
BOOL cg_bittorrent_setbitfield(CgByte *bitfield, int bitfieldLen, int pieceIdx, BOOL flag);
BOOL cg_bittorrent_haspiece(CgByte *bitfield, int bitfieldLen, int pieceIdx);

#ifdef  __cplusplus
}
#endif

#endif
