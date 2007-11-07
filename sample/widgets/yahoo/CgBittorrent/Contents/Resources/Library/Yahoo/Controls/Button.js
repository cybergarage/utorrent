/*---------------------------------------------------------------------*/
/// <copyright from='2005' to='2007' company='Yahoo! Inc.'>
/// (C) Copyright 2005-2007 Yahoo! Inc. All Rights Reserved.
/// </copyright>

/**
 * Button control.
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
Yahoo.Controls.Button = function(theme) {

	//log("Button.ctor()");
	if(arguments.length>0) {
		this.initialize(theme);
	}
}

/**
 * Define inheritance chain.
 */
Yahoo.Controls.Button.prototype = new Yahoo.Controls.Sizable3PartControlBase();
Yahoo.Controls.Button.prototype.constructor = Yahoo.Controls.Button;
Yahoo.Controls.Button.prototype.baseclassButton = Yahoo.Controls.Sizable3PartControlBase.prototype;

/*-----------------------------------------------------------*/
// Control code
/*-----------------------------------------------------------*/
/**
 * Raises the onEnabledChanged event.
 * @param {Object} sender The source of the event.
 * @param {Yahoo.EventArgs} e The EventArgs object that contains event details.
 */
Yahoo.Controls.Button.prototype._onEnabledChanged = function(sender, e) {

	//log("Button._onEnabledChanged");

	// Call baseclass
	this.baseclassButton._onEnabledChanged.call(this, sender, e);

	this._lblText.enabled = this.enabled;
	this._button_setButtonState();
}

/**
 * Raises the onFontChanged event.
 * @param {Object} sender The source of the event.
 * @param {Yahoo.EventArgs} e The EventArgs object that contains event details.
 */
Yahoo.Controls.Button.prototype._onFontChanged = function(sender, e) {

	//log("Button._onFontChanged");

	// Call baseclass
	this.baseclassButton._onFontChanged.call(this, sender, e);

	this._lblText.font = this.font;
}

/**
 * Raises the onForeColorChanged event.
 * @param {Object} sender The source of the event.
 * @param {Yahoo.EventArgs} e The EventArgs object that contains event details.
 */
Yahoo.Controls.Button.prototype._onForeColorChanged = function(sender, e) {

	//log("Button._onForeColorChanged");

	// Call baseclass
	this.baseclassButton._onForeColorChanged.call(this, sender, e);
	
	this._lblText.foreColor = this.foreColor;
}

/**
 * Raises the onResize event.
 * @param {Object} sender The source of the event.
 * @param {Yahoo.EventArgs} e The EventArgs object that contains event details.
 */
Yahoo.Controls.Button.prototype._onResize = function(sender, e) {

	//log("Button._onResize");

	// Call baseclass
	this.baseclassButton._onResize.call(this, sender, e);
	
	// Resize text
	this._button_setTextLocation();
}

/**
 * Raises the onTextChanged event.
 * @param {Object} sender The source of the event.
 * @param {Yahoo.EventArgs} e The EventArgs object that contains event details.
 */
Yahoo.Controls.Button.prototype._onTextChanged = function(sender, e) {

	//log("Button._onTextChanged");

	// Call baseclass
	this.baseclassButton._onTextChanged.call(this, sender, e);
	
	// Resize text
	this._lblText.text = this.text;
}

/**
 * Raises the onToolTipChanged event.
 * @param {Object} sender The source of the event.
 * @param {Yahoo.EventArgs} e The EventArgs object that contains event details.
 */
Yahoo.Controls.Button.prototype._onToolTipChanged = function(sender, e) {

	//log("Button._onToolTipChanged");

	// Call baseclass
	this.baseclassButton._onToolTipChanged.call(this, sender, e);
	
	// Set tooltip
	this._lblText.toolTip = this.toolTip;
}

/**
 * Handles onEnter event for whole control.
 * @param {Object} sender The source of the event.
 * @param {Yahoo.EventArgs} e The EventArgs object that contains event details.
 */
Yahoo.Controls.Button.prototype._onEnter = function(sender, e) {

	//log("Button._onEnter");

	// Cancel enter event if we entered from / left one of our subcontrols
	if((this._isMouseOver == false) || this.displayRectangle.contains(system.event.x + this.left, system.event.y + this.top) == false) {
	
		// Call baseclass
		this.baseclassButton._onEnter.call(this, sender, e);

		this._button_setButtonState();
	}
}

/**
 * Handles onLeave event for whole control.
 * @param {Object} sender The source of the event.
 * @param {Yahoo.EventArgs} e The EventArgs object that contains event details.
 */
