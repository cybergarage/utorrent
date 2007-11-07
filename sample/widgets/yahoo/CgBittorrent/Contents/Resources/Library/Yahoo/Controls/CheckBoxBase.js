/*---------------------------------------------------------------------*/
/// <copyright from='2005' to='2007' company='Yahoo! Inc.'>
/// (C) Copyright 2005-2007 Yahoo! Inc. All Rights Reserved.
/// </copyright>

/**
 * CheckBoxBase control.
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
Yahoo.Controls.CheckBoxBase = function(theme, themePrefix) {

	//log("CheckBoxBase.ctor()");
	if(arguments.length>0) {
		this.initialize(theme, themePrefix);
	}
}

/**
 * Define inheritance chain.
 */
Yahoo.Controls.CheckBoxBase.prototype = new Yahoo.Controls.Control();
Yahoo.Controls.CheckBoxBase.prototype.constructor = Yahoo.Controls.CheckBoxBase;
Yahoo.Controls.CheckBoxBase.prototype.baseclassCheckBoxBase = Yahoo.Controls.Control.prototype;

/*---------------------------------------------------------------------*/
// Public enums
/*---------------------------------------------------------------------*/
/**
 * Available border styles for forms.
 */
Yahoo.Controls.CheckState = {
    Unchecked: 0,
    Checked: 1,
    Indeterminate: 2
}

/*-----------------------------------------------------------*/
// Control code
/*-----------------------------------------------------------*/
/**
 * Raises the onBackColorChanged event.
 * @param {Object} sender The source of the event.
 * @param {Yahoo.EventArgs} e The EventArgs object that contains event details.
 */
Yahoo.Controls.CheckBoxBase.prototype._onBackColorChanged = function(sender, e) {

	//log("CheckBoxBase._onBackColorChanged");

	// Call base class
	this.baseclassCheckBoxBase._onBackColorChanged.call(this, sender, e);
	
	this._imgBackground.colorize = this._backColor;
}

/**
 * Control's internal resize handler.
 * @param {Object} sender The source of the event.
 * @param {Yahoo.EventArgs} e The EventArgs object that contains event details.
 */
Yahoo.Controls.CheckBoxBase.prototype._onResize = function(sender, e) {

	//log("CheckBoxBase._onResize");

	// Call base class
	this.baseclassCheckBoxBase._onResize.call(this, sender, e);

	// Resize background
	this._checkBoxBase_paintBackground();

	// Resize text
	this._checkBoxBase_setCheckLocation();
}

/**
 * Raises the onToolTipChanged event.
 * @param {Object} sender The source of the event.
 * @param {Yahoo.EventArgs} e The EventArgs object that contains event details.
 */
Yahoo.Controls.CheckBoxBase.prototype._onToolTipChanged = function(sender, e) {

	//log("baseclassCheckBoxBase._onToolTipChanged");

	// Call base class
	this.baseclassCheckBoxBase._onToolTipChanged.call(this, sender, e);
	
	// Set tooltip
	this._imgBackground.tooltip = this.tooltip;
	this._imgCheck.tooltip = this.tooltip;
}

/**
 * Raises the onCheckedChanged event.
 * @param {Object} sender The source of the event.
 * @param {Yahoo.EventArgs} e The EventArgs object that contains event details.
 */
Yahoo.Controls.CheckBoxBase.prototype._onCheckedChanged = function(sender, e) {

	//log("CheckBoxBase._onCheckedChanged");

	this._checkBoxBase_setCheckBoxBaseState();

	Yahoo.raiseEvent(sender, sender._onCheckedChangedEventHandlers, e);
}

/**
 * Raises the onCheckStateChanged event.
 * @param {Object} sender The source of the event.
 * @param {Yahoo.EventArgs} e The EventArgs object that contains event details.
 */
Yahoo.Controls.CheckBoxBase.prototype._onCheckStateChanged = function(sender, e) {

	//log("CheckBoxBase._onCheckStateChanged");

	this._checkBoxBase_setCheckBoxBaseState();

	Yahoo.raiseEvent(sender, sender._onCheckStateChangedEventHandlers, e);
}

