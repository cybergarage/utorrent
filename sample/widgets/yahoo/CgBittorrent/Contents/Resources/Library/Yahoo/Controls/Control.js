/*---------------------------------------------------------------------*/
/// <copyright from='2005' to='2007' company='Yahoo! Inc.'>
/// (C) Copyright 2005-2007 Yahoo! Inc. All Rights Reserved.
/// </copyright>

/**
 * Base class for all controls.
 */
/*---------------------------------------------------------------------*/

/*---------------------------------------------------------------------*/
// Namespace
/*---------------------------------------------------------------------*/
// Create namespace if it doesn't already exist
if(Yahoo==undefined) { var Yahoo = new Object(); }
if(Yahoo.Controls==undefined) { Yahoo.Controls = new Object(); }

/*---------------------------------------------------------------------*/
// Constructor
/*---------------------------------------------------------------------*/
/**
 * Default constructor.
 * @constructor
 * @param {Yahoo.Controls.Theme} theme The theme this control should use or null to create an instance of the default theme.
 */
Yahoo.Controls.Control = function(theme) {

	if(arguments.length>0) {
		this.initialize(theme);
	}
}

/*-----------------------------------------------------------*/
// Control code
/*-----------------------------------------------------------*/
/**
 * Raises the onBackColorChanged event.
 * @param {Object} sender The source of the event.
 * @param {Yahoo.EventArgs} e The EventArgs object that contains event details.
 */
Yahoo.Controls.Control.prototype._onBackColorChanged = function(sender, e) {

	//log("Control._onBackColorChanged");
	this._frame.style.backgroundColor = this._backColor;
	Yahoo.raiseEvent(sender, sender._onBackColorChangedEventHandlers, e);
}

/**
 * Raises the onClick event.
 * @param {Object} sender The source of the event.
 * @param {Yahoo.EventArgs} e The EventArgs object that contains event details.
 */
Yahoo.Controls.Control.prototype._onClick = function(sender, e) {

	//log("Control._onClick");
	if(this.enabled == true) {
		Yahoo.raiseEvent(sender, sender._onClickEventHandlers, e);
	}
}

/**
 * Raises the onEnabledChanged event.
 * @param {Object} sender The source of the event.
 * @param {Yahoo.EventArgs} e The EventArgs object that contains event details.
 */
Yahoo.Controls.Control.prototype._onEnabledChanged = function(sender, e) {

	//log("Control._onEnabledChanged");
	Yahoo.raiseEvent(sender, sender._onEnabledChangedEventHandlers, e);
}

/**
 * Raises the onEnter event.
 * @param {Object} sender The source of the event.
 * @param {Yahoo.EventArgs} e The EventArgs object that contains event details.
 */
Yahoo.Controls.Control.prototype._onEnter = function(sender, e) {

	//log("Control._onEnter");
	this._isMouseOver = true;
	if(this.enabled == true) {
		Yahoo.raiseEvent(sender, sender._onEnterEventHandlers, e);
	}
}

/**
 * Raises the onFontChanged event.
 * @param {Object} sender The source of the event.
 * @param {Yahoo.EventArgs} e The EventArgs object that contains event details.
 */
Yahoo.Controls.Control.prototype._onFontChanged = function(sender, e) {

	//log("Control._onFontChanged");
	Yahoo.raiseEvent(sender, sender._onFontChangedEventHandlers, e);
}

/**
 * Raises the onForeColorChanged event.
 * @param {Object} sender The source of the event.
 * @param {Yahoo.EventArgs} e The EventArgs object that contains event details.
 */
Yahoo.Controls.Control.prototype._onForeColorChanged = function(sender, e) {

	//log("Control._onForeColorChanged");
	Yahoo.raiseEvent(sender, sender._onForeColorChangedEventHandlers, e);
}

/**
 * Raises the onLeave event.
 * @param {Object} sender The source of the event.
 * @param {Yahoo.EventArgs} e The EventArgs object that contains event details.
 */
Yahoo.Controls.Control.prototype._onLeave = function(sender, e) {

	//log("Control._onLeave");
	this._isMouseOver = false;
	if(this.enabled == true) {
		Yahoo.raiseEvent(sender, sender._onLeaveEventHandlers, e);
	}
}

