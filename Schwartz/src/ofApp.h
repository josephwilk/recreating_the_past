#pragma once

#include "ofMain.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

    int res;
    int resx;
    int resy;
    ofMesh buildMesh(int x, int y, int z, int size);

    vector<ofMesh> pyramids;
    vector<ofColor> colors;

    ofEasyCam mainCam;

    ofVideoGrabber cam;
    ofPixels pix;
    vector<ofVec3f> offsets;
    ofTexture mTex;
    ofLight light;
  
    
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
