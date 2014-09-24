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
    
    
    
    offsetZ = 0.0f;
    
    plane.set(width, height);
    plane.setPosition(width*.5f, height*.5f, 0);
    material.setShininess( 120 );
	material.setSpecularColor(ofColor(0, 0, 0, 255));
    
    ofSetSmoothLighting(true);
    pointLight.setDiffuseColor( ofFloatColor(19.f/255.f,94.f/255.f,77.f/255.f)  );
    pointLight.setSpecularColor( ofFloatColor(18.f/255.f,150.f/255.f,135.f/255.f));
    
    
    ofSetVerticalSync(true);
    setupTcp();
    
}

void ofApp::setupTcp(){
    tcpClient.setup(IP, PORT);
    tcpClient.setMessageDelimiter("\n");
    
}

//--------------------------------------------------------------
void ofApp::update(){
    if (tcpClient.isConnected())
    {
        string str = tcpClient.receive();
        
        if( str.length() > 0 )
        {
            cout << "str = " << str << endl;
            offsetZ = ofToFloat(str);
//            parseJSONString(str);
        }
    }
    else
    {
        deltaTime = ofGetElapsedTimeMillis() - connectTime;
		if( deltaTime > 5000 ){
			setupTcp();
			connectTime = ofGetElapsedTimeMillis();
		}
	}

}


//--------------------------------------------------------------
void ofApp::draw(){
    
    ofClear(0);
    
    ofEnableDepthTest();
    ofEnableLighting();
    
    plane.setPosition(plane.getPosition().x, plane.getPosition().y, plane.getPosition().z);
    pointLight.setPosition(plane.getPosition().x,
                           plane.getPosition().y,
                           plane.getPosition().z + sin(offsetZ*.5f)*plane.getHeight()*1.5);
    pointLight.lookAt(plane);
    pointLight.enable();
    
//    plane.rotate(cos(ofGetElapsedTimef()*.6), 1.0, 0.0, 0.0);
    
	material.begin();
    
    ofFill();
    ofSetColor(255);
    plane.draw();
    
    material.end();
    
    ofDisableLighting();
    ofDisableDepthTest();
    ofFill();
    
    
    
    
    
    
    ofSetColor(255, 255, 255);
    float frame = 80*factor;
    ofRect(markerX-(frame/2), markerY-(frame/2), markerWidth+frame, markerHeight+frame);
    markerImage.draw(markerX, markerY, markerWidth, markerHeight);
    
    
    
    
    
    
    syphonServer.publishScreen();
    
    ofDrawBitmapString("Syphon Server: " + syphonName, width-150, 15);
    
    ofDrawBitmapString("framerate: " + ofToString(ofGetFrameRate()), ofGetWidth()-150, height-15);
    string tcpString = "";
    if (tcpClient.isConnected()) {
        tcpString = "TCP client is connected to ip " + ofToString(tcpClient.getIP()) + " at port: " + ofToString(tcpClient.getPort());
    }
    else{
        tcpString = "TCP client couldn't connect to ip " + ofToString(IP) + " at port: " + ofToString(PORT);
    }
    ofDrawBitmapString(tcpString, 10, height-15);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}