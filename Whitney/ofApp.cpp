#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
  ofBackground(0, 0, 0);
  ofEnableAntiAliasing();

  //Purposely add a little stop animation feel through low frames per second
  ofSetFrameRate(20);

  midiOut.openPort("IAC Bus 1");
  play = ofGetElapsedTimef();
  sender.setup("192.168.1.64", 4559);
  m.setAddress("/edrum0");
  sender.sendMessage(m);
  m.clear();

  midiOut.sendNoteOn(1, 50,  100); //D3
  midiOut.sendControlChange(1, 100, 0);

  post.init(ofGetWidth(), ofGetHeight());

  //Warmth, fuzz and glow of the cathoray tube
  post.createPass<RGBShiftPass>();
  post.createPass<FxaaPass>();
  post.createPass<BloomPass>();
  post.createPass<TubePass>();

}

//--------------------------------------------------------------
void ofApp::update(){
  timeBandit = (sin(ofGetElapsedTimef() * 0.05) * 0.3) +0.3;
  time = ofGetElapsedTimef() * 0.5f * timeBandit;
  scale = ofGetElapsedTimef() * 0.05f;
  color = ofGetElapsedTimef() * 0.001f;
}

//--------------------------------------------------------------
void ofApp::draw(){
  float seed;
  post.begin();
  float size1=2;
  float size2=2;
  float size3=2;
  float size=0;
  float sizeFactor = 0.8*time+10;
  for(int i=0; i < 24; i++){
    if((i%3) == 0){ size1 = size1+sizeFactor; size = size1;}
    if((i%3) == 1){ size2 = size2+sizeFactor; size = size2; }
    if((i%3) == 2){ size3 = size3+sizeFactor; size = size3; }
    hex(i,size);
  }
  post.end();
}

void ofApp::hex(int id, float hex_radius){
  float x_margin = 500;
  float y_margin = 400;
  float x_amp = 420.0f;
  float y_amp = 320.0f;
  float horz_lobes=3.0f;
  float vert_lobes=2.0f;
  float offset= sin(time*0.1+id*0.05)*(1.5);

  if((time-play) > 0.1f || (play-time)> 0.1f){
    midiOut.sendControlChange(1, 102, ofMap(timeBandit, 0.0, 0.3, 0, 10)); //sample
    midiOut.sendControlChange(1, 103, ofMap(timeBandit, 0.0, 0.3, 0.0, 127)); //sample
//    if(offset > 0.0){
//       order
//      midiOut.sendControlChange(1, 103, 0);
//    }
//    else{
//      midiOut.sendControlChange(1, 103, ofMap(timeBandit, 0.0, 0.3, 0.0, 127));
//      midiOut.sendControlChange(1, 102, 0);
//    }

    midiOut.sendControlChange(1, 100, ofMap(offset, -1.5, 1.5, 0.0, 127));
    midiOut.sendControlChange(1, 99,  ofMap(time, 0.0, 10.0, 10, 127));
    midiOut.sendControlChange(1, 101, ofMap(hex_radius, 0.0, 200.0, 0, 127));
    play = time;

    m.setAddress("/edrum0");
    m.addFloatArg(0.1f);
    sender.sendMessage(m);
    m.clear();
  }

  ofPushMatrix();
  ofSetPolyMode(OF_POLY_WINDING_ODD);
  ofSetLineWidth(4.0f);

  if((id % 3) == 0){
    ofTranslate((x_amp * sin(horz_lobes*time+ (PI/2.0)*6 + offset))+x_margin,
                y_amp *  sin(vert_lobes*time             +offset) +y_margin);

  }else if((id % 3) == 1){
    ofTranslate((x_amp * sin(horz_lobes*time+ (PI/2.0)*12 + offset) +x_margin),
                 y_amp * sin(vert_lobes*time             +offset) +y_margin);

  }
  else if((id % 3) == 2){

   ofTranslate((x_amp * sin(horz_lobes*time + (PI/3.0)*4+ offset))+x_margin,
                y_amp * sin(vert_lobes*time  +offset) + y_margin);


  }

  ofSetColor(255, 120, 220);
  ofNoFill();
  ofBeginShape();

  for (int deg = 0; deg < 360; deg += 60) {
    ofVertex(hex_radius * cos(deg * DEG_TO_RAD+55),
             hex_radius * sin(deg * DEG_TO_RAD+55));
  }
  ofEndShape(true);
  ofPopMatrix();
}
