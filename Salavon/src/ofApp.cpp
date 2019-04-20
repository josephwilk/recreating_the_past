#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
  go=0;
  ofEnableSmoothing();
  ofBackground(0);
  drawY=20;
  image.load("/Users/josephwilk/Workspace/sfpc/creatingthepast/of_v0.10.1_osx_release/apps/myApps/Salavon2/bin/data/sourcecode.png");
myfont.load("arial.ttf", 32);
  triangulation.reset();

  gui.setup(); // most of the time you don't need a name
  //gui.add(center.setup("center", ofVec2f(ofGetWidth()*.5, ofGetHeight()*.5), ofVec2f(0, 0), ofVec2f(ofGetWidth(), ofGetHeight())));
  gui.add(color.setup("color", ofColor(100, 100, 140), ofColor(0, 0), ofColor(255, 255)));


  float intensityThreshold = 100;
  int w = image.getWidth();
  int h = image.getHeight();

  //TopCorner
  triangulation.addPoint(ofVec3f(w,0,0));
  triangulation.addPoint(ofVec3f(0,0,0));
  for (int x=0; x<w; x=x+5) {
    for (int y=0; y<drawY; y=y+5) {
      ofColor c = image.getColor(x, y);
      float intensity = c.getLightness();
      if (intensity < intensityThreshold) {
        ofVec3f pos(x, y, 0.0);
        //if(abs(pos.x - prev.x) > 0.00000001){
        triangulation.addPoint(pos);
        //        mesh.addVertex(pos);
        //        mesh.addColor(c);
        //}

      }
    }
  }




//  mesh.setMode(OF_PRIMITIVE_TRIANGLES);
//  mesh.enableColors();
//  ofVec3f prevPos;
//  ofVec3f prevPosx;
//  float intensityThreshold = 200;
//  int w = image.getWidth();
//  int h = image.getHeight();
//
//  for (int x=0; x<w; x=x+2) {
//    for (int y=0; y<h; y=y+2) {
//      ofColor c = image.getColor(x, y);
//      float intensity = c.getLightness();
//      if (intensity < intensityThreshold) {
//        ofVec3f pos(x, y, 0.0);
//        //if(abs(pos.y - prevPos.y) > 50 || (pos.x != prevPos.x)){
//          //if(pos.x != prevPos.x){
//            //prevPosx = pos;
//          //}
//          //prevPos = pos;
//          triangulation.addPoint(pos);
//        //}
////        mesh.addVertex(pos);
////        mesh.addColor(c);
//        //}
//
//      }
//    }
//  }
//  triangulation.triangulate();

//  mesh.enableIndices();
//
//  float connectionDistance = 20;
//  int numVerts = mesh.getNumVertices();
//  for (int a=0; a<numVerts; ++a) {
//    ofVec3f verta = mesh.getVertex(a);
//    for (int b=a+1; b<numVerts; ++b) {
//      ofVec3f vertb = mesh.getVertex(b);
//      float distance = verta.distance(vertb);
//      if (distance <= connectionDistance) {
//        mesh.addIndex(a);
//        mesh.addIndex(b);
//      }
//    }
//  }

}

