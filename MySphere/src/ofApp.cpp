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
    light.setPosition(300, 100, 100);
    light.setAmbientColor(ofFloatColor(0.1, 0.1, 0.1));
    light.setDiffuseColor(ofFloatColor(0.7, 0.55, 0.5));
    light.setSpecularColor(ofFloatColor(0.2, 0.2, 0.2));
    
    light2.enable();
    light2.setPointLight();
    light2.setPosition(-300, 100, -100);
    light2.setAmbientColor(ofFloatColor(0.1, 0.1, 0.1));
    light2.setDiffuseColor(ofFloatColor(0.4, 0.6, 0.7));
    light2.setSpecularColor(ofFloatColor(0.2, 0.2, 0.2));
    
    light3.enable();
    light3.setPointLight();
    light3.setPosition(0, -100, -100);
    light3.setAmbientColor(ofFloatColor(0.1, 0.1, 0.1));
    light3.setDiffuseColor(ofFloatColor(0.5, 0.6, 0.5));
    light3.setSpecularColor(ofFloatColor(0.2, 0.2, 0.2));
    
    
    //Material
    material.setShininess( 120 );
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
    mod.loadModel("models/oppao.3ds");
    modmesh = mod.getMesh(0);
    verts = modmesh.getVertices();
    
    //みに球を生成    //球からメッシュを生成//点の多さは決められるう。
    sphere.set(10, 10);
    sphereMesh = sphere.getMesh();
    sphereverts = sphereMesh.getVertices();

    
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
    

    ////半球をの頂点を計算//////

//    ofPopMatrix();
//    ofTranslate(100, 0);
//    
//    float hx,hy,hz;
//    float hr = 50.f;
//    float hradianCvt = 13.1415926/180.f;
//    
//    int hi_count = 0;
//    int hk_count = 0;
//    
//    for (int hk=0;hk<=360; hk++) {
//        hk_count++;
//        
//        for (int hi=-90;hi<=180; hi++) {
//            if (hk == 0) hi_count++;
//            
//            hy = hr*sin( hi*hradianCvt );
//            
//            float hxz = hr*cos( hi*hradianCvt );
//            
//            hx = hxz*cos(hk*radianCvt);
//            hz = hxz*sin(hk*radianCvt);
//            
//            int hkIndex = (int)hk;
//            int hiIndex = ((int)hi+90);
//            
//            hvtxs[hkIndex][hiIndex].x = hx;
//            hvtxs[hkIndex][hiIndex].y = hy;
//            hvtxs[hkIndex][hiIndex].z = hz;
    
//                //3角ポリゴンのインデックス
//                for (int hk = 0;hk < hk_count - 1;hk++)
//                {
//                    for (int hi = 0;hi < hi_count-1;hi++)
//                    {
//                        hshperemesh.addIndex(hk * hi_count + hi);
//                        hshperemesh.addIndex(hk * hi_count + hi + 1);
//                        hshperemesh.addIndex(hk * hi_count + hi + hi_count);
//            
//                        hshperemesh.addIndex(hk * hi_count + hi + 1);
//                        hshperemesh.addIndex(hk * hi_count + hi + hi_count);
//                        hshperemesh.addIndex(hk * hi_count + hi + hi_count + 1);
//                    }
//                }
            
            
           // hshperemesh.addVertex(ofVec3f(hvtxs[hk][hi].x,hvtxs[hk][hi].y,hvtxs[hk][hi].z));