/**
 * Raises the onEnabledChanged event.
 * @param {Object} sender The source of the event.
 * @param {Yahoo.EventArgs} e The EventArgs object that contains event details.
 */
Yahoo.Controls.CheckBoxBase.prototype._onEnabledChanged = function(sender, e) {

	//log("CheckBoxBase._onEnabledChanged");

	// Call baseclass
	this.baseclassCheckBoxBase._onEnabledChanged.call(this, sender, e);

	this._checkBoxBase_setCheckBoxBaseState();
}

/**
 * Handles onEnter event for whole control.
 * @param {Object} sender The source of the event.
 * @param {Yahoo.EventArgs} e The EventArgs object that contains event details.
 */
Yahoo.Controls.CheckBoxBase.prototype._onEnter = function(sender, e) {

	//log("CheckBoxBase._onEnter");

	// Cancel enter event if we entered from / left one of our subcontrols
	if((this._isMouseOver == false) || this.displayRectangle.contains(system.event.x + this.left, system.event.y + this.top) == false) {
	
		// Call baseclass
		this.baseclassCheckBoxBase._onEnter.call(this, sender, e);

		this._checkBoxBase_setCheckBoxBaseState();
	}
}

/**
 * Handles onLeave event for whole control.
 * @param {Object} sender The source of the event.
 * @param {Yahoo.EventArgs} e The EventArgs object that contains event details.
 */
Yahoo.Controls.CheckBoxBase.prototype._onLeave = function(sender, e) {

	//log("CheckBoxBase._onLeave");

	// Cancel leave event if we entered one of our subcontrols
	if(this.displayRectangle.contains(system.event.x + this.left, system.event.y + this.top) == false) {

		// Call baseclass
		this.baseclassCheckBoxBase._onLeave.call(this, sender, e);
		this._checkBoxBase_setCheckBoxBaseState();
	}
}

/**
 * Handles onMouseDown event for whole control.
 * @param {Object} sender The source of the event.
 * @param {Yahoo.EventArgs} e The EventArgs object that contains event details.
 */
Yahoo.Controls.CheckBoxBase.prototype._checkBoxBase_onMouseDown = function(sender, e) {

	//log("CheckBoxBase._checkBoxBase_onMouseDown");

	sender._checkBoxBase_setCheckBoxBaseState();
}

/**
 * Handles onMouseUp event for whole control.
 * @param {Object} sender The source of the event.
 * @param {Yahoo.EventArgs} e The EventArgs object that contains event details.
 */
Yahoo.Controls.CheckBoxBase.prototype._checkBoxBase_onMouseUp = function(sender, e) {

	//log("CheckBoxBase._checkBoxBase_onMouseUp");

	if(sender.enabled==true) {

		// Check if we should switch states
		if(sender.autoCheck==true) {
			if(sender._isMouseOver) {
				if(sender._threeState==true) {
					switch(sender._checkState) {
						case Yahoo.Controls.CheckState.Checked:
							sender.checkState = Yahoo.Controls.CheckState.Indeterminate;
							break;
						case Yahoo.Controls.CheckState.Unchecked:
							sender.checkState = Yahoo.Controls.CheckState.Checked;
							break;
						case Yahoo.Controls.CheckState.Indeterminate:
							sender.checkState = Yahoo.Controls.CheckState.Unchecked;
							break;
					}
				}
				else {
					sender.checked = !sender.checked;
				}  // threeState
			} // isMouseOver
		}  // autoCheck
	}  // enabled==true

	sender._checkBoxBase_setCheckBoxBaseState();
}

/**
 * Handles onMouseEnter event for label.
 * @param {Object} sender The source of the event.
 * @param {Yahoo.EventArgs} e The EventArgs object that contains event details.
 */
Yahoo.Controls.CheckBoxBase.prototype._checkBoxBase_imgCheck_onEnter = function(sender, e) {

	//log("CheckBoxBase._checkBoxBase_imgCheck_onEnter");

	sender.parent._onEnter.call(sender.parent, sender.parent, new Yahoo.EventArgs());
}

