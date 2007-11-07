/*---------------------------------------------------------------------*/
/// <copyright from='2005' to='2006' company='Yahoo! Inc.'>
/// (C) Copyright 2005-2006 Yahoo! Inc. All Rights Reserved.
/// </copyright>

/**
 * TextBox control.
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
Yahoo.Controls.TextBox = function(theme) {

	//log("TextBox.ctor()");
	if(arguments.length>0) {
		this.initialize(theme);
	}
}

/**
 * Define inheritance chain.
 */
Yahoo.Controls.TextBox.prototype = new Yahoo.Controls.SizableControlBase();
Yahoo.Controls.TextBox.prototype.constructor = Yahoo.Controls.TextBox;
Yahoo.Controls.TextBox.prototype.baseclassTextBox = Yahoo.Controls.SizableControlBase.prototype;

/*-----------------------------------------------------------*/
// Control code
/*-----------------------------------------------------------*/
/**
 * Raises the onEnabledChanged event.
 * @param {Object} sender The source of the event.
 * @param {Yahoo.EventArgs} e The EventArgs object that contains event details.
 */
Yahoo.Controls.TextBox.prototype._onEnabledChanged = function(sender, e) {

	//log("TextBox._onEnabledChanged");

	// Call baseclass
	this.baseclassTextBox._onEnabledChanged.call(this, sender, e);

	this._textBox_setTextBoxState();
}

/**
 * Raises the onFontChanged event.
 * @param {Object} sender The source of the event.
 * @param {Yahoo.EventArgs} e The EventArgs object that contains event details.
 */
Yahoo.Controls.TextBox.prototype._onFontChanged = function(sender, e) {

	//log("TextBox._onFontChanged");

	// Call baseclass
	this.baseclassTextBox._onFontChanged.call(this, sender, e);

	this._txtTextBox.font = this.font;

}
/**
 * Raises the onForeColorChanged event.
 * @param {Object} sender The source of the event.
 * @param {Yahoo.EventArgs} e The EventArgs object that contains event details.
 */
Yahoo.Controls.TextBox.prototype._onForeColorChanged = function(sender, e) {

	//log("TextBox._onForeColorChanged");

	// Call baseclass
	this.baseclassTextBox._onForeColorChanged.call(this, sender, e);
	
	this._txtTextBox.foreColor = this.foreColor;
}

/**
 * Raises the onKeyDown event.
 * @param {Object} sender The source of the event.
 * @param {Yahoo.KeyPressEventArgs} e The KeyPressEventArgs object that contains event details.
 */
Yahoo.Controls.TextBox.prototype._onKeyDown = function(sender, e) {

	//log("TextBox._onKeyDown");
   	Yahoo.raiseEvent(this, this._onKeyDownEventHandlers, e);
}

/**
 * Raises the onKeyUp event.
 * @param {Object} sender The source of the event.
 * @param {Yahoo.KeyPressEventArgs} e The KeyPressEventArgs object that contains event details.
 */
Yahoo.Controls.TextBox.prototype._onKeyUp = function(sender, e) {

	//log("TextBox._onKeyUp");
   	Yahoo.raiseEvent(this, this._onKeyUpEventHandlers, e);
}

/**
 * Raises the onKeyPress event.
 * @param {Object} sender The source of the event.
 * @param {Yahoo.KeyPressEventArgs} e The KeyPressEventArgs object that contains event details.
 */
Yahoo.Controls.TextBox.prototype._onKeyPress = function(sender, e) {

	//log("TextBox._onKeyPress");
   	Yahoo.raiseEvent(this, this._onKeyPressEventHandlers, e);
}

/**
 * Raises the onResize event.
 * @param {Object} sender The source of the event.
 * @param {Yahoo.EventArgs} e The EventArgs object that contains event details.
 */
Yahoo.Controls.TextBox.prototype._onResize = function(sender, e) {

	//log("TextBox._onResize");

	// Call baseclass
	this.baseclassTextBox._onResize.call(this, sender, e);
	
	// Resize elements
	this._textBox_setTextLocation();
}

/**
 * Raises the onTextChanged event.
 * @param {Object} sender The source of the event.
 * @param {Yahoo.EventArgs} e The EventArgs object that contains event details.
 */
Yahoo.Controls.TextBox.prototype._onTextChanged = function(sender, e) {

	//log("TextBox._onTextChanged");
	if(this._previousText != this.text)
	{
    	this._previousText = this.text;
    	this._txtTextBox.data = this._previousText;
        // Call baseclass
        this.baseclassTextBox._onTextChanged.call(this, sender, e);	
	}
}