//        }
//    }
//    ofPushMatrix();
  

 
    
    
//    for (int k=1;k<=90; k++) {
//        for (int i=1;i<=90; i++) {
//            
//            vtxs[k][i].x = ofLerp(vtxs[k][i].x, verts[i].x, 0.2);
//            vtxs[k][i].y = ofLerp(vtxs[k][i].y, verts[i].y, 0.2);
//            vtxs[k][i].z = ofLerp(vtxs[k][i].z, verts[i].z, 0.2);
//        }
//    }
//    
//    
//    for (int k=50;k<=140; k++) {
//        for (int i=1;i<=90; i++) {
//            vtxs[k][i].x = ofLerp(vtxs[k][i].x, verts[i].x, 0.2);
//            vtxs[k][i].y = ofLerp(vtxs[k][i].y, verts[i].y, 0.2);
//            vtxs[k][i].z = ofLerp(vtxs[k][i].z, verts[i].z, 0.2);
//        }
//    }
    
    
    for (int k=0;k<=360; k++) {
        for (int i=0;i<=180; i++) {
            vtxs[k][i].x = ofLerp(vtxs[k][i].x, verts[i].x,0.5);
            vtxs[k][i].y = ofLerp(vtxs[k][i].y, verts[i].y,0.5);
            vtxs[k][i].z = ofLerp(vtxs[k][i].z, verts[i].z,0.5);
        }
    }
    

    
    

}
//--------------------------------------------------------------
void ofApp::update(){


    
}
//--------------------------------------------------------------
void ofApp::draw(){
    
//    float liquidness = 50;
//    float amplitude = 0.02;
//    float amplitude2 = 0.05;
//    float amplitude3 = 0.03;
//    float amplitude4 = 0.01;
//    float speedDampen = ofNoise(50,70);
//    float speedDampen2 = ofNoise(0,70);
//    float speedDampen3 = ofNoise(30,50);
//    float speedDampen4 = ofNoise(50,100);
//    
    
//    for (int k=120;k<=180; k++) {
//        for (int i=120;i<=180; i++) {
//            
//            vtxs[k][i].x = ofLerp(vtxs[k][i].x, hvtxs[k][i].x *0.2, ofSignedNoise(0,5,ofGetElapsedTimef()/speedDampen2)*amplitude4);
//            vtxs[k][i].y = ofLerp(vtxs[k][i].y, hvtxs[k][i].y *0.5, ofSignedNoise(0,5,ofGetElapsedTimef()/speedDampen2)*amplitude4);
//            vtxs[k][i].z = ofLerp(vtxs[k][i].z, hvtxs[k][i].z *1.5, ofSignedNoise(0,5,ofGetElapsedTimef()/speedDampen2)*amplitude4);
//        }
//    }

    
    
//    for (int k=0;k<=360; k++) {
//        for (int i=0;i<=180; i++) {
//            vtxs[k][i].x = ofLerp(vtxs[k][i].x, verts[i].x, ofSignedNoise(0,5,ofGetElapsedTimef()/speedDampen2)*amplitude4);
//            vtxs[k][i].y = ofLerp(vtxs[k][i].y, verts[i].y, ofSignedNoise(0,5,ofGetElapsedTimef()/speedDampen2)*amplitude4);
//            vtxs[k][i].z = ofLerp(vtxs[k][i].z, verts[i].z, ofSignedNoise(0,5,ofGetElapsedTimef()/speedDampen2)*amplitude4);
//        }
//    }
    
    
//    
//    float p;
//    p=20;
//    ofDrawBitmapString(ofToString(sphereMesh.getVertices().size()), 10,10);
//    ofDrawBitmapString(ofToString(sphereMesh.getVertices().size()/2), 50,10);
//    ofDrawBitmapString(ofToString(p),80,10);
//    ofDrawBitmapString(ofToString(pow(p,2.0)), 100,10);
//    
//    //肌がもにもにしている。(鳥肌っぽい)
//    for (int k=1; k<=180; k++) {
//        for (int i=-89; i<=90; i++) {
//            
//            vtxs[k][i].x += ofSignedNoise(vtxs[k][i].x,vtxs[k][i].y,vtxs[k][i].z,ofGetElapsedTimef()/speedDampen)*amplitude;
//     
//            vtxs[k][i].y += ofSignedNoise(vtxs[k][i].z,vtxs[k][i].x,vtxs[k][i].y,ofGetElapsedTimef()/speedDampen)*amplitude;
//         
//            vtxs[k][i].z += ofSignedNoise(vtxs[k][i].y,vtxs[k][i].z,vtxs[k][i].x,ofGetElapsedTimef()/speedDampen)*amplitude;
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
    ofTranslate(500, 0);
    glPointSize(1);
    hshperemesh.drawVertices();
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
