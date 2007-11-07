/*---------------------------------------------------------------------*/
/// <copyright from='2005' to='2006' company='Yahoo! Inc.'>
/// (C) Copyright 2005-2006 Yahoo! Inc. All Rights Reserved.
/// </copyright>

/**
 * Label control.
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
Yahoo.Controls.Label = function(theme) {

	//log("Label.ctor()");
	if(arguments.length>0) {
		this.initialize(theme);
	}
}

/**
 * Define inheritance chain.
 */
Yahoo.Controls.Label.prototype = new Yahoo.Controls.Control();
Yahoo.Controls.Label.prototype.constructor = Yahoo.Controls.Label;
Yahoo.Controls.Label.prototype.baseclassLabel = Yahoo.Controls.Control.prototype;

/*-----------------------------------------------------------*/
// Control code
/*-----------------------------------------------------------*/
/**
 * Raises the onFontChanged event.
 * @param {Object} sender The source of the event.
 * @param {Yahoo.EventArgs} e The EventArgs object that contains event details.
 */
Yahoo.Controls.Label.prototype._onFontChanged = function(sender, e) {

	//log("Label._onFontChanged");

	// Call base class
	this.baseclassLabel._onFontChanged.call(this, sender, e);

	this._lblText.style.fontFamily = this.font.name;
	this._lblText.style.fontSize = this.font.size + "px";

	this._label_setTextLocation();
}

/**
 * Raises the onForeColorChanged event.
 * @param {Object} sender The source of the event.
 * @param {Yahoo.EventArgs} e The EventArgs object that contains event details.
 */
Yahoo.Controls.Label.prototype._onForeColorChanged = function(sender, e) {

	//log("Label._onForeColorChanged");

	// Call base class
	this.baseclassLabel._onForeColorChanged.call(this, sender, e);
	
	this._lblText.color = this.foreColor;
}

/**
 * Raises the onResize event.
 * @param {Object} sender The source of the event.
 * @param {Yahoo.EventArgs} e The EventArgs object that contains event details.
 */
Yahoo.Controls.Label.prototype._onResize = function(sender, e) {

	//log("Label._onResize");

	// Call base class
	this.baseclassLabel._onResize.call(this, sender, e);
	
	// Resize text
	this._label_setTextLocation();
}

/**
 * Raises the onTextChanged event.
 * @param {Object} sender The source of the event.
 * @param {Yahoo.EventArgs} e The EventArgs object that contains event details.
 */
Yahoo.Controls.Label.prototype._onTextChanged = function(sender, e) {

	//log("Label._onTextChanged");

	// Call base class
	this.baseclassLabel._onTextChanged.call(this, sender, e);

	// Set text
	this._lblText.data = this.text;

    // Set/Update location
	this._label_setTextLocation();
}

/**
 * Raises the onToolTipChanged event.
 * @param {Object} sender The source of the event.
 * @param {Yahoo.EventArgs} e The EventArgs object that contains event details.
 */
Yahoo.Controls.Label.prototype._onToolTipChanged = function(sender, e) {

	//log("Label._onToolTipChanged");

	// Call base class
	this.baseclassLabel._onToolTipChanged.call(this, sender, e);
	
	// Set tooltip
	this._lblText.tooltip = this.toolTip;
}

/**
 * Raises the onThemeChanged event.
 * @param {Object} sender The source of the event.
 * @param {Yahoo.EventArgs} e The EventArgs object that contains event details.
 */
Yahoo.Controls.Label.prototype._onThemeChanged = function(sender, e) {

	log("Label._onThemeChanged");

	// Call base class
	this.baseclassLabel._onThemeChanged.call(this, sender, e);

	this._label_loadTheme();
}

/*---------------------------------------------------------------------*/
// Private code
/*---------------------------------------------------------------------*/
/**
 * Disposes native Widget Engine objects.
 * @private
 */
Yahoo.Controls.Label.prototype._label_disposeNativeObjects = function() {

	//log("Label._label_disposeNativeObjects");
	
	if(this._lblText!=null) { this._lblText.removeFromSuperview(); this._lblText = null; }
}

/**
 * Loads control elements based on current theme.
 * @private
 */
Yahoo.Controls.Label.prototype._label_loadTheme = function() {

    //log("_label_loadTheme");

	// Remove any current objects
	this._label_disposeNativeObjects();

	this._lblText = this._theme.getItem("labelLabel");
	this._lblText.anchorStyle = "topLeft";
	// Change tracking for label so we can use it to detect when the mouse is over the whole Label
	this._lblText.tracking = "rectangle";
	this._frame.addSubview(this._lblText);

    this._lblText.data = this.text;
    
    this._label_setTextLocation();
}

/**
 * Sets the hOffset for the text label.
 * @private
 */
