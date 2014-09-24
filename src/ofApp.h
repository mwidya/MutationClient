#pragma once

#include "ofMain.h"
#include "ofxSyphonServer.h"
#include "testBoard.h"

class ofApp : public ofBaseApp{

public:
    void setup();
    void update();
    void draw();

    void keyPressed(int key);
    void mousePressed(int x, int y, int button);
    
    float width;
    float height;
    string syphonName;
    
    ofxSyphonServer syphonServer;
    
    ofTrueTypeFont font;
		
};
