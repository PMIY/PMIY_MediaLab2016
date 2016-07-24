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

};
