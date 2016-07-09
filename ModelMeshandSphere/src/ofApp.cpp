#include "ofApp.h"


///メモ///メッシュの通し番号がめちゃくちゃなのでFacesを作れない。
//GLで表面を作るにしても番号がめちゃくちゃでインデックスを操作しても穴だらけです。
//MyVectorの番号の並びを、綺麗に整理できませんかね。153690380->12345678...........
//MyVectorの位置は変わらず、インデックスが作りやすいように、ナンバリングだけ変えたい。

//課題//
//・3Dモデルのvertexの順を整える方法
//・->　インデックスの作り方を工夫する。
//・一個ずつ書くのめんどくさすぎるので、クラスに分ける。インスタンス生成

//--------------------------------------------------------------
void ofApp::setup(){
    
    
    ofSetFrameRate(30);
    ofEnableDepthTest();
    ofBackground(0);
    ofSetColor(255);
    
    //Lighting
    light.enable();
    light.setPosition(-300, 500, 300);
    light.setAmbientColor(ofFloatColor(0.1, 0.1, 0.1));
    light.setDiffuseColor(ofFloatColor(1.0, 1.0, 1.0));
    //  light.setSpecularColor(ofFloatColor(1.0, 1.0, 1.0));
    //画像
    image.load("ST0006.jpg");
    ofTexture oftex = image.getTexture();
    tex_width = oftex.getWidth();
    tex_height = oftex.getHeight();
    //texture　GL設定
    glGenTextures(1, &tex);
    glBindTexture(GL_TEXTURE_RECTANGLE_EXT, tex);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glTexImage2D(GL_TEXTURE_RECTANGLE_EXT, 0, GL_RGBA,
                 image.getWidth(), image.getHeight(),
                 0,
                 GL_RGB, GL_UNSIGNED_BYTE, image.getPixels());

    
    
    
    //球の大きさ
    sphered = 10;
    
    //モデルからメッシュ取り
    mod.loadModel("models/Bast.3ds");
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
    
   finmesh.clear();
    
    yNoise += 0.01;
    if (yNoise > 10) {
        yNoise = 0;
    }
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    //String yNoise
    ofDrawBitmapString(ofToString(yNoise),10,10);
    
    int i_count = 0;
    
    //モデルのメッシュの点の数全てに
    for(int i=0; i< verts.size();i++){
        
        i_count++;

        float dist = ofDist(verts[i].x, verts[i].y,verts[i].z, 0, 0, 0);    //原点からモデルの点の距離もとめる
        ofVec3f myVector = ofVec3f(verts[i].x, verts[i].y,verts[i].z);  //新しい空ベクターにモデルの点を代入
        myVector = myVector.getNormalized();    //新しいベクターをサイズを１に変換
        myVector *= ofLerp(sphered,dist*200,ofNoise(yNoise)); //myVectorと球の間の数値をラープさせる。
        myVerts[i] = myVector;//myVertsの[i]番目だけにプッシュバック
        
        //空メッシュにmyVertsを投下
        finmesh.addVertex(ofVec3f(myVerts[i].x,myVerts[i].y,myVerts[i].z));
        
        //通し番号を見ますよ〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜
        ofPushMatrix();
        ofTranslate(myVerts[i]);
        //ofDrawBitmapString(ofToString(i), 0, 0);
        ofPopMatrix();
        
        //index　作り方ちょっと違うな・・・・
        finmesh.addIndex(i_count + i);
        finmesh.addIndex(i_count + i + 1);
        finmesh.addIndex(i_count + i + i_count);
        
        finmesh.addIndex(i_count + i + 1);
        finmesh.addIndex(i_count + i + i_count);
        finmesh.addIndex(i_count + i + i_count + 1);
        
    }
    
    
    cam.begin();
    
    
    
//    ////////////////////////GLでテクスチャを貼る！
//    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
//    glBindTexture(GL_TEXTURE_RECTANGLE_EXT, tex);
//    glEnable(GL_TEXTURE_RECTANGLE_EXT);
//    
//    glColor3f(1, 1, 1);
//    
//    float tx1,tx2,ty1,ty2;
//    for(int i=0; i< verts.size();i++){
//        
//        glBegin(GL_QUADS);
//        
//            tx1 = tex_width*i;
//            ty1 = tex_height*i;
//            tx2 = tex_width*i;
//            ty2 = tex_height*i;
//        
//            //4点ポリゴン・インデックス
//            glTexCoord2f(tx1, ty1);
//            glVertex3f(myVerts[i].x, myVerts[i].y, myVerts[i].z);
//            
//            glTexCoord2f(tx1, ty2);
//            glVertex3f(myVerts[i+1].x, myVerts[i+1].y, myVerts[i+1].z);
//            
//            glTexCoord2f(tx2, ty2);
//            glVertex3f(myVerts[i+1].x, myVerts[i+1].y, myVerts[i+1].z);
//            
//            glTexCoord2f(tx2, ty1);
//            glVertex3f(myVerts[i].x, myVerts[i].y, myVerts[i].z);
//        
//        glEnd();
//    }
//    glDisable(GL_TEXTURE_RECTANGLE_EXT);

    
    image.getTexture().bind();
    //finmesh.drawWireframe();
    //finmesh.drawVertices();
    finmesh.drawFaces();
    image.getTexture().unbind();
    
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