/**
 * Raises the onLocationChanged event.
 * @param {Object} sender The source of the event.
 * @param {Yahoo.EventArgs} e The EventArgs object that contains event details.
 */
Yahoo.Controls.Control.prototype._onLocationChanged = function(sender, e) {

	//log("Control._onLocationChanged");
	Yahoo.raiseEvent(this, this._onLocationChangedEventHandlers, new Yahoo.EventArgs());
}

/**
 * Raises the onMouseDown event.
 * @param {Object} sender The source of the event.
 * @param {Yahoo.EventArgs} e The EventArgs object that contains event details.
 */
Yahoo.Controls.Control.prototype._onMouseDown = function(sender, e) {

	//log("Control._onMouseDown");
	this._isMouseDown = true;
	if(this.enabled == true) {
		Yahoo.raiseEvent(sender, sender._onMouseDownEventHandlers, e);
	}
}

/**
 * Raises the onMouseDrag event.
 * @param {Object} sender The source of the event.
 * @param {Yahoo.EventArgs} e The EventArgs object that contains event details.
 */
Yahoo.Controls.Control.prototype._onMouseDrag = function(sender, e) {

	//log("Control._onMouseDrag");
	if(this.enabled == true) {
		Yahoo.raiseEvent(sender, sender._onMouseDragEventHandlers, e);
	}
}

/**
 * Raises the onMouseUp event.
 * @param {Object} sender The source of the event.
 * @param {Yahoo.EventArgs} e The EventArgs object that contains event details.
 */
Yahoo.Controls.Control.prototype._onMouseUp = function(sender, e) {

	//log("Control._onMouseUp");

	this._isMouseDown = false;

	// Raise click event
	if(this._isMouseOver==true) {
		this._onClick.call(sender, sender, new Yahoo.EventArgs());
	}

	if(this.enabled == true) {
		Yahoo.raiseEvent(sender, sender._onMouseUpEventHandlers, e);
	}
}

/**
 * Raises the onOpacityChanged event.
 * @param {Object} sender The source of the event.
 * @param {Yahoo.EventArgs} e The EventArgs object that contains event details.
 */
Yahoo.Controls.Control.prototype._onOpacityChanged = function(sender, e) {

	//log("Control._onOpacityChanged");
	Yahoo.raiseEvent(this, this._onOpacityChangedEventHandlers, new Yahoo.EventArgs());
}

/**
 * Raises the onResize event.
 * @param {Object} sender The source of the event.
 * @param {Yahoo.EventArgs} e The EventArgs object that contains event details.
 */
Yahoo.Controls.Control.prototype._onResize = function(sender, e) {

	//log("Control._onResize");
	Yahoo.raiseEvent(sender, sender._onResizeEventHandlers, e);
}

/**
 * Raises the onTextChanged event.
 * @param {Object} sender The source of the event.
 * @param {Yahoo.EventArgs} e The EventArgs object that contains event details.
 */
Yahoo.Controls.Control.prototype._onTextChanged = function(sender, e) {

	//log("Control._onTextChanged");
	Yahoo.raiseEvent(sender, sender._onTextChangedEventHandlers, e);
}

/**
 * Raises the onThemeChanged event.
 * @param {Object} sender The source of the event.
 * @param {Yahoo.EventArgs} e The EventArgs object that contains event details.
 */
Yahoo.Controls.Control.prototype._onThemeChanged = function(sender, e) {

	//log("Control._onThemeChanged");
	
	// TODO: Check if this points to the correct object (should be changed to the control from here on)
	Yahoo.raiseEvent(this, this._onThemeChangedEventHandlers, e);
}

/**
 * Raises the onToolTipChanged event.
 * @param {Object} sender The source of the event.
 * @param {Yahoo.EventArgs} e The EventArgs object that contains event details.
 */
Yahoo.Controls.Control.prototype._onToolTipChanged = function(sender, e) {

	//log("Control._onToolTipChanged");
	Yahoo.raiseEvent(sender, sender._onToolTipChangedChangedEventHandlers, e);
}

