#include "ofApp.h"

#define PIN_LED 13

void ofApp::setup() 
{
	ofSetFrameRate(20);
	

	gui.setup();
	gui.add(drawGrid.set("Grid", false));
	gui.add(useLight.set("Light", true));
	gui.add(doRotate.set("Rotation", true));

	light.setDirectional();
	light.setDiffuseColor(ofColor::white);
	light.enable();

	ofBackground(ofColor::black);

	// set listener - call ofApp::setupArduino when arduino is ready for use
	ofAddListener(arduino.EInitialized, this, &ofApp::setupArduino);

	// connect to the Arduino
	// use the same device name used in the Arduino IDE
	arduino.connect("COM3", 9600);
	//arduino.sendFirmwareVersionRequest(); // workaround for ofArduino/firmata bug

	Width = 150;
	Height = 150;
	Length = 150;

	x = ofRandom(-100, Width);
	y = ofRandom(-100, Height);
	z = ofRandom(0, Length);

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

	// set listeners for pin events
	ofAddListener(arduino.EDigitalPinChanged, this, &ofApp::digitalPinChanged);
	ofAddListener(arduino.EAnalogPinChanged, this, &ofApp::analogPinChanged);
}

void ofApp::update() 
{
	//rotateX = rotateX + 1;
	//rotateY = 200;
	rotateY += 2; // zelfde, maar korter dan rotateY = rotateY + 2
	//rotateZ += 3;

	arduino.update();
	ofLog() << "isArduinoReady" << arduino.isArduinoReady() << endl;
	

	if (x < -150)
	{
		//cout << "links" << endl;
		x = -150;
		speedX = -speedX;
	}

	if (x > Width)
	{
		//cout << "rechts" << endl;
		x = Width;
		speedX = -speedX;

	}
	////////////////////

	if (y < -150)
	{
		//cout << "boven" << endl;
		y = -150;
		speedY = -speedY;
	}

	if (y > Height)
	{
		//cout << "onder" << endl;
		y = Height;
		speedY = -speedY;
	}
	/////////////////

	if (z < -150)
	{
		z = -150;
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
	//arduino.sendDigital(PIN_LED, ARD_HIGH);

	gui.draw();

	ofTranslate(ofGetWidth() / 2, ofGetHeight() / 2);

	ofEnableDepthTest();

	

	//cam.setVFlip(true);
	//cam.begin();

	if (useLight) 
	{
		ofEnableLighting();
	}
	else 
	{
		ofDisableLighting();
	}

	if (drawGui) 
	{
		ofDisableLighting();
	}

	////////////////


	ofSetColor(color);
	ofDrawSphere(x, y, z, radius);


	/////////////////


	

	if (doRotate)
	{
		//ofRotateXDeg(rotateX);
		ofRotateYDeg(rotateY);
		//ofRotateZDeg(rotateZ);
	}

	if (drawGrid) 
	{
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
	ofLogNotice() << "Digital Pin " << PIN_LED << " value: " << arduino.getDigital(PIN_LED) << endl;
}

void ofApp::analogPinChanged(const int& pinNum) 
{
	// get value with arduino.getAnalog(pinNum));
	ofLogNotice() << "Analog Pin " << PIN_LED << " value: " << arduino.getAnalog(PIN_LED) << endl;
}


void ofApp::mousePressed(int x, int y, int button) 
{
	// switch the LED on
	//doRotate = !doRotate;
	
	//useLight = !useLight;
	//drawGrid = !drawGrid;
	arduino.sendDigital(PIN_LED, ARD_HIGH);
	cout << "aan" << endl;
}

void ofApp::mouseReleased(int x, int y, int button) 
{
	// switch the LED off
	arduino.sendDigital(13, ARD_LOW);
	cout << "uit" << endl;
}