/**
 * Handles onMouseExit event for label.
 * @param {Object} sender The source of the event.
 * @param {Yahoo.EventArgs} e The EventArgs object that contains event details.
 */
Yahoo.Controls.CheckBoxBase.prototype._checkBoxBase_imgCheck_onLeave = function(sender, e) {

	//log("CheckBoxBase._checkBoxBase_imgCheck_onLeave");
	
	// Don't forward this if we are still within the parent control
	if(sender.parent.displayRectangle.contains(system.event.x + sender.left + sender.parent.left, system.event.y + sender.top + sender.parent.top) == false) {
		sender.parent._onLeave.call(sender.parent, sender.parent, new Yahoo.EventArgs());
	}
}

/**
 * Handles onMouseDown event for check image.
 * @param {Object} sender The source of the event.
 * @param {Yahoo.EventArgs} e The EventArgs object that contains event details.
 */
Yahoo.Controls.CheckBoxBase.prototype._checkBoxBase_imgCheck_onMouseDown = function(sender, e) {

	//log("CheckBoxBase._checkBoxBase_imgCheck_onMouseDown");
	sender.parent._onMouseDown.call(sender.parent, sender.parent, new Yahoo.EventArgs());
}

/**
 * Handles onMouseUp event for check image.
 * @param {Object} sender The source of the event.
 * @param {Yahoo.EventArgs} e The EventArgs object that contains event details.
 */
Yahoo.Controls.CheckBoxBase.prototype._checkBoxBase_imgCheck_onMouseUp = function(sender, e) {

	//log("CheckBoxBase._checkBoxBase_imgCheck_onMouseUp");
	sender.parent._onMouseUp.call(sender.parent, sender.parent, new Yahoo.EventArgs());
}

/**
 * Raises the onThemeChanged event.
 * @param {Object} sender The source of the event.
 * @param {Yahoo.EventArgs} e The EventArgs object that contains event details.
 */
Yahoo.Controls.CheckBoxBase.prototype._onThemeChanged = function(sender, e) {

	//log("CheckBoxBase._onThemeChanged");

	// Call base class
	this.baseclassCheckBoxBase._onThemeChanged.call(this, sender, e);

	this._checkBoxBase_loadTheme();
}

/*---------------------------------------------------------------------*/
// Private code
/*---------------------------------------------------------------------*/
/**
 * Disposes native Widget Engine objects.
 * @private
 */
Yahoo.Controls.CheckBoxBase.prototype._checkBoxBase_disposeNativeObjects = function() {

	//log("CheckBoxBase._checkBoxBase_disposeNativeObjects");

	if(this._imgBackground!=null) { this._imgBackground.removeFromSuperview(); this._imgBackground = null; }
	if(this._imgCheck!=null) { this._imgCheck.removeFromSuperview(); this._imgCheck = null; }
}

/**
 * Loads control elements based on current theme.
 * @private
 */
Yahoo.Controls.CheckBoxBase.prototype._checkBoxBase_loadTheme = function() {

	//log("CheckBoxBase._checkBoxBase_loadTheme");

	// Remove any current objects
	this._checkBoxBase_disposeNativeObjects();

	// Load objects using current theme
	this._imgBackground = this._theme.getItem(this._themePrefix + "Background");
	this._imgBackground.tag = this;
	this._frame.addSubview(this._imgBackground);

	this._imgCheck = this._theme.getItem(this._themePrefix + "Check");
	this._imgCheck.tag = this;
	this._frame.addSubview(this._imgCheck);

	this._checkBoxBase_setCheckLocation();
	this._checkBoxBase_setCheckBoxBaseState();
}

/**
 * Resizes control border elements.
 * @private
 */
Yahoo.Controls.CheckBoxBase.prototype._checkBoxBase_paintBackground = function() {

	//log("CheckBoxBase._checkBoxBase_paintBackground");

	this._imgBackground.width = this.width;
	this._imgBackground.height = this.height;
}