/**
 * Raises the onVisibleChanged event.
 * @param {Object} sender The source of the event.
 * @param {Yahoo.EventArgs} e The EventArgs object that contains event details.
 */
Yahoo.Controls.Control.prototype._onVisibleChanged = function(sender, e) {

	//log("Control._onVisibleChanged");
	Yahoo.raiseEvent(sender, sender._onVisibleChangedEventHandlers, e);
}

/**
 * Handles onMouseDown event for control objects.
 */
Yahoo.Controls.Control.prototype._control_onMouseDown = function() {

	//log("Control._control_onMouseDown");
	this.tag._onMouseDown.call(this.tag, this.tag, new Yahoo.EventArgs());
}

/**
 * Handles onMouseEnter event for control objects.
 */
Yahoo.Controls.Control.prototype._control_onMouseEnter = function() {

	//log("Control._control_onMouseEnter");
	this.tag._onEnter.call(this.tag, this.tag, new Yahoo.EventArgs());
}

/**
 * Handles onMouseExit event for control objects.
 */
Yahoo.Controls.Control.prototype._control_onMouseExit = function() {

	//log("Control._control_onMouseExit");
	this.tag._onLeave.call(this.tag, this.tag, new Yahoo.EventArgs());
}

/**
 * Handles onMouseDrag event for control objects.
 */
Yahoo.Controls.Control.prototype._control_onMouseDrag = function() {

	//log("Control._control_onMouseDrag");
	this.tag._onMouseDrag.call(this.tag, this.tag, new Yahoo.EventArgs());
}

/**
 * Handles onMouseUp event for control objects.
 */
Yahoo.Controls.Control.prototype._control_onMouseUp = function() {

	//log("Control._control_onMouseUp");
	this.tag._onMouseUp.call(this.tag, this.tag, new Yahoo.EventArgs());
}

/*---------------------------------------------------------------------*/
// Private code
/*---------------------------------------------------------------------*/
/**
 * Disposes controls.
 * @private
 */
Yahoo.Controls.Control.prototype._control_disposeControls = function() {

	var count;

	// Tell Widget Class Library controls to dispose	
	for(count=0; count<this._controls.length; count++) {
		if(this._controls[count].dispose!=undefined) {
			this._controls[count].dispose();
		}
		this._controls = null;
		this._controls = new Array();
	}

	// Remove any other items that are left over in the frame
	if(this._frame!=null) {
		if(this._frame.subviews!=null) {
			for(count=0; count<this._frame.subviews.length; count++) {
				try {
					this._frame.subviews[count].removeFromSuperview();
				}
				catch(e) {
					log(e);
				}
				if(this._frame.subviews==null) {
					break;
				}
			}
		}
		
		// Remove frame
		this._frame.removeFromSuperview();
		this._frame = null;
	}
}

/**
 * Changes the control size.
 * @private
 * @param {Integer} width The width of the control.
 * @param {Integer} height The height of the control.
 */
Yahoo.Controls.Control.prototype._control_setSize = function(width, height) {

	var notify = false;

	//log("Control._control_setSize()");

	if(this._isInitializing==false) {

		if(width!=this._frame.width) {
			this._frame.width = width;
			notify = true;
		}
	
		if(height!=this._frame.height) {
			this._frame.height = height;
			notify = true;
		}

		if(notify==true) {
			this._onResize(this, new Yahoo.EventArgs());
		}
	}
}

/**
 * Changes the control location.
 * @private
 * @param {Integer} left The left edge of the control.
 * @param {Integer} top The top edge of the control.
 */
Yahoo.Controls.Control.prototype._control_setLocation = function(left, top) {

	var notify = false;

	if(left!=this._frame.hOffset) {
		this._frame.hOffset = left;
		notify = true;
	}

	if(top!=this._frame.vOffset) {
		this._frame.vOffset = top;
		notify = true;
	}

	if(notify==true) {
		this._onLocationChanged(this, new Yahoo.EventArgs());
	}
}

