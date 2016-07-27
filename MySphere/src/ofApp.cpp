#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    modmesh.clear();
    
    //ofSetWindowPosition(1441, 0);
    ofSetFullscreen(true);
    
    ofBackground(0);
    ofEnableDepthTest();
    cam.setDistance(100);
    
    //Lighting
    light.enable();
    light.setPointLight();
    light.setPosition(300, 100, 0);
    light.setAmbientColor(ofFloatColor(0.1, 0.1, 0.1));
    light.setDiffuseColor(ofFloatColor(0.7, 0.55, 0.5));
    light.setSpecularColor(ofFloatColor(0.2, 0.2, 0.2));
    
    light2.enable();
    light2.setPointLight();
    light2.setPosition(-300, 100, 0);
    light2.setAmbientColor(ofFloatColor(0.1, 0.1, 0.1));
    light2.setDiffuseColor(ofFloatColor(0.4, 0.6, 0.7));
    light2.setSpecularColor(ofFloatColor(0.2, 0.2, 0.2));
    
    light3.enable();
    light3.setPointLight();
    light3.setPosition(0, -100, 0);
    light3.setAmbientColor(ofFloatColor(0.1, 0.1, 0.1));
    light3.setDiffuseColor(ofFloatColor(0.5, 0.6, 0.5));
    light3.setSpecularColor(ofFloatColor(0.2, 0.2, 0.2));
    
    //Material
    material.setShininess( 120 );
    material.setAmbientColor(ofColor(110,100,100,255));
    material.setSpecularColor(ofColor(255, 255, 255, 255));
    material.setDiffuseColor(ofColor(100,100,100,255));
    
    //画像読み込み
    ofDisableArbTex();
    image.load("skin2.jpg");
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
    
    //モデル読み込み、メッシュ変換
    mod.loadModel("models/oppai.3ds");
    modmesh = mod.getMesh(0);
    verts = modmesh.getVertices();
    
    
    //////球をの頂点を計算//////
    float x,y,z;
    float r = 50.f;
    float radianCvt = 3.1415926/180.f;
    
    int i_count = 0;
    int k_count = 0;
    
    
    for (int k=0;k<=360; k++) {
        k_count++;
        
        for (int i=-90;i<=90; i++) {
            if (k == 0) i_count++;
            
            y = r*sin( i*radianCvt );
            
            float xz = r*cos( i*radianCvt );
            
            x = xz*cos(k*radianCvt);
            z = xz*sin(k*radianCvt);
            
            int kIndex = (int)k;
            int iIndex = ((int)i+90);
            
            vtxs[kIndex][iIndex].x = x;
            vtxs[kIndex][iIndex].y = y;
            vtxs[kIndex][iIndex].z = z;
        }
    }
    
    
}
//--------------------------------------------------------------
void ofApp::update(){
    
    
    
}
//--------------------------------------------------------------
void ofApp::draw(){
    
    
    float amplitude = 0.1;
    float speedDampen = ofNoise(50,100);
    float speedDampen2 = ofNoise(50,70);
    float speedDampen3 = ofNoise(50,90);
    
    //面白いけど重い
    for (int k=0;k<=360; k++) {
        for (int i=0;i<=180; i++) {
            vtxs[k][i].x = ofLerp(vtxs[k][i].x, HomeoBox[i],ofSignedNoise(ofSignedNoise(ofGetElapsedTimef()/speedDampen)*amplitude));
            vtxs[k][i].y = ofLerp(vtxs[k][i].y, HomeoBox[i],ofSignedNoise(ofSignedNoise(ofGetElapsedTimef()/speedDampen2)*amplitude));
            vtxs[k][i].z = ofLerp(vtxs[k][i].z, HomeoBox[i],ofSignedNoise(ofSignedNoise(ofGetElapsedTimef()/speedDampen3)*amplitude));
            if(HomeoBox[i]>68){
                HomeoBox[i]=0;
            }
        }
    }
    
    //
    //    for (int k=0;k<=360; k++) {
    //        for (int i=0;i<=180; i++) {
    //            vtxs[k][i].x = ofLerp(vtxs[k][i].x, verts[i].x,ofSignedNoise(ofSignedNoise(ofGetElapsedTimef()/speedDampen)*amplitude));
    //            vtxs[k][i].y = ofLerp(vtxs[k][i].y, verts[i].y,ofSignedNoise(ofSignedNoise(ofGetElapsedTimef()/speedDampen2)*amplitude));
    //            vtxs[k][i].z = ofLerp(vtxs[k][i].z, verts[i].z,ofSignedNoise(ofSignedNoise(ofGetElapsedTimef()/speedDampen3)*amplitude));
    //        }
    //    }
    
    
    
    
    
    //    for (int k=0;k<=360; k++) {
    //        for (int i=0;i<=180; i++) {
    //
    //            vtxs[k][i].x = ofLerp(vtxs[k][i].x, verts[i].x,HomeoBox[i]/10);
    //            vtxs[k][i].y = ofLerp(vtxs[k][i].y, verts[i].y,HomeoBox[i]/10);
    //            vtxs[k][i].z = ofLerp(vtxs[k][i].z, verts[i].z,HomeoBox[i]/10);
    //
    //            if(HomeoBox[i]>68){
    //                i=0;
    //            }
    //        }
    //    }
    //
    
    
    
    
    cam.begin();
    ofRotateY(ofGetElapsedTimef()*10);
    material.begin();
    
    //GLでテクスチャを貼る！
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glBindTexture(GL_TEXTURE_RECTANGLE_EXT, tex);
    glEnable(GL_TEXTURE_RECTANGLE_EXT);
    
    glColor3f(1, 1, 1);
    
    float tx1,tx2,ty1,ty2;
    for (int k=0;k<360; k++) {
        
        glBegin(GL_QUADS);
        for (int i=0;i<180; i++) {
            
            tx1 = tex_width*k/360.f;
            tx2 = tex_width*(k+1)/360.f;
            
            ty1 = tex_height*i/180.f;
            ty2 = tex_height*(i+1)/180.f;
            
            
            //4点ポリゴン・インデックス
            glTexCoord2f(tx1, ty1);
            glVertex3f(vtxs[k][i].x, vtxs[k][i].y, vtxs[k][i].z);
            
            glTexCoord2f(tx1, ty2);
            glVertex3f(vtxs[k][i+1].x, vtxs[k][i+1].y, vtxs[k][i+1].z);
            
            glTexCoord2f(tx2, ty2);
            glVertex3f(vtxs[k+1][i+1].x, vtxs[k+1][i+1].y, vtxs[k+1][i+1].z);
            
            glTexCoord2f(tx2, ty1);
            glVertex3f(vtxs[k+1][i].x, vtxs[k+1][i].y, vtxs[k+1][i].z);
            
        }
        glEnd();
    }
    glDisable(GL_TEXTURE_RECTANGLE_EXT);
    material.end();
    
    
    ofPopMatrix();
    glPointSize(1);
    ofPushMatrix();
    
    
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
