/*---------------------------------------------------------------------*/
/// <copyright from='2005' to='2006' company='Yahoo! Inc.'>
/// (C) Copyright 2005-2006 Yahoo! Inc. All Rights Reserved.
/// </copyright>

/**
 * Sizable rectangular control base.
 */
/*---------------------------------------------------------------------*/

/*---------------------------------------------------------------------*/
// Constructor
/*---------------------------------------------------------------------*/
/**
 * Default constructor.
 * @constructor
 * @param {Yahoo.Controls.Theme} theme The theme this control should use or null to create an instance of the default theme.
 */
Yahoo.Controls.SizableControlBase = function(theme, themePrefix) {

	//log("SizableControlBase.ctor()");

	if(arguments.length>0) {
		this.initialize(theme, themePrefix);
	}
}

/**
 * Define inheritance chain.
 */
Yahoo.Controls.SizableControlBase.prototype = new Yahoo.Controls.Control();
Yahoo.Controls.SizableControlBase.prototype.constructor = Yahoo.Controls.SizableControlBase;
Yahoo.Controls.SizableControlBase.prototype.baseclassSizableControlBase = Yahoo.Controls.Control.prototype;

/*-----------------------------------------------------------*/
// Control code
/*-----------------------------------------------------------*/
/**
 * Raises the onBackColorChanged event.
 * @param {Object} sender The source of the event.
 * @param {Yahoo.EventArgs} e The EventArgs object that contains event details.
 */
Yahoo.Controls.SizableControlBase.prototype._onBackColorChanged = function(sender, e) {

	//log("SizableControlBase._onBackColorChanged");

	// Call base class
	this.baseclassSizableControlBase._onBackColorChanged.call(this, sender, e);
	
	this._imgBackground.colorize = this._backColor;
}

/**
 * Control's internal resize handler.
 * @param {Object} sender The source of the event.
 * @param {Yahoo.EventArgs} e The EventArgs object that contains event details.
 */
Yahoo.Controls.SizableControlBase.prototype._onResize = function(sender, e) {

	//log("SizableControlBase._onResize");

	// sender = top level control that inherits from us
	// this = SizableControlBase

	// Call base class
	this.baseclassSizableControlBase._onResize.call(this, sender, e);

	// Resize borders and background
	sender._sizableControlBase_paintBackground();
}

/**
 * Raises the onThemeChanged event.
 * @param {Object} sender The source of the event.
 * @param {Yahoo.EventArgs} e The EventArgs object that contains event details.
 */
Yahoo.Controls.SizableControlBase.prototype._onThemeChanged = function(sender, e) {

	//log("SizableControlBase._onThemeChanged");

	// Call base class
	this.baseclassSizableControlBase._onThemeChanged.call(this, sender, e);

	this._sizableControlBase_loadTheme();
	this._sizableControlBase_paintBackground();
}

/**
 * Raises the onToolTipChanged event.
 * @param {Object} sender The source of the event.
 * @param {Yahoo.EventArgs} e The EventArgs object that contains event details.
 */
Yahoo.Controls.SizableControlBase.prototype._onToolTipChanged = function(sender, e) {

	//log("SizableControlBase._onToolTipChanged");

	// Call base class
	this.baseclassSizableControlBase._onToolTipChanged.call(this, sender, e);
	
	// Set tooltip
	this._imgBackground.tooltip = this.tooltip;
	this._imgCornerTopLeft.tooltip = this.tooltip;
	this._imgCornerTopRight.tooltip = this.tooltip;
	this._imgCornerBottomLeft.tooltip = this.tooltip;
	this._imgCornerBottomRight.tooltip = this.tooltip;
	this._imgBorderTop.tooltip = this.tooltip;
	this._imgBorderBottom.tooltip = this.tooltip;
	this._imgBorderLeft.tooltip = this.tooltip;
	this._imgBorderRight.tooltip = this.tooltip;
}

/*-----------------------------------------------------------*/
// Private code
/*-----------------------------------------------------------*/
/**
 * Disposes native Widget Engine objects.
 * @private
 */