/*---------------------------------------------------------------------*/
// Public code
/*---------------------------------------------------------------------*/
/**
 * True constructor. Must be called when this class is overridden.
 * @param {Yahoo.Controls.Theme} theme The theme this control should use or null to create an instance of the default theme.
 */
Yahoo.Controls.Control.prototype.initialize = function(theme) {

	//log("Control.initialize");

	this._isInitializing = true;

	// Includes
	lib.include("Yahoo.ArgumentNullException");
	lib.include("Yahoo.ArgumentOutOfRangeException");
	lib.include("Yahoo.EventArgs");
	lib.include("Yahoo.Drawing.Common");
	lib.include("Yahoo.Controls.Theme");

	// Initialize variables
	this._frame = new Frame();
	this._frame.tag = this;
	this._frame.zOrder = 0;
	this._frame.onMouseEnter = this._control_onMouseEnter;
	this._frame.onMouseExit = this._control_onMouseExit;
	this._disposing = false;
	this._text = "";
	this._toolTip = "";
	this._enabled = true;
	this._isMouseDown = false;
	this._isMouseOver = false;
	this._controls = new Array();

	// Check if we were given a theme or create default
	if(theme!=null) {
		this._theme = theme;
	}
	else {
		this._theme = new Yahoo.Controls.Theme(lib.getClassResourcePath("Yahoo.Controls") + "/Themes");
		this._theme.loadTheme(lib.defaultTheme);
	}

	this._isInitializing = false;
}

/**
 * Adds a control to the controls collection.
 * @param {Yahoo.Controls.Control} value The child control to add to this control.
 */
Yahoo.Controls.Control.prototype.addControl = function(value) {

	//log("Control.addControl");

	if(value!=null) {
		value.parent = this;
		this._controls.push(value);
		this._frame.addSubview(value.frame);
	} // if(null)
}

/**
 * Adds an event handler for the requested event. Supported events are:
 * BackColorChanged, Click, EnabledChanged, Enter, FontChanged, ForeColorChanged, 
 * Leave, LocationChanged, MouseDown, MouseDrag, MouseUp, OpacityChanged, Resize, 
 * TextChanged, ThemeChanged, TooltipChanged, VisibleChanged.
 * @param {Function} eventHandler The function that is to be called when the event is raised.
 * @param {String} eventName The name of the event that is being listened to.
 */
