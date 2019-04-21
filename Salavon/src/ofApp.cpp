#include "ofApp.h"


void ofApp::init(string file, string newTitle, int theme){
  image.load(file);
  triangulation.reset();
  colors.clear();

  title=newTitle;

  //Kolor Themes
  if(theme==0){
    colors.push_back(ofColor(242,133,153,255)); //pink
    colors.push_back(ofColor(242,92,147,255));
    colors.push_back(ofColor(63,191,191,255));
    colors.push_back(ofColor(242,209,179,255));
    colors.push_back(ofColor(242,181,167,255));
  }
  if(theme==1){
    colors.push_back(ofColor(30, 45, 89));
    colors.push_back(ofColor( 91, 146, 217));
    colors.push_back(ofColor( 128, 189, 242));
    colors.push_back(ofColor( 126, 161, 191));
    colors.push_back(ofColor( 167, 213, 242));
  }

  vertexCount=0;
  drawY=20;

  float intensityThreshold = 100;
  int w = image.getWidth();
  int h = image.getHeight();

  //TopCorner
  triangulation.addPoint(ofVec3f(w,0,0));
  triangulation.addPoint(ofVec3f(0,0,0));

  for (int y=0; y<drawY; y=y+5) {
    for (int x=0; x<w; x=x+5) {
      ofColor c = image.getColor(x, y);
      float intensity = c.getLightness();
      if (intensity < intensityThreshold) {
        ofVec3f pos(x, y, 0.0);
        triangulation.addPoint(pos);
      }
    }
  }
}

//--------------------------------------------------------------
void ofApp::setup(){
  go=0;
  ofEnableSmoothing();
  ofBackground(0);
  colorLookup.clear();

  gui.setup();
  gui.add(color.setup("color", ofColor(100, 100, 140), ofColor(0, 0), ofColor(255, 255)));

  init("/Users/josephwilk/Workspace/sfpc/creatingthepast/of_v0.10.1_osx_release/apps/myApps/Salavon2/bin/data/sourcecode.png",
       "Openframeworks",
       0);
}

//--------------------------------------------------------------
void ofApp::update(){

  if(go==1){
    if(drawY < image.getHeight()){
      float intensityThreshold = 200;
      int w = image.getWidth();
      int h = image.getHeight();
      for (int x=0; x<w; x=x+5) {
        int y = drawY;
        for (int y=drawY; y<drawY+5; y=y+5) {
          ofColor c = image.getColor(x, y);
          float intensity = c.getLightness();
          if (intensity < intensityThreshold) {
              ofVec3f pos(x, y, 0.0);
              triangulation.addPoint(pos);
          }
        }
      }

      triangulation.triangulate();
    }
    if(drawY < image.getHeight()){
      drawY+=5;
    }
    else{
      go=0;
      int w = image.getWidth();
      int h = image.getHeight();

      triangulation.addPoint(ofVec3f(w,h,0));
      triangulation.addPoint(ofVec3f(0,h,0));
      triangulation.triangulate();
    }
  }

}

//--------------------------------------------------------------
void ofApp::draw(){
  ofBackground(ofColor(0,0,0));
  ofPushMatrix();
  ofTranslate((ofGetWidth()/2.0) - (image.getWidth()/2.0), 0);

  image.draw(0,0, image.getWidth(), image.getHeight());

  ofMesh tris = triangulation.triangleMesh;
  auto verts = tris.getVertices();
  auto idxs = tris.getIndices();

  //show source mesh
  //triangulation.draw();
  int c=0;
  int hueidx=0;
  int inc=0;
  ofColor newColor;
  newColor = ofColor(colors.at(0).r, colors.at(0).g, colors.at(0).b);
  ofSetColor(newColor);

  for(int i=0; i< idxs.size(); i=i+3){
    ofPoint p1 = verts[idxs[i]];
    ofPoint p2 = verts[idxs[i+1]];
    ofPoint p3 = verts[idxs[i+2]];
    float triangleArea = 0.5*abs(p1.x*(p2.y - p3.y) + p2.x*(p3.y - p1.y)+ p3.x*(p1.y - p2.y));

    stringstream ss;
    ss << idxs[i] << "." << idxs[i+1] <<  "." << idxs[i+2];

    if(colorLookup.count(ss.str()) > 0){
      newColor = colorLookup[ss.str()];
    }
    else{
      if(hueidx==0){
        inc=1;
      }
      else if(hueidx == colors.size()-1){
        inc=-1;
      }

      ofColor selected = colors.at(hueidx % colors.size());

      if(c%2 == 0){
        selected.setBrightness(selected.getBrightness()*1.1);
        selected.setSaturation(selected.getSaturation()*0.8);
      }

      if(ofRandom(100.0) > 99){
        hueidx += inc;
        newColor = ofColor(selected.r,selected.g,selected.b, selected.a);
      }

      if (triangleArea > 20000.0){
        hueidx += inc;
        newColor = ofColor(selected.r,selected.g,selected.b, selected.a);
        newColor.setSaturation(newColor.getSaturation()*0.8);
      }

      newColor.setHue(newColor.getHue()- (c*0.0003));
      newColor.setBrightness(newColor.getBrightness()+ (i*0.001));
      newColor.setSaturation(newColor.getSaturation()- (c*0.0012));

      colorLookup[ss.str()] = newColor;
    }

    c+=1;

    ofSetColor(newColor);
    ofFill();

    ofDrawTriangle(p1, p2, p3);
  }

  ofSetColor(ofColor(0,0,0,200));
  ofDrawRectangle(0, 0, 180, 20);
  ofSetColor(ofColor(255,255,255));
  ofDrawBitmapString(title, ofPoint(3,15));

  ofPopMatrix();

  if(!bHide){
    gui.draw();
  }

  ofSetColor(ofColor(255,255,255,255));
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
  if(key == 'h'){
    bHide = !bHide;
  }
  else if(key == 's'){
    gui.saveToFile("settings.xml");
  }
  else if(key == 'l'){
    gui.loadFromFile("settings.xml");
  }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
  if(key == 'g'){
    go=1;
    colorLookup.clear();
  }

  if(key == 'r'){
    init("/Users/josephwilk/Workspace/sfpc/creatingthepast/of_v0.10.1_osx_release/apps/myApps/Salavon2/bin/data/html2.png",
         "SFPC",
         1);
    colorLookup.clear();
    go=1;
  }

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
