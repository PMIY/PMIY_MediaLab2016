#include "Deform.h"


Deform::Deform( string fileName ){
    
    mod.loadModel(fileName);
    ofDisableArbTex();
    image.load("skin3.jpg");
    
    }


void Deform::setup(){
    
    materialPlane.setAmbientColor(ofFloatColor(0.1,0.1,0.1,1.0));
    materialPlane.setDiffuseColor(ofFloatColor(0.8,0.8,0.8,1.0));
    materialPlane.setSpecularColor(ofFloatColor(0.8,0.8,0.8,1.0));
    materialPlane.setShininess(10);
    
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
    
    
    //テクスチャ貼り付け、メッシュの描画
    materialPlane.begin();
    image.getTexture().bind();
    
    mesh.drawFaces();
    
    image.getTexture().unbind();
    materialPlane.end();
    
    ofPopMatrix();
}
    

   
    
    
    
    //POINT

void Deform::drawDebug(int pnum){
    ofVec3f scale = mod.getScale();
    ofVec3f position = mod.getPosition();
    float normalizedScale = mod.getNormalizedScale();
    mesh = mod.getMesh(0);
    
    ofPushMatrix();
    
    //スケール
    ofScale(normalizedScale, normalizedScale, normalizedScale);
    ofScale(scale.x,scale.y,scale.z);
    
    
    //modify mesh with some noise
    float liquidness = 10;
    float amplitude = 0.02;
    float speedDampen = ofNoise(50,100);
    vector<ofVec3f>& verts = mesh.getVertices();
    
    ofSetColor(0, 255, 255);

    for(unsigned int i = 0; i < verts.size(); i++){
        if(i != pnum){
        ofDrawCircle(verts[i].x, verts[i].y, verts[i].z,0.01);
        }
    }
    
    if(pnum < verts.size()){
        ofSetColor(255, 0, 0);

        ofDrawCircle(verts[pnum].x, verts[pnum].y, verts[pnum].z,0.05);
    }

    ofSetColor(255,255,255);
    
    ofPopMatrix();

}