Yahoo.Controls.Control.prototype.addEventHandler = function(eventHandler, eventName) {

	switch(eventName) {
		case "BackColorChanged":
	        if(this._onBackColorChangedEventHandlers == null) {
    	        this._onBackColorChangedEventHandlers = new Array();
	        }
			this._onBackColorEventHandlers.push(eventHandler);
			break;
		case "Click":
		    if(this._onClickEventHandlers == null) {
	            this._onClickEventHandlers = new Array();
    	        // This is also set in onMouseUp
	            this._frame.onMouseUp = this._control_onMouseUp;
	        }
			this._onClickEventHandlers.push(eventHandler);
			break;
		case "EnabledChanged":
		    if(this._onEnabledChangedEventHandlers == null) {
	            this._onEnabledChangedEventHandlers = new Array();
	        }
			this._onEnabledChangedEventHandlers.push(eventHandler);
			break;
		case "Enter":
		    if(this._onEnterEventHandlers == null) {
	            this._onEnterEventHandlers = new Array();
	        }
			this._onEnterEventHandlers.push(eventHandler);
			break;
		case "FontChanged":
		    if(this._onFontChangedEventHandlers == null) {
	            this._onFontChangedEventHandlers = new Array();
	        }
			this._onFontChangedEventHandlers.push(eventHandler);
			break;
		case "ForeColorChanged":
		    if(this._onForeColorChangedEventHandlers == null) {
	            this._onForeColorChangedEventHandlers = new Array();
	        }
			this._onForeColorChangedEventHandlers.push(eventHandler);
			break;
		case "Leave":
		    if(this._onLeaveEventHandlers == null) {
	            this._onLeaveEventHandlers = new Array();
	        }
			this._onLeaveEventHandlers.push(eventHandler);
			break;
		case "LocationChanged":
		    if(this._onLocationChangedEventHandlers == null) {
	            this._onLocationChangedEventHandlers = new Array();
	        }
			this._onLocationChangedEventHandlers.push(eventHandler);
			break;
		case "MouseDown":
		    if(this._onMouseDownEventHandlers == null) {
	            this._onMouseDownEventHandlers = new Array();
            	this._frame.onMouseDown = this._control_onMouseDown;
	        }
			this._onMouseDownEventHandlers.push(eventHandler);
			break;
		case "MouseDrag":
		    if(this._onMouseDragEventHandlers == null) {
	            this._onMouseDragEventHandlers = new Array();
	            this._frame.onMouseDrag = this._control_onMouseDrag;
	        }
			this._onMouseDragEventHandlers.push(eventHandler);
			break;
		case "MouseUp":
		    if(this._onMouseUpEventHandlers == null) {
	            this._onMouseUpEventHandlers = new Array();
    	        // This is also set in onClick
	            this._frame.onMouseUp = this._control_onMouseUp;
	        }
			this._onMouseUpEventHandlers.push(eventHandler);
			break;
		case "OpacityChanged":
		    if(this._onOpacityChangedEventHandlers == null) {
	            this._onOpacityChangedEventHandlers = new Array();
	        }
			this._onOpacityChangedEventHandlers.push(eventHandler);
			break;
		case "Resize":
		    if(this._onResizeEventHandlers == null) {
	            this._onResizeEventHandlers = new Array();
	        }
			this._onResizeEventHandlers.push(eventHandler);
			break;
		case "TextChanged":
		    if(this._onTextChangedEventHandlers == null) {
	            this._onTextChangedEventHandlers = new Array();
	        }
			this._onTextChangedEventHandlers.push(eventHandler);
			break;
		case "ThemeChanged":
		    if(this._onThemeChangedEventHandlers == null) {
	            this._onThemeChangedEventHandlers = new Array();
	        }
			this._onThemeChangedEventHandlers.push(eventHandler);
			break;
		case "ToolTipChanged":
		    if(this._onToolTipChangedEventHandlers == null) {
	            this._onToolTipChangedEventHandlers = new Array();
	        }
			this._onToolTipChangedEventHandlers.push(eventHandler);
			break;
		case "VisibleChanged":
		    if(this._onVisibleChangedEventHandlers == null) {
	            this._onVisibleChangedEventHandlers = new Array();
	        }
			this._onVisibleChangedEventHandlers.push(eventHandler);
			break;
	}
}

// TODO: RemoveEventHandler

/**
 * Disposes control's resources.
 */
Yahoo.Controls.Control.prototype.dispose = function() {

	this._disposing = true;

	// Dispose controls
	this._control_disposeControls();

}

/**
 * Hides the control.
 */
Yahoo.Controls.Control.prototype.hide = function() {

	this._frame.visible = false;
}

/**
 * Returns the specified client point in client (window) coordinate.
 * @param {Yahoo.Drawing.Point} point The point to convert.
 * @type Yahoo.Drawing.Point
 */
Yahoo.Controls.Control.prototype.pointToClient = function(point) {

	var item;
	var parent;
	var x;
	var y;
	
	// Start with the given point
	x = point.x;
	y = point.y;

	item = this.frame;

	if(item.superview!=null) {

		// Add the offset of the control's main frame
		if(item.hOffset!=-1) { x += item.hOffset; }
		if(item.vOffset!=-1) { y += item.vOffset; }

		// Get first parent
		parent = item.superview;
	
		// Loop all parents
		while(parent!=null) {
			if(parent instanceof Frame) {
				item = parent;
				if(item.hOffset!=-1) { x += item.hOffset; }
				if(item.vOffset!=-1) { y += item.vOffset; }
				parent = item.superview;
			}
			else {
				break;
			}
		}  // while parent
		
	}  //this.superview!=null

	return new Yahoo.Drawing.Point(x, y);
}

/**
 * Returns the specified client point in screen coordinate.
 * @param {Yahoo.Drawing.Point} point The point to convert.
 * @type Yahoo.Drawing.Point
 */
