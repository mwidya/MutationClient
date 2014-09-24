#include "ofApp.h"
#include "constants.h"

void ofApp::writeSettings(){
    
    for (int i = 0; i<10; i++) {
        settings.setValue("settings:width", surfacesLong[i]);
        settings.setValue("settings:height", surfacesShort[i]);
        settings.setValue("settings:syphon_name", "f"+ofToString(i));
        settings.setValue("settings:markerId", markerIds[i]);
        settings.setValue("settings:markerX", markerXs[i]);
        settings.setValue("settings:markerY", markerYs[i]);
        settings.setValue("settings:markerWidth", markerWidths[i]);
        settings.setValue("settings:markerHeight", markerHeights[i]);
        settings.saveFile("settings"+ofToString(i)+".xml"); //puts settings.xml file in the bin/data folder
        
    }
    
}

//--------------------------------------------------------------
void ofApp::setup(){

    ofSetDataPathRoot("../Resources/data/");
    
//    writeSettings();
    
    for (int i = 0; i<10; i++) {
        bool loaded = settings.loadFile("../../../../settings"+ofToString(i)+".xml");
        width = settings.getValue("settings:width", 100.0);
        height = settings.getValue("settings:height", 100.0);
        syphonName = settings.getValue("settings:syphon_name", "...");
        markerId = settings.getValue("settings:markerId", 0);
        markerX = settings.getValue("settings:markerX", 0);
        markerY = settings.getValue("settings:markerY", 0);
        markerWidth = settings.getValue("settings:markerWidth", 0);
        markerHeight = settings.getValue("settings:markerHeight", 0);
        if (loaded) {
            break;
        }
    }
    
    ofSetWindowShape(width, height);
    
    syphonServer.setName(syphonName);
    
    string path = "images/marker_" + ofToString(markerId) + ".png";
    markerImage.loadImage(path);
    
    
    
    
    
    font.loadFont("vag.ttf", 30);
}

//--------------------------------------------------------------
void ofApp::update(){

}

void ofApp::drawMarker(){
    ofSetColor(255, 255, 255);
    float frame = 80*factor;
    ofRect(markerX-(frame/2), markerY-(frame/2), markerWidth+frame, markerHeight+frame);
    markerImage.draw(markerX, markerY, markerWidth, markerHeight);
}

//--------------------------------------------------------------
void ofApp::draw(){

    ofDrawBitmapString("framerate: " + ofToString(ofGetFrameRate()), ofGetWidth()-140, 10);
    
    font.drawString("Syphon Server: " + syphonName, 0, height);
    
    drawMarker();
    
    
    
    
    syphonServer.publishScreen();

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}