/**
 * Sets the check image location and size
 * @private
 */
Yahoo.Controls.CheckBoxBase.prototype._checkBoxBase_setCheckLocation = function() {

	if(this._imgCheck!=null) {
		this._imgCheck.hOffset = parseInt(this._checkMargins.left);
		this._imgCheck.vOffset = parseInt(this._checkMargins.top);
		this._imgCheck.width = this.width - (parseInt(this._checkMargins.left) + parseInt(this._checkMargins.right));
		this._imgCheck.height = this.height - (parseInt(this._checkMargins.top) + parseInt(this._checkMargins.bottom));
	}
}

/**
 * Sets the checkBoxBase state.
 * @private
 */
Yahoo.Controls.CheckBoxBase.prototype._checkBoxBase_setCheckBoxBaseState = function() {

	if(this.enabled==false) {
		this._checkBoxBase_setCheckBoxBaseStyle(this._paramDisabled);
	}
	else {
		if(this._isMouseOver==true && this._isMouseDown==true) {
			this._checkBoxBase_setCheckBoxBaseStyle(this._paramDown);
		}
		else if(this._isMouseOver==true && this._isMouseDown==false) {
			this._checkBoxBase_setCheckBoxBaseStyle(this._paramOver);
		}
		else {
			this._checkBoxBase_setCheckBoxBaseStyle(this._paramNormal);
		}
	}  // if enabled
	
	// Set check image
	switch(this._checkState) {
		case Yahoo.Controls.CheckState.Checked:
			this._imgCheck.opacity = 255;
			break;
		case Yahoo.Controls.CheckState.Unchecked:
			this._imgCheck.opacity = 0;
			break;
		case Yahoo.Controls.CheckState.Indeterminate:
			this._imgCheck.opacity = 128;
			break;
	}	
}

/**
 * Sets checkBoxBase elements to match current state.
 * @private
 * @param {Object} params Object that contains the control style parameters.
 */
Yahoo.Controls.CheckBoxBase.prototype._checkBoxBase_setCheckBoxBaseStyle = function(params) {

	this._imgBackground.colorize = params.colorize;
	this._imgBackground.hslAdjustment = params.hslAdjustment;
	this._imgBackground.hslTinting = params.hslTinting;
	this._imgBackground.opacity = params.opacity;

	//this._imgCheck.colorize = params.colorize;
	this._imgCheck.hslAdjustment = params.hslAdjustment;
	this._imgCheck.hslTinting = params.hslTinting;
	this._imgCheck.opacity = params.opacity;
}

/*---------------------------------------------------------------------*/
// Public code
/*---------------------------------------------------------------------*/
/**
 * True constructor. Must be called if this class is overridden.
 * @param {Yahoo.Controls.Theme} theme The theme this control should use or null to create an instance of the default theme.
 * @param {String} themePrefix The prefix used to retrieve styles from the theme for this control.
 */
Yahoo.Controls.CheckBoxBase.prototype.initialize = function(theme, themePrefix) {

	//log("CheckBoxBase.initialize()");
	
	this._themePrefix = themePrefix;
	
	// Call baseclass constructor
	this.baseclassCheckBoxBase.initialize.call(this, theme, themePrefix);

	this._isInitializing = true;

	// Initialize properties
	this._autoCheck = true;
	this._checked = false;
	this._checkState = Yahoo.Controls.CheckState.Unchecked;
	this._threeState = false;

	this._onCheckedChangedEventHandlers = new Array();
	this._onCheckStateChangedEventHandlers = new Array();

	// Get options for checkBoxBase from theme
	this._checkMargins = this._theme.getParameter(themePrefix + "CheckMargins");
	this._paramDisabled = this._theme.getParameter(themePrefix + "Disabled");
	this._paramDown = this._theme.getParameter(themePrefix + "Down");
	this._paramNormal = this._theme.getParameter(themePrefix + "Normal");
	this._paramOver = this._theme.getParameter(themePrefix + "Over");

    // Hook into mouse events for whole control
   	this.addEventHandler(this._checkBoxBase_onMouseDown, "MouseDown");
	this.addEventHandler(this._checkBoxBase_onMouseUp, "MouseUp");

	// Get objects
	this._checkBoxBase_loadTheme();

    // Get initial size from theme images
    this.width = this._imgBackground.width;
    this.height = this._imgBackground.height;

	this._isInitializing = false;
}

