/*---------------------------------------------------------------------*/
/// <copyright from='2005' to='2006' company='Yahoo! Inc.'>
/// (C) Copyright 2005-2006 Yahoo! Inc. All Rights Reserved.
/// </copyright>

/**
 * Three part sizable rectangular control base.
 */
/*---------------------------------------------------------------------*/

/*---------------------------------------------------------------------*/
// Constructor
/*---------------------------------------------------------------------*/
/**
 * Default constructor.
 * @constructor
 * @param {Yahoo.Controls.Theme} theme The theme this control should use or null to create an instance of the default theme.
 * @param {String} themePrefix The prefix used to retrieve styles from the theme for this control.
 */
Yahoo.Controls.Sizable3PartControlBase = function(theme, themePrefix) {

	//log("Sizable3PartControlBase.ctor()");

	if(arguments.length>0) {
		this.initialize(theme, themePrefix);
	}
}

/**
 * Define inheritance chain.
 */
Yahoo.Controls.Sizable3PartControlBase.prototype = new Yahoo.Controls.Control();
Yahoo.Controls.Sizable3PartControlBase.prototype.constructor = Yahoo.Controls.Sizable3PartControlBase;
Yahoo.Controls.Sizable3PartControlBase.prototype.baseclassSizable3PartControlBase = Yahoo.Controls.Control.prototype;

/*-----------------------------------------------------------*/
// Control code
/*-----------------------------------------------------------*/
/**
 * Raises the onBackColorChanged event.
 * @param {Object} sender The source of the event.
 * @param {Yahoo.EventArgs} e The EventArgs object that contains event details.
 */
Yahoo.Controls.Sizable3PartControlBase.prototype._onBackColorChanged = function(sender, e) {

	//log("Sizable3PartControlBase._onBackColorChanged");

	// Call base class
	this.baseclassSizable3PartControlBase._onBackColorChanged.call(this, sender, e);
	
	this._imgMiddle.colorize = this._backColor;
}

/**
 * Control's internal resize handler.
 * @param {Object} sender The source of the event.
 * @param {Yahoo.EventArgs} e The EventArgs object that contains event details.
 */
Yahoo.Controls.Sizable3PartControlBase.prototype._onResize = function(sender, e) {

	//log("Sizable3PartControlBase._onResize");

	// sender = top level control that inherits from us
	// this = Sizable3PartControlBase

	// Call base class
	this.baseclassSizable3PartControlBase._onResize.call(this, sender, e);

	// Resize borders and background
	sender._Sizable3PartControlBase_paintBackground();
}

/**
 * Raises the onThemeChanged event.
 * @param {Object} sender The source of the event.
 * @param {Yahoo.EventArgs} e The EventArgs object that contains event details.
 */
Yahoo.Controls.Sizable3PartControlBase.prototype._onThemeChanged = function(sender, e) {

	//log("Sizable3PartControlBase._onThemeChanged");

	// Call base class
	this.baseclassSizable3PartControlBase._onThemeChanged.call(this, sender, e);

	this._Sizable3PartControlBase_loadTheme();
	this._Sizable3PartControlBase_paintBackground();
}

/**
 * Raises the onToolTipChanged event.
 * @param {Object} sender The source of the event.
 * @param {Yahoo.EventArgs} e The EventArgs object that contains event details.
 */
Yahoo.Controls.Sizable3PartControlBase.prototype._onToolTipChanged = function(sender, e) {

	//log("Sizable3PartControlBase._onToolTipChanged");

	// Call base class
	this.baseclassSizable3PartControlBase._onToolTipChanged.call(this, sender, e);
	
	// Set tooltip
	this._imgMiddle.tooltip = this.tooltip;
	this._imgLeft.tooltip = this.tooltip;
	this._imgRight.tooltip = this.tooltip;
}

/*-----------------------------------------------------------*/
// Private code
/*-----------------------------------------------------------*/
/**
 * Disposes native Widget Engine objects.
 * @private
 */
