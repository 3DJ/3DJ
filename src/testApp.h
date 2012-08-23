#pragma once

#include "ofMain.h"
#include "ofxKinect.h"
#include "World.h"

// uncomment this to read from two kinects simultaneously
//#define USE_TWO_KINECTS

class testApp : public ofBaseApp {

  void cleanUp();

 public:
	
	void setup();
	void update();
	void draw();
	void exit();
	
	void keyPressed(int key);
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void windowResized(int w, int h);
	
  World * g_world; // world to hold and test all buttons, etc
	
	// used for viewing the point cloud
	ofLight light;
};