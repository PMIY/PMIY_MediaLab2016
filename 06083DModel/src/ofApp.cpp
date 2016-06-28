#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

    
    def = new Deform("models/Hip.3ds");
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
    //ライトを配置
    light.enable();
    light.setPosition(-100, 100, 500);
    light.setAmbientColor(ofFloatColor(0.5,0.5,0.5));
    light.setDiffuseColor(ofFloatColor(1.0,1.0,1.0));
    light.setSpecularColor(ofFloatColor(1.0,1.0,1.0));
    
}

//--------------------------------------------------------------
void ofApp::update(){
    
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    


    cam.begin();
    
    def->draw();
    def2->draw();
    def3->draw();
    def4->draw();
    def5->draw();
    def6->draw();
    def7->draw();
    def8->draw();

    cam.end();

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    /*
     switch(key) {
         case 's':mesh.save("mesh.ply");
     }
     */
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