//--------------------------------------------------------------
void ofApp::update(){

  if(go==1){
    if(drawY < image.getHeight()){
        //triangulation.reset();
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
    //else{
  //
  //  }
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
//  ofColor centerColor = ofColor(255, 255, 255);
//  ofColor edgeColor(230, 230, 230);
//  ofBackgroundGradient(centerColor, edgeColor, OF_GRADIENT_CIRCULAR);
  ofBackground(ofColor(0,0,0));

  //ofFill();
  //triangulation.triangleMesh.setMode(OF_PRIMITIVE_LINE_LOOP);
//  triangulation.triangleMesh.draw(OF_MESH_FILL);

  ofPushMatrix();
  ofTranslate((ofGetWidth()/2.0) - (image.getWidth()/2.0), 0);
  //  mesh.draw();
  image.draw(0,0, image.getWidth(), image.getHeight());



  ofMesh tris = triangulation.triangleMesh;
  auto verts = tris.getVertices();
  auto idxs = tris.getIndices();

  vector<ofColor> colors;
//
  colors.push_back(ofColor(242,133,153)); //pink
  colors.push_back(ofColor(242,92,147));
  colors.push_back(ofColor(63,191,191));
  colors.push_back(ofColor(242,209,179));
  colors.push_back(ofColor(242,181,167));


//  colors.push_back(ofColor( 119, 227, 196));
//  colors.push_back(ofColor( 255, 137, 134));
//  colors.push_back(ofColor( 255, 199, 167));
//  colors.push_back(ofColor( 255, 239, 213));
//  colors.push_back(ofColor( 255, 175, 123));


  //blue
  //colors.push_back(ofColor( 30, 45, 100, 200));
  //colors.push_back(color);


//  colors.push_back(ofColor( 91, 146, 217,200));
//  colors.push_back(ofColor( 91, 146, 217,200));
//  colors.push_back(ofColor( 128, 189, 242,200));
//    colors.push_back(ofColor( 128, 189, 242,200));
//  colors.push_back(ofColor( 126, 161, 191,200));
//  colors.push_back(ofColor( 167, 213, 242,200));
//  colors.push_back(ofColor( 126, 161, 191,200));
//




//  colors.push_back(ofColor(246,64,119)); //pink
//  colors.push_back(ofColor(54,171,176)); //blue
//  colors.push_back(ofColor(253,157,146)); //blue

//  colors.push_back(ofColor(253,160,150));
//  colors.push_back(ofColor(251,70,124));
//  colors.push_back(ofColor(233,161,144));
//  colors.push_back(ofColor(218,213,161));
//  colors.push_back(ofColor(252,129,144));

//
//  colors.push_back(ofColor(93,180,171));
//  colors.push_back(ofColor(118,166,165));
//  colors.push_back(ofColor(71,170,167));
//  colors.push_back(ofColor(152,197,169));
//  //colors.push_back(ofColor(251,69,123));
//  colors.push_back(ofColor(98,184,175));

  //triangulation.draw();
  int c=0;
  int hueidx=0;
  ofColor newColor;
  newColor = ofColor(colors.at(0).r, colors.at(0).g, colors.at(0).b);
  //newColor.setHue(0);
  ofSetColor(newColor);
  for(int i=0; i< idxs.size(); i=i+3){
    ofPoint p1 = verts[idxs[i]];
    ofPoint p2 = verts[idxs[i+1]];
    ofPoint p3 = verts[idxs[i+2]];
    float triangleArea = 0.5*abs(p1.x*(p2.y - p3.y) + p2.x*(p3.y - p1.y)+ p3.x*(p1.y - p2.y));

    if(c < triangleColors.size()){
      newColor = triangleColors.at(c);
    }
    else{
      ofColor selected = colors.at(c % colors.size());

      if(c%2 == 0){
        selected.setBrightness(selected.getBrightness()*1.1);
        selected.setSaturation(selected.getSaturation()*0.8);
      }

      if(ofRandom(100.0) > 95.0){
        newColor = ofColor(selected.r,selected.g,selected.b);
        //newColor.setHue((c*0.02));
      }
      else{
        //newColor.setSaturation(newColor.getSaturation()-(c*0.01));
        //newColor.setSaturation(c*0.05);
        //newColor.setHue(newColor.getHue()+ (c*0.00015));
      }


      if (triangleArea > 20000.0){
        newColor = ofColor(selected.r,selected.g,selected.b);
        newColor.setSaturation(newColor.getSaturation()*0.8);
          //newColor.setBrightness(newColor.getBrightness()*1.1);
      }
      else{
       // newColor = ofColor(selected.r,selected.g,selected.b);
       // newColor.setHue(c*0.01);
      }

      //newColor.setHue((c*0.02));
      newColor.setHue(newColor.getHue()- (c*0.0003));
      newColor.setBrightness(newColor.getBrightness()+ (i*0.001));
      newColor.setSaturation(newColor.getSaturation()- (c*0.0012));

      triangleColors.push_back(newColor);
    }

    c+=1;
    //newColor.setSaturation( newColor.getSaturation()- ((c % 40)));
    //newColor.setBrightness( newColor.getBrightness()+ (i % 50)  );
    //newColor.setHue(selected.getHue()+c*0.01);
    ofSetColor(newColor);
    ofFill();

    ofDrawTriangle(p1, p2, p3);
  }

  ofSetColor(ofColor(0,0,0,200));
  ofDrawRectangle(0, 0, 180, 20);
  ofSetColor(ofColor(255,255,255));
  ofDrawBitmapString("40,000* Github: blah", ofPoint(3,15));


  ofPopMatrix();


  if(!bHide){
    gui.draw();
  }


  ofSetColor(ofColor(255,255,255,255));
  //myfont.drawString("40,000* Github: blah", 0,0);
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
    triangleColors.clear();
  }

  if(key == 'r'){
    triangleColors.clear();
    triangulation.reset();
    drawY
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
