#pragma once

#include "ofMain.h"
#include "ofxAssimpModelLoader.h"

class ofApp : public ofBaseApp{
    
public:
    void setup();
    void update();
    void draw();
    
    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void mouseEntered(int x, int y);
    void mouseExited(int x, int y);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
    
    ofEasyCam cam;
    ofVboMesh modmesh,hshperemesh;
    ofVec3f vtxs[361][181];
    ofVec3f hvtxs[361][181];
    vector<ofVec3f> verts,sphereverts;
    ofVec3f modVec;
    
    ofxAssimpModelLoader mod;
    ofLight light,light2,light3;
    ofImage image;
    ofMaterial material;
    
    GLuint tex;
    float tex_width;
    float tex_height;
    
    ofSpherePrimitive sphere;
    ofMesh sphereMesh;
    
    float HomeoBox [68] = {18,18,18,7,18,17,20,25,20,18,25,17,20,12,5,12,5,11,5,6,8,20,14,8,25,12,20,18,18,18,18,9,5,13,1,8,1,12,3,12,20,5,18,17,9,11,9,23,6,17,14,18,18,13,11,12,11,11,5,9};
    
    
};
