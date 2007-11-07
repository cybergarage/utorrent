/*---------------------------------------------------------------------*/
/// <copyright from='2005' to='2007' company='Yahoo! Inc.'>
/// (C) Copyright 2005-2007 Yahoo! Inc. All Rights Reserved.
/// </copyright>

/**
 * CheckedListBox control.
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
Yahoo.Controls.CheckedListBox = function(theme) {

	//log("CheckedListBox.ctor()");
	if(arguments.length>0) {
		this.initialize(theme);
	}
}

/**
 * Define inheritance chain.
 */
Yahoo.Controls.CheckedListBox.prototype = new Yahoo.Controls.SizableControlBase();
Yahoo.Controls.CheckedListBox.prototype.constructor = Yahoo.Controls.CheckedListBox;
Yahoo.Controls.CheckedListBox.prototype.baseclassCheckedListBox = Yahoo.Controls.SizableControlBase.prototype;

/*-----------------------------------------------------------*/
// Control code
/*-----------------------------------------------------------*/
/**
 * Raises the onEnabledChanged event.
 * @param {Object} sender The source of the event.
 * @param {Yahoo.EventArgs} e The EventArgs object that contains event details.
 */
Yahoo.Controls.CheckedListBox.prototype._onEnabledChanged = function(sender, e) {

	//log("CheckedListBox._onEnabledChanged");

	// Call baseclass
	this.baseclassCheckedListBox._onEnabledChanged.call(this, sender, e);

	// TODO: Loop all items
}

/**
 * Raises the onFontChanged event.
 * @param {Object} sender The source of the event.
 * @param {Yahoo.EventArgs} e The EventArgs object that contains event details.
 */
Yahoo.Controls.CheckedListBox.prototype._onFontChanged = function(sender, e) {

	//log("CheckedListBox._onFontChanged");

	// Call baseclass
	this.baseclassCheckedListBox._onFontChanged.call(this, sender, e);

	// TODO: Loop all items

}

/**
 * Raises the onForeColorChanged event.
 * @param {Object} sender The source of the event.
 * @param {Yahoo.EventArgs} e The EventArgs object that contains event details.
 */
Yahoo.Controls.CheckedListBox.prototype._onForeColorChanged = function(sender, e) {

	//log("CheckedListBox._onForeColorChanged");

	// Call baseclass
	this.baseclassCheckedListBox._onForeColorChanged.call(this, sender, e);
	
	// TODO: Loop all items
}

/**
 * Raises the onResize event.
 * @param {Object} sender The source of the event.
 * @param {Yahoo.EventArgs} e The EventArgs object that contains event details.
 */
Yahoo.Controls.CheckedListBox.prototype._onResize = function(sender, e) {

	//log("CheckedListBox._onResize");

	// Call baseclass
	this.baseclassCheckedListBox._onResize.call(this, sender, e);
	
	// Resize elements
	this._checkedListBox_setSize();
}

/**
 * Raises the onToolTipChanged event.
 * @param {Object} sender The source of the event.
 * @param {Yahoo.EventArgs} e The EventArgs object that contains event details.
 */
Yahoo.Controls.CheckedListBox.prototype._onToolTipChanged = function(sender, e) {

	//log("CheckedListBox._onToolTipChanged");

	// Call baseclass
	this.baseclassCheckedListBox._onToolTipChanged.call(this, sender, e);
	
	// Set tooltip
	// TODO: Loop all items

}

/**
 * Handles onEnter event for whole control.
 * @param {Object} sender The source of the event.
 * @param {Yahoo.EventArgs} e The EventArgs object that contains event details.
 */
Yahoo.Controls.CheckedListBox.prototype._onEnter = function(sender, e) {

	//log("CheckedListBox._onEnter");

	// Cancel enter event if we entered from / left one of our subcontrols
	if((this._isMouseOver == false) || this.displayRectangle.contains(system.event.x + this.left, system.event.y + this.top) == false) {
	
		// Call baseclass
		this.baseclassCheckedListBox._onEnter.call(this, sender, e);
	}
}

