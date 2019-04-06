#include "ofApp.h"

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
//  mesh.addVertex( v1 );
//  mesh.addVertex( v2 );
//  mesh.addVertex( v3 );
//
//  mesh.addVertex( v1 );
//  mesh.addVertex( v0 );
//  mesh.addVertex( v3 );

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
  return mesh;
}

//--------------------------------------------------------------
void ofApp::setup(){
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_LIGHTING);

  ofSetVerticalSync(true);
  ofSetFrameRate(60);
  ofSetBackgroundColor(10, 10, 10);
  ofEnableDepthTest();
  ofSetSmoothLighting(true);

  //ofFloatColor diffuseColor;
  //diffuseColor.set(1.0,1.0,1.0);
//  ofDisableAlphaBlending();
//  ofEnableDepthTest();
  //light.setDirectional();
  //light.setAttenuation(2,0.4,2.0)
  //light.enable();
//  light.setPosition(ofVec3f(100,100,200));
//  light.lookAt(ofVec3f(0,0,0));
//  ofDisableArbTex();


  //pointLight
  light.setPointLight();
  light.setSpecularColor(ofColor(255));
  light.setDiffuseColor(ofColor(255));
  light.setAmbientColor(ofColor(100));


//  light.setSpotlight();
//  light.setSpotlightCutOff(50);
//  light.setSpotConcentration(45);
//  light.setAttenuation(1,0,0);
//  light.setSpecularColor(ofColor(255));
//  light.setDiffuseColor(ofColor(255));
//  light.setAmbientColor(ofColor(100));


//  light.setDirectional();
//  light.setSpecularColor(ofColor(255));
//  light.setDiffuseColor(ofColor(255));
//  light.setAmbientColor(ofColor(100));


  light.enable();


  ofEnableDepthTest();
  ofColor centerColor = ofColor(85, 78, 68);
  ofColor edgeColor(0, 0, 0);
  ofBackgroundGradient(centerColor, edgeColor, OF_GRADIENT_CIRCULAR);


  ofSetFrameRate(20);
  cam.setDeviceID(1);
  cam.setup(960,720);
  //mesh.setMode(OF_PRIMITIVE_POINTS);
//  mesh.setMode(OF_PRIMITIVE_LINES);
//  mesh.enableIndices();
  //mesh.enableColors();
  //mesh.enableNormals();
//  mesh.usingTextures();

  resy = 60;
  resx = 80;
  int size = 8;
  for(int y=0;   y < resy; y++){
    for(int x=0; x < resx; x++){
      ofMesh m = buildMesh(x*(16+2),y*(16+2), 70, size);
      pyramids.push_back(m);
    }
  }
  pyramids.reserve(pyramids.size());

  //std::reverse(pyramids.begin(), pyramids.end());

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

      ofPoint dir = ( (v2 - v1).crossed( v3 - v1 ) ).normalized();
      //Accumulate it to norm array for i1, i2, i3
      norm[ i1 ] += dir;
      norm[ i2 ] += dir;
      norm[ i3 ] += dir; }
    for (int i=0; i<nV; i++) {
      norm[i] = glm::normalize(norm[i]);
    }
    m.clearNormals();
    m.addNormals(norm);

  }


  cam.update();
  ofPixels pix = cam.getPixels();
//  }
//
//  float connectionDistance = 20;
//  int numVerts = mesh.getNumVertices();
//  for (int a=0; a<numVerts; ++a) {
//    ofVec3f verta = mesh.getVertex(a);
//    for (int b=a+1; b<numVerts; ++b) {
//      ofVec3f vertb = mesh.getVertex(b);
//      float distance = verta.distance(vertb);
//      if (distance <= connectionDistance) {
//        // In OF_PRIMITIVE_LINES, every pair of vertices or indices will be
//        // connected to form a line
//        mesh.addIndex(a);
//        mesh.addIndex(b);
//      }
//    }
  }


//Universal function which sets normals for the triangle mesh
//void setNormals( ofMesh &mesh )
//{
//  //The number of the vertices
//  int nV = mesh.getNumVertices();
//  //The number of the triangles
//  int nT = mesh.getNumIndices() / 3;
//  vector<ofPoint> norm( nV );
//  //Array for the normals
//  //Scan all the triangles. For each triangle add its
//  //normal to norm's vectors of triangle's vertices
//  for (int t=0; t<nT; t++) { //Get indices of the triangle t
//    int i1 = mesh.getIndex( 3 * t );
//    int i2 = mesh.getIndex( 3 * t + 1 );
//    int i3 = mesh.getIndex( 3 * t + 2 );
//    //Get vertices of the triangle
//    const ofPoint &v1 = mesh.getVertex( i1 );
//    const ofPoint &v2 = mesh.getVertex( i2 );
//    const ofPoint &v3 = mesh.getVertex( i3 );
//    //Compute the triangle's normal
//    ofPoint dir = ( (v2 - v1).crossed( v3 - v1 ) ).normalized();
//    //Accumulate it to norm array for i1, i2, i3
//    norm[ i1 ] += dir;
//    norm[ i2 ] += dir;
//    norm[ i3 ] += dir; }
//  //Normalize the normal's length
//    for (int i=0; i<nV; i++) {
//      norm[i].normalize();
//    }
//  //Set the normals to mesh
//    mesh.clearNormals();
//  //mesh.addNormals(norm);
//
//  //addNormals( norm );
//}