Yahoo.Controls.Control.prototype.pointToScreen = function(point) {

	var item;
	var parent;
	var x;
	var y;
	
	// Start with the given point
	x = point.x;
	y = point.y;

	item = this.frame;

	if(item.superview!=null) {

		// Add the offset of the control's main frame
		if(item.hOffset!=-1) { x += item.hOffset; }
		if(item.vOffset!=-1) { y += item.vOffset; }

		// Get first parent
		parent = item.superview;
	
		// Loop all parents
		while(parent!=null) {
			if(parent instanceof Frame) {
				item = parent;
				if(item.hOffset!=-1) { x += item.hOffset; }
				if(item.vOffset!=-1) { y += item.vOffset; }
				parent = item.superview;
			}
			else {
				break;
			}
		}  // while parent
		
	}  //this.superview!=null

	// Get window of last item in chain
	if(item.window!=null) {
		if(item.window.hOffset!=-1) { x += item.window.hOffset; }
		if(item.window.vOffset!=-1) { y += item.window.vOffset; }
	}
	
	return new Yahoo.Drawing.Point(x, y);
}

/**
 * Displays the control.
 */
Yahoo.Controls.Control.prototype.show = function() {

	this._frame.visible = true;
}

/*---------------------------------------------------------------------*/
// Public properties
/*---------------------------------------------------------------------*/
/**
 * Gets or sets the Control back color.
 * @type String
 */
Yahoo.Controls.Control.prototype.backColor getter = function() {

	return this._backColor;
}

Yahoo.Controls.Control.prototype.backColor setter = function(value) {

	if(value!=this._backColor) {
		this._backColor = value;
		this._onBackColorChanged(this, new Yahoo.EventArgs());
	}
}

/**
 * Gets the a rectangle that represents the control client area.
 * @type Yahoo.Drawing.Rectangle
 */
Yahoo.Controls.Control.prototype.clientRectangle getter = function() {

	// TODO: Check if we really should be adding the top/left
	if(this._disposing==false) {
		return new Yahoo.Drawing.Rectangle(this.left + this._frame.hOffset, this.top + this._frame.vOffset, this._frame.width, this._frame.height);
	}
}

Yahoo.Controls.Control.prototype.clientRectangle setter = function(value) {

	throw new Error("clientRectangle is read-only");
}

/**
 * Gets or sets the height and width of the client area.
 * @type Yahoo.Drawing.Size
 */
Yahoo.Controls.Control.prototype.clientSize getter = function() {

	if(this._disposing==false) {
		return new Yahoo.Drawing.Size(this._frame.width, this._frame.height);
	}
}

Yahoo.Controls.Control.prototype.clientSize setter = function(value) {

	throw new Error("clientSize is read-only");
}

/**
 * Gets the subcontrols contained in this control.
 * @type Array
 */
Yahoo.Controls.Control.prototype.controls getter = function() {

	return this._controls;
}

Yahoo.Controls.Control.prototype.controls setter = function(value) {

	throw new Error("controls is read-only");
}

/**
 * Gets or sets the font of the control.
 * @type Yahoo.Drawing.Font
 */
Yahoo.Controls.Control.prototype.defaultFont getter = function() {

	return new Yahoo.Drawing.Font("Arial", 12);
}

Yahoo.Controls.Control.prototype.defaultFont setter = function(value) {

	throw new Error("defaultFont is read-only");
}

/**
 * Gets the a rectangle that represents the control display area.
 * @type Yahoo.Drawing.Rectangle
 */
Yahoo.Controls.Control.prototype.displayRectangle getter = function() {

	return new Yahoo.Drawing.Rectangle(this.left, this.top, this.width, this.height);
}

Yahoo.Controls.Control.prototype.displayRectangle setter = function(value) {

	throw new Error("displayRectangle is read-only");
}

/**
 * Gets a value describing whether the control is disposing.
 * @type Boolean
 */
Yahoo.Controls.Control.prototype.disposing getter = function() {

	return this._disposing;
}

Yahoo.Controls.Control.prototype.disposing setter = function(value) {

	throw new Error("disposing is read-only");
}