Yahoo.Controls.SizableControlBase.prototype._sizableControlBase_disposeNativeObjects = function() {

	//log("SizableControlBase._sizableControlBase_disposeNativeObjects");

	if(this._imgBackground!=null) { this._imgBackground.removeFromSuperview(); this._imgBackground = null; }
	if(this._imgCornerTopLeft!=null) { this._imgCornerTopLeft.removeFromSuperview(); this._imgCornerTopLeft = null; }
	if(this._imgCornerTopRight!=null) { this._imgCornerTopRight.removeFromSuperview(); this._imgCornerTopRight = null; }
	if(this._imgCornerBottomLeft!=null) { this._imgCornerBottomLeft.removeFromSuperview(); this._imgCornerBottomLeft = null; }
	if(this._imgCornerBottomRight!=null) { this._imgCornerBottomRight.removeFromSuperview(); this._imgCornerBottomRight = null; }
	if(this._imgBorderTop!=null) { this._imgBorderTop.removeFromSuperview(); this._imgBorderTop = null; }
	if(this._imgBorderBottom!=null) { this._imgBorderBottom.removeFromSuperview(); this._imgBorderBottom = null; }
	if(this._imgBorderLeft!=null) { this._imgBorderLeft.removeFromSuperview(); this._imgBorderLeft = null; }
	if(this._imgBorderRight!=null) { this._imgBorderRight.removeFromSuperview(); this._imgBorderRight = null; }
}

/**
 * Loads control elements based on current theme.
 * @private
 */
Yahoo.Controls.SizableControlBase.prototype._sizableControlBase_loadTheme = function() {

	//log("SizableControlBase._sizableControlBase_loadTheme");

	// Remove any current objects
	this._sizableControlBase_disposeNativeObjects();

	// Load objects using current theme
	this._imgBackground = this._theme.getItem(this._themePrefix + "Background");
	this._imgBackground.tag = this;
	this._frame.addSubview(this._imgBackground);
	this._imgCornerTopLeft = this._theme.getItem(this._themePrefix + "CornerTopLeft");
	this._imgCornerTopLeft.tag = this;
	this._frame.addSubview(this._imgCornerTopLeft);
	this._imgCornerTopRight = this._theme.getItem(this._themePrefix + "CornerTopRight");
	this._imgCornerTopRight.tag = this;
	this._frame.addSubview(this._imgCornerTopRight);
	this._imgCornerBottomLeft = this._theme.getItem(this._themePrefix + "CornerBottomLeft");
	this._imgCornerBottomLeft.tag = this;
	this._frame.addSubview(this._imgCornerBottomLeft);
	this._imgCornerBottomRight = this._theme.getItem(this._themePrefix + "CornerBottomRight");
	this._imgCornerBottomRight.tag = this;
	this._frame.addSubview(this._imgCornerBottomRight);
	this._imgBorderTop = this._theme.getItem(this._themePrefix + "BorderTop");
	this._imgBorderTop.tag = this;
	this._frame.addSubview(this._imgBorderTop);
	this._imgBorderBottom = this._theme.getItem(this._themePrefix + "BorderBottom");
	this._imgBorderBottom.tag = this;
	this._frame.addSubview(this._imgBorderBottom);
	this._imgBorderLeft = this._theme.getItem(this._themePrefix + "BorderLeft");
	this._imgBorderLeft.tag = this;
	this._frame.addSubview(this._imgBorderLeft);
	this._imgBorderRight = this._theme.getItem(this._themePrefix + "BorderRight");
	this._imgBorderRight.tag = this;
	this._frame.addSubview(this._imgBorderRight);
}

/**
 * Resizes control border elements.
 * @private
 */
