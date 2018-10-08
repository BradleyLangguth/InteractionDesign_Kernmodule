#pragma once

#include "ofMain.h"
#include "ofEvents.h"
#include "ofxGui.h"

class ofApp : public ofBaseApp {

public:
	void setup();
	void update();
	void draw();

	void mousePressed(int x, int y, int button);

	void mouseReleased(int x, int y, int button);
		
	ofxPanel gui;

	ofParameter<bool> drawGrid;
	ofParameter<bool> useLight;
	ofParameter<bool> doRotate;

	bool drawGui = true;

	ofLight light;
	ofEasyCam cam;

private:

	float x;
	float y;
	float z;

	float speedX;
	float speedY;
	float speedZ;

	float Width;
	float Length;
	float Height;

	int radius;


	//bool doRotate;


	ofColor color;

	ofArduino arduino;

	void setupArduino(const int& version);

	void digitalPinChanged(const int& pinNum);

	void analogPinChanged(const int& pinNum);

	float rotateX;
    float rotateY;
    float rotateZ;
};