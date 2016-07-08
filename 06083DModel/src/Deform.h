#ifndef ____Deform__
#define ____Deform__

#include <stdio.h>
#include "ofMain.h"
#include "ofxAssimpModelLoader.h"

class Deform{
public:
    
    Deform( string fileName );
    
    void setup();
    void update();
    void draw();
    void drawDebug(int pnum);
    ofVec3f position;
    
    ofVboMesh mesh;
    ofImage image;
    ofxAssimpModelLoader mod;
    //ofThread thread;
    
    float degree = ofRandom(360);
    float rotatex = ofRandom(360);
    float rotatey = ofRandom(360);
    float rotatez = ofRandom(360);
    
    ofMaterial 	materialPlane;

};

#endif /* defined(____Deform__) */
