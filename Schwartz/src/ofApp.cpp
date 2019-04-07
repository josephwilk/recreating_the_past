#include "ofApp.h"


//--------------------------------------------------------------
void ofApp::setup(){
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_LIGHTING);

  ofEnableDepthTest();
  ofSetVerticalSync(true);
  ofSetFrameRate(60);
  ofSetBackgroundColor(10, 10, 10);
  ofSetSmoothLighting(true);

  light.setPointLight();
  light.setSpecularColor(ofColor(255));
  light.setDiffuseColor(ofColor(200));
  light.setAmbientColor(ofColor(190));

  spotlight.setSpotlight();
  spotlight.setSpotlightCutOff( 40 );
  spotlight.setSpotConcentration( 20 );
  spotlight.setDiffuseColor(ofColor(255));
  spotlight.setAmbientColor(ofColor(100));

  spotlight.enable();
  light.enable();

  ofSetFrameRate(20);
  cam.setDeviceID(1);
  cam.setup(960,720);

  resy = 60;
  resx = 80;
  int size = 9;
  for(int y=0;   y < resy; y++){
    for(int x=0; x < resx; x++){
      ofMesh m = buildMesh(x*(16+2),y*(16+2), 70, size);
      pyramids.push_back(m);
    }
  }
  pyramids.reserve(pyramids.size());

  cam.update();
  ofPixels pix = cam.getPixels();

  ofDisableArbTex();
}


//--------------------------------------------------------------
void ofApp::update(){
  spotlight.setOrientation( ofVec3f( 30, -10, 0) );
  spotlight.setPosition( 400, 500, 300);
  cam.update();
  ofPixels pix = cam.getPixels();

    int w = pix.getWidth();
    int h = pix.getHeight();

    int scalex = w/resx;
    int scaley = h/resy;
    colors.clear();

    for (int y=0; y<(h/scaley); y++) {
      for (int x=0; x<(w/scalex); x++) {
        ofColor c = pix.getColor(scalex*x, scaley*y);
        colors.push_back(c);
      }
    }

  ofPoint topPoint;
  vector<ofMesh> newPyramids;
  int c=0;
  for(auto& mesh : pyramids) {
    topPoint = mesh.getVertex(0);


    int zFactor = colors.at(c).getSaturation() + colors.at(c).getHue();
    float newHeight;
//    if (zFactor >= 40) {
      zFactor = zFactor*1.2;
    if(zFactor > 500){

      zFactor = 400;
    }
//    }
//    else{
//      zFactor = 30;
//    }



    //smooth
    if (colors.at(c).getLightness() > 100) {
      zFactor = 120;
      newHeight = zFactor;
    }else{


    if(abs(topPoint.z - zFactor) > 0.05){
      if(topPoint.z > zFactor){
        newHeight = topPoint.z - (topPoint.z-zFactor)*0.01;
      }
      else if(topPoint.z < zFactor){
        newHeight = topPoint.z + (zFactor+topPoint.z)*0.01;
      }
    }
    }
    c+=1;

//    if(ofRandom(1.0) < 0.03){//flickers
//      newHeight = 0.5;
//    }

    topPoint.z=newHeight;
    mesh.setVertex(0, topPoint);

    topPoint = mesh.getVertex(3);
    topPoint.z=newHeight;
    mesh.setVertex(3, topPoint);

    topPoint = mesh.getVertex(6);
    topPoint.z=newHeight;
    mesh.setVertex(6, topPoint);

    topPoint = mesh.getVertex(9);
    topPoint.z=newHeight;
    mesh.setVertex(9, topPoint);
    newPyramids.push_back(mesh);
  }
  pyramids = newPyramids;

  for(auto& m : pyramids) {
    int nV = m.getNumVertices();
    int nT = m.getNumIndices() / 3;
    std::vector<glm::vec3> norm( nV );

    for (int t=0; t<nT; t++) {
      int i1 = m.getIndex( 3 * t );
      int i2 = m.getIndex( 3 * t + 1 );
      int i3 = m.getIndex( 3 * t + 2 );

      //Get vertices of the triangle
      const ofPoint &v1 = m.getVertex( i1 );
      const ofPoint &v2 = m.getVertex( i2 );
      const ofPoint &v3 = m.getVertex( i3 );
      //Compute the triangle's normal

      //
      ofPoint dir = ( (v2 - v1).crossed( v3 - v1 ) ).normalized();

      norm[ i1 ] += dir;
      norm[ i2 ] += dir;
      norm[ i3 ] += dir; }
      for (int i=0; i<nV; i++) {
        norm[i] = glm::normalize(norm[i]);
      }
      m.clearNormals();
      m.addNormals(norm);
  }
}

