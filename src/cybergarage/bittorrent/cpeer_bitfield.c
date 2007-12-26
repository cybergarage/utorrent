/******************************************************************
*
*	CyberBittorrent for C
*
*	Copyright (C) Satoshi Konno 2007
*
*	File: cpeer_bitfield.c
*
*	Revision:
*
*	12/26/07
*		- first revision
*
******************************************************************/

#include <cybergarage/bittorrent/cpeer.h>
#include <cybergarage/util/cstring.h>

/****************************************
* cg_bittorrent_peer_getbitfieldparam
****************************************/

BOOL cg_bittorrent_peer_getbitfieldparam(int pieceIdx, int *bitfieldNum, CgByte *bitfieldMask)
{
	int bitfieldOffset;

	*bitfieldNum = pieceIdx / 8;
	bitfieldOffset = pieceIdx % 8;
	*bitfieldMask = (CgByte)((1 << (7 - bitfieldOffset)) & 0xff); 

	return TRUE;
}

/****************************************
* cg_bittorrent_metainfo_haspiece
****************************************/

BOOL cg_bittorrent_peer_haspiece(CgByte *bitfield, int bitfieldLen, int pieceIdx)
{
	int bitfieldNum;
	CgByte bitfieldMask;

	if (!cg_bittorrent_peer_getbitfieldparam(pieceIdx, &bitfieldNum, &bitfieldMask))
		return FALSE;
	if ((bitfieldLen-1) < bitfieldNum)
		return FALSE;
	
	return (cbm->bitfield[bitfieldNum] & bitfieldMask) ? TRUE : FALSE;
}
