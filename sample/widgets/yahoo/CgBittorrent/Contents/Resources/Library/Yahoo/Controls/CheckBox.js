/*---------------------------------------------------------------------*/
/// <copyright from='2005' to='2007' company='Yahoo! Inc.'>
/// (C) Copyright 2005-2007 Yahoo! Inc. All Rights Reserved.
/// </copyright>

/**
 * CheckBox control.
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
Yahoo.Controls.CheckBox = function(theme) {

	//log("CheckBox.ctor()");
	if(arguments.length>0) {
		this.initialize(theme);
	}
}

/**
 * Define inheritance chain.
 */
Yahoo.Controls.CheckBox.prototype = new Yahoo.Controls.Control();
Yahoo.Controls.CheckBox.prototype.constructor = Yahoo.Controls.CheckBox;
Yahoo.Controls.CheckBox.prototype.baseclassCheckBox = Yahoo.Controls.Control.prototype;

/*-----------------------------------------------------------*/
// Control code
/*-----------------------------------------------------------*/
/**
 * Raises the onEnabledChanged event.
 * @param {Object} sender The source of the event.
 * @param {Yahoo.EventArgs} e The EventArgs object that contains event details.
 */
Yahoo.Controls.CheckBox.prototype._onEnabledChanged = function(sender, e) {

	//log("CheckBox._onEnabledChanged");

	// Call baseclass
	this.baseclassCheckBox._onEnabledChanged.call(this, sender, e);

	this._chkCheck.enabled = this.enabled;
	this._lblText.enabled = this.enabled;
}

/**
 * Raises the onFontChanged event.
 * @param {Object} sender The source of the event.
 * @param {Yahoo.EventArgs} e The EventArgs object that contains event details.
 */
Yahoo.Controls.CheckBox.prototype._onFontChanged = function(sender, e) {

	//log("CheckBox._onFontChanged");

	// Call baseclass
	this.baseclassCheckBox._onFontChanged.call(this, sender, e);

	this._lblText.font = this.font;

}
/**
 * Raises the onForeColorChanged event.
 * @param {Object} sender The source of the event.
 * @param {Yahoo.EventArgs} e The EventArgs object that contains event details.
 */
Yahoo.Controls.CheckBox.prototype._onForeColorChanged = function(sender, e) {

	//log("CheckBox._onForeColorChanged");

	// Call baseclass
	this.baseclassCheckBox._onForeColorChanged.call(this, sender, e);
	
	this._lblText.foreColor = this.foreColor;
}

/**
 * Raises the onResize event.
 * @param {Object} sender The source of the event.
 * @param {Yahoo.EventArgs} e The EventArgs object that contains event details.
 */
Yahoo.Controls.CheckBox.prototype._onResize = function(sender, e) {

	//log("CheckBox._onResize");

	// Call baseclass
	this.baseclassCheckBox._onResize.call(this, sender, e);

	// Resize check and text
	this._checkBox_setCheckBoxSize();
	this._checkBox_setTextLocation();
}

/**
 * Raises the onTextChanged event.
 * @param {Object} sender The source of the event.
 * @param {Yahoo.EventArgs} e The EventArgs object that contains event details.
 */
Yahoo.Controls.CheckBox.prototype._onTextChanged = function(sender, e) {

	//log("CheckBox._onTextChanged");

	// Call baseclass
	this.baseclassCheckBox._onTextChanged.call(this, sender, e);
	
	// Set text
	this._lblText.text = this.text;
}

/**
 * Raises the onToolTipChanged event.
 * @param {Object} sender The source of the event.
 * @param {Yahoo.EventArgs} e The EventArgs object that contains event details.
 */
Yahoo.Controls.CheckBox.prototype._onToolTipChanged = function(sender, e) {

	//log("CheckBox._onToolTipChanged");

	// Call baseclass
	this.baseclassCheckBox._onToolTipChanged.call(this, sender, e);
	
	// Set tooltip
	this._lblText.toolTip = this.toolTip;
}

/**
 * Handles onEnter event for whole control.
 * @param {Object} sender The source of the event.
 * @param {Yahoo.EventArgs} e The EventArgs object that contains event details.
 */
Yahoo.Controls.CheckBox.prototype._onEnter = function(sender, e) {

	//log("CheckBox._onEnter");

	// Cancel enter event if we entered from / left one of our subcontrols
	if((this._isMouseOver == false) || this.displayRectangle.contains(system.event.x + this.left, system.event.y + this.top) == false) {
	
		// Call baseclass
		this.baseclassCheckBox._onEnter.call(this, sender, e);

		// Send enter event the checkboxbase
		this._chkCheck._isMouseOver = true;
		this._chkCheck._checkBoxBase_setCheckBoxBaseState.call(this._chkCheck);
	}
}