ofColor ofApp::averageColor(int cellx, int celly){
  int startCell = (cellx-1);
  int r=0;
  int g=0;
  int b=0;

  ofColor sample;
  
  for(int i=0; i<3; i++){
    startCell = (cellx-1);
    if((startCell+i)>0 && (startCell+i) < colors.size()){
      sample = colors.at(startCell+i);
    }
    else{
      sample = colors.at(cellx);
    }
    r += sample.r;
    g += sample.g;
    b += sample.b;

//    startCell = (resx*(celly+1)) + (cellx-1);
//    if((startCell+i)>0 && (startCell+i) < colors.size()){
//      sample = colors.at(startCell+i);
//    }
//    else{
//      sample = colors.at(cellx);
//    }
//
//    r += sample.r;
//    g += sample.g;
//    b += sample.b;
//
//    startCell = (resx*(celly-1)) + (cellx-1);
//    if((startCell+i)>0 && (startCell+i) < colors.size()){
//      sample = colors.at(startCell+i);
//    }
//    else{
//      sample = colors.at(cellx);
//    }
//
//    r += sample.r;
//    g += sample.g;
//    b += sample.b;


  }

  r=r/3;
  g=g/3;
  b=b/3;

  return ofColor(r,g,b);
}

ofMesh ofApp::buildMesh(int x, int y, int z, int size){
  ofMesh mesh;
  float ratio = 1.0;
  //size = 960/size;
  //int size = 12;
  ofPoint v0 = ofPoint( x+(-size*ratio), y+(-size*ratio), 0);
  ofPoint v1 = ofPoint( x+(-size*ratio), y+(size*ratio),  0);
  ofPoint v2 = ofPoint( x+(size*ratio),  y+(size*ratio),  0);
  ofPoint v3 = ofPoint( x+(size*ratio), y+(-size*ratio),  0);
  ofPoint v4 = ofPoint( x+0, y+0,    z ); //top

  //Base triangles
  mesh.addVertex( v1 );
  mesh.addVertex( v2 );
  mesh.addVertex( v3 );

  mesh.addVertex( v1 );
  mesh.addVertex( v0 );
  mesh.addVertex( v3 );

  mesh.addVertex( v4 );  //0
  mesh.addVertex( v0 );
  mesh.addVertex( v1 );

  mesh.addVertex( v4 );  //3
  mesh.addVertex( v1 );
  mesh.addVertex( v2 );

  mesh.addVertex( v4 );  //6
  mesh.addVertex( v2 );
  mesh.addVertex( v3 );

  mesh.addVertex( v4 );  //9
  mesh.addVertex( v3 );
  mesh.addVertex( v0 );
  mesh.setupIndicesAuto();

  mesh.enableColors();
  mesh.enableIndices();
  mesh.enableColors();
  mesh.enableNormals();
  return mesh;
}


//--------------------------------------------------------------
void ofApp::draw(){
  ofEnableLighting();
  ofPushMatrix();
  ofTranslate( 200, 100, 0 );

  int x=0;
  int y=0;
  int r=0;
  int g=0;
  int b=0;

  ofColor pick;
  for(auto& m : pyramids) {

    pick = averageColor(x, y);
    if(pick.getLightness() > 110){
      ofSetColor(ofColor(15,1,40));
//      ofSetColor(ofColor(8,9,35));
//      if(y < 10 || y > resy-10){
//       ofSetColor(ofColor(15,1,21));
//      }
//      if(x%resx < 10 || x%resx > resx-10){
//
//      }

    }
    else{
      pick.setSaturation(pick.getSaturation()+100);
      pick.setBrightness(pick.getBrightness()+10);
      ofSetColor(pick);
    }

    m.draw();
    x=x+1;
    if((x%resx)==0){ y+=1; }
  }

  ofPopMatrix();
  ofDisableLighting();
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