/**
 * Adds an event handler. Supported events are: CheckedChanged, CheckStateChanged
 * @param {Function} eventHandler The function that is to be called when the event is raised.
 * @param {String} eventName The name of the event that is being listened to.
 */
Yahoo.Controls.CheckBoxBase.prototype.addEventHandler = function(eventHandler, eventName) {

	// Call baseclass
	this.baseclassCheckBoxBase.addEventHandler.call(this, eventHandler, eventName)

	switch(eventName) {
		case "CheckedChanged":
			this._onCheckedChangedEventHandlers.push(eventHandler);
			break;
		case "CheckStateChanged":
			this._onCheckStateChangedEventHandlers.push(eventHandler);
			break;
	}
}

/**
 * Disposes control's resources.
 */
Yahoo.Controls.CheckBoxBase.prototype.dispose = function() {
	
	// Call baseclass
	this.baseclassCheckBoxBase.dispose.call(this);
}

/*---------------------------------------------------------------------*/
// Public properties
/*---------------------------------------------------------------------*/
/**
 * Gets or sets the a value indicating whether the checked state changes automatically when the user click on the control.
 * @type Boolean
 */
Yahoo.Controls.CheckBoxBase.prototype.autoCheck getter = function() {

	return this._autoCheck;
}

Yahoo.Controls.CheckBoxBase.prototype.autoCheck setter = function(value) {

	if(value!=null) {
		this._autoCheck = value;
	}
	else {
		throw new Yahoo.ArgumentNullException("value");
	}
}

/**
 * Gets or sets the a value indicating whether the control is checked.
 * @type Boolean
 */
Yahoo.Controls.CheckBoxBase.prototype.checked getter = function() {

	return this._checked;
}

Yahoo.Controls.CheckBoxBase.prototype.checked setter = function(value) {

	if(value!=null) {
		if(this._checked!=value) {
			this._checked = value;
			if(this._checked==true) {
				this._checkState = Yahoo.Controls.CheckState.Checked;
			}
			else {
				this._checkState = Yahoo.Controls.CheckState.Unchecked;
			}
			this._onCheckedChanged(this, new Yahoo.EventArgs());
		}
	}
	else {
		throw new Yahoo.ArgumentNullException("value");
	}
}

/**
 * Gets or sets the state of the checkbox.
 * @type Yahoo.Controls.CheckState
 */
Yahoo.Controls.CheckBoxBase.prototype.checkState getter = function() {

	return this._checkState;
}

Yahoo.Controls.CheckBoxBase.prototype.checkState setter = function(value) {

	if(value!=null) {
		if(this._checkState!=value) {
			this._checkState = value;
			switch(this._checkState) {
				case Yahoo.Controls.CheckState.Checked:
					this._checked = true;
					break;
				case Yahoo.Controls.CheckState.Unchecked:
					this._checked = false;
					break;
				case Yahoo.Controls.CheckState.Indeterminate:
					// Invalid setting for two state checkbox
					this._checked = false;
					break;
			}
			this._onCheckStateChanged(this, new Yahoo.EventArgs());
		}
	}
	else {
		throw new Yahoo.ArgumentNullException("value");
	}
}

/**
 * Gets or sets a value indicating whether the checkbox supports three states instead of two.
 * @type Boolean
 */
Yahoo.Controls.CheckBoxBase.prototype.threeState getter = function() {

	return this._threeState;
}

Yahoo.Controls.CheckBoxBase.prototype.threeState setter = function(value) {

	if(value!=null) {
		if(this._threeState!=value) {
			this._threeState = value;
		}
	}
	else {
		throw new Yahoo.ArgumentNullException("value");
	}
}