/**
 * Raises the onThemeChanged event.
 * @param {Object} sender The source of the event.
 * @param {Yahoo.EventArgs} e The EventArgs object that contains event details.
 */
Yahoo.Controls.TextBox.prototype._onThemeChanged = function(sender, e) {

	//log("TextBox._onThemeChanged");

	// Call base class
	this.baseclassTextBox._onThemeChanged.call(this, sender, e);

	this._textBox_loadTheme();
}

/**
 * Handles the onKeyDown event for the native TextArea control.
 */
Yahoo.Controls.TextBox.prototype._textBox_onKeyDown = function() {

	//log("TextBox._textBox_onKeyDown");
	var e = this.tag._getKeyPressEventArgs();
	this.tag._onKeyDown.call(this.tag, this.tag, e);
}

/**
 * Handles the onKeyUp event for the native TextArea control.
 */
Yahoo.Controls.TextBox.prototype._textBox_onKeyUp = function() {

	//log("TextBox._textBox_onKeyUp");
	var e = this.tag._getKeyPressEventArgs();
	this.tag._onKeyUp.call(this.tag, this.tag, e);
	this.tag.text = this.tag._txtTextBox.data;
}

/**
 * Handles the onKeyPress event for the native TextArea control.
 */
Yahoo.Controls.TextBox.prototype._textBox_onKeyPress = function() {

	//log("TextBox._textBox_onKeyPress");
	var e = this.tag._getKeyPressEventArgs();
	this.tag._onKeyPress.call(this.tag, this.tag, e);
	
	// Check if we should cancel the keystroke
	if(e.cancel == true) {
	    this.rejectKeyPress();
	    
	    // Check if the key was changed
	    if(system.event.key != e.key) {
	        this.replaceSelection(e.key);
	    }
	}
}

/*---------------------------------------------------------------------*/
// Private code
/*---------------------------------------------------------------------*/
/**
 * Disposes native Widget Engine objects.
 * @private
 */
Yahoo.Controls.TextBox.prototype._textBox_disposeNativeObjects = function() {

	//log("TextBox._textBox_disposeNativeObjects");

	if(this._txtTextBox!=null) { this._txtTextBox.removeFromSuperview(); this._txtTextBox = null; }
}

/**
 * Loads control elements based on current theme.
 * @private
 */
Yahoo.Controls.TextBox.prototype._textBox_loadTheme = function() {

    var text = "";
    
    if(this._txtTextBox != null)
    {
        text = this._txtTextBox.text;
    }

	// Remove any current objects
	this._textBox_disposeNativeObjects();

    // Add native TextArea control
    this._txtTextBox = new TextArea();
    this._txtTextBox.zOrder = 999;
    this._txtTextBox.lines = 1;
    this._txtTextBox.scrollbar = false;
    this._txtTextBox.tag = this;
    this._txtTextBox.onKeyDown = this._textBox_onKeyDown;
    this._txtTextBox.onKeyUp = this._textBox_onKeyUp;
    this._txtTextBox.onKeyPress = this._textBox_onKeyPress;
    this.frame.addSubview(this._txtTextBox);

	this._textMargins = this._theme.getParameter("textBoxTextMargins");

    this._txtTextBox.text = text;

    this._textBox_setTextLocation();
	this._textBox_setTextBoxState();
}

/**
 * Sets the size and location of the native TextArea control.
 * @private
 */
Yahoo.Controls.TextBox.prototype._textBox_setTextLocation = function() {

	this._txtTextBox.hOffset = parseInt(this._textMargins.left);
	this._txtTextBox.vOffset = parseInt(this._textMargins.top);
	this._txtTextBox.width = this.width - (parseInt(this._textMargins.left) + parseInt(this._textMargins.right));
	this._txtTextBox.height = this.height - (parseInt(this._textMargins.top) + parseInt(this._textMargins.bottom));
}

/**
 * Sets the textbox state.
 * @private
 */
Yahoo.Controls.TextBox.prototype._textBox_setTextBoxState = function() {

	if(this.enabled==false) {
		this._txtTextBox.enabled = false;
	}
	else {
	    this._txtTextBox.enabled = true;
	}  // if enabled
}

/**
 * Returns a prefilled KeyPressEventArgs class.
 * @private
 */
Yahoo.Controls.TextBox.prototype._getKeyPressEventArgs = function() {

	var result = new Yahoo.Controls.KeyPressEventArgs();
	result.key = system.event.key;
	result.keyString = system.event.keyString;
	result.modifiers = system.event.modifiers;

    return result;
}

/*---------------------------------------------------------------------*/
// Public code
/*---------------------------------------------------------------------*/
/**
 * True constructor. Must be called if this class is overridden.
 * @param {Yahoo.Controls.Theme} theme The theme this control should use or null to create an instance of the default theme.
 */