/**
 * Handles onLeave event for whole control.
 * @param {Object} sender The source of the event.
 * @param {Yahoo.EventArgs} e The EventArgs object that contains event details.
 */
Yahoo.Controls.CheckedListBox.prototype._onLeave = function(sender, e) {

	//log("CheckedListBox._onLeave");

	// Cancel leave event if we entered one of our subcontrols
	if(this.displayRectangle.contains(system.event.x + this.left, system.event.y + this.top) == false) {

		// Call baseclass
		this.baseclassCheckedListBox._onLeave.call(this, sender, e);
	}
}

/**
 * Raises the onThemeChanged event.
 * @param {Object} sender The source of the event.
 * @param {Yahoo.EventArgs} e The EventArgs object that contains event details.
 */
Yahoo.Controls.CheckedListBox.prototype._onThemeChanged = function(sender, e) {

	//log("CheckedListBox._onThemeChanged");

	// Call base class
	this.baseclassCheckedListBox._onThemeChanged.call(this, sender, e);

	this._checkedListBox_loadTheme();
}

/**
 * Handles onMouseEnter event for item.
 * @param {Object} sender The source of the event.
 * @param {Yahoo.EventArgs} e The EventArgs object that contains event details.
 */
Yahoo.Controls.CheckedListBox.prototype._checkedListBox_chkItem_onEnter = function(sender, e) {

	//log("CheckedListBox._checkedListBox_chkItem_onEnter");

	sender.parent._onEnter.call(sender.parent, sender.parent, new Yahoo.EventArgs());
}

/**
 * Handles onMouseExit event for item.
 * @param {Object} sender The source of the event.
 * @param {Yahoo.EventArgs} e The EventArgs object that contains event details.
 */
Yahoo.Controls.CheckedListBox.prototype._checkedListBox_chkItem_onLeave = function(sender, e) {

	//log("CheckedListBox._checkedListBox_chkItem_onLeave");
	
	// Don't forward this if we are still within the parent control
	if(sender.parent.displayRectangle.contains(system.event.x + sender.left + sender.parent.left, system.event.y + sender.top + sender.parent.top) == false) {
		sender.parent._onLeave.call(sender.parent, sender.parent, new Yahoo.EventArgs());
	}
}

/**
 * Handles onMouseDown event for item.
 * @param {Object} sender The source of the event.
 * @param {Yahoo.EventArgs} e The EventArgs object that contains event details.
 */
Yahoo.Controls.CheckedListBox.prototype._checkedListBox_chkItem_onMouseDown = function(sender, e) {

	//log("CheckedListBox._checkedListBox_chkItem_onMouseDown");
	sender.parent._onMouseDown.call(sender.parent, sender.parent, new Yahoo.EventArgs());
}

/**
 * Handles onMouseUp event for item.
 * @param {Object} sender The source of the event.
 * @param {Yahoo.EventArgs} e The EventArgs object that contains event details.
 */
Yahoo.Controls.CheckedListBox.prototype._checkedListBox_chkItem_onMouseUp = function(sender, e) {

	//log("CheckedListBox._checkedListBox_chkItem_onMouseUp");
	sender.parent._onMouseUp.call(sender.parent, sender.parent, new Yahoo.EventArgs());
}

/**
 * Handles onCollectionChanged event for object collection.
 * @param {Object} sender The source of the event.
 * @param {Yahoo.EventArgs} e The EventArgs object that contains event details.
 */
Yahoo.Controls.CheckedListBox.prototype._checkedListBox_collection_onCollectionChanged = function(sender, e) {

	//log("CheckedListBox._checkedListBox_collection_onCollectionChanged");

	sender.parent._checkedListBox_refreshItems.call(sender.parent);
}

/*---------------------------------------------------------------------*/
// Private code
/*---------------------------------------------------------------------*/
/**
 * Disposes native Widget Engine objects.
 * @private
 */
Yahoo.Controls.CheckedListBox.prototype._checkedListBox_disposeNativeObjects = function() {

	//log("CheckedListBox._checkedListBox_disposeNativeObjects");

	if(this._scbContent!=null) { this._scbContent.removeFromSuperview(); this._scbContent = null; }
	if(this._fraContent!=null) { this._fraContent.removeFromSuperview(); this._fraContent = null; }

	// These aren't native objects, but we still dispose them here
}

