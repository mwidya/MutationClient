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
    void mouseDragged(int x, int y, int button);
    void exit();
    
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
	
	
    
    float offsetZ;
    ofPlanePrimitive plane;
    ofMaterial material;
    ofLight diffuseLight;
    
    ofxTCPClient tcpClient;
    int deltaTime = 0;
    int connectTime = 0;
    
    ofxJSONElement jsonElement;
    ofVec2f screenPoint;
    string event;
    int aMarkerId;
    
    float lightPosX;
};