/**
 * Gets or sets a value specifying whether the control is enabled.
 * @type Boolean
 */
Yahoo.Controls.Control.prototype.enabled getter = function() {

	return this._enabled;
}

Yahoo.Controls.Control.prototype.enabled setter = function(value) {

	if(value!=null) {
		if(this._enabled!=value) {
			this._enabled = value;
			
			this._onEnabledChanged(this, new Yahoo.EventArgs());
		}
	}
	else {
		throw new Yahoo.ArgumentNullException("value");
	}
}

/**
 * Gets or sets the font of the control.
 * @type Yahoo.Drawing.Font
 */
Yahoo.Controls.Control.prototype.font getter = function() {

	return this._font;
}

Yahoo.Controls.Control.prototype.font setter = function(value) {

	if(value!=this._font) {
		this._font = value;
		this._onFontChanged(this, new Yahoo.EventArgs());
	}
}

/**
 * Gets or sets the foreground color of the control.
 * @type String
 */
Yahoo.Controls.Control.prototype.foreColor getter = function() {

	return this._foreColor;
}

Yahoo.Controls.Control.prototype.foreColor setter = function(value) {

	if(value!=this._foreColor) {
		this._foreColor = value;
		this._onForeColorChanged(this, new Yahoo.EventArgs());
	}
}

/**
 * Gets the frame of the control.
 * @type Frame
 */
Yahoo.Controls.Control.prototype.frame getter = function() {

	return this._frame;
}

Yahoo.Controls.Control.prototype.frame setter = function(value) {

	throw new Error("frame is read-only");
}

/**
 * Gets a value indicating if this control has children.
 * @type Boolean
 */
Yahoo.Controls.Control.prototype.hasChildren getter = function() {

	if(this._controls.length>0) {
		return true;
	}
	else {
		return false;
	}
	return this._controls;
}

Yahoo.Controls.Control.prototype.hasChildren setter = function(value) {

	throw new Error("hasChildren is read-only");
}

/**
 * Gets or sets the x-coordinate of the left edge of this control.
 * @type Integer
 */
Yahoo.Controls.Control.prototype.left getter = function() {

	if(this._disposing==false) {
		return this._frame.hOffset;
	}
}

Yahoo.Controls.Control.prototype.left setter = function(value) {

	if(value!=null) {
		this._control_setLocation(value, this.top);
	}
	else {
		throw new Yahoo.ArgumentNullException("value");
	}
}

/**
 * Gets or sets the height of the control.
 * @type Integer
 */
Yahoo.Controls.Control.prototype.height getter = function() {

	if(this._disposing==false) {
		return this._frame.height;
	}
}

Yahoo.Controls.Control.prototype.height setter = function(value) {

	if(value!=null) {
	    if(this._frame.height != value) {
    		this._control_setSize(this._frame.width, value);
	    }
	}
	else {
		throw new Yahoo.ArgumentNullException("value");
	}
}

/**
 * Gets or sets the control frame's id.
 * @type String
 */
Yahoo.Controls.Control.prototype.id getter = function() {

	return this._frame.id;
}

Yahoo.Controls.Control.prototype.id setter = function(value) {

	this._frame.id = value;
}

/**
 * Gets or sets a value specifying opacity of the control.
 * @type Integer
 */
Yahoo.Controls.Control.prototype.opacity getter = function() {

	if(this._disposing==false) {
		return this._frame.opacity;
	}
}

Yahoo.Controls.Control.prototype.opacity setter = function(value) {

	if(value!=null) {
		if(this._frame.opacity!=value) {
			this._frame.opacity = value;
			this._onOpacityChanged(this, new Yahoo.EventArgs());
		}
	}
	else {
		throw new Yahoo.ArgumentNullException("value");
	}
}

/**
 * Gets or sets the parent of this control.
 * @type Yahoo.Controls.Control
 */
Yahoo.Controls.Control.prototype.parent getter = function() {

	return this._parent;
}

Yahoo.Controls.Control.prototype.parent setter = function(value) {

	if(value!=null) {
		this._parent = value;
	}
	else {
		throw new Yahoo.ArgumentNullException("value");
	}
}

