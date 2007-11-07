/*---------------------------------------------------------------------*/
/// <copyright from='2005' to='2007' company='Yahoo! Inc.'>
/// (C) Copyright 2005-2007 Yahoo! Inc. All Rights Reserved.
/// </copyright>

/**
 * ComboBox control.
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
Yahoo.Controls.ComboBox = function(theme) {

	//log("ComboBox.ctor()");
	if(arguments.length>0) {
		this.initialize(theme);
	}
}

/**
 * Define inheritance chain.
 */
Yahoo.Controls.ComboBox.prototype = new Yahoo.Controls.SizableControlBase();
Yahoo.Controls.ComboBox.prototype.constructor = Yahoo.Controls.ComboBox;
Yahoo.Controls.ComboBox.prototype.baseclassComboBox = Yahoo.Controls.SizableControlBase.prototype;

/*-----------------------------------------------------------*/
// Control code
/*-----------------------------------------------------------*/
/**
 * Raises the onEnabledChanged event.
 * @param {Object} sender The source of the event.
 * @param {Yahoo.EventArgs} e The EventArgs object that contains event details.
 */
Yahoo.Controls.ComboBox.prototype._onEnabledChanged = function(sender, e) {

	//log("ComboBox._onEnabledChanged");

	// Call baseclass
	this.baseclassComboBox._onEnabledChanged.call(this, sender, e);

	this._lblText.enabled = this.enabled;
	this._comboBox_setComboBoxState();
}

/**
 * Raises the onFontChanged event.
 * @param {Object} sender The source of the event.
 * @param {Yahoo.EventArgs} e The EventArgs object that contains event details.
 */
Yahoo.Controls.ComboBox.prototype._onFontChanged = function(sender, e) {

	//log("ComboBox._onFontChanged");

	// Call baseclass
	this.baseclassComboBox._onFontChanged.call(this, sender, e);

	this._lblText.font = this.font;

}
/**
 * Raises the onForeColorChanged event.
 * @param {Object} sender The source of the event.
 * @param {Yahoo.EventArgs} e The EventArgs object that contains event details.
 */
Yahoo.Controls.ComboBox.prototype._onForeColorChanged = function(sender, e) {

	//log("ComboBox._onForeColorChanged");

	// Call baseclass
	this.baseclassComboBox._onForeColorChanged.call(this, sender, e);
	
	this._lblText.foreColor = this.foreColor;
}

/**
 * Raises the onResize event.
 * @param {Object} sender The source of the event.
 * @param {Yahoo.EventArgs} e The EventArgs object that contains event details.
 */
Yahoo.Controls.ComboBox.prototype._onResize = function(sender, e) {

	//log("ComboBox._onResize");

	// Call baseclass
	this.baseclassComboBox._onResize.call(this, sender, e);
	
	// Resize elements
	this._comboBox_setButtonLocation();
	this._comboBox_setTextLocation();
}

/**
 * Raises the onTextChanged event.
 * @param {Object} sender The source of the event.
 * @param {Yahoo.EventArgs} e The EventArgs object that contains event details.
 */
Yahoo.Controls.ComboBox.prototype._onTextChanged = function(sender, e) {

	//log("ComboBox._onTextChanged");

	// Call baseclass
	this.baseclassComboBox._onTextChanged.call(this, sender, e);
	
	// Set text
	this._lblText.text = this.text;
}

/**
 * Raises the onToolTipChanged event.
 * @param {Object} sender The source of the event.
 * @param {Yahoo.EventArgs} e The EventArgs object that contains event details.
 */
Yahoo.Controls.ComboBox.prototype._onToolTipChanged = function(sender, e) {

	//log("ComboBox._onToolTipChanged");

	// Call baseclass
	this.baseclassComboBox._onToolTipChanged.call(this, sender, e);
	
	// Set tooltip
	this._lblText.toolTip = this.toolTip;

}

