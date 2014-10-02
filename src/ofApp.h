#pragma once

#include "ofMain.h"
#include "ofxSyphonServer.h"
#include "ofxXmlSettings.h"
#include "ofxNetwork.h"
#include "ofxJSONElement.h"
#include "ofxOsc.h"

class ofApp : public ofBaseApp{

public:
    void setup();
    void update();
    void draw();
    void writeSettings();
    void readSettings();
    
    ofVec2f normalizedPointToScreenPoint(ofVec2f);
    void parseJSONString(string str);
    
    ofxXmlSettings settings;
    float width;
    float height;
    
    string syphonName;
    ofxSyphonServer syphonServer;
    
    ofImage markerImage;
    int markerId;
    float markerX;
    float markerY;
    float markerWidth;
    float markerHeight;
	
    ofPlanePrimitive plane;
    ofMaterial material;
    ofLight diffuseLight;
    
    int orientation;
    
    ofxOscReceiver receiver;
    
    int oscPort;
    
    ofVec3f planePosition;
    ofVec3f diffuseLightPosition;
    
    bool markerOn;
    
};
