#include "ofApp.h"
#include "constants.h"
#include "ofxXmlSettings.h"

//--------------------------------------------------------------
void ofApp::setup(){

    ofSetDataPathRoot("../Resources/data/");
    
    /*
     ofxXmlSettings settings;
     settings.setValue("settings:width", f0Long);
     settings.setValue("settings:height", f0Short);
     settings.setValue("settings:syphon_name", "f0");
     settings.saveFile("settings.xml"); //puts settings.xml file in the bin/data folder*/
    
    ofxXmlSettings settings;
    settings.loadFile("../settings.xml");
    width = settings.getValue("settings:width", 100.0);
    height = settings.getValue("settings:height", 100.0);
    syphonName = settings.getValue("settings:syphon_name", "...");
    
    ofSetWindowShape(width, height);
    
    syphonServer.setName(syphonName);
    
    font.loadFont("vag.ttf", 30);
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){

    ofDrawBitmapString("framerate: " + ofToString(ofGetFrameRate()), ofGetWidth()-140, 10);
    
    font.drawString("Syphon Server: " + syphonName, 0, height);
    
    syphonServer.publishScreen();

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}