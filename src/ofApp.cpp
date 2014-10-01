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
        settings.setValue("settings:oscPort", oscPorts[i]);
        settings.setValue("settings:orientation", orientations[i]);
        
        settings.saveFile("settings"+ofToString(i)+".xml"); //puts settings.xml file in the bin/data folder
        
    }
    
}

void ofApp::readSettings(){
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
        oscPort = settings.getValue("settings:oscPort", 6999);
        orientation = settings.getValue("settings:orientation", -1);
        if (loaded) {
            break;
        }
    }
    
}

//--------------------------------------------------------------
void ofApp::setup(){

    ofSetDataPathRoot("../Resources/data/");
    
//    writeSettings();
    readSettings();
    
    ofSetWindowShape(width, height);
    
    syphonServer.setName(syphonName);
    
    ofSetVerticalSync(true);
    
    receiver.setup(oscPort);
    
    string path = "images/marker_" + ofToString(markerId) + ".png";
    markerImage.loadImage(path);
    
    ofSetGlobalAmbientColor(ofFloatColor(0.5f,0.5f, 0.5f));
    
    ofSetSmoothLighting(true);
    diffuseLight.setDiffuseColor(ofFloatColor(19.f/255.f,94.f/255.f,77.f/255.f));
    
    material.setShininess( 120 );
	material.setSpecularColor(ofFloatColor(1));
    
    
    
    plane.set(width, height);
//    plane.rotate(-90, 0, 1, 0);
}

void ofApp::update(){
    
    while(receiver.hasWaitingMessages()){
        
        ofxOscMessage m;
		receiver.getNextMessage(&m);
        
        string s = syphonName+"/position";
		if(m.getAddress() == s){
            planePosition = ofVec3f(m.getArgAsFloat(0), m.getArgAsFloat(1), m.getArgAsFloat(2));
            plane.setPosition(planePosition);
		}
        
		if(m.getAddress() == "/diffuseLight/position"){
            switch (orientation) {
                case EAST:
                    diffuseLightPosition = ofVec3f(m.getArgAsFloat(2)+planePosition.x, m.getArgAsFloat(1), m.getArgAsFloat(0)-planePosition.x);
                    break;
                    
                default:
                    break;
            }
            diffuseLight.setPosition(diffuseLightPosition);
		}
    }
}

void ofApp::draw(){
    
    ofClear(0);
    
    ofPushMatrix();
    
    ofEnableDepthTest();
    ofEnableLighting();
	material.begin();
    
    ofTranslate(width*.5f-planePosition.x, height*.5f-planePosition.y);
//    ofRotateY(90);
    
    diffuseLight.lookAt(plane);
    diffuseLight.enable();
    plane.draw();
    diffuseLight.draw();
    
    ofPopMatrix();
    
    material.end();
    ofDisableLighting();
    ofDisableDepthTest();
    
    
    syphonServer.publishScreen();
    
    int linePitch = 20;
    
    ofDrawBitmapString("Plane Pos: " + ofToString(plane.getPosition().x)+", "+ofToString(plane.getPosition().y)+", "+ofToString(plane.getPosition().z),  10, height-(linePitch*4));
    ofDrawBitmapString("Light Pos: " + ofToString(diffuseLight.getPosition().x)+", "+ofToString(diffuseLight.getPosition().y)+", "+ofToString(diffuseLight.getPosition().z),  10, height-(linePitch*3));
    ofDrawBitmapString("Syphon Server: " + syphonName, 10, height-(linePitch*2));
    string tcpString = "";
    
    ofDrawBitmapString("fps: " + ofToString(ofGetFrameRate()), 10, height-linePitch);
    ofDrawBitmapString(tcpString, width-470, height-linePitch);
}