/**
 * Loads control elements based on current theme.
 * @private
 */
Yahoo.Controls.CheckedListBox.prototype._checkedListBox_loadTheme = function() {

	// Remove any current objects
	this._checkedListBox_disposeNativeObjects();

	var count;
	
	// Create client frame and scrollbar
	this._scbContent = new ScrollBar();
	this._scbContent.zOrder = 101;
	this._scbContent.autoHide = false;
	this._scbContent.vOffset = this._imgBorderTop.height;
	this._scbContent.thumbColor = this._theme.getParameter("checkedListBoxScrollBarThumbColor").color;
	this._fraContent = new Frame();
	this._fraContent.zOrder = 100;
	this.frame.addSubview(this._fraContent);
	this.frame.addSubview(this._scbContent);
	this._fraContent.vScrollBar = this._scbContent;

	// Redraw items
	this._checkedListBox_refreshItems();

	this._checkedListBox_setSize();
}

/**
 * Sets the size for all the items.
 * @private
 */
Yahoo.Controls.CheckedListBox.prototype._checkedListBox_setSize = function() {

	var count;

	if(this._fraContent!=null) {

		this._fraContent.hOffset = this._imgBorderLeft.width;
		this._fraContent.vOffset = this._imgBorderTop.height;
		this._fraContent.width = this.width - this._scbContent.width - (this._imgBorderLeft.width + this._imgBorderRight.width) - 1;
		this._fraContent.height = this.height - (this._imgBorderTop.height + this._imgBorderBottom.height);
		this._scbContent.hOffset = this._fraContent.width + 1;
		this._scbContent.height = this._fraContent.height;
	
		// Loop all items and set theme
		for(count=0; count<this._displayItems.length; count++) {
			this._displayItems[count].width = this._fraContent.width - 4;
		}  // for displayItems

	} // fraContent!=null
}

/**
 * Creates display items for all items in the collection.
 * @private
 */
Yahoo.Controls.CheckedListBox.prototype._checkedListBox_refreshItems = function() {

	var count;
	var item;
	var top = 0;
	
	//log("_checkedListBox_refreshItems");
	
	// Remove all existing items, if any
	for(count=0; count<this._displayItems.length; count++) {
		this._displayItems[count].dispose();
		this._displayItems[count] = null;
	}
	
	this._displayItems = null;
	this._displayItems = new Array();
	
	// Create display items
	for(count=0; count<this._items.count; count++) {
		item = new Yahoo.Controls.CheckBox(this._theme);
		item._lblText.fromTextObject(this._theme.getItem("checkedListBoxLabel"));
		item.width = this._fraContent.width - 4;
		item.left = 2;
		item.top = top;
		item.text = this._items.item(count).toString();
		this._displayItems.push(item);
		this._fraContent.addSubview(item.frame);
		
		top += item.height + 2;
	}
}

/**
 * Gets an array with the indexes of the checked items.
 * @private
 * @type Array
 */
Yahoo.Controls.CheckedListBox.prototype._checkedListBox_getCheckedIndices = function() {

	var count;
	var result = new Array();
	
	for(count=0; count<this._displayItems.length; count++) {
		if(this._displayItems[count].checked == true) {
			result.push(count);
		}
	}

	return result;
}

/**
 * Sets checked items base on given array.
 * @private
 * @param {Array} checkedArray An array containing the indexes of items the be checked.
 */
Yahoo.Controls.CheckedListBox.prototype._checkedListBox_setCheckedIndices = function(checkedArray) {

	var countItems;
	var countChecked;
	var checked;

	for(countItems=0; countItems<this._displayItems.length; countItems++) {

		checked = false;

		for(countChecked=0; countChecked<checkedArray.length; countChecked++) {
	
			// Check if index at this point of the given array is within valid range
			if(checkedArray[countChecked]>=0 && checkedArray[countChecked]<this._displayItems.length) {
				// Check if given index is the current one in displayItems
				if(countItems==checkedArray[countChecked]) {
					checked = true;
					// Skip rest of checked array items
					break;
				}  // if match
			}
			else {
				throw new Yahoo.ArgumentOutOfRange("index");
			}
		
		}  // for checkedArray

		// Set check accordingly
		this._displayItems[countItems].checked = checked;

	}  // for displayItems
}