Yahoo.Controls.Sizable3PartControlBase.prototype._Sizable3PartControlBase_disposeNativeObjects = function() {

	//log("Sizable3PartControlBase._Sizable3PartControlBase_disposeNativeObjects");

	if(this._imgMiddle!=null) { this._imgMiddle.removeFromSuperview(); this._imgMiddle = null; }
	if(this._imgLeft!=null) { this._imgLeft.removeFromSuperview(); this._imgLeft = null; }
	if(this._imgRight!=null) { this._imgRight.removeFromSuperview(); this._imgRight = null; }
}

/**
 * Loads control elements based on current theme.
 * @private
 */
Yahoo.Controls.Sizable3PartControlBase.prototype._Sizable3PartControlBase_loadTheme = function() {

	//log("Sizable3PartControlBase._Sizable3PartControlBase_loadTheme");

	// Remove any current objects
	this._Sizable3PartControlBase_disposeNativeObjects();

	// Load objects using current theme
	this._imgMiddle = this._theme.getItem(this._themePrefix + "Middle");
	this._imgMiddle.tag = this;
	this._frame.addSubview(this._imgMiddle);
	this._imgLeft = this._theme.getItem(this._themePrefix + "Left");
	this._imgLeft.tag = this;
	this._frame.addSubview(this._imgLeft);
	this._imgRight = this._theme.getItem(this._themePrefix + "Right");
	this._imgRight.tag = this;
	this._frame.addSubview(this._imgRight);
}

/**
 * Resizes control border elements.
 * @private
 */
Yahoo.Controls.Sizable3PartControlBase.prototype._Sizable3PartControlBase_paintBackground = function() {

	var width;
	var height;
	
	width = this.width;
	height = this.height;

	this._imgLeft.height = height;
	this._imgMiddle.hOffset = this._imgLeft.width;
	this._imgMiddle.width = width - (this._imgLeft.width + this._imgRight.width);
	this._imgMiddle.height = height;
	this._imgRight.hOffset = width - this._imgRight.width;
	this._imgRight.height = height;
}

/*-----------------------------------------------------------*/
// Public code
/*-----------------------------------------------------------*/
/**
 * Initializes control.
 * @param {Yahoo.Controls.Theme} theme The theme this control should use or null to create an instance of the default theme.
 * @param {String} themePrefix The prefix used to retrieve styles from the theme for this control.
 */
Yahoo.Controls.Sizable3PartControlBase.prototype.initialize = function(theme, themePrefix) {

	//log("Sizable3PartControlBase.initialize()");
	
	if(themePrefix==null) { throw new Yahoo.ArgumentNullException("themePrefix"); }

	// Call base class
	this.baseclassSizable3PartControlBase.initialize.call(this, theme);

	this._isInitializing = true;

	this._themePrefix = themePrefix;

	// Internal objects
	this._imgMiddle = null;
	this._imgLeft = null;
	this._imgRight = null;
	
	// Load image objects
	this._Sizable3PartControlBase_loadTheme();
	
	// Set locations/sizes that do not change
	this._imgLeft.hOffset = 0;
	this._imgLeft.vOffset = 0;
	// Size from image

	this._imgMiddle.vOffset = 0;
	this._imgRight.vOffset = 0;
	// Size from image

	// We don't resize since we must be inherited
	//this._onResize(this, new Yahoo.EventArgs());

	this._isInitializing = false;
}

/**
 * Disposes control's resources.
 */
Yahoo.Controls.Sizable3PartControlBase.prototype.dispose = function() {
	
	// Call base class
	this.baseclassSizable3PartControlBase.dispose.call(this);
	
	// Dispose native items
	this._Sizable3PartControlBase_disposeNativeObjects();
}

/*-----------------------------------------------------------*/
// Public properties
/*-----------------------------------------------------------*/