Yahoo.Controls.SizableControlBase.prototype._sizableControlBase_paintBackground = function() {

	var width;
	var height;
	
	width = this.width;
	height = this.height;

	this._imgCornerTopRight.hOffset = width - this._imgCornerTopRight.width;

	this._imgCornerBottomLeft.vOffset = height - this._imgCornerBottomLeft.height;

	this._imgCornerBottomRight.hOffset = width - this._imgCornerBottomRight.width;
	this._imgCornerBottomRight.vOffset = height - this._imgCornerBottomRight.height;
	// Size from image

	// Top border width is width - (corner widths)
	this._imgBorderTop.hOffset = this._imgCornerTopLeft.hOffset + this._imgCornerTopLeft.width;
	this._imgBorderTop.width = width - (this._imgCornerTopLeft.width + this._imgCornerTopRight.width);
	// Height from image

	// Left border height is height - (corner heights)
	this._imgBorderLeft.vOffset = this._imgCornerTopLeft.height;
	// Width from image
	this._imgBorderLeft.height = height - (this._imgCornerTopLeft.height + this._imgCornerBottomLeft.height);
	
	// Right border height is height - (corner heights)
	this._imgBorderRight.hOffset = width - this._imgBorderRight.width;
	this._imgBorderRight.vOffset = this._imgCornerTopRight.height;
	// Width from image
	this._imgBorderRight.height = height - (this._imgCornerTopRight.height + this._imgCornerBottomRight.height);
	
	// Bottom border width is width - (corner widths)
	this._imgBorderBottom.hOffset = this._imgCornerBottomLeft.hOffset + this._imgCornerBottomLeft.width;
	this._imgBorderBottom.vOffset = height - this._imgBorderBottom.height;
	this._imgBorderBottom.width = width - (this._imgCornerBottomLeft.width + this._imgCornerBottomRight.width);
	// Height from image

	this._imgBackground.hOffset = this._imgBorderLeft.width + this._imgBorderLeft.hOffset;
	this._imgBackground.vOffset = this._imgBorderTop.height + this._imgBorderTop.vOffset;
	this._imgBackground.width = width - (this._imgBorderLeft.width + this._imgBorderRight.width);
	this._imgBackground.height = height - (this._imgBorderTop.height + this._imgBorderBottom.height);
}

/*-----------------------------------------------------------*/
// Public code
/*-----------------------------------------------------------*/
/**
 * Initializes control.
 * @param {Yahoo.Controls.Theme} theme The theme this control should use or null to create an instance of the default theme.
 */
Yahoo.Controls.SizableControlBase.prototype.initialize = function(theme, themePrefix) {

	//log("SizableControlBase.initialize()");
	
	if(themePrefix==null) { throw new Yahoo.ArgumentNullException("themePrefix"); }

	// Call base class
	this.baseclassSizableControlBase.initialize.call(this, theme);

	this._isInitializing = true;

	this._themePrefix = themePrefix;

	// Internal objects
	this._imgBackground = null;
	this._imgCornerTopLeft = null;
	this._imgCornerTopRight = null;
	this._imgCornerBottomLeft = null;
	this._imgCornerBottomRight = null;
	this._imgBorderTop = null;
	this._imgBorderBottom = null;
	this._imgBorderLeft = null;
	this._imgBorderRight = null;
	
	// Load image objects
	this._sizableControlBase_loadTheme();
	
	// Set locations/sizes that do not change
	this._imgCornerTopLeft.hOffset = 0;
	this._imgCornerTopLeft.vOffset = 0;
	// Size from image

	this._imgCornerTopRight.vOffset = 0;
	// Size from image

	this._imgCornerBottomLeft.hOffset = 0;
	// Size from image

	this._imgBorderTop.vOffset = 0;

	this._imgBorderLeft.hOffset = 0;

	// We don't resize since we must be inherited
	//this._onResize(this, new Yahoo.EventArgs());

	this._isInitializing = false;
}

/**
 * Disposes control's resources.
 */
Yahoo.Controls.SizableControlBase.prototype.dispose = function() {
	
	// Call base class
	this.baseclassSizableControlBase.dispose.call(this);
	
	// Dispose native items
	this._sizableControlBase_disposeNativeObjects();
}

/*-----------------------------------------------------------*/
// Public properties
/*-----------------------------------------------------------*/
