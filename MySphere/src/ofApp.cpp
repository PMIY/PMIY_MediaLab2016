#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    modmesh.clear();
    
    ofBackground(0);
    ofEnableDepthTest();
    cam.setDistance(100);
    //ofSetFullscreen(TRUE);

    
    //Lighting
    light.enable();
    light.setPosition(-300, 500, 300);
    light.setAmbientColor(ofFloatColor(0.1, 0.1, 0.1));
    light.setDiffuseColor(ofFloatColor(1.0, 1.0, 1.0));
//  light.setSpecularColor(ofFloatColor(1.0, 1.0, 1.0));

    
    //画像読み込み
    ofDisableArbTex();
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
    
    //モデル読み込み、メッシュ変換
    mod.loadModel("sphere266p.3ds");
    modmesh = mod.getMesh(0);
    vector<ofVec3f>& verts = modmesh.getVertices();

        //////球をの頂点を計算//////
        float x,y,z;
        float r = 10.f;
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
    
    
//    //////////////////////変形しているよおおおお
//    for (int k=0; k<=90; k++) {
//        for (int i=0; i<=90; i++) {
//            for(int m=0; m < verts.size(); m++){
//                vtxs[k][i].x *= verts[m].x;
//                vtxs[k][i].y *= verts[m].y;
//                vtxs[k][i].z *= verts[m].z;
//            }
//        }
//    }
    
    
 
}
//--------------------------------------------------------------
void ofApp::update(){

    
}
//--------------------------------------------------------------
void ofApp::draw(){
    
    //肌がもにもにしている。(鳥肌っぽい)
    float liquidness = 10;
    float amplitude = 0.1;
    float speedDampen = ofNoise(50,100);
    
    for (int k=200; k<=360; k++) {
        for (int i=-80; i<=90; i++) {
            
            vtxs[k][i].x += ofSignedNoise(vtxs[k][i].x,vtxs[k][i].y,vtxs[k][i].z,ofGetElapsedTimef()/speedDampen)*amplitude;
     
            vtxs[k][i].y += ofSignedNoise(vtxs[k][i].z,vtxs[k][i].x,vtxs[k][i].y,ofGetElapsedTimef()/speedDampen)*amplitude;
         
            vtxs[k][i].z += ofSignedNoise(vtxs[k][i].y,vtxs[k][i].z,vtxs[k][i].x,ofGetElapsedTimef()/speedDampen)*amplitude;
        }
    }
    
   
    cam.begin();
    
  
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
