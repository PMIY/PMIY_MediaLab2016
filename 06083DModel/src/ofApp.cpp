#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    ofSetFullscreen(true);
    cam.setPosition(0, 0, 1000);

    def = new Deform("models/Bast.3ds");
    def2 = new Deform("models/bast.3ds");
    def3 = new Deform("models/Belly.3ds");
    def4 = new Deform("models/Back.3ds");
    def5 = new Deform("models/Sholder.3ds");
    def6 = new Deform("models/Neck.3ds");
    def7 = new Deform("models/Norse.3ds");
    def8 = new Deform("models/Ear.3ds");
    
    ofSetFrameRate(60);
    ofBackground(0);
    ofEnableDepthTest();
    ofSetVerticalSync(true);
    
    debug_num = 0;
    
    areaLight.setAmbientColor(ofFloatColor(0.1,0.1,0.1));
    areaLight.setDiffuseColor(ofFloatColor(1,1,1));
    areaLight.setSpecularColor(ofFloatColor(1,1,1));
    areaLight.setPosition(0,500,500);
    
}

//--------------------------------------------------------------
void ofApp::update(){
    
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    
    
    cam.begin();
    
    //def->drawDebug(debug_num);
    def->draw();
    def2->draw();
    def3->draw();
    def4->draw();
    def5->draw();
    def6->draw();
    def7->draw();
    def8->draw();
    
    cam.end();
   // ofDrawBitmapString(ofToString(debug_num), 10, 10);
    

    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    /*
     switch(key) {
         case 's':mesh.save("mesh.ply");
     }
     */
    if(key == OF_KEY_UP){
        debug_num++;
    }
    if(key == OF_KEY_DOWN){
        debug_num--;
    }
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