/**
 * Handles onEnter event for whole control.
 * @param {Object} sender The source of the event.
 * @param {Yahoo.EventArgs} e The EventArgs object that contains event details.
 */
Yahoo.Controls.ComboBox.prototype._onEnter = function(sender, e) {

	//log("ComboBox._onEnter");

	// Cancel enter event if we entered from / left one of our subcontrols
	if((this._isMouseOver == false) || this.displayRectangle.contains(system.event.x + this.left, system.event.y + this.top) == false) {
	
		// Call baseclass
		this.baseclassComboBox._onEnter.call(this, sender, e);

		this._comboBox_setComboBoxState();
	}
}

/**
 * Handles onLeave event for whole control.
 * @param {Object} sender The source of the event.
 * @param {Yahoo.EventArgs} e The EventArgs object that contains event details.
 */
Yahoo.Controls.ComboBox.prototype._onLeave = function(sender, e) {

	//log("ComboBox._onLeave");

	// Cancel leave event if we entered one of our subcontrols
	if(this.displayRectangle.contains(system.event.x + this.left, system.event.y + this.top) == false) {

		// Call baseclass
		this.baseclassComboBox._onLeave.call(this, sender, e);
		this._comboBox_setComboBoxState();
	}
}

/**
 * Handles onMouseDown event for whole control.
 * @param {Object} sender The source of the event.
 * @param {Yahoo.EventArgs} e The EventArgs object that contains event details.
 */
Yahoo.Controls.ComboBox.prototype._comboBox_onMouseDown = function(sender, e) {

	//log("ComboBox._comboBox_onMouseDown");

	sender._comboBox_setComboBoxState();
}

/**
 * Handles onMouseUp event for whole control.
 * @param {Object} sender The source of the event.
 * @param {Yahoo.EventArgs} e The EventArgs object that contains event details.
 */
Yahoo.Controls.ComboBox.prototype._comboBox_onMouseUp = function(sender, e) {

	//log("ComboBox._comboBox_onMouseUp");

	sender._comboBox_setComboBoxState();
}

/**
 * Raises the onSelectedIndexChanged event.
 * @param {Object} sender The source of the event.
 * @param {Yahoo.EventArgs} e The EventArgs object that contains event details.
 */
Yahoo.Controls.ComboBox.prototype._onSelectedIndexChanged = function(sender, e) {

	//log("ComboBox._onSelectedIndexChanged");

	if(this._selectedIndex!=-1) {
		this._lblText.text = this._items.item(this._selectedIndex).toString();
	}
	else {
		this._lblText.text = "";
	}

	// Raise event
	Yahoo.raiseEvent(sender, sender._onSelectedIndexChangedEventHandlers, e);
}

/**
 * Raises the onThemeChanged event.
 * @param {Object} sender The source of the event.
 * @param {Yahoo.EventArgs} e The EventArgs object that contains event details.
 */
Yahoo.Controls.ComboBox.prototype._onThemeChanged = function(sender, e) {

	//log("ComboBox._onThemeChanged");

	// Call base class
	this.baseclassComboBox._onThemeChanged.call(this, sender, e);

	this._comboBox_loadTheme();
}

/**
 * Handles onMouseEnter event for label.
 * @param {Object} sender The source of the event.
 * @param {Yahoo.EventArgs} e The EventArgs object that contains event details.
 */
Yahoo.Controls.ComboBox.prototype._comboBox_lblText_onEnter = function(sender, e) {

	//log("ComboBox._comboBox_lblText_onEnter");

	sender.parent._onEnter.call(sender.parent, sender.parent, new Yahoo.EventArgs());
}

/**
 * Handles onMouseExit event for label.
 * @param {Object} sender The source of the event.
 * @param {Yahoo.EventArgs} e The EventArgs object that contains event details.
 */
