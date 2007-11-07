/*---------------------------------------------------------------------*/
/// <copyright from='2005' to='2006' company='Yahoo! Inc.'>
/// (C) Copyright 2005-2006 Yahoo! Inc. All Rights Reserved.
/// </copyright>

/**
 * ProgressBar control.
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
Yahoo.Controls.ProgressBar = function(theme) {

	//log("ProgressBar.ctor()");
	if(arguments.length>0) {
		this.initialize(theme);
	}
}

/**
 * Define inheritance chain.
 */
Yahoo.Controls.ProgressBar.prototype = new Yahoo.Controls.SizableControlBase();
Yahoo.Controls.ProgressBar.prototype.constructor = Yahoo.Controls.ProgressBar;
Yahoo.Controls.ProgressBar.prototype.baseclassProgressBar = Yahoo.Controls.SizableControlBase.prototype;

/*-----------------------------------------------------------*/
// Control code
/*-----------------------------------------------------------*/
/**
 * Raises the onResize event.
 * @param {Object} sender The source of the event.
 * @param {Yahoo.EventArgs} e The EventArgs object that contains event details.
 */
Yahoo.Controls.ProgressBar.prototype._onResize = function(sender, e) {

	//log("ProgressBar._onResize");

	// Call base class
	this.baseclassProgressBar._onResize.call(this, sender, e);
	
	// Resize fill image
	this._progressBar_setFillImageHeight();
	this._progressBar_setFill();
}

/**
 * Raises the onThemeChanged event.
 * @param {Object} sender The source of the event.
 * @param {Yahoo.EventArgs} e The EventArgs object that contains event details.
 */
Yahoo.Controls.ProgressBar.prototype._onThemeChanged = function(sender, e) {

	//log("ProgressBar._onThemeChanged");

	// Call base class
	this.baseclassProgressBar._onThemeChanged.call(this, sender, e);

	// TODO:
	//this._progressBar_loadTheme();
}

/*---------------------------------------------------------------------*/
// Private code
/*---------------------------------------------------------------------*/
/**
 * Sets the hOffset for the fill image.
 * @private
 */
Yahoo.Controls.ProgressBar.prototype._progressBar_setFillImageLeft = function() {
	
	if(this._imgFill!=null) {
		this._imgFill.hOffset = this._fillMarginLeft;
	}
}

/**
 * Sets the vOffset for the fill image.
 * @private
 */
Yahoo.Controls.ProgressBar.prototype._progressBar_setFillImageTop = function() {
	
	if(this._imgFill!=null) {
		this._imgFill.vOffset = this._fillMarginTop;
	}
}

/**
 * Sets the height for the fill image.
 * @private
 */
Yahoo.Controls.ProgressBar.prototype._progressBar_setFillImageHeight = function() {
	
	if(this._imgFill!=null) {
		this._imgFill.height = this.height - this._fillMarginTop - this._fillMarginBottom;
	}
}

/**
 * Sets the size of the fill image to match the current value.
 * @private
 */
Yahoo.Controls.ProgressBar.prototype._progressBar_setFill = function() {
	
	var width;
	
	if(this._imgFill!=null) {
		try {
			if(this._maximum!=0) {
				width = (this._value / this._maximum) * (this.width - this._fillMarginLeft - this._fillMarginRight);
			}
			else {
				width = 0;
			}
			if(isNaN(width)==false) {
				this._imgFill.width = Math.round(width);
			}
		}
		catch(e) {
			log(e);
		}
	}
}

/*---------------------------------------------------------------------*/
// Public code
/*---------------------------------------------------------------------*/
/**
 * True constructor. Must be called if this class is overridden.
 * @param {Yahoo.Controls.Theme} theme The theme this control should use or null to create an instance of the default theme.
 */
Yahoo.Controls.ProgressBar.prototype.initialize = function(theme) {

	//log("ProgressBar.initialize()");
	
	var params;
	
	// Call base class constructor
	this.baseclassProgressBar.initialize.call(this, theme, "progressBar");

	// Initialize variables
	this._maximum = 0;
	this._minimum = 0;
	this._value = 0;
	this._imgFill = this._theme.getItem("progressBarFill");
	this._frame.addSubview(this._imgFill);

	// Get margins for fill image from theme
	params = this._theme.getParameter("progressBarFillMargins");
	this._fillMarginLeft = parseInt(params.left);
	this._fillMarginRight = parseInt(params.right);
	this._fillMarginTop = parseInt(params.top);
	this._fillMarginBottom = parseInt(params.bottom);

	this._progressBar_setFillImageLeft();
	this._progressBar_setFillImageTop();
	this._progressBar_setFillImageHeight();
	this._progressBar_setFill();
}

/**
 * Disposes control's resources.
 */
Yahoo.Controls.ProgressBar.prototype.dispose = function() {
	
	// Dispose native items
	// TODO: This should be moved elsewhere once we support changing themes on the fly
	if(this._imgFill!=null) { this._imgFill.removeFromSuperview(); this._imgFill = null; }

	// Call base class
	this.baseclassProgressBar.dispose.call(this);

}

/*---------------------------------------------------------------------*/
// Public properties
/*---------------------------------------------------------------------*/
/**
 * Gets or sets the maximum value.
 * @type Integer
 */
Yahoo.Controls.ProgressBar.prototype.maximum getter = function() {

	return this._maximum;
}

Yahoo.Controls.ProgressBar.prototype.maximum setter = function(value) {

	if(value!=null) {
		this._maximum = value;
	}
	else {
		throw new Yahoo.ArgumentNullException("value");
	}
}

/**
 * Gets or sets the minimimum value.
 * @type Integer
 */
Yahoo.Controls.ProgressBar.prototype.minimum getter = function() {

	return this._minimum;
}

Yahoo.Controls.ProgressBar.prototype.minimum setter = function(value) {

	if(value!=null) {
		this._minimum = value;
	}
	else {
		throw new Yahoo.ArgumentNullException("value");
	}
}

/**
 * Gets or sets the current value.
 * @type Integer
 */
Yahoo.Controls.ProgressBar.prototype.value getter = function() {

	return this._value;
}

Yahoo.Controls.ProgressBar.prototype.value setter = function(value) {

	if(value!=null) {
		if((value<this._minimum) || (value>this._maximum)) {
			throw new Yahoo.ArgumentOutOfRangeException("value");
		}
		else {
			this._value = value;
			this._progressBar_setFill();
		}
	}
	else {
		throw new Yahoo.ArgumentNullException("value");
	}
}

