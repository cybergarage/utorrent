/******************************************************************
*
*	CyberBittorrent for C
*
*	Copyright (C) Satoshi Konno 2007
*
*	File: cutil.c
*
*	Revision:
*
*	12/26/07
*		- first revision
*
******************************************************************/

#include <cybergarage/bittorrent/cutil.h>
#include <cybergarage/util/cstring.h>

/****************************************
* cg_bittorrent_peer_getbitfieldparam
****************************************/

BOOL cg_bittorrent_getbitfieldparam(int pieceIdx, int *bitfieldNum, CgByte *bitfieldMask)
{
	int bitfieldOffset;

	*bitfieldNum = pieceIdx / 8;
	bitfieldOffset = pieceIdx % 8;
	*bitfieldMask = (CgByte)((1 << (7 - bitfieldOffset)) & 0xff); 

	return TRUE;
}

/****************************************
* cg_bittorrent_setbitfield
****************************************/

BOOL cg_bittorrent_setbitfield(CgByte *bitfield, int bitfieldLen, int pieceIdx, BOOL flag)
{
	int bitfieldNum;
	CgByte bitfieldMask;

	if (!cg_bittorrent_getbitfieldparam(pieceIdx, &bitfieldNum, &bitfieldMask))
		return FALSE;
	if ((bitfieldLen-1) < bitfieldNum)
		return FALSE;
	
	if (flag)
		bitfield[bitfieldNum] |= bitfieldMask;
	else
		bitfield[bitfieldNum] &= ~bitfieldMask;

	return TRUE;
}

/****************************************
* cg_bittorrent_haspiece
****************************************/

BOOL cg_bittorrent_haspiece(CgByte *bitfield, int bitfieldLen, int pieceIdx)
{
	int bitfieldNum;
	CgByte bitfieldMask;

	if (!cg_bittorrent_getbitfieldparam(pieceIdx, &bitfieldNum, &bitfieldMask))
		return FALSE;
	if ((bitfieldLen-1) < bitfieldNum)
		return FALSE;
	
	return (bitfield[bitfieldNum] & bitfieldMask) ? TRUE : FALSE;
}
