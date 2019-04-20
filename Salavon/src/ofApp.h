#pragma once

#include "ofMain.h"
#include "ofxDelaunay.h"
#include "ofxGui.h"
class ofApp : public ofBaseApp{

  public:
    ofxDelaunay triangulation;
  int drawY;

  // in the h file:
  ofTrueTypeFont myfont;

		void setup();
		void update();
		void draw();
  int go;
  
  bool bHide;

  ofxFloatSlider radius;
  ofxColorSlider color;

  
  ofxVec2Slider center;
  ofxIntSlider circleResolution;
  ofxToggle filled;
  ofxButton twoCircles;
  ofxButton ringButton;
  ofxLabel screenSize;

  ofxPanel gui;
  vector<ofColor> triangleColors;

  ofPoint prevPos;
    ofMesh mesh;
    ofImage image;
    ofEasyCam easyCam;

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
		
};