/*---------------------------------------------------------------------*/
// Public code
/*---------------------------------------------------------------------*/
/**
 * True constructor. Must be called if this class is overridden.
 * @param {Yahoo.Controls.Theme} theme The theme this control should use or null to create an instance of the default theme.
 */
Yahoo.Controls.CheckedListBox.prototype.initialize = function(theme) {

	//log("CheckedListBox.initialize()");
	
	// Call baseclass constructor
	this.baseclassCheckedListBox.initialize.call(this, theme, "checkedListBox");

	// Includes
	lib.include("Yahoo.Controls.CheckBox");

	// Initialize variables/controls
	this._displayItems = new Array();
	this._items = new Yahoo.Controls.CheckedListBox.ObjectCollection();
	this._items.parent = this;
	this._items.addEventHandler(this._checkedListBox_collection_onCollectionChanged, "CollectionChanged");
	
	this._checkedListBox_loadTheme();
}

/**
 * Disposes control's resources.
 */
Yahoo.Controls.CheckedListBox.prototype.dispose = function() {
	
	this._checkedListBoxItem_disposeNativeObjects();

	// Call baseclass
	this.baseclassCheckedListBox.dispose.call(this);

	// Baseclass disposes our custom controls
}

/**
 * Sets item checked based on given value.
 * @param {Integer} index The index of the item to modify.
 * @param {Boolean} value A value indicating whether the item should be checked.
 */
Yahoo.Controls.CheckedListBox.prototype.setItemChecked = function(index, value) {

	// Check if index at this point of the given array is within valid range
	if(index>=0 && index<this._displayItems.length) {
		if(value==true) {
			this._displayItems[index].checked = true;
		}
		else {
			this._displayItems[index].checked = false;
		}
	}
	else {
		throw new Yahoo.ArgumentOutOfRange("index");
	}
}

/**
 * Sets item checkstate based on given value.
 * @param {Integer} index The index of the item to modify.
 * @param {Yahoo.Controls.CheckState} value A value indicating the item check state.
 */
Yahoo.Controls.CheckedListBox.prototype.setItemCheckState = function(index, value) {

	// Check if index at this point of the given array is within valid range
	if(index>=0 && index<this._displayItems.length) {
		// TODO: Check value for valid enum item
		this._displayItems[index].checkState = value;
	}
	else {
		throw new Yahoo.ArgumentOutOfRange("index");
	}
}

/*---------------------------------------------------------------------*/
// Public properties
/*---------------------------------------------------------------------*/
/**
 * Gets the collection of items in the control.
 * @type Yahoo.Controls.CheckedListBox.ObjectCollection
 */
Yahoo.Controls.CheckedListBox.prototype.items getter = function() {

	return this._items;
}

Yahoo.Controls.CheckedListBox.prototype.items setter = function(value) {
	
	throw new Error("items is read-only");
}

/**
 * Gets or sets the selected items.
 * @type Array
 */
Yahoo.Controls.CheckedListBox.prototype.checkedIndices getter = function() {

	return this._checkedListBox_getCheckedIndices();
}