Yahoo.Controls.ComboBox.prototype._comboBox_lblText_onLeave = function(sender, e) {

	//log("ComboBox._comboBox_lblText_onLeave");
	
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
Yahoo.Controls.ComboBox.prototype._comboBox_lblText_onMouseDown = function(sender, e) {

	//log("ComboBox._comboBox_lblText_onMouseDown");
	sender.parent._comboBox_onMouseDown.call(sender.parent, sender.parent, new Yahoo.EventArgs());
}

/**
 * Handles onMouseUp event for label.
 * @param {Object} sender The source of the event.
 * @param {Yahoo.EventArgs} e The EventArgs object that contains event details.
 */
Yahoo.Controls.ComboBox.prototype._comboBox_lblText_onMouseUp = function(sender, e) {

	//log("ComboBox._comboBox_lblText_onMouseUp");
	sender.parent._comboBox_onMouseUp.call(sender.parent, sender.parent, new Yahoo.EventArgs());
}

/**
 * Handles onMouseEnter event for image.
 * @param {Object} sender The source of the event.
 * @param {Yahoo.EventArgs} e The EventArgs object that contains event details.
 */
Yahoo.Controls.ComboBox.prototype._comboBox_btnDropDown_onEnter = function(sender, e) {

	//log("ComboBox._comboBox_btnDropDown_onEnter");

	sender.parent._onEnter.call(sender.parent, sender.parent, new Yahoo.EventArgs());
}

/**
 * Handles onMouseExit event for imagebutton.
 * @param {Object} sender The source of the event.
 * @param {Yahoo.EventArgs} e The EventArgs object that contains event details.
 */
Yahoo.Controls.ComboBox.prototype._comboBox_btnDropDown_onLeave = function(sender, e) {

	//log("ComboBox._comboBox_btnDropDown_onLeave");
	
	// Don't forward this if we are still within the parent control
	if(sender.parent.displayRectangle.contains(system.event.x + sender.left + sender.parent.left, system.event.y + sender.top + sender.parent.top) == false) {
		sender.parent._onLeave.call(sender.parent, sender.parent, new Yahoo.EventArgs());
	}
}

/**
 * Handles onMouseDown event for imagebutton.
 * @param {Object} sender The source of the event.
 * @param {Yahoo.EventArgs} e The EventArgs object that contains event details.
 */
Yahoo.Controls.ComboBox.prototype._comboBox_btnDropDown_onMouseDown = function(sender, e) {

	//log("ComboBox._comboBox_btnDropDown_onMouseDown");
	sender.parent._comboBox_onMouseDown.call(sender.parent, sender.parent, new Yahoo.EventArgs());
}

/**
 * Handles onMouseUp event for imagebutton.
 * @param {Object} sender The source of the event.
 * @param {Yahoo.EventArgs} e The EventArgs object that contains event details.
 */
Yahoo.Controls.ComboBox.prototype._comboBox_btnDropDown_onMouseUp = function(sender, e) {

	//log("ComboBox._comboBox_btnDropDown_onMouseUp");
	sender.parent._comboBox_onMouseUp.call(sender.parent, sender.parent, new Yahoo.EventArgs());
}

/**
 * Handles onClick event for imagebutton.
 * @param {Object} sender The source of the event.
 * @param {Yahoo.EventArgs} e The EventArgs object that contains event details.
 */
Yahoo.Controls.ComboBox.prototype._comboBox_btnDropDown_onClick = function(sender, e) {

	//log("ComboBox._comboBox_btnDropDown_onClick");
	
	sender.parent._comboBox_showMenu.call(sender.parent);
}

/**
 * Handles click event for comboitem.
 */
Yahoo.Controls.ComboBox.prototype._comboBox_item_onClick = function() {

	//log("ComboBox._comboBox_item_onClick");
    this.tag.selectedIndex = this.index;
}

/*---------------------------------------------------------------------*/
// Private code
/*---------------------------------------------------------------------*/
/**
 * Disposes native Widget Engine objects.
 * @private
 */
Yahoo.Controls.ComboBox.prototype._comboBox_disposeNativeObjects = function() {

	//log("ComboBox._comboBox_disposeNativeObjects");

	// These aren't native objects, but we still dispose them here
	if(this._lblText!=null) { this._lblText.dispose(); this._lblText = null; }
	if(this._btnDropDown!=null) { this._btnDropDown.dispose(); this._btnDropDown = null; }
}

/**
 * Loads control elements based on current theme.
 * @private
 */
Yahoo.Controls.ComboBox.prototype._comboBox_loadTheme = function() {

    var text;
    
    if(this._lblText != null) {
        text = this._lblText.text;
    }
    else {
        text = this.text;
    }
    
	// Remove any current objects
	this._comboBox_disposeNativeObjects();

	this._lblText = new Yahoo.Controls.Label(this._theme);
	this._lblText.fromTextObject(this._theme.getItem("comboBoxLabel"));
	this._lblText.textAlign = Yahoo.Drawing.ContentAlignment.MiddleLeft;
	this._lblText.addEventHandler(this._comboBox_lblText_onEnter, "Enter");
	this._lblText.addEventHandler(this._comboBox_lblText_onLeave, "Leave");
	this._lblText.addEventHandler(this._comboBox_lblText_onMouseDown, "MouseDown");
	this._lblText.addEventHandler(this._comboBox_lblText_onMouseUp, "MouseUp");
	this._lblText.zOrder = 4;
	this.addControl(this._lblText);

	this._btnDropDown = new Yahoo.Controls.ImageButton(this._theme, "comboBoxButtonNormal", "comboBoxButtonOver", "comboBoxButtonDown", "comboBoxButtonDisabled");
	this._btnDropDown.addEventHandler(this._comboBox_btnDropDown_onEnter, "Enter");
	this._btnDropDown.addEventHandler(this._comboBox_btnDropDown_onLeave, "Leave");
	this._btnDropDown.addEventHandler(this._comboBox_btnDropDown_onMouseDown, "MouseDown");
	this._btnDropDown.addEventHandler(this._comboBox_btnDropDown_onMouseUp, "MouseUp");
	this._btnDropDown.addEventHandler(this._comboBox_btnDropDown_onClick, "Click");
	this._btnDropDown.zOrder = 5;
	this.addControl(this._btnDropDown);

	// Get options for comboBox from theme
	this._textMargins = this._theme.getParameter("comboBoxTextMargins");
	this._buttonMargins = this._theme.getParameter("comboBoxButtonMargins");
	this._paramDisabled = this._theme.getParameter("comboBoxDisabled");
	this._paramDown = this._theme.getParameter("comboBoxDown");
	this._paramNormal = this._theme.getParameter("comboBoxNormal");
	this._paramOver = this._theme.getParameter("comboBoxOver");

    // Restore text
	this._lblText.text = text;

	this._comboBox_setButtonLocation();
	this._comboBox_setTextLocation();
	this._comboBox_setComboBoxStyle(this._paramNormal);
}

/**
 * Sets the location and size for the text label.
 * @private
 */
Yahoo.Controls.ComboBox.prototype._comboBox_setTextLocation = function() {

	if(this._lblText!=null) {
		this._lblText.left = parseInt(this._textMargins.left);
		this._lblText.top = parseInt(this._textMargins.top);
		this._lblText.width = this._btnDropDown.left - (parseInt(this._textMargins.left) + parseInt(this._textMargins.right));
		this._lblText.height = this.height - (parseInt(this._textMargins.top) + parseInt(this._textMargins.bottom));
	}
}

/**
 * Sets the location and size for the dropdown button.
 * @private
 */
Yahoo.Controls.ComboBox.prototype._comboBox_setButtonLocation = function() {

	if(this._btnDropDown!=null) {
		this._btnDropDown.width = this.height - (parseInt(this._buttonMargins.left) + parseInt(this._buttonMargins.right));
		this._btnDropDown.left = this.width - this._btnDropDown.width - parseInt(this._buttonMargins.right);
		this._btnDropDown.top = parseInt(this._buttonMargins.top);
		this._btnDropDown.height = this.height - (parseInt(this._buttonMargins.top) + parseInt(this._buttonMargins.bottom));
	}
}

/**
 * Sets the comboBox state.
 * @private
 */
Yahoo.Controls.ComboBox.prototype._comboBox_setComboBoxState = function() {

	if(this.enabled==false) {
		this._comboBox_setComboBoxStyle(this._paramDisabled);
	}
	else {
		if(this._isMouseOver==true && this._isMouseDown==true) {
			this._comboBox_setComboBoxStyle(this._paramDown);
		}
		else if(this._isMouseOver==true && this._isMouseDown==false) {
			this._comboBox_setComboBoxStyle(this._paramOver);
		}
		else {
			this._comboBox_setComboBoxStyle(this._paramNormal);
		}
	}  // if enabled
}

/**
 * Sets comboBox elements to match current state.
 * @private
 * @param {Object} params Object that contains the control style parameters.
 */
Yahoo.Controls.ComboBox.prototype._comboBox_setComboBoxStyle = function(params) {

	this._imgBackground.colorize = params.colorize;
	this._imgBackground.hslAdjustment = params.hslAdjustment;
	this._imgBackground.hslTinting = params.hslTinting;
	this._imgBackground.opacity = params.opacity;

	this._imgCornerTopLeft.colorize = params.colorize;
	this._imgCornerTopLeft.hslAdjustment = params.hslAdjustment;
	this._imgCornerTopLeft.hslTinting = params.hslTinting;
	this._imgCornerTopLeft.opacity = params.opacity;

	this._imgCornerTopRight.colorize = params.colorize;
	this._imgCornerTopRight.hslAdjustment = params.hslAdjustment;
	this._imgCornerTopRight.hslTinting = params.hslTinting;
	this._imgCornerTopRight.opacity = params.opacity;

	this._imgCornerBottomLeft.colorize = params.colorize;
	this._imgCornerBottomLeft.hslAdjustment = params.hslAdjustment;
	this._imgCornerBottomLeft.hslTinting = params.hslTinting;
	this._imgCornerBottomLeft.opacity = params.opacity;

	this._imgCornerBottomRight.colorize = params.colorize;
	this._imgCornerBottomRight.hslAdjustment = params.hslAdjustment;
	this._imgCornerBottomRight.hslTinting = params.hslTinting;
	this._imgCornerBottomRight.opacity = params.opacity;

	this._imgBorderTop.colorize = params.colorize;
	this._imgBorderTop.hslAdjustment = params.hslAdjustment;
	this._imgBorderTop.hslTinting = params.hslTinting;
	this._imgBorderTop.opacity = params.opacity;

	this._imgBorderBottom.colorize = params.colorize;
	this._imgBorderBottom.hslAdjustment = params.hslAdjustment;
	this._imgBorderBottom.hslTinting = params.hslTinting;
	this._imgBorderBottom.opacity = params.opacity;

	this._imgBorderLeft.colorize = params.colorize;
	this._imgBorderLeft.hslAdjustment = params.hslAdjustment;
	this._imgBorderLeft.hslTinting = params.hslTinting;
	this._imgBorderLeft.opacity = params.opacity;

	this._imgBorderRight.colorize = params.colorize;
	this._imgBorderRight.hslAdjustment = params.hslAdjustment;
	this._imgBorderRight.hslTinting = params.hslTinting;
	this._imgBorderRight.opacity = params.opacity;

	this._lblText.opacity = params.opacity;
	this._btnDropDown.opacity = params.opacity;
}

/**
 * Displays menu.
 * @private
 */
Yahoo.Controls.ComboBox.prototype._comboBox_showMenu = function() {

	var count;
	var menu = new Array();
	var point;

	for(count=0; count<this._items.count; count++) {
		menu[count] = new MenuItem();
		menu[count].title = this._items.item(count).toString();
		menu[count].index = count;
		menu[count].tag = this;
		menu[count].onSelect = this._comboBox_item_onClick;
	}  // for items
	
	if(menu.length>0) {
		point = this.pointToClient(new Yahoo.Drawing.Point(0, this.height));
		popupMenu(menu, point.x, point.y);
	}
}

/*---------------------------------------------------------------------*/
// Public code
/*---------------------------------------------------------------------*/
/**
 * True constructor. Must be called if this class is overridden.
 * @param {Yahoo.Controls.Theme} theme The theme this control should use or null to create an instance of the default theme.
 */
Yahoo.Controls.ComboBox.prototype.initialize = function(theme) {

	//log("ComboBox.initialize()");
	
	// Call baseclass constructor
	this.baseclassComboBox.initialize.call(this, theme, "comboBox");

	// Includes
	lib.include("Yahoo.Controls.Label");
	lib.include("Yahoo.Controls.ImageButton");

	// Initialize variables/controls
	this._items = new Yahoo.Controls.ComboBox.ObjectCollection();
	this._selectedIndex = -1
	
    // Hook into mouse events for whole control
   	this.addEventHandler(this._comboBox_onMouseDown, "MouseDown");
	this.addEventHandler(this._comboBox_onMouseUp, "MouseUp");

	this._onSelectedIndexChangedEventHandlers = new Array();

	this._comboBox_loadTheme();
}

/**
 * Adds an event handler. Supported events are: SelectedIndexChanged.
 * @param {Function} eventHandler The function that is to be called when the event is raised.
 * @param {String} eventName The name of the event that is being listened to.
 */
Yahoo.Controls.ComboBox.prototype.addEventHandler = function(eventHandler, eventName) {

	// Call baseclass
	this.baseclassComboBox.addEventHandler.call(this, eventHandler, eventName)

	switch(eventName) {
		case "SelectedIndexChanged":
			this._onSelectedIndexChangedEventHandlers.push(eventHandler);
			break;
	}
}

/**
 * Disposes control's resources.
 */
Yahoo.Controls.ComboBox.prototype.dispose = function() {
	
	this._comboBox_disposeNativeObjects();

	// Call baseclass
	this.baseclassComboBox.dispose.call(this);

	// Baseclass disposes our custom controls
}

/*---------------------------------------------------------------------*/
// Public properties
/*---------------------------------------------------------------------*/
/**
 * Gets the collection of items in the combobox.
 * @type Yahoo.Controls.ComboBox.ObjectCollection
 */
Yahoo.Controls.ComboBox.prototype.items getter = function() {

	return this._items;
}

Yahoo.Controls.ComboBox.prototype.items setter = function(value) {
	
	throw new Error("items is read-only");
}

/**
 * Gets or sets the selected item index.
 * @type Integer
 */
Yahoo.Controls.ComboBox.prototype.selectedIndex getter = function() {

	return this._selectedIndex;
}

Yahoo.Controls.ComboBox.prototype.selectedIndex setter = function(value) {

	if(value!=null) {
		if(this._selectedIndex!=value) {
			if(value<-1 || value>=this._items.count) {
				throw new Yahoo.ArgumentOutOfRangeException("value");
			}
			else {
				this._selectedIndex = value;
				this._onSelectedIndexChanged(this, new Yahoo.EventArgs());
			}
		}
	}
	else {
		throw new Yahoo.ArgumentNullException("value");
	}
}

/**
 * Gets or sets the alignment of the text on the comboBox.
 * @type Yahoo.Drawing.ContentAlignment
 */
Yahoo.Controls.ComboBox.prototype.textAlign getter = function() {

	return this._lblText.textAlign;
}

Yahoo.Controls.ComboBox.prototype.textAlign setter = function(value) {

	if(value!=null) {
		this._lblText.textAlign = value;
	}
	else {
		throw new Yahoo.ArgumentNullException("value");
	}
}

/*---------------------------------------------------------------------*/
/// <copyright from='2005' to='2006' company='Yahoo! Inc.'>
/// (C) Copyright 2005-2006 Yahoo! Inc. All Rights Reserved.
/// </copyright>

/**
 * ComboBoxCollection control.
 */
/*---------------------------------------------------------------------*/

/*---------------------------------------------------------------------*/
// Namespace
/*---------------------------------------------------------------------*/
// Create namespace Yahoo.Controls if it doesn't already exist
if(Yahoo==undefined) { var Yahoo = new Object(); }
if(Yahoo.Controls==undefined) { Yahoo.Controls = new Object(); }

/*---------------------------------------------------------------------*/
// Constructor
/*---------------------------------------------------------------------*/
/**
 * Default constructor.
 */
Yahoo.Controls.ComboBox.ObjectCollection = function() {

	//log("ComboBox.ObjectCollection.ctor()");
	this.initialize();
}

/*---------------------------------------------------------------------*/
// Public code
/*---------------------------------------------------------------------*/
/**
 * True constructor. Must be called if this class is overridden.
 */
Yahoo.Controls.ComboBox.ObjectCollection.prototype.initialize = function() {

	//log("ComboBox.ObjectCollection.initialize()");

	this._items = new Array();	
}

/**
 * Adds an item to the collection.
 * @param {Object} item The item to add to the collection.
 * @type Integer
 */
Yahoo.Controls.ComboBox.ObjectCollection.prototype.add = function(item) {
	
	var result = -1;
	
	if(item!=null) {
		result = this._items.push(item) - 1;
	}
	else {
		throw new Yahoo.ArgumentNullException("item");
	}

	return result;	
}

/**
 * Removes all items from the collection.
 */
Yahoo.Controls.ComboBox.ObjectCollection.prototype.clear = function() {
	
	delete this._items;
	this._items = new Array();
}

/**
 * Gets the index of the given item.
 * @param {Object} item The item to to find in the collection.
 * @type Integer
 */
Yahoo.Controls.ComboBox.ObjectCollection.prototype.indexOf = function(item) {
	
	var count;
	var result = -1;

	if(item!=null) {

		// Find the item
		for(count=0; count<this.length; count++) {
			if(this[count] == item) {
				result = count;
				break;
			} //if(items[count]==item)
		}
	}

	return result;
}

/**
 * Gets the item at the given index.
 * @param {Integer} index The index of the item to retrieve from the collection.
 * @type Integer
 */
Yahoo.Controls.ComboBox.ObjectCollection.prototype.item = function(index) {

	if(index>=0 && index<this._items.length) {
		return this._items[index];
	}
	else {
		throw new Yahoo.ArgumentOutOfRange("index");
	}
}

/**
 * Removes the given item from the collection.
 * @param {Object} item The item to remove from the collection.
 */
Yahoo.Controls.ComboBox.ObjectCollection.prototype.remove = function(item) {

	var position = -1;
	var item;
	var newItems;

	if(item!=null) {

		// Find the item
		position = this.indexOf(item);

		// Make sure we found the item
		if(position != -1) {
			// Remove the item
			this.splice(position, 1);
		}  // position != -1

	}
	else {
		throw new Yahoo.ArgumentNullException("item");
	}
}

/**
 * Removes the given item from the collection.
 * @param {Integer} index The index of the item to remove from the collection.
 */
Yahoo.Controls.ComboBox.ObjectCollection.prototype.removeAt = function(index) {

	var position = -1;
	var item;
	var newItems;

	if(index>=0 && index<this._items.length) {
		// Remove the item
		this.splice(index, 1);
	}
	else {
		throw new Yahoo.ArgumentOutOfRange("index");
	}
}

/*---------------------------------------------------------------------*/
// Public properties
/*---------------------------------------------------------------------*/
/**
 * Gets the number of items in the collection.
 * @type Integer
 */
Yahoo.Controls.ComboBox.ObjectCollection.prototype.count getter = function() {

	return this._items.length;
}

Yahoo.Controls.ComboBox.ObjectCollection.prototype.count setter = function(value) {

	throw new Error("count is read-only");
}

