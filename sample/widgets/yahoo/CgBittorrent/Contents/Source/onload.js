var updateCounter = 0;
var trayState = preferences.trayState.value;
var vitalityDoc = XMLDOM.parse( filesystem.readFile( "Source/vitality.xml" ) );

function doTray() {

	if (trayState == "open") {
	
		userShadow.opacity = 0;
		user.opacity = 0;
		userDataShadow.opacity = 0;
		userData.opacity = 0;
		
		sysShadow.opacity = 0;
		sys.opacity = 0;
		sysDataShadow.opacity = 0;
		sysData.opacity = 0;
	
		trayRight.slide("left", 100, 2);
		trayLeft.opacity = 0;
		trayButton.src = "Images/Open.png";
		mainWindow.width = 77;
		trayState = preferences.trayState.value = "closed";
	} else {
		mainWindow.width = 169;
		trayLeft.opacity = 255;
		trayRight.slide("right", 100, 2);
		
		userShadow.opacity = 255;
		user.opacity = 255;
		userDataShadow.opacity = 255;
		userData.opacity = 255;
		
		sysShadow.opacity = 255;
		sys.opacity = 255;
		sysDataShadow.opacity = 255;
		sysData.opacity = 255;
		trayButton.src = "Images/Close.png";
		trayState = preferences.trayState.value = "open";
	}
}

var fadeVitality = function() {
	var doc = vitalityDoc;
	
	doc.getElementById('miniTen').setAttribute("src", ten.src);
	doc.getElementById('miniOne').setAttribute("src", one.src);
	var adjustedOpacity = red.opacity/255;
	doc.getElementById('miniRed').setAttribute("style", "opacity: " + adjustedOpacity + ";" );

	widget.setDockItem(doc,"fade");

	vitalityChange = updateVitality;
}

var updateVitality = function() {
	var doc = vitalityDoc;
	
	doc.getElementById('miniTen').setAttribute("src", ten.src);
	doc.getElementById('miniOne').setAttribute("src", one.src);
	var adjustedOpacity = red.opacity/255;
	doc.getElementById('miniRed').setAttribute("style", "opacity: " + adjustedOpacity + ";" );

	widget.setDockItem(doc);
}

function doCalc(){
	red.opacity = system.cpu.activity * 2.55;
	cpuString = String(system.cpu.activity);
	
 	if (cpuString.length == 1) {
		cpuString = "b" + String(cpuString);
	} else if (cpuString.length == 3) {
		cpuString = "bb";
	}
	
	if (cpuString == "b0") {
		cpuString = "bb";
	}

	ten.src = "Images/" + cpuString.substr(0,1) + ".png";
	one.src = "Images/" + cpuString.substr(1,1) + ".png";
	userDataShadow.text = userData.text = system.cpu.user + "%";
	sysDataShadow.text = sysData.text = system.cpu.sys + "%";

	vitalityChange();

}

if (trayState == "closed") {
	userShadow.opacity = user.opacity = 0;
	userDataShadow.opacity = userData.opacity = 0;
	sysShadow.opacity = sys.opacity = 0;
	sysDataShadow.opacity = sysData.opacity = 0;
	trayRight.slide("left", 100, 2);
	trayLeft.opacity = 0;
	trayButton.src = "Images/Open.png";
	mainWindow.width = 77;
}

// the first vitality change is a fade; the rest are flickers
var vitalityChange = fadeVitality;
cpuTicker.interval = preferences.updateFrequency.value;
doCalc();
mainWindow.visible = true;