Yahoo.Controls.Button.prototype._onLeave = function(sender, e) {

	//log("Button._onLeave");

	// Cancel leave event if we entered one of our subcontrols
	if(this.displayRectangle.contains(system.event.x + this.left, system.event.y + this.top) == false) {

		// Call baseclass
		this.baseclassButton._onLeave.call(this, sender, e);
		this._button_setButtonState();
	}
}

/**
 * Handles onMouseDown event for whole control.
 * @param {Object} sender The source of the event.
 * @param {Yahoo.EventArgs} e The EventArgs object that contains event details.
 */
Yahoo.Controls.Button.prototype._button_onMouseDown = function(sender, e) {

	//log("Button._button_onMouseDown");

	sender._button_setButtonState();
}

/**
 * Handles onMouseUp event for whole control.
 * @param {Object} sender The source of the event.
 * @param {Yahoo.EventArgs} e The EventArgs object that contains event details.
 */
Yahoo.Controls.Button.prototype._button_onMouseUp = function(sender, e) {

	//log("Button._button_onMouseUp");

	sender._button_setButtonState();
}

/**
 * Handles onMouseEnter event for label.
 * @param {Object} sender The source of the event.
 * @param {Yahoo.EventArgs} e The EventArgs object that contains event details.
 */
Yahoo.Controls.Button.prototype._button_lblText_onEnter = function(sender, e) {

	//log("Button._button_lblText_onEnter");
	sender.parent._onEnter.call(sender.parent, sender.parent, new Yahoo.EventArgs());
}

/**
 * Handles the onThemeChanged event.
 * @param {Object} sender The source of the event.
 * @param {Yahoo.EventArgs} e The EventArgs object that contains event details.
 */
Yahoo.Controls.Button.prototype._onThemeChanged = function(sender, e) {

	//log("Button._onThemeChanged");

	// Call base class
	this.baseclassButton._onThemeChanged.call(this, sender, e);

	this._button_loadTheme();
}

/**
 * Handles onMouseExit event for label.
 * @param {Object} sender The source of the event.
 * @param {Yahoo.EventArgs} e The EventArgs object that contains event details.
 */
Yahoo.Controls.Button.prototype._button_lblText_onLeave = function(sender, e) {

	//log("Button._button_lblText_onLeave");
	
	// Don't forward this if we are still within the parent control
	if(sender.parent.displayRectangle.contains(system.event.x + sender.left + sender.parent.left, system.event.y + sender.top + sender.parent.top) == false) {
		sender.parent._onLeave.call(sender.parent, sender.parent, new Yahoo.EventArgs());
	}
}

/**
 * Handles onMouseDown event for label.
 * @param {Object} sender The source of the event.
 * @param {Yahoo.EventArgs} e The EventArgs object that contains event details.
 */
Yahoo.Controls.Button.prototype._button_lblText_onMouseDown = function(sender, e) {

	//log("Button._button_lblText_onMouseDown");
	sender.parent._onMouseDown.call(sender.parent, sender.parent, new Yahoo.EventArgs());
}

/**
 * Handles onMouseUp event for label.
 * @param {Object} sender The source of the event.
 * @param {Yahoo.EventArgs} e The EventArgs object that contains event details.
 */
Yahoo.Controls.Button.prototype._button_lblText_onMouseUp = function(sender, e) {

	//log("Button._button_lblText_onMouseUp");
	sender.parent._onMouseUp.call(sender.parent, sender.parent, new Yahoo.EventArgs());
}

/*---------------------------------------------------------------------*/
// Private code
/*---------------------------------------------------------------------*/
/**
 * Disposes native Widget Engine objects.
 * @private
 */
Yahoo.Controls.Button.prototype._button_disposeNativeObjects = function() {

	//log("ComboBox._comboBox_disposeNativeObjects");

	// This isn't a native object, but we still dispose it here, baseclass takes care of its own
	if(this._lblText!=null) { this._lblText.dispose(); this._lblText = null; }
}

/**
 * Loads control elements based on current theme.
 * @private
 */
