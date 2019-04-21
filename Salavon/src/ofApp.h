#pragma once

#include "ofMain.h"
#include "ofxDelaunay.h"
#include "ofxGui.h"
class ofApp : public ofBaseApp{

  public:
    ofxDelaunay triangulation;
    int drawY;
    std::map<string, ofColor> colorLookup;
    vector<ofColor> colors;
    string title;
    int go;
    bool bHide;

    ofxColorSlider color;
    ofxPanel gui;

    ofPoint prevPos;
    ofMesh mesh;
    ofImage image;
    ofEasyCam easyCam;

		void setup();
		void update();
    void draw();
    void init(string file, string title, int theme);

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
