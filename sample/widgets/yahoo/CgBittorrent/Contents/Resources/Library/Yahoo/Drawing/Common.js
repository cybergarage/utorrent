/*---------------------------------------------------------------------*/
/// <copyright from='2005' to='2006' company='Yahoo! Inc.'>
/// (C) Copyright 2005-2006 Yahoo! Inc. All Rights Reserved.
/// </copyright>

/**
 * Defines a format for text.
 */
/*---------------------------------------------------------------------*/
/*---------------------------------------------------------------------*/
// Constructor
/*---------------------------------------------------------------------*/
// Create namespace Yahoo.Drawing if it doesn't already exist
if(Yahoo==undefined) { var Yahoo = new Object(); }
if(Yahoo.Drawing==undefined) { Yahoo.Drawing = new Object(); }
if(Yahoo.Drawing.Common==undefined) { Yahoo.Drawing.Common = new Object(); }

/**
 * Default constructor.
 * @constructor
 * @param {String} familyName The font family name of this font object.
 * @param {String} size The size of this font.
 */
Yahoo.Drawing.Font = function(familyName, size) {

	//log("Font.ctor()");
	if(arguments.length>0) {
		this.initialize(familyName, size);
	}
}

/*---------------------------------------------------------------------*/
// Public code
/*---------------------------------------------------------------------*/
/**
 * True constructor. Must be called if this class is overridden.
 * @param {String} familyName The font family name of this font object.
 * @param {String} size The size of this font.
 */
Yahoo.Drawing.Font.prototype.initialize = function(familyName, size) {

	//log("Font.initialize()");

	if(familyName==null || size==null) {
		throw new Yahoo.ArgumentNullException();
	}
	
	else {

		this._name = familyName;	
		this._size = parseInt(size);
	}  // arguments == null
}

/**
 * Returns a human-readable version of this object.
 */
Yahoo.Drawing.Font.prototype.toString = function() {

	return "[name=" + this.name + ", size=" + this.size + "]";
}

/*---------------------------------------------------------------------*/
// Public properties
/*---------------------------------------------------------------------*/
/**
 * Gets the family of this font.
 * @type String
 */
Yahoo.Drawing.Font.prototype.name getter = function() {

	return this._name;
}

Yahoo.Drawing.Font.prototype.name setter = function(value) {

	throw new Error("name is read-only");
}

/**
 * Gets the size of this font.
 * @type Integer
 */
Yahoo.Drawing.Font.prototype.size getter = function() {

	return this._size;
}

Yahoo.Drawing.Font.prototype.size setter = function(value) {

	throw new Error("size is read-only");
}

/*---------------------------------------------------------------------*/
/// <copyright from='2005' to='2006' company='Yahoo! Inc.'>
/// (C) Copyright 2005-2006 Yahoo! Inc. All Rights Reserved.
/// </copyright>

/**
 * Stores a set of numbers describing a two-dimensional location.
 */
/*---------------------------------------------------------------------*/

/**
 * Default constructor.
 * @constructor
 * @param {Integer} x The x-coordinate of this point.
 * @param {Integer} y The y-coordinate of this point.
 */
Yahoo.Drawing.Point = function(x, y) {
	this.x = x;
	this.y = y;
}

Yahoo.Drawing.Point.prototype.toString = function() {
	return "{x=" + this.x + ", y=" + this.y + "}";
}

/*---------------------------------------------------------------------*/
/// <copyright from='2005' to='2006' company='Yahoo! Inc.'>
/// (C) Copyright 2005-2006 Yahoo! Inc. All Rights Reserved.
/// </copyright>

/**
 * Stores a set of numbers describing the location and size of a rectangle.
 */
/*---------------------------------------------------------------------*/

/*---------------------------------------------------------------------*/
// Constructor
/*---------------------------------------------------------------------*/
/**
 * Default constructor.
 * @constructor
 * @param {Integer} x The x-coordinate of this rectangle.
 * @param {Integer} y The y-coordinate of this rectangle.
 * @param {Integer} width The width of the rectangle.
 * @param {Integer} height The height of the rectangle.
 */
