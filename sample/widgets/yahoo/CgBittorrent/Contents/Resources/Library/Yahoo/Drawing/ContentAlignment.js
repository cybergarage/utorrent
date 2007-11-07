/*---------------------------------------------------------------------*/
/// <copyright from='2005' to='2006' company='Yahoo! Inc.'>
/// (C) Copyright 2005-2006 Yahoo! Inc. All Rights Reserved.
/// </copyright>

/**
 * Describes available alignment options for controls.
 */
/*---------------------------------------------------------------------*/

/*---------------------------------------------------------------------*/
// Namespace
/*---------------------------------------------------------------------*/
// Create namespace Yahoo.Drawing if it doesn't already exist
if(Yahoo==undefined) { var Yahoo = new Object(); }
if(Yahoo.Drawing==undefined) { Yahoo.Drawing = new Object(); }

/*---------------------------------------------------------------------*/
// Constructor
/*---------------------------------------------------------------------*/
/**
 * Default constructor.
 */
Yahoo.Drawing.ContentAlignment = {
	BottomCenter: 512,
	BottomLeft: 256,
	BottomRight: 1024,
	MiddleCenter: 32,
	MiddleLeft: 16,
	MiddleRight: 64,
	TopCenter: 2,
	TopLeft: 1,
	TopRight: 4
}
