#include "ofApp.h"
///田所先生ありがとううううううううううううううううううううう

//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(0);
    ofDisableArbTex();
    image.load("ST0006.jpg");
    
    //球を生成
    sphere.set(200, 8);
    //球からメッシュを生成
    sphereMesh = sphere.getMesh();
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
    //隠面消去
    ofEnableDepthTest();
    //テクスチャー適用
    image.getTexture().bind();
    
    cam.begin();
    
    //球から生成したメッシュを描画
    ofSetColor(255);
    sphereMesh.drawFaces();

    
    //メッシュの頂点の数だけくりかえし
    for (int i = 0; i < sphereMesh.getVertices().size(); i++) {
        
        ofPushMatrix();
        //メッシュのそれぞれの頂点の位置を取得
        ofTranslate(sphereMesh.getVertices()[i]);
        //頂点番号を表示
        ofDrawBitmapString(ofToString(i), 0, 0);
        ofPopMatrix();
        
        
        
    }
    cam.end();

    image.getTexture().unbind();
    ofDisableDepthTest();
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