//--------------------------------------------------------------
void ofApp::update(){
  cam.update();
  ofPixels pix = cam.getPixels();

    int w = pix.getWidth();
    int h = pix.getHeight();

    int scalex = w/resx; //960     16-pix
    int scaley = h/resy; //720     18-pix
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

    int zFactor = colors[c].getBrightness();
    float newHeight;
    if (zFactor >= 40) {
      zFactor = zFactor*1.1 + 55;
    }
    else{
      zFactor = 60;
    }
    c+=1;

    //smooth
    if(abs(topPoint.z - zFactor) > 0.05){
      if(topPoint.z > zFactor){
        newHeight = topPoint.z - (topPoint.z-zFactor)*0.01;
      }
      else if(topPoint.z < zFactor){
        newHeight = topPoint.z + (zFactor+topPoint.z)*0.01;
      }
    }

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

      ofPoint dir = ( (v2 - v1).crossed( v3 - v1 ) ).normalized();
      //Accumulate it to norm array for i1, i2, i3
      norm[ i1 ] += dir;
      norm[ i2 ] += dir;
      norm[ i3 ] += dir; }
    for (int i=0; i<nV; i++) {
      norm[i] = glm::normalize(norm[i]);
    }
    m.clearNormals();
    m.addNormals(norm);

  }
  

  //colors.reserve(colors.size());
    //std::reverse(colors.begin(), colors.end());

//  mesh.clear();
//  float intensityThreshold = 10;
//  int w = pix.getWidth();
//  int h = pix.getHeight();
//  int scale = 15;
//  for (int x=0; (x+scale)<w; x=x+scale) {
//    for (int y=0; (y+scale)<h; y=y+scale) {
//      ofColor c = pix.getColor(x, y);
//      float intensity = c.getLightness();
//
////      if (intensity >= intensityThreshold) {
////        float saturation = c.getSaturation();
////        float z = ofMap(saturation, 0, 255, -100, 100);
////        ofVec3f pos(x*2, y*2, z);
////        mesh.addVertex(pos);
////        mesh.addColor(c);
////      }
//
//      if (intensity >= intensityThreshold) {
//        float saturation = c.getSaturation();
//        float z;
//        if((x+y)%2 == 0.0){
//          z = ofMap(255-intensity, 0, 255.0, 0.0, 100.0);
//        }else{
//           z = ofMap(intensity, 0, 255, 0, 0);
//        }
//        ofVec3f pos(x, y, z);
//        mesh.addVertex(pos);
//        mesh.addColor(c);
//      }
//    }
//  }
//
//
//  float connectionDistance = 2;
//  int numVerts = mesh.getNumVertices();
//  for (int a=0; a<numVerts; ++a) {
//    ofVec3f verta = mesh.getVertex(a);
//    for (int b=a+1; b<numVerts; ++b) {
//      ofVec3f vertb = mesh.getVertex(b);
//      float distance = verta.distance(vertb);
//      if (distance <= connectionDistance) {
//        // In OF_PRIMITIVE_LINES, every pair of vertices or indices will be
//        // connected to form a line
//        mesh.addIndex(a);
//        mesh.addIndex(b);
//      }
//    }
//  }
//  mesh.smoothNormals(0.1);

}

//--------------------------------------------------------------
void ofApp::draw(){
  //mainCam.begin();

  ofPushMatrix();
  ofTranslate( 200, 100, 0 );

  float time = ofGetElapsedTimef(); //Get time in seconds
  //float angle = time * 30; //Rotate angle
  //ofRotate(50, 1, 0.5, 0)

  //ofRotate( 10, 1, 0, 0 );


  int x=0;
  int y=0;
  for(auto& m : pyramids) {
    if((x%resx)==0){
//      ofPushMatrix();
//      ofTranslate( 0, 24, 0.05 );
//      ofRotate( 2, 1, 0, 0 );
      y+=1;
//      ofPopMatrix();
    }
    ofSetColor( colors[x] );
    m.draw();
    x=x+1;


    //ofDrawCircle(4, 4, 4);
  }

 //mainCam.begin();
  //mesh.draw();
  ofPopMatrix();
  //mainCam.end();
  //mesh.draw();
  //mainCam.end();
  //cam.draw(0, 0);
//  for(int x=0; x < 1024; x++){
//    for(int y=0; y < 768; y++){
//      //pix.getColor(x,y);
//  }
//  }
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

