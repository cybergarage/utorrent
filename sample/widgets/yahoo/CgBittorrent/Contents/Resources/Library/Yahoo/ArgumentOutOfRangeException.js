/*---------------------------------------------------------------------*/
/// <copyright from='2005' to='2006' company='Yahoo! Inc.'>
/// (C) Copyright 2005-2006 Yahoo! Inc. All Rights Reserved.
/// </copyright>

/**
 * The exception that is thrown when an argument is outside the valid range for the method.
 */
/*---------------------------------------------------------------------*/

/*---------------------------------------------------------------------*/
// Namespace
/*---------------------------------------------------------------------*/
// Create namespace Yahoo if it doesn't already exist
if(Yahoo==undefined) { var Yahoo = new Object() }

/*---------------------------------------------------------------------*/
// Constructor
/*---------------------------------------------------------------------*/
/**
 * Default constructor.
 * @constructor
 * @param {String} paramName The name of the parameter.
 * @param {String} message The error text for this exception.
 */
Yahoo.ArgumentOutOfRangeException = function(paramName, message) {

	this.initialize(paramName, message);
}

/**
 * Define inheritance chain.
 */
Yahoo.ArgumentOutOfRangeException.prototype = new Error();
Yahoo.ArgumentOutOfRangeException.prototype.constructor = Yahoo.ArgumentOutOfRangeException ;
Yahoo.ArgumentOutOfRangeException.prototype.baseclass = Error.prototype;

/*---------------------------------------------------------------------*/
// Public code
/*---------------------------------------------------------------------*/
/**
 * True constructor. Must be called if this class is overridden.
 * @param {String} paramName The name of the parameter.
 * @param {String} message The error text for this exception.
 */
Yahoo.ArgumentOutOfRangeException.prototype.initialize = function(paramName, message) {

	this.paramName = paramName;
	if(message!=null && message!="") {
		this.message = message;
	}
	else {
		this.message = paramName;
	}
	this.name = "ArgumentOutOfRangeException ";
}