Yahoo.Controls.CheckedListBox.prototype.checkedIndices setter = function(value) {

	if(value!=null) {
		this._checkedListBox_setCheckedIndices(value);
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
 * CheckedListBoxCollection control.
 */
/*---------------------------------------------------------------------*/

/*---------------------------------------------------------------------*/
// Namespace
/*---------------------------------------------------------------------*/
// Create namespace Yahoo.Controls if it doesn't already exist
//if(Yahoo==undefined) { var Yahoo = new Object(); }
//if(Yahoo.Controls==undefined) { Yahoo.Controls = new Object(); }

/*---------------------------------------------------------------------*/
// Constructor
/*---------------------------------------------------------------------*/
/**
 * Default constructor.
 * @constructor
 */
Yahoo.Controls.CheckedListBox.ObjectCollection = function() {

	//log("CheckedListBox.ObjectCollection.ctor()");
	this.initialize();
}

/*---------------------------------------------------------------------*/
// Private code
/*---------------------------------------------------------------------*/

/*---------------------------------------------------------------------*/
// Public code
/*---------------------------------------------------------------------*/
/**
 * True constructor. Must be called if this class is overridden.
 */
Yahoo.Controls.CheckedListBox.ObjectCollection.prototype.initialize = function() {

	//log("CheckedListBox.ObjectCollection.initialize()");

	this._items = new Array();	
	this._onCollectionChangedEventHandlers = new Array();
}

/**
 * Adds an event handler. Supported events are: CollectionChanged.
 * @param {Function} eventHandler The function that is to be called when the event is raised.
 * @param {String} eventName The name of the event that is being listened to.
 */
Yahoo.Controls.CheckedListBox.ObjectCollection.prototype.addEventHandler = function(eventHandler, eventName) {

	switch(eventName) {
		case "CollectionChanged":
			this._onCollectionChangedEventHandlers.push(eventHandler);
			break;
	}
}

/**
 * Adds an item to the collection.
 * @param {Object} item The item to add to the collection.
 * @type Integer
 */
Yahoo.Controls.CheckedListBox.ObjectCollection.prototype.add = function(item) {
	
	var result = -1;
	
	if(item!=null) {
		result = this._items.push(item) - 1;
		Yahoo.raiseEvent(this, this._onCollectionChangedEventHandlers, new Yahoo.EventArgs());
	}
	else {
		throw new Yahoo.ArgumentNullException("item");
	}

	return result;	
}

/**
 * Adds an array of items to the collection.
 * @param {Array} value The array of items to add to the collection.
 */
Yahoo.Controls.CheckedListBox.ObjectCollection.prototype.addRange = function(value) {
	
	var count;
	
	if(value!=null) {
		for(count=0; count<value.length; count++) {
			this._items.push(value[count]);
		}
		Yahoo.raiseEvent(this, this._onCollectionChangedEventHandlers, new Yahoo.EventArgs());
	}
	else {
		throw new Yahoo.ArgumentNullException("value");
	}
}

/**
 * Removes all items from the collection.
 */
Yahoo.Controls.CheckedListBox.ObjectCollection.prototype.clear = function() {
	
	delete this._items;
	this._items = new Array();
	Yahoo.raiseEvent(this, this._onCollectionChangedEventHandlers, new Yahoo.EventArgs());
}

/**
 * Gets the index of the given item.
 * @param {Object} item The item to to find in the collection.
 * @type Integer
 */
Yahoo.Controls.CheckedListBox.ObjectCollection.prototype.indexOf = function(item) {
	
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
 * @type Object
 */
Yahoo.Controls.CheckedListBox.ObjectCollection.prototype.item = function(index) {

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
Yahoo.Controls.CheckedListBox.ObjectCollection.prototype.remove = function(item) {

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
			Yahoo.raiseEvent(this, this._onCollectionChangedEventHandlers, new Yahoo.EventArgs());
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
Yahoo.Controls.CheckedListBox.ObjectCollection.prototype.removeAt = function(index) {

	if(index>=0 && index<this._items.length) {
		// Remove the item
		this.splice(index, 1);
		Yahoo.raiseEvent(this, this._onCollectionChangedEventHandlers, new Yahoo.EventArgs());
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
 * @type Array
 */
Yahoo.Controls.CheckedListBox.ObjectCollection.prototype.count getter = function() {

	return this._items.length;
}

Yahoo.Controls.CheckedListBox.ObjectCollection.prototype.count setter = function(value) {

	throw new Error("count is read-only");
}

/**
 * Gets or sets the listbox that contains this collection.
 * @type Yahoo.Controls.CheckedListBox
 */
Yahoo.Controls.CheckedListBox.ObjectCollection.prototype.parent getter = function() {

	return this._parent;
}

Yahoo.Controls.CheckedListBox.ObjectCollection.prototype.parent setter = function(value) {

	this._parent = value;
}

