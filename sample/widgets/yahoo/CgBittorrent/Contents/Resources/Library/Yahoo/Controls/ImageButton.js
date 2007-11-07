/*---------------------------------------------------------------------*/
/// <copyright from='2005' to='2006' company='Yahoo! Inc.'>
/// (C) Copyright 2005-2006 Yahoo! Inc. All Rights Reserved.
/// </copyright>

/**
 * ImageButton control.
 */
/*---------------------------------------------------------------------*/

/*---------------------------------------------------------------------*/
// Constructor
/*---------------------------------------------------------------------*/
/**
 * Default constructor.
 * @constructor
 * @param {Yahoo.Controls.Theme} theme The theme this control should use or null to create an instance of the default theme.
 * param {Image} normal The image to use in the rest state.
 * param {Image} over The image to use in the mouse over state.
 * param {Image} down The image to use in the mouse down state.
 * param {Image} disabled The image to use in the disabled state.
 */
Yahoo.Controls.ImageButton = function(theme, normal, over, down, disabled) {

	//log("ImageButton.ctor()");
	if(arguments.length>0) {
		this.initialize(theme, normal, over, down, disabled);
	}
}

/**
 * Define inheritance chain.
 */
Yahoo.Controls.ImageButton.prototype = new Yahoo.Controls.Control();
Yahoo.Controls.ImageButton.prototype.constructor = Yahoo.Controls.ImageButton;
Yahoo.Controls.ImageButton.prototype.baseclassImageButton = Yahoo.Controls.Control.prototype;

/*-----------------------------------------------------------*/
// Control code
/*-----------------------------------------------------------*/
/**
 * Raises the onEnabledChanged event.
 * @param {Object} sender The source of the event.
 * @param {Yahoo.EventArgs} e The EventArgs object that contains event details.
 */
Yahoo.Controls.ImageButton.prototype._onEnabledChanged = function(sender, e) {

	//log("ImageButton._onEnabledChanged");

	// Call baseclass
	this.baseclassImageButton._onEnabledChanged.call(this, sender, e);

	this._imageButton_setButtonState();
}

/**
 * Raises the onToolTipChanged event.
 * @param {Object} sender The source of the event.
 * @param {Yahoo.EventArgs} e The EventArgs object that contains event details.
 */
Yahoo.Controls.ImageButton.prototype._onToolTipChanged = function(sender, e) {

	//log("ImageButton._onToolTipChanged");

	// Call baseclass
	this.baseclassImageButton._onToolTipChanged.call(this, sender, e);
	
	// Set tooltip
	this._imgDisabled.tooltip = this.toolTip;
	this._imgDown.tooltip = this.toolTip;
	this._imgNormal.tooltip = this.toolTip;
	this._imgOver.tooltip = this.toolTip;
}

/**
 * Handles onEnter event for whole control.
 * @param {Object} sender The source of the event.
 * @param {Yahoo.EventArgs} e The EventArgs object that contains event details.
 */
Yahoo.Controls.ImageButton.prototype._onEnter = function(sender, e) {

	//log("ImageButton._onEnter");

	// Call baseclass
	this.baseclassImageButton._onEnter.call(this, sender, e);

	this._imageButton_setButtonState();
}

/**
 * Handles onLeave event for whole control.
 * @param {Object} sender The source of the event.
 * @param {Yahoo.EventArgs} e The EventArgs object that contains event details.
 */
Yahoo.Controls.ImageButton.prototype._onLeave = function(sender, e) {

	//log("ImageButton._onLeave");

	// Call baseclass
	this.baseclassImageButton._onLeave.call(this, sender, e);
	
	this._imageButton_setButtonState();
}

/**
 * Handles onMouseDown event for whole control.
 * @param {Object} sender The source of the event.
 * @param {Yahoo.EventArgs} e The EventArgs object that contains event details.
 */
Yahoo.Controls.ImageButton.prototype._imageButton_onMouseDown = function(sender, e) {

	//log("ImageButton._imageButton_onMouseDown");

	sender._imageButton_setButtonState();
}

/**
 * Handles onMouseUp event for whole control.
 * @param {Object} sender The source of the event.
 * @param {Yahoo.EventArgs} e The EventArgs object that contains event details.
 */
Yahoo.Controls.ImageButton.prototype._imageButton_onMouseUp = function(sender, e) {

	//log("ImageButton._imageButton_onMouseUp");

	sender._imageButton_setButtonState();
}

/**
 * Raises the onResize event.
 * @param {Object} sender The source of the event.
 * @param {Yahoo.EventArgs} e The EventArgs object that contains event details.
 */
Yahoo.Controls.ImageButton.prototype._onResize = function(sender, e) {

	//log("ImageButton._onResize");

	// Call baseclass
	this.baseclassImageButton._onResize.call(this, sender, e);
	
	var width = this.width;
	var height = this.height;
	
	// Resize images
	this._imgDisabled.width = width;
	this._imgDisabled.height = height;
	this._imgDown.width = width;
	this._imgDown.height = height;
	this._imgNormal.width = width;
	this._imgNormal.height = height;
	this._imgOver.width = width;
	this._imgOver.height = height;
}

/**
 * Handles the onThemeChanged event.
 * @param {Object} sender The source of the event.
 * @param {Yahoo.EventArgs} e The EventArgs object that contains event details.
 */