Yahoo.Controls.Label.prototype._label_setTextLocation = function() {
	
	//log("Label._label_setTextLocation");
	
	var width;
	var height;
	
	if(this._isInitializing==false) {
	
		width = this.width;
		height = this.height;
	
		if(this._autoSize==true) {
			this._lblText.width = -1;
		}
		else {
			this._lblText.width = width;
		}
		
		// This takes care of aligning the text in a way that is more familiar for programmers
		switch(this._textAlign) {
			// Do vertical alignment
			case Yahoo.Drawing.ContentAlignment.BottomCenter:
			case Yahoo.Drawing.ContentAlignment.BottomLeft:
			case Yahoo.Drawing.ContentAlignment.BottomRight:
				this._lblText.vOffset = (height - this._lblText.height);
				break;
			case Yahoo.Drawing.ContentAlignment.MiddleCenter:
			case Yahoo.Drawing.ContentAlignment.MiddleLeft:
			case Yahoo.Drawing.ContentAlignment.MiddleRight:
				this._lblText.vOffset = ((height / 2) - (this._lblText.height / 2));
				break;
			case Yahoo.Drawing.ContentAlignment.TopCenter:
			case Yahoo.Drawing.ContentAlignment.TopLeft:
			case Yahoo.Drawing.ContentAlignment.TopRight:
				this._lblText.vOffset = 0;
				break;
			default:
				throw new Yahoo.InvalidEnumArgumentException();
				break;
		}
		
		switch(this._textAlign) {
			// Do horizontal alignment
			case Yahoo.Drawing.ContentAlignment.BottomCenter:
			case Yahoo.Drawing.ContentAlignment.MiddleCenter:
			case Yahoo.Drawing.ContentAlignment.TopCenter:
				this._lblText.alignment = "center";
				this._lblText.hOffset = width / 2;
				break;
			case Yahoo.Drawing.ContentAlignment.BottomLeft:
			case Yahoo.Drawing.ContentAlignment.MiddleLeft:
			case Yahoo.Drawing.ContentAlignment.TopLeft:
				this._lblText.alignment = "left";
				this._lblText.hOffset = 0;
				break;
			case Yahoo.Drawing.ContentAlignment.BottomRight:
			case Yahoo.Drawing.ContentAlignment.MiddleRight:
			case Yahoo.Drawing.ContentAlignment.TopRight:
				this._lblText.alignment = "right";
				this._lblText.hOffset = width;
				break;
			//default:
				//throw new Yahoo.InvalidEnumArgumentException();
				//break;
		}
	}  // isInitializing
}

/*---------------------------------------------------------------------*/
// Public code
/*---------------------------------------------------------------------*/
/**
 * True constructor. Must be called if this class is overridden.
 * @param {Yahoo.Controls.Theme} theme The theme this control should use or null to create an instance of the default theme.
 */
Yahoo.Controls.Label.prototype.initialize = function(theme) {

	//log("Label.initialize()");
	
	var params;
	
	// Call base class constructor
	this.baseclassLabel.initialize.call(this, theme);

	this._isInitializing = true;

	// Includes
	lib.include("Yahoo.InvalidEnumArgumentException");
	lib.include("Yahoo.Drawing.ContentAlignment");

	// Initialize variables (optimized version)
	this._autoSize = false;
	this._textAlign = Yahoo.Drawing.ContentAlignment.MiddleLeft;

	this._label_loadTheme();

	this._isInitializing = false;
}

/**
 * Disposes control's resources.
 */
Yahoo.Controls.Label.prototype.dispose = function() {
	
	// Dispose native items
	this._label_disposeNativeObjects();

	// Call base class
	this.baseclassLabel.dispose.call(this);
}

/**
 * Sets the label properties based on a Widget Engine Text-object.
 * @param {Text} text The Text object to set the label style from.
 */
Yahoo.Controls.Label.prototype.fromTextObject = function(text) {

	if(text!=null) {
	    this._lblText.style.fontFamily = text.style.fontFamily;
	    this._lblText.style.fontSize = text.style.fontSize;
	    this._lblText.style.fontWeight = text.style.fontWeight;
	    if(text.style.KonTextTruncation != "") {
    	    this._lblText.style.KonTextTruncation = text.style.KonTextTruncation;
	    }
	    
		this._backColor = text.bgColor;
		this._frame.style.backgroundColor = this._backColor;
		
		this._foreColor = text.color;
		this._lblText.color = this._foreColor;
		
		this._text = text.data;
		this._lblText.data = this.text;

		this.opacity = text.opacity;
		this._lblText.scrolling = text.scrolling;

		this._toolTip = text.tooltip;
		this._lblText.tooltip = this._toolTip;

		this.visible = text.visible;
		this.zOrder = text.zOrder;

		this._control_setSize(text.width, text.height)

		// This will call setLocation
		this.font = new Yahoo.Drawing.Font(text.font, text.size);
	}
	else {
		throw new Yahoo.ArgumentNullException("text");
	}
}

/*---------------------------------------------------------------------*/
// Public properties
/*---------------------------------------------------------------------*/
/**
 * Gets or sets a value indicating whether the label resizes to fit its contents.
 * @type Boolean
 */
Yahoo.Controls.Label.prototype.autoSize getter = function() {

	return this._autoSize;
}

Yahoo.Controls.Label.prototype.autoSize setter = function(value) {

	if(value!=null) {
		this._autoSize = value;
		this._label_setTextLocation();
	}
	else {
		throw new Yahoo.ArgumentNullException("value");
	}
}

/**
 * Gets or sets the alignment of the text on the Label.
 * @type Yahoo.Drawing.ContentAlignment
 */
Yahoo.Controls.Label.prototype.textAlign getter = function() {

	return this._textAlign;
}

Yahoo.Controls.Label.prototype.textAlign setter = function(value) {

	if(value!=null) {
		this._textAlign = value;
		this._label_setTextLocation();
	}
	else {
		throw new Yahoo.ArgumentNullException("value");
	}
}

/**
 * Gets or sets a value indicating whether the text should scroll if it does not fit.
 * @type Boolean
 */
Yahoo.Controls.Label.prototype.scrolling getter = function() {

	return this._lblText.scrolling;
}

Yahoo.Controls.Label.prototype.scrolling setter = function(value) {

	if(value!=null) {
		this._lblText.scrolling = value;
	}
	else {
		throw new Yahoo.ArgumentNullException("value");
	}
}

/**
 * Gets the style object for this text label.
 * @type Style
 */
Yahoo.Controls.Label.prototype.style getter = function() {

	return this._lblText.style;
}

Yahoo.Controls.Label.prototype.style setter = function(value) {

	throw new Error("style is read-only");
}
