#pragma once

#include "ofMain.h"
#include "ofxSyphonServer.h"
#include "ofxXmlSettings.h"

class ofApp : public ofBaseApp{

public:
    void setup();
    void update();
    void draw();
    void writeSettings();

    void keyPressed(int key);
    void mousePressed(int x, int y, int button);
    
    float width;
    float height;
    string syphonName;
    
    
    ofxXmlSettings settings;
    ofxSyphonServer syphonServer;
    
    ofTrueTypeFont font;
		
};