/**
 * Handles onLeave event for whole control.
 * @param {Object} sender The source of the event.
 * @param {Yahoo.EventArgs} e The EventArgs object that contains event details.
 */
Yahoo.Controls.CheckBox.prototype._onLeave = function(sender, e) {

	//log("CheckBox._onLeave");

	// Cancel leave event if we entered one of our subcontrols
	if(this.displayRectangle.contains(system.event.x + this.left, system.event.y + this.top) == false) {

		// Call baseclass
		this.baseclassCheckBox._onLeave.call(this, sender, e);

		// Send leave event the checkboxbase
		this._chkCheck._isMouseOver = false;
		this._chkCheck._checkBoxBase_setCheckBoxBaseState.call(this._chkCheck);
	}
}

/**
 * Handles onMouseDown event for whole control.
 * @param {Object} sender The source of the event.
 * @param {Yahoo.EventArgs} e The EventArgs object that contains event details.
 */
Yahoo.Controls.CheckBox.prototype._checkBox_onMouseDown = function(sender, e) {

	//log("CheckBox._checkBox_onMouseDown");

	// Send event the checkboxbase
	sender._chkCheck._isMouseDown = true;
	sender._chkCheck._checkBoxBase_setCheckBoxBaseState.call(sender._chkCheck);
}

/**
 * Handles onMouseUp event for whole control.
 * @param {Object} sender The source of the event.
 * @param {Yahoo.EventArgs} e The EventArgs object that contains event details.
 */
Yahoo.Controls.CheckBox.prototype._checkBox_onMouseUp = function(sender, e) {

	//log("CheckBox._checkBox_onMouseUp");

	// Send event via the checkboxbase
	if(e.fromCheckBoxBase != true) {
		sender._chkCheck._isMouseDown = false;
		sender._chkCheck._checkBoxBase_onMouseUp.call(sender._chkCheck, sender._chkCheck, new Yahoo.EventArgs());
	}
}

/**
 * Raises the onThemeChanged event.
 * @param {Object} sender The source of the event.
 * @param {Yahoo.EventArgs} e The EventArgs object that contains event details.
 */
Yahoo.Controls.CheckBox.prototype._onThemeChanged = function(sender, e) {

	//log("CheckBox._onThemeChanged");

	// Call base class
	this.baseclassCheckBox._onThemeChanged.call(this, sender, e);

	this._checkBox_loadTheme();
}

/**
 * Handles onMouseEnter event for checkbox.
 * @param {Object} sender The source of the event.
 * @param {Yahoo.EventArgs} e The EventArgs object that contains event details.
 */
Yahoo.Controls.CheckBox.prototype._checkBox_chkCheck_onEnter = function(sender, e) {

	//log("CheckBox._checkBox_chkCheck_onEnter");

	sender.parent._onEnter.call(sender.parent, sender.parent, new Yahoo.EventArgs());
}

/**
 * Handles onMouseExit event for checkbox.
 * @param {Object} sender The source of the event.
 * @param {Yahoo.EventArgs} e The EventArgs object that contains event details.
 */
Yahoo.Controls.CheckBox.prototype._checkBox_chkCheck_onLeave = function(sender, e) {

	//log("CheckBox._checkBox_chkCheck_onLeave");
	
	// Don't forward this if we are still within the parent control
	if(sender.parent.displayRectangle.contains(system.event.x + sender.left + sender.parent.left, system.event.y + sender.top + sender.parent.top) == false) {
		sender.parent._onLeave.call(sender.parent, sender.parent, new Yahoo.EventArgs());
	}
}

/**
 * Handles onMouseDown event for checkbox.
 * @param {Object} sender The source of the event.
 * @param {Yahoo.EventArgs} e The EventArgs object that contains event details.
 */
Yahoo.Controls.CheckBox.prototype._checkBox_chkCheck_onMouseDown = function(sender, e) {

	//log("CheckBox._checkBox_chkCheck_onMouseDown");
	sender.parent._onMouseDown.call(sender.parent, sender.parent, new Yahoo.EventArgs());
}

/**
 * Handles onMouseUp event for checkbox.
 * @param {Object} sender The source of the event.
 * @param {Yahoo.EventArgs} e The EventArgs object that contains event details.
 */
