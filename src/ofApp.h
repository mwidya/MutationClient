#pragma once

#include "ofMain.h"
#include "ofxSyphonServer.h"
#include "ofxXmlSettings.h"
#include "ofxNetwork.h"
#include "ofxJSONElement.h"

class ofApp : public ofBaseApp{

public:
    void setup();
    void setupTcp();
    void update();
    void draw();
    void writeSettings();
    void keyPressed(int key);
    void mousePressed(int x, int y, int button);
    
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
	
	
    
    float offsetZ;
    ofPlanePrimitive plane;
    ofMaterial material;
    ofLight pointLight;
    
    
    
    
    ofxTCPClient tcpClient;
    int deltaTime = 0;
    int connectTime = 0;
};