Yahoo.Drawing.Rectangle = function(x, y, width, height) {
	this._x = x;
	this._y = y;
	this.width = width;
	this.height = height;
}

/*---------------------------------------------------------------------*/
// Public code
/*---------------------------------------------------------------------*/
/**
 * Returns a value indicating whether the given co-ordinates are within the rectangle.
 * @param {Integer} x The x-coordinate of the point to check.
 * @param {Integer} y The y-coordinate of the point to check.
 * @type Boolean
 */
Yahoo.Drawing.Rectangle.prototype.contains = function(x, y) {

	var result = false;

	if((this.x <= x) && (x <= (this.x + this.width)) && (this.y <= y) && (y < (this.y + this.height))) {
		result = true
	}

	return result;
}

/**
 * Returns the object in a human-readable format.
 */
Yahoo.Drawing.Rectangle.prototype.toString = function() {

	return "{x=" + this.x + ", y=" + this.y + ", width=" + this.width + ", height=" + this.height + "}";
}

/*---------------------------------------------------------------------*/
// Public properties
/*---------------------------------------------------------------------*/
/**
 * Gets or sets the x-coordinate of this Rectangle.
 * @type Integer
 */
Yahoo.Drawing.Rectangle.prototype.x getter = function() {

	return this._x;
}

Yahoo.Drawing.Rectangle.prototype.x setter = function(x) {

	this._x = x;
}

/**
 * Gets or sets the y-coordinate of this Rectangle.
 * @type Integer
 */
Yahoo.Drawing.Rectangle.prototype.y getter = function() {

	return this._y;
}

Yahoo.Drawing.Rectangle.prototype.y setter = function(y) {

	this._y = y;
}

/**
 * Gets the x-coordinate of the top-left corner of this Rectangle.
 * @type Integer
 */
Yahoo.Drawing.Rectangle.prototype.left getter = function() {

	return this._x;
}

Yahoo.Drawing.Rectangle.prototype.left setter = function() {

	throw new Error("'left' is read-only");
}

/**
 * Gets the y-coordinate of the top edge of this Rectangle.
 * @type Integer
 */
Yahoo.Drawing.Rectangle.prototype.top getter = function() {

	return this._x;
}

Yahoo.Drawing.Rectangle.prototype.top setter = function() {

	throw new Error("'top' is read-only");
}

/**
 * Gets the x-coordinate of the right edge of this Rectangle.
 * @type Integer
 */
Yahoo.Drawing.Rectangle.prototype.right getter = function() {

	return this._x + this.width;
}

Yahoo.Drawing.Rectangle.prototype.right setter = function() {

	throw new Error("'right' is read-only");
}

/**
 * Gets the y-coordinate of the bottom edge of this Rectangle.
 * @type Integer
 */
Yahoo.Drawing.Rectangle.prototype.bottom getter = function() {

	return this._y + this.height;
}

Yahoo.Drawing.Rectangle.prototype.bottom setter = function() {

	throw new Error("'bottom' is read-only");
}

/*---------------------------------------------------------------------*/
/// <copyright from='2005' to='2006' company='Yahoo! Inc.'>
/// (C) Copyright 2005-2006 Yahoo! Inc. All Rights Reserved.
/// </copyright>

/**
 * Stores a set of numbers describing the size of a rectangle.
 */
/*---------------------------------------------------------------------*/
/**
 * Default constructor.
 * @constructor
 * @param {Integer} width The width of the size object.
 * @param {Integer} height The height of the size object.
 */
Yahoo.Drawing.Size = function(width, height) {
	this.width = width;
	this.height = height;
}

Yahoo.Drawing.Size.prototype.toString = function() {
	return "{width=" + this.width + ", height=" + this.height + "}";
}
