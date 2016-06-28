#include "Deform.h"


Deform::Deform( string fileName ){
    
    mod.loadModel(fileName);

    ofDisableArbTex();
    image.load("skin2.jpg");
    
    ofSetVerticalSync(true);

    //we need to call this for textures to work on models
    ofDisableArbTex();
    
    //this makes sure that the back of the model doesn't show through the front
    ofEnableDepthTest();
    
    }


void Deform::setup(){
    
    
}

void Deform::update(){
    
    
}

void Deform::draw(){
    
    //モデルのスケール取得・位置取得・スケールのノーマライズ化、メッシュ取得
    ofVec3f scale = mod.getScale();
    ofVec3f position = mod.getPosition();
    float normalizedScale = mod.getNormalizedScale();
    mesh = mod.getMesh(0);
    
    ofPushMatrix();
    
    //translate and scale based on the positioning.
    ofScale(normalizedScale, normalizedScale, normalizedScale);
    ofScale(scale.x,scale.y,scale.z);
    ofTranslate(position);
    
    
    //modify mesh with some noise
    float liquidness = 10;
    float amplitude = 0.1;
    float speedDampen = ofNoise(50,100);
    vector<ofVec3f>& verts = mesh.getVertices();
    for(unsigned int i = 0; i < verts.size(); i++){
        
        verts[i].x += ofSignedNoise(verts[i].x/liquidness, verts[i].y/liquidness,verts[i].z/liquidness, ofGetElapsedTimef()/speedDampen)*amplitude;
        verts[i].y += ofSignedNoise(verts[i].z/liquidness, verts[i].x/liquidness,verts[i].y/liquidness, ofGetElapsedTimef()/speedDampen)*amplitude;
        verts[i].z += ofSignedNoise(verts[i].y/liquidness, verts[i].z/liquidness,verts[i].x/liquidness, ofGetElapsedTimef()/speedDampen)*amplitude;
    }
    
    //位置と向きをランダムに
    ofRotate(degree, rotatex, rotatey, rotatez);

    //テクスチャ貼り付け、メッシュの描画
    image.getTexture().bind();
    mesh.drawFaces();
    image.getTexture().unbind();
    
    ofPopMatrix();

      
}