Yahoo.Controls.ImageButton.prototype._onThemeChanged = function(sender, e) {

	//log("Button._onThemeChanged");

	// Call base class
	this.baseclassImageButton._onThemeChanged.call(this, sender, e);

	this._imageButton_loadTheme();
}

/*---------------------------------------------------------------------*/
// Private code
/*---------------------------------------------------------------------*/
/**
 * Disposes native Widget Engine objects.
 * @private
 */
Yahoo.Controls.ImageButton.prototype._imageButton_disposeNativeObjects = function() {

	//log("ImageButton._imageButton_disposeNativeObjects");
	
	if(this._imgDisabled!=null) { this._imgDisabled.removeFromSuperview(); this._imgDisabled = null; }
	if(this._imgDown!=null) { this._imgDown.removeFromSuperview(); this._imgDown = null; }
	if(this._imgNormal!=null) { this._imgNormal.removeFromSuperview(); this._imgNormal = null; }
	if(this._imgOver!=null) { this._imgOver.removeFromSuperview(); this._imgOver = null; }
}

/**
 * Loads control elements based on current theme.
 * @private
 */
Yahoo.Controls.ImageButton.prototype._imageButton_loadTheme = function() {

	// Load images
	this._imgDisabled = this._imageButton_getButton(this._disabledItem);
	this._imgDown = this._imageButton_getButton(this._downItem);
	this._imgNormal = this._imageButton_getButton(this._normalItem);
	this._imgOver = this._imageButton_getButton(this._overItem);
	
	this._imageButton_setButtonState();
}

/**
 * Sets the button state.
 * @private
 */
Yahoo.Controls.ImageButton.prototype._imageButton_setButtonState = function() {

	if(this.disposing==false) {

		// Hide all buttons
		this._imgDisabled.visible = false;
		this._imgDown.visible = false;
		this._imgNormal.visible = false;
		this._imgOver.visible = false;
	
		if(this.enabled==false) {
			this._imgDisabled.visible = true;
		}
		else {
			if(this._isMouseOver==true && this._isMouseDown==true) {
				this._imgDown.visible = true;
			}
			else if(this._isMouseOver==true && this._isMouseDown==false) {
				this._imgOver.visible = true;
			}
			else {
				this._imgNormal.visible = true;
			}
		}  // if enabled
	}  // if disposing
}

/**
 * Loads an image from the theme.
 * @private
 * @param {String} itemName The style name to retrieve.
 * @type Image
 */
Yahoo.Controls.ImageButton.prototype._imageButton_getButton = function(itemName) {

	var result;

	result = this._theme.getItem(itemName);
	result.visible = false;
	result.tooltip = this.toolTip;
	result.tag = this;
	this._frame.addSubview(result);
	
	return result;
}

/*---------------------------------------------------------------------*/
// Public code
/*---------------------------------------------------------------------*/
/**
 * True constructor. Must be called if this class is overridden.
 * @param {Yahoo.Controls.Theme} theme The theme this control should use or null to create an instance of the default theme.
 * param {Image} normal The image to use in the rest state.
 * param {Image} over The image to use in the mouse over state.
 * param {Image} down The image to use in the mouse down state.
 * param {Image} disabled The image to use in the disabled state.
 */
Yahoo.Controls.ImageButton.prototype.initialize = function(theme, normal, over, down, disabled) {

	//log("ImageButton.initialize()");
	
	// Call base class constructor
	this.baseclassImageButton.initialize.call(this, theme);
	
	this._normalItem = normal;
	this._overItem = over;
	this._downItem = down;
	this._disabledItem = disabled;

    // Hook into mouse events for whole control
   	this.addEventHandler(this._imageButton_onMouseDown, "MouseDown");
	this.addEventHandler(this._imageButton_onMouseUp, "MouseUp");

    this._imageButton_loadTheme();
}

/**
 * Disposes control's resources.
 */
Yahoo.Controls.ImageButton.prototype.dispose = function() {

	this._imageButton_disposeNativeObjects();
	
	// Call base class
	this.baseclassImageButton.dispose.call(this);
}

/*---------------------------------------------------------------------*/
// Public properties
/*---------------------------------------------------------------------*/
/**
 * Gets or sets the height of the control.
 * @type Integer
 */
Yahoo.Controls.ImageButton.prototype.height getter = function() {

	var result;

	// NOTE: Overrides baseclass
	if(this._frame.height!=-1) {
		result = this._frame.height;
	}
	else {
		result = this._imgNormal.height;
	}
	
	return result;
}

Yahoo.Controls.ImageButton.prototype.height setter = function(value) {

	if(value!=null) {
		this._control_setSize(this.width, value);
	}
	else {
		throw new Yahoo.ArgumentNullException("value");
	}
}

/**
 * Gets or sets the width of the control.
 * @type Integer
 */
Yahoo.Controls.ImageButton.prototype.width getter = function() {

	var result;

	// NOTE: Overrides baseclass
	if(this._frame.width!=-1) {
		result = this._frame.width;
	}
	else {
		result = this._imgNormal.width;
	}
	
	return result;
}

Yahoo.Controls.ImageButton.prototype.width setter = function(value) {

	if(value!=null) {
		this._control_setSize(value, this.height);
	}
	else {
		throw new Yahoo.ArgumentNullException("value");
	}
}