/**
 * Gets or sets the width & height of the control.
 * @type Yahoo.Drawing.Size
 */
Yahoo.Controls.Control.prototype.size getter = function() {

	if(this._disposing==false) {
		return new Yahoo.Drawing.Size(this._frame.width, this._frame.height);
	}
}

Yahoo.Controls.Control.prototype.size setter = function(value) {

	if(value!=null) {
		this._control_setSize(value.width, value.height);
	}
	else {
		throw new Yahoo.ArgumentNullException("value");
	}
}

/**
 * Gets or sets the control text.
 * @type String
 */
Yahoo.Controls.Control.prototype.text getter = function() {

	return this._text;
}

Yahoo.Controls.Control.prototype.text setter = function(value) {

	if(this._text!=value) {
		this._text = value;
		this._onTextChanged(this, new Yahoo.EventArgs());
	}
}

/**
 * Gets or sets the control theme.
 * @type Yahoo.Controls.Theme
 */
Yahoo.Controls.Control.prototype.theme getter = function() {

	return this._theme;
}

Yahoo.Controls.Control.prototype.theme setter = function(value) {

	if(value!=null) {
		//if(this._theme!=value) {
			this._theme = value;
			this._onThemeChanged(this, new Yahoo.EventArgs());
		//}
	}
	else {
		throw new Yahoo.ArgumentNullException("value");
	}
}

/**
 * Gets or sets the tooltip displayed for this control.
 * @type String
 */
Yahoo.Controls.Control.prototype.toolTip getter = function() {

	return this._toolTip;
}

Yahoo.Controls.Control.prototype.toolTip setter = function(value) {

	if(value!=null) {
		if(this._toolTip!=value) {
			this._toolTip = value;
			this._onToolTipChanged(this, new Yahoo.EventArgs());
		}
	}
	else {
		this._toolTip = "";
	}
}

/**
 * Gets or sets the y-coordinate of the top edge of this control.
 * @type Integer
 */
Yahoo.Controls.Control.prototype.top getter = function() {

	if(this._disposing==false) {
		return this._frame.vOffset;
	}
}

Yahoo.Controls.Control.prototype.top setter = function(value) {

	if(value!=null) {
		this._control_setLocation(this.left, value);
	}
	else {
		throw new Yahoo.ArgumentNullException("value");
	}
}

/**
 * Gets or sets a value specifying whether the control is visible.
 * @type Boolean
 */
Yahoo.Controls.Control.prototype.visible getter = function() {

	if(this._disposing==false) {
		return this._frame.visible;
	}
}

Yahoo.Controls.Control.prototype.visible setter = function(value) {

	if(value!=null) {
		if(this._frame.visible!=value) {
			this._frame.visible = value;
			this._onVisibleChanged(this, new Yahoo.EventArgs());
		}
	}
	else {
		throw new Yahoo.ArgumentNullException("value");
	}
}

/**
 * Gets or sets the width of the control.
 * @type Integer
 */
Yahoo.Controls.Control.prototype.width getter = function() {

	if(this._disposing==false) {
		return this._frame.width;
	}
}

Yahoo.Controls.Control.prototype.width setter = function(value) {

	if(value!=null) {
	    if(this._frame.width != value) {
    		this._control_setSize(value, this._frame.height);
    	}
	}
	else {
		throw new Yahoo.ArgumentNullException("value");
	}
}

/**
 * Gets or sets the Window that contains this control.
 * @type Window
 */
Yahoo.Controls.Control.prototype.window getter = function() {

	if(this._disposing==false) {
		return this._frame.window;
	}
}

Yahoo.Controls.Control.prototype.window setter = function(value) {

	this._frame.window = value;
}

/**
 * Gets or sets the zOrder of this control.
 * @type Integer
 */
Yahoo.Controls.Control.prototype.zOrder getter = function() {

	if(this._disposing==false) {
		return this._frame.zOrder;
	}
}

Yahoo.Controls.Control.prototype.zOrder setter = function(value) {

	if(value!=null) {
		this._frame.zOrder = value;
	}
	else {
		throw new Yahoo.ArgumentNullException("value");
	}
}

