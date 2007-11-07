/*---------------------------------------------------------------------*/
/// <copyright from='2005' to='2007' company='Yahoo! Inc.'>
/// (C) Copyright 2005-2007 Yahoo! Inc. All Rights Reserved.
/// </copyright>

/**
 * Library management class for a local (non-shared) installation of library. Does not support modifying the library.
 */
/*---------------------------------------------------------------------*/
// Constructor
/*---------------------------------------------------------------------*/
// Create namespace Yahoo.Utility if it doesn't already exist
if(Yahoo==undefined) { var Yahoo = new Object() }
if(Yahoo.Utility==undefined) { Yahoo.Utility = new Object() }

/**
 * Default constructor.
 * @constructor
 * @param {String} libraryPath The path to the library root folder.
 */
Yahoo.Utility.Library = function(libraryPath) {

	if(arguments.length > 0) {
		this.initialize(libraryPath);
	}  //arguments.length > 0
}

/*---------------------------------------------------------------------*/
// Global constants
/*---------------------------------------------------------------------*/
// These are defined here to provide hardcoded default settings to all items in the library
Yahoo.Utility.Library.prototype.defaultTheme = "Purple";

/*---------------------------------------------------------------------*/
// Private code
/*---------------------------------------------------------------------*/
/*---------------------------------------------------------------------*/
// Public code
/*---------------------------------------------------------------------*/
/**
 * True constructor. Must be called if this class is overridden.
 * @param {String} libraryPath The path to the library root folder.
 */
Yahoo.Utility.Library.prototype.initialize = function(libraryPath) {

	if(libraryPath!="") {
		this._libraryPath = libraryPath;

	}  // libraryPath = ""
	else {
		throw new Error("Required parameter 'libraryPath' missing.");
	}  // libraryPath = ""

}

/**
 * Includes the given class into the currently running widget.
 * @param {String} className The full name of the class to include into the currently running widget.
 * @param {String} version The version of the class to include into the currently running widget.
 * @param {Boolean} exactVersion A value indicating whether the exact version should be included. If false, the latest version will be used.
 */
Yahoo.Utility.Library.prototype.include = function(className, version, exactVersion) {

	var classPath;
	var classExists;

	if(className!="") {
		// Check if the given class has already been included
		try {
			if(eval(className)==undefined) {
				classExists = false
			}
			else {
				classExists = true;
			}  // className==undefined
		}  // try
		catch(e) {
			classExists = false;
		}
		
		if(classExists==false) {
		
			classPath = this.getClass(className, version, exactVersion)
			
			if(classPath!="") {
				include(classPath);
			}  // classPath!=""
			
		}  // class already included
	}  // className = ""
	else {
		throw new Error("Required parameter 'className' missing.");
	}  // className = ""
		
	return classPath;
}

/**
 * Gets the path to the class to include.
 * @param {String} className The full name of the class to get the file name for.
 * @param {String} version Not implemented! This parameter is only used in the shared version of this class.
 */
Yahoo.Utility.Library.prototype.getClass = function(className, version) {

	var count;
	var classPath;
	var names;
	var library;
	var fullPath = "";
	var dirContents;
	var file;
	var versions;
	var result = "";

	if(className!="") {

		// Get full path to folder where this class should be located
		classPath = this._libraryPath;

		names = className.split(".");
		for(count=0; count<names.length-1; count++) {
			classPath += "/" + names[count];
		}
		
		// Get library name (without version or file extension)
		library = names[names.length-1];

        version = __LIBRARY_VERSION__;
		fullPath = classPath + "/" + library + ".v" + version.toFixed(2) + ".js";			
		result = fullPath;

	}  // className = ""
	else {
		throw new Error("Required parameter 'className' missing.");
	}  // className = ""

	return result;
}

/**
 * Gets the path to the class resources.
 * @param {String} className The full name of the class to get the path to resources.
 * @param {String} version The version of the class to get the path to resources.
 */
Yahoo.Utility.Library.prototype.getClassResourcePath = function(className, version) {

	var count;
	var classPath;
	var fullPath = "";
	var dirContents;
	var folder;
	var versions;
	var result = "";

	if(className!="") {

		// Get full path to folder where the resources for this class should be located
		classPath = this._libraryPath + "/" + className.replace(/\./g, "/") + "/res";
		
		// Path is in the form "library/my/name/space/res/1.00"
        version = __LIBRARY_VERSION__;
		fullPath = classPath + "/" + version.toFixed(2);
		result = fullPath;

	}  // className = ""
	else {
		throw new Error("Required parameter 'className' missing.");
	}  // className = ""

	return result;
}

/*---------------------------------------------------------------------*/
// Public properties
/*---------------------------------------------------------------------*/
/**
 * Gets the base path for libraries.
 * @type String
 */
Yahoo.Utility.Library.prototype.libraryPath getter = function() {

	return this._libraryPath;
}

Yahoo.Utility.Library.prototype.libraryPath setter = function() {

	throw new Error("libraryPath is read-only.");
	
}

