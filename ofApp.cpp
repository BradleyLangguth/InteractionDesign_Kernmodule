#include "ofApp.h"

#define PIN_LED 13
#define PIN_LDR 0

void ofApp::setup() 
{
	ofSetFrameRate(20);
	ofBackground(ofColor::black);

	gui.setup();
	gui.add(drawGrid.set("Grid", false));
	gui.add(useLight.set("Light", true));

	light.setDirectional();
	light.setDiffuseColor(ofColor::white);
	light.enable();

	// set listener - call ofApp::setupArduino when arduino is ready for use
	ofAddListener(arduino.EInitialized, this, &ofApp::setupArduino);

	// connect to the Arduino
	// use the same device name used in the Arduino IDE
	arduino.connect("COM3", 9600);
	arduino.sendFirmwareVersionRequest(); // workaround for ofArduino/firmata bug

	Width = 600;
	Height = 600;
	Length = 300;

	x = ofRandom(100, Width);
	y = ofRandom(100, Height);
	z = ofRandom(100, Length);

	speedX = (2);
	speedY = (2);
	speedZ = (2);


	radius = 20;
	color = ofColor::blueViolet;


	
}

void ofApp::setupArduino(const int& version) {
	// remove listener because we don't need it anymore
	ofRemoveListener(arduino.EInitialized, this, &ofApp::setupArduino);

	// print firmware name and version to the console
	ofLog() << "Arduino firmware found: " << arduino.getFirmwareName()
		<< " v" << arduino.getMajorFirmwareVersion() << "." << arduino.getMinorFirmwareVersion();

	arduino.sendDigitalPinMode(PIN_LED, ARD_OUTPUT);
	arduino.sendAnalogPinReporting(PIN_LDR, ARD_ANALOG);

	// set listeners for pin events
	ofAddListener(arduino.EDigitalPinChanged, this, &ofApp::digitalPinChanged);
	ofAddListener(arduino.EAnalogPinChanged, this, &ofApp::analogPinChanged);
}

void ofApp::update() 
{
	rotateX = rotateX + 1;
	rotateY += 2; // zelfde, maar korter dan rotateY = rotateY + 2
	rotateZ += 3;


	arduino.sendDigital(PIN_LED, ARD_HIGH);

	arduino.update();
	ofLog() << "isArduinoReady" << arduino.isArduinoReady() << endl;
	

	if (x < 100)
	{
		//cout << "links" << endl;
		x = 100;
		speedX = -speedX;
	}

	if (x > Width)
	{
		//cout << "rechts" << endl;
		x = Width;
		speedX = -speedX;

	}
	////////////////////

	if (y < 100) 
	{
		//cout << "boven" << endl;
		y = 100;
		speedY = -speedY;
	}

	if (y > Height)
	{
		//cout << "onder" << endl;
		y = Height;
		speedY = -speedY;
	}
	/////////////////

	if (z < 0)
	{
		z = 0;
		speedZ = -speedZ;
	}

	if (z > Length)
	{
		z = Length;
		speedZ = -speedZ;
	}

	x += speedX;
	y += speedY;
	z += speedZ;


}

void ofApp::draw() 
{
	ofEnableDepthTest();

	cam.setVFlip(true);
	cam.begin();

	if (useLight) {
		ofEnableLighting();
	}
	else {
		ofDisableLighting();
	}

	if (drawGrid) ofDrawGrid(200);

	cam.end();
	ofDisableDepthTest();

	if (drawGui) {
		ofDisableLighting();
		gui.draw();
	}

	////////////////


	ofSetColor(color);
	ofDrawSphere(x, y, z, radius);


	/////////////////


	ofTranslate(ofGetWidth() / 2, ofGetHeight() / 2);

	if (doRotate) {
		//ofRotateXDeg(rotateX);
		ofRotateYDeg(rotateY);
		//ofRotateZDeg(rotateZ);
	}

	if (drawGrid2) {
		ofDrawGrid(200);
	}

	ofSetColor(ofColor::yellow);
	ofDrawSphere(0, 0, 0, 100);

	ofSetColor(ofColor::blue);
	ofDrawSphere(200, 0, 0, 50);
}





void ofApp::digitalPinChanged(const int& pinNum) 
{
	// get value with arduino.getDigital(pinNum)
	ofLogNotice() << "Digital Pin " << pinNum << " value: " << arduino.getDigital(pinNum) << endl;
}

void ofApp::analogPinChanged(const int& pinNum) 
{
	// get value with arduino.getAnalog(pinNum));
	ofLogNotice() << "Analog Pin " << pinNum << " value: " << arduino.getAnalog(pinNum) << endl;
}


void ofApp::mousePressed(int x, int y, int button) 
{
	// switch the LED on
	arduino.sendDigital(PIN_LED, ARD_HIGH);
	doRotate = !doRotate;
	drawGrid2 = !drawGrid;
	useLight = !useLight;
	cout << "aan" << endl;
}

void ofApp::mouseReleased(int x, int y, int button) 
{
	// switch the LED off
	arduino.sendDigital(PIN_LED, ARD_LOW);
	cout << "uit" << endl;
}