Yahoo.Controls.TextBox.prototype.initialize = function(theme) {

	//log("TextBox.initialize()");
	
	// Call baseclass constructor
	this.baseclassTextBox.initialize.call(this, theme, "textBox");

	this._previousText = "";

	// Initialize variables/controls
	this._onKeyDownEventHandlers = new Array();
	this._onKeyUpEventHandlers = new Array();
	this._onKeyPressEventHandlers = new Array();
	this._onTextChangedEventHandlers = new Array();

	this._textBox_loadTheme();
}

/**
 * Adds an event handler. Supported events are: KeyDown, KeyUp, KeyPress.
 * @param {Function} eventHandler The function that is to be called when the event is raised.
 * @param {String} eventName The name of the event that is being listened to.
 */
Yahoo.Controls.TextBox.prototype.addEventHandler = function(eventHandler, eventName) {

	// Call baseclass
	this.baseclassTextBox.addEventHandler.call(this, eventHandler, eventName)

	switch(eventName) {
		case "KeyDown":
			this._onKeyDownEventHandlers.push(eventHandler);
			break;
		case "KeyUp":
			this._onKeyUpEventHandlers.push(eventHandler);
			break;
		case "KeyPress":
			this._onKeyPressEventHandlers.push(eventHandler);
			break;
	}
}

/**
 * Disposes control's resources.
 */
Yahoo.Controls.TextBox.prototype.dispose = function() {
	
	this._textBox_disposeNativeObjects();

	// Call baseclass
	this.baseclassTextBox.dispose.call(this);

	// Baseclass disposes our custom controls
}

/**
 * Moves the keyboard focus to the textbox.
 */
Yahoo.Controls.TextBox.prototype.focus = function() {

    this._txtTextBox.focus();
}

/*---------------------------------------------------------------------*/
/// <copyright from='2005' to='2006' company='Yahoo! Inc.'>
/// (C) Copyright 2005-2006 Yahoo! Inc. All Rights Reserved.
/// </copyright>

/**
 * KeyPressEventArgs class.
 */
/*---------------------------------------------------------------------*/

/*---------------------------------------------------------------------*/
// Constructor
/*---------------------------------------------------------------------*/
/**
 * Default constructor.
 */
Yahoo.Controls.KeyPressEventArgs = function() {

	this.initialize();
}

/**
 * Define inheritance chain.
 */
Yahoo.Controls.KeyPressEventArgs.prototype = new Yahoo.EventArgs();
Yahoo.Controls.KeyPressEventArgs.prototype.constructor = Yahoo.Controls.KeyPressEventArgs;
Yahoo.Controls.KeyPressEventArgs.prototype.baseclassKeyPressEventArgs = Yahoo.EventArgs.prototype;

/*---------------------------------------------------------------------*/
// Public code
/*---------------------------------------------------------------------*/
/**
 * True constructor. Must be called if this class is overridden.
 */
Yahoo.Controls.KeyPressEventArgs.prototype.initialize = function() {

	//log("KeyPressEventArgs.initialize()");
	
	// Call baseclass constructor
	this.baseclassKeyPressEventArgs.initialize.call();
	
	this._key = "";
	this._keyString = "";
	this._modifiers = "";
}

/**
 * Returns a string representation of this class.
 */
Yahoo.Controls.KeyPressEventArgs.prototype.toString = function() {

    return "{Cancel=" + this.cancel + ", key='" + this._key + "', keyString='" 
            + this._keyString + "', modifiers=" + this._modifiers + "}";
}

/*---------------------------------------------------------------------*/
// Public properties
/*---------------------------------------------------------------------*/
/**
 * Gets or sets the key that was pressed.
 * @type String
 */
Yahoo.Controls.KeyPressEventArgs.prototype.key getter = function() {

	return this._key;
}

Yahoo.Controls.KeyPressEventArgs.prototype.key setter = function(value) {

    this._key = value;
}

/**
 * Gets or sets the name of the key that was pressed.
 * @type String
 */
Yahoo.Controls.KeyPressEventArgs.prototype.keyString getter = function() {

	return this._keyString;
}

Yahoo.Controls.KeyPressEventArgs.prototype.keyString setter = function(value) {

    this._keyString = value;
}

/**
 * Gets or sets the modifier keys that were pressed.
 * @type String
 */
Yahoo.Controls.KeyPressEventArgs.prototype.modifiers getter = function() {

	return this._modifiers;
}

Yahoo.Controls.KeyPressEventArgs.prototype.modifiers setter = function(value) {

    this._modifiers = value;
}