Yahoo.Controls.Button.prototype._button_loadTheme = function() {

	// Initialize variables/controls
	this._lblText = new Yahoo.Controls.Label(this._theme);
	this._lblText.fromTextObject(this._theme.getItem("buttonLabel"));
	this._lblText.textAlign = Yahoo.Drawing.ContentAlignment.MiddleCenter;
	this._lblText.addEventHandler(this._button_lblText_onEnter, "Enter");
	this._lblText.addEventHandler(this._button_lblText_onLeave, "Leave");
	this._lblText.addEventHandler(this._button_lblText_onMouseDown, "MouseDown");
	this._lblText.addEventHandler(this._button_lblText_onMouseUp, "MouseUp");
	this.addControl(this._lblText);

	// Get options for button from theme
	this._textMargins = this._theme.getParameter("buttonTextMargins");
	this._paramDisabled = this._theme.getParameter("buttonDisabled");
	this._paramDown = this._theme.getParameter("buttonDown");
	this._paramNormal = this._theme.getParameter("buttonNormal");
	this._paramOver = this._theme.getParameter("buttonOver");

	this._button_setTextLocation();
	this._button_setButtonStyle(this._paramNormal);
}

/**
 * Sets the location and size for the text label.
 * @private
 */
Yahoo.Controls.Button.prototype._button_setTextLocation = function() {

	if(this._lblText!=null) {
		this._lblText.left = parseInt(this._textMargins.left);
		this._lblText.top = parseInt(this._textMargins.top);
		this._lblText.width = this.width - (parseInt(this._textMargins.left) + parseInt(this._textMargins.right));
		this._lblText.height = this.height - (parseInt(this._textMargins.top) + parseInt(this._textMargins.bottom));
	}
}

/**
 * Sets the button state.
 * @private
 */
Yahoo.Controls.Button.prototype._button_setButtonState = function() {

	if(this.enabled==false) {
		this._button_setButtonStyle(this._paramDisabled);
	}
	else {
		if(this._isMouseOver==true && this._isMouseDown==true) {
			this._button_setButtonStyle(this._paramDown);
		}
		else if(this._isMouseOver==true && this._isMouseDown==false) {
			this._button_setButtonStyle(this._paramOver);
		}
		else {
			this._button_setButtonStyle(this._paramNormal);
		}
	}  // if enabled
}

/**
 * Sets button elements to match current state.
 * @private
 * @param {Object} params Object that contains the control style parameters.
 */
Yahoo.Controls.Button.prototype._button_setButtonStyle = function(params) {

	if(this._disposing==false) {
		this._imgLeft.colorize = params.colorize;
		this._imgLeft.hslAdjustment = params.hslAdjustment;
		this._imgLeft.hslTinting = params.hslTinting;
		this._imgLeft.opacity = params.opacity;
	
		this._imgMiddle.colorize = params.colorize;
		this._imgMiddle.hslAdjustment = params.hslAdjustment;
		this._imgMiddle.hslTinting = params.hslTinting;
		this._imgMiddle.opacity = params.opacity;
	
		this._imgRight.colorize = params.colorize;
		this._imgRight.hslAdjustment = params.hslAdjustment;
		this._imgRight.hslTinting = params.hslTinting;
		this._imgRight.opacity = params.opacity;
	
		this._lblText.opacity = params.opacity;
	}  //if disposing
}

/*---------------------------------------------------------------------*/
// Public code
/*---------------------------------------------------------------------*/
/**
 * True constructor. Must be called if this class is overridden.
 * @param {Yahoo.Controls.Theme} theme The theme this control should use or null to create an instance of the default theme.
 */
Yahoo.Controls.Button.prototype.initialize = function(theme) {

	//log("Button.initialize()");
	
	// Call baseclass constructor
	this.baseclassButton.initialize.call(this, theme, "button");

	// Includes
	lib.include("Yahoo.Controls.Label");

    // Hook into mouse events for whole control
   	this.addEventHandler(this._button_onMouseDown, "MouseDown");
	this.addEventHandler(this._button_onMouseUp, "MouseUp");

    this._button_loadTheme();
}

/**
 * Disposes control's resources.
 */
Yahoo.Controls.Button.prototype.dispose = function() {
	
	// Dispose native items
	this._button_disposeNativeObjects();

	// Call baseclass
	this.baseclassButton.dispose.call(this);
}

/*---------------------------------------------------------------------*/
// Public properties
/*---------------------------------------------------------------------*/
/**
 * Gets or sets the alignment of the text on the button.
 * @type Yahoo.Drawing.ContentAlignment
 */
Yahoo.Controls.Button.prototype.textAlign getter = function() {

	return this._lblText.textAlign;
}

Yahoo.Controls.Button.prototype.textAlign setter = function(value) {

	if(value!=null) {
		this._lblText.textAlign = value;
	}
	else {
		throw new Yahoo.ArgumentNullException("value");
	}
}

