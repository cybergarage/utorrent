/*---------------------------------------------------------------------*/
/// <copyright from='2005' to='2006' company='Yahoo! Inc.'>
/// (C) Copyright 2005-2006 Yahoo! Inc. All Rights Reserved.
/// </copyright>

/**
 * The exception that is thrown when an argument is outside the valid range for an enumerator.
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
 * @param {String} type The type of the enumeration this exception is related to.
 */
Yahoo.InvalidEnumArgumentException = function(paramName, message, type) {

	this.initialize(paramName, message, type);
}

/**
 * Define inheritance chain.
 */
Yahoo.InvalidEnumArgumentException.prototype = new Error();
Yahoo.InvalidEnumArgumentException.prototype.constructor = Yahoo.InvalidEnumArgumentException ;
Yahoo.InvalidEnumArgumentException.prototype.baseclass = Error.prototype;

/*---------------------------------------------------------------------*/
// Public code
/*---------------------------------------------------------------------*/
/**
 * True constructor. Must be called if this class is overridden.
 * @param {String} paramName The name of the parameter.
 * @param {String} message The error text for this exception.
 * @param {String} type The type of the enumeration this exception is related to.
 */
Yahoo.InvalidEnumArgumentException.prototype.initialize = function(paramName, message, type) {

	this.paramName = paramName;
	if(message!=null && message!="") {
		this.message = message;
	}
	else {
		this.message = paramName;
	}
	this.name = "InvalidEnumArgumentException ";
	this.type = type;
}
