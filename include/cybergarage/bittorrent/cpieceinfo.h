/******************************************************************
*
*	CyberBittorrent for C
*
*	Copyright (C) Satoshi Konno 2007
*
*	File: cpieceinfo.h
*
*	Revision:
*
*	12/07/07
*		- first revision
*
******************************************************************/

#ifndef _CG_BITTORRENT_PIECEINFO_H_
#define _CG_BITTORRENT_PIECEINFO_H_

#ifdef  __cplusplus
extern "C" {
#endif

#include <cybergarage/typedef.h>

/****************************************
* Data Type
****************************************/

typedef struct _CgBittorrentPieceInfo {
	BOOL isDownloaded;
} CgBittorrentPieceInfo;

/****************************************
* Function
****************************************/

/**
 * Create a new instance of the bittorrent pieceinfo.
 *
 * \return New instance.
 */
CgBittorrentPieceInfo *cg_bittorrent_pieceinfo_new();

/**
 * Destroy a instance of the bittorrent pieceinfo.
 *
 * \param cbpi PieceInfo to destory.
 */
void cg_bittorrent_pieceinfo_delete(CgBittorrentPieceInfo *cbpi);

/**
 * Set a strategy manager of the specified download manager.
 *
 * \param cbpi  PieceInfo in question.
 * \param value Flag to set.
 */
#define cg_bittorrent_pieceinfo_setdownloaded(cbpi, value) (cbpi->isDownloaded = value)

/**
 * Return a  strategy manager of the specified download manager.
 *
 * \param cbpi Download manager in question.
 *
 * \return TRUE if the piece block is downloaded, otherwise FALSE.
 */
#define cg_bittorrent_pieceinfo_isdownloaded(cbpi) (cbpi->isDownloaded)

#ifdef  __cplusplus
}
#endif

#endif