Yahoo.Controls.CheckBox.prototype._checkBox_chkCheck_onMouseUp = function(sender, e) {

	//log("CheckBox._checkBox_chkCheck_onMouseUp");
	
	e = new Yahoo.EventArgs();
	e.fromCheckBoxBase = true;

	// We keep the sender as the checkbox so we don't end up in an infinite loop later
	sender.parent._checkBox_onMouseUp.call(sender.parent, sender.parent, e);
}

/**
 * Handles onMouseEnter event for label.
 * @param {Object} sender The source of the event.
 * @param {Yahoo.EventArgs} e The EventArgs object that contains event details.
 */
Yahoo.Controls.CheckBox.prototype._checkBox_lblText_onEnter = function(sender, e) {

	//log("CheckBox._checkBox_lblText_onEnter");

	sender.parent._onEnter.call(sender.parent, sender.parent, new Yahoo.EventArgs());
}

/**
 * Handles onMouseExit event for label.
 * @param {Object} sender The source of the event.
 * @param {Yahoo.EventArgs} e The EventArgs object that contains event details.
 */
Yahoo.Controls.CheckBox.prototype._checkBox_lblText_onLeave = function(sender, e) {

	//log("CheckBox._checkBox_lblText_onLeave");
	
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
Yahoo.Controls.CheckBox.prototype._checkBox_lblText_onMouseDown = function(sender, e) {

	//log("CheckBox._checkBox_lblText_onMouseDown");
	sender.parent._checkBox_onMouseDown.call(sender.parent, sender.parent, new Yahoo.EventArgs());
}

/**
 * Handles onMouseUp event for label.
 * @param {Object} sender The source of the event.
 * @param {Yahoo.EventArgs} e The EventArgs object that contains event details.
 */
Yahoo.Controls.CheckBox.prototype._checkBox_lblText_onMouseUp = function(sender, e) {

	//log("CheckBox._checkBox_lblText_onMouseUp");
	sender.parent._checkBox_onMouseUp.call(sender.parent, sender.parent, new Yahoo.EventArgs());
}

/*---------------------------------------------------------------------*/
// Private code
/*---------------------------------------------------------------------*/
/**
 * Disposes native Widget Engine objects.
 * @private
 */
Yahoo.Controls.CheckBox.prototype._checkBox_disposeNativeObjects = function() {

	//log("CheckBox._checkBox_disposeNativeObjects");

	// These aren't native objects, but we still dispose them here
	if(this._chkCheck!=null) { this._chkCheck.dispose(); this._chkCheck = null; }
	if(this._lblText!=null) { this._lblText.dispose(); this._lblText = null; }
}

/**
 * Loads control elements based on current theme.
 * @private
 */
Yahoo.Controls.CheckBox.prototype._checkBox_loadTheme = function() {

    var checked = false;

    if(this._chkCheck != null)
    {
        checked = this._chkCheck.checked;
    }

	// Remove any current objects
	this._checkBox_disposeNativeObjects();

	this._chkCheck = new Yahoo.Controls.CheckBoxBase(this._theme, "checkBox");
	this._chkCheck.left = 0;
	this._chkCheck.top = 0;
	this._chkCheck.addEventHandler(this._checkBox_chkCheck_onEnter, "Enter");
	this._chkCheck.addEventHandler(this._checkBox_chkCheck_onLeave, "Leave");
	this._chkCheck.addEventHandler(this._checkBox_chkCheck_onMouseDown, "MouseDown");
	this._chkCheck.addEventHandler(this._checkBox_chkCheck_onMouseUp, "MouseUp");
	this.addControl(this._chkCheck);

	this._lblText = new Yahoo.Controls.Label(this._theme);
	this._lblText.fromTextObject(this._theme.getItem("checkBoxLabel"));
	this._lblText.textAlign = Yahoo.Drawing.ContentAlignment.MiddleLeft;
	this._lblText.addEventHandler(this._checkBox_lblText_onEnter, "Enter");
	this._lblText.addEventHandler(this._checkBox_lblText_onLeave, "Leave");
	this._lblText.addEventHandler(this._checkBox_lblText_onMouseDown, "MouseDown");
	this._lblText.addEventHandler(this._checkBox_lblText_onMouseUp, "MouseUp");
	this.addControl(this._lblText);

	// Get options for checkBox from theme
	this._textMargins = this._theme.getParameter("checkBoxTextMargins");
	this._paramDisabled = this._theme.getParameter("checkBoxDisabled");
	this._paramDown = this._theme.getParameter("checkBoxDown");
	this._paramNormal = this._theme.getParameter("checkBoxNormal");
	this._paramOver = this._theme.getParameter("checkBoxOver");

	// Set text
	this._lblText.text = this.text;
	this._chkCheck.checked = checked;

    if(this._isInitializing == true) {
        // Get initial height from checkbox theme
        this._frame.height = this._chkCheck.height;
    }

	this._checkBox_setCheckBoxSize();
	this._checkBox_setTextLocation();
}

/**
 * Sets the size for the checkbox.
 * @private
 */
Yahoo.Controls.CheckBox.prototype._checkBox_setCheckBoxSize = function() {

	//log("CheckBox._checkBox_setCheckBoxSize");

	if(this._chkCheck!=null) {
		this._chkCheck.size = new Yahoo.Drawing.Size(this.height, this.height);
	}
}

/**
 * Sets the location and size for the text label.
 * @private
 */
Yahoo.Controls.CheckBox.prototype._checkBox_setTextLocation = function() {

	//log("CheckBox._checkBox_setTextLocation");

	if(this._lblText!=null) {
		this._lblText.left = this._chkCheck.width + parseInt(this._textMargins.left);
		this._lblText.top = parseInt(this._textMargins.top);
		this._lblText.size = new Yahoo.Drawing.Size((this.width - (parseInt(this._textMargins.left) + parseInt(this._textMargins.right)) - this._chkCheck.width - 1),
								(this.height - (parseInt(this._textMargins.top) + parseInt(this._textMargins.bottom))));
	}
}

/*---------------------------------------------------------------------*/
// Public code
/*---------------------------------------------------------------------*/
/**
 * True constructor. Must be called if this class is overridden.
 * @param {Yahoo.Controls.Theme} theme The theme this control should use or null to create an instance of the default theme.
 */
Yahoo.Controls.CheckBox.prototype.initialize = function(theme) {

	//log("CheckBox.initialize()");
	
	// Call baseclass constructor
	this.baseclassCheckBox.initialize.call(this, theme, "checkBox");

	this._isInitializing = true;

	// Includes
	lib.include("Yahoo.Controls.CheckBoxBase");
	lib.include("Yahoo.Controls.Label");

    // Hook into mouse events for whole control
   	this.addEventHandler(this._checkBox_onMouseDown, "MouseDown");
	this.addEventHandler(this._checkBox_onMouseUp, "MouseUp");

	// Load theme and do layout
	this._checkBox_loadTheme();

	this._isInitializing = false;
}

/**
 * Disposes control's resources.
 */
Yahoo.Controls.CheckBox.prototype.dispose = function() {
	
	this._checkBox_disposeNativeObjects();
	
	// Call baseclass
	this.baseclassCheckBox.dispose.call(this);

}

// TODO: We need the events from CheckBoxBase !!!

/*---------------------------------------------------------------------*/
// Public properties
/*---------------------------------------------------------------------*/
/**
 * Gets or sets a value indicating whether the checked state changes automatically when the user clicks on the control.
 * @type Boolean
 */
Yahoo.Controls.CheckBox.prototype.autoCheck getter = function() {

	return this._chkCheck.autoCheck;
}

Yahoo.Controls.CheckBox.prototype.autoCheck setter = function(value) {

	this._chkCheck.autoCheck = value;
}

/**
 * Gets or sets a value indicating whether the control is checked.
 * @type Boolean
 */
Yahoo.Controls.CheckBox.prototype.checked getter = function() {

	return this._chkCheck.checked;
}

Yahoo.Controls.CheckBox.prototype.checked setter = function(value) {

	this._chkCheck.checked = value;
}

/**
 * Gets or sets the state of the checkbox when in three state mode.
 * @type Yahoo.Controls.CheckState
 */
Yahoo.Controls.CheckBox.prototype.checkState getter = function() {

	return this._chkCheck.checkState;
}

Yahoo.Controls.CheckBox.prototype.checkState setter = function(value) {

	this._chkCheck.checkState = value;
}

/**
 * Gets or sets a value indicating whether the checkbox supports three states instead of two.
 * @type Boolean
 */
Yahoo.Controls.CheckBox.prototype.threeState getter = function() {

	return this._chkCheck.threeState;
}

Yahoo.Controls.CheckBox.prototype.threeState setter = function(value) {

	this._chkCheck.threeState = value;
}

/**
 * Gets or sets the alignment of the text on the checkBox.
 * @type Yahoo.Drawing.ContentAlignment
 */
Yahoo.Controls.CheckBox.prototype.textAlign getter = function() {

	return this._lblText.textAlign;
}

Yahoo.Controls.CheckBox.prototype.textAlign setter = function(value) {

	if(value!=null) {
		this._lblText.textAlign = value;
	}
	else {
		throw new Yahoo.ArgumentNullException("value");
	}
}

