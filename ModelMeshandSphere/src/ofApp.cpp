#include "ofApp.h"


///メモ///メッシュの通し番号がめちゃくちゃなのでFacesを作れない。
//GLで表面を作るにしても番号がめちゃくちゃで繋ぐ点をインデックスで操作できない。
//MyVectorの番号の並びを、綺麗に整理できませんかね。153690380->12345678...........
//MyVectorの位置は変わらず、インデックスが作りやすいように、ナンバリングだけ変えたい。

//--------------------------------------------------------------
void ofApp::setup(){
    
    finmesh.clear();
    ofEnableDepthTest();
    ofBackground(0);
    ofSetColor(255);
    
    //球の大きさ
    sphered = 100;
    
    //モデルからメッシュ取り
    mod.loadModel("models/hip.obj");
    modmesh = mod.getMesh(0);
    
    //モデルのメッシュから点を取り出す
    verts = modmesh.getVertices();
    
    //モデルのメッシュの点の数全てに
    for(int i=0; i< verts.size();i++){
        float dist = ofDist(verts[i].x, verts[i].y,verts[i].z, 0, 0, 0);    //原点からモデルの点の距離もとめる
        ofVec3f myVector = ofVec3f(verts[i].x, verts[i].y,verts[i].z);  //新しい空ベクターにモデルの点を代入
        myVector = myVector.getNormalized();    //新しいベクターをサイズを１に変換
        myVector *= ofLerp(sphered,dist*200,0.1); //myVectorと球の間の数値をラープさせる。
        myVerts.push_back(myVector);    //myVertsにmyvectorで得られた点を挿入！
    }
    
  
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
    
      cam.begin();

    //モデルのメッシュの点の数全てに
    for(int i=0; i< verts.size();i++){
        float dist = ofDist(verts[i].x, verts[i].y,verts[i].z, 0, 0, 0);    //原点からモデルの点の距離もとめる
        ofVec3f myVector = ofVec3f(verts[i].x, verts[i].y,verts[i].z);  //新しい空ベクターにモデルの点を代入
        myVector = myVector.getNormalized();    //新しいベクターをサイズを１に変換
        myVector *= ofLerp(sphered,dist*200,0.5); //myVectorと球の間の数値をラープさせる。
        myVerts[i] = myVector;//myVertsの[i]番目だけにプッシュバック
        
        //空メッシュにmyVertsを投下
        finmesh.addVertex(ofVec3f(myVerts[i].x,myVerts[i].y,myVerts[i].z));
        
        //通し番号を見ますよ〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜
        ofPushMatrix();
        ofTranslate(myVerts[i]);
        ofDrawBitmapString(ofToString(i), 0, 0);
        ofPopMatrix();
        
    }
    //finmesh.drawWireframe();
    finmesh.drawVertices();
    //finmesh.drawFaces();
    cam.end();


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
