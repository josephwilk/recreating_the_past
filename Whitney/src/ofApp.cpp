#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
  ofBackground(0, 0, 0);
  ofEnableAntiAliasing();

  post.init(ofGetWidth(), ofGetHeight());
  post.createPass<FxaaPass>();
  post.createPass<BloomPass>();
  post.createPass<RGBShiftPass>();
  post.createPass<TubePass>();
}

//--------------------------------------------------------------
void ofApp::update(){
  time = ofGetElapsedTimef() * (sin(ofGetElapsedTimef()*0.05)*0.5)+0.5;
  scale = ofGetElapsedTimef()*0.05f;
  color = ofGetElapsedTimef()*0.001f;
}

//--------------------------------------------------------------
void ofApp::draw(){
  float seed;
  post.begin();
  for(int i=0; i < 20; i++){
    hex(i*2,i*2);
  }
  post.end();
}

void ofApp::hex(int x, int y){
  float tmp_radius = x*0.5f + (sin(scale+x)*80);
  ofPushMatrix();
  ofSetPolyMode(OF_POLY_WINDING_ODD);
  ofTranslate((((sin(time+x*2)*0.5)+0.5)*512+10*x)+100,
                (cos(time-x*2)*0.5+0.5f)*400 + 10*x);
  ofSetColor(255*(sin(color)*0.5+0.5)+10,255*(sin(color)*0.5+0.5)+10,255*(sin(color)*0.5+0.5)+10);
  ofNoFill();


  ofBeginShape();
  for (int deg = 0; deg < 360; deg += 60) {
    ofVertex(tmp_radius * cos(deg * DEG_TO_RAD), tmp_radius * sin(deg * DEG_TO_RAD));
  }

  ofEndShape(true);
  ofPopMatrix();
}




//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
