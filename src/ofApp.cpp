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

void ofApp::setupTcp(){
    //    tcpClient.setup(IP, PORT);
    //    tcpClient.setMessageDelimiter("\n");
    
}

ofVec2f ofApp::normalizedPointToScreenPoint(ofVec2f normalizedPoint){
    ofVec2f point;
    
    point.x = normalizedPoint.x * ofGetWidth();
    point.y = normalizedPoint.y * ofGetHeight();
    
    return point;
}

void ofApp::parseJSONString(string str){
    
    jsonElement = ofxJSONElement(str);
    
    /*lightPosition.x = jsonElement["lightPosX"].asFloat();
     
     event = jsonElement["event"].asString();
     aMarkerId = jsonElement["id"].asInt();
     float x = jsonElement["x"].asFloat();
     float y = jsonElement["y"].asFloat();
     
     screenPoint = normalizedPointToScreenPoint(ofVec2f(x, y));*/
    
}

//--------------------------------------------------------------
void ofApp::setup(){

    ofSetDataPathRoot("../Resources/data/");
    
    writeSettings();
    
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
        anOrientation = settings.getValue("settings:orientation", -1);
        if (loaded) {
            break;
        }
    }
    
    ofSetWindowShape(width, height);
    
    syphonServer.setName(syphonName);
    
    string path = "images/marker_" + ofToString(markerId) + ".png";
    markerImage.loadImage(path);
    
    
    
    offsetZ = 0.0f;
    
    float grayAttenuation = 0.0f;
    ofSetGlobalAmbientColor(ofColor(245*grayAttenuation,224*grayAttenuation,253*grayAttenuation));
    
    plane.set(width, height);
    plane.rotate(-90, 1, 0, 0);
    plane.setPosition(width*.5f, height*.5f, 0);
    
    ofSetSmoothLighting(true);
    diffuseLight.setDiffuseColor(ofFloatColor(1));
    diffuseLight.setPosition(plane.getPosition().x, plane.getPosition().y, plane.getPosition().z);
    
    material.setShininess( 120 );
	material.setSpecularColor(ofFloatColor(1,0,0));
    
    
    ofSetVerticalSync(true);
    setupTcp();
    
    receiver.setup(oscPort);
}

//--------------------------------------------------------------
void ofApp::update(){
    if (tcpClient.isConnected())
    {
        string str = tcpClient.receive();
        
        if( str.length() > 0 )
        {
            cout << "str = " << str << endl;
            parseJSONString(str);
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
    
    while(receiver.hasWaitingMessages()){
    
        ofxOscMessage m;
		receiver.getNextMessage(&m);
        
		if(m.getAddress() == "/diffuseLight/position"){
			lightPosition = ofVec3f(m.getArgAsFloat(0), m.getArgAsFloat(1), m.getArgAsFloat(2));
		}
        
        string s = syphonName+"/position";
		if(m.getAddress() == s){
            cout << "m = " << m.getAddress() << endl;
            cout << "m = " << m.getRemoteIp() << endl;
            cout << "m = " << m.getRemotePort() << endl;
            
            position = ofVec3f(m.getArgAsFloat(0), m.getArgAsFloat(1), m.getArgAsFloat(2));
//            plane.setPosition(position.x, position.y, position.z);
            cout << "position = " << position << endl;
		}
    }

}

//--------------------------------------------------------------
void ofApp::draw(){
    
    ofClear(0);
    
    ofEnableDepthTest();
    ofEnableLighting();
    
    
    ofPushMatrix();
    ofTranslate(width*.5f, height*.5);
    
    
    ofRotateX(90);
    
    plane.setPosition(0, 0, 0 + offsetZ);
	material.begin();
    
    ofFill();
    ofSetColor(255);
    plane.draw();
    
    material.end();
    ofPopMatrix();
    
    ofPushMatrix();
    ofTranslate(width*.5f, height*.5);
    
    
    ofRotateX(-90);
    switch (anOrientation) {
        case FLOOR:
            // ...
            break;
        case EAST:
            diffuseLight.setPosition(0,
                                     position.x - lightPosition.x,
                                     diffuseLight.getPosition().z + offsetZ);
            break;
        case WEST:
            // ...
            break;
            
        default:
            break;
    }
    
    diffuseLight.lookAt(plane);
    diffuseLight.enable();
    
    offsetZ = 0.0f;
    
//    plane.rotate(cos(ofGetElapsedTimef()*.6), 1.0, 0.0, 0.0);
    
    
    diffuseLight.draw();
    ofPopMatrix();
    
    ofDisableLighting();
    ofDisableDepthTest();
    ofFill();
    
    
    
    
    
    
    ofSetColor(255, 255, 255);
    float frame = 80*factor;
    ofRect(markerX-(frame/2), markerY-(frame/2), markerWidth+frame, markerHeight+frame);
    markerImage.draw(markerX, markerY, markerWidth, markerHeight);
    
    
    
    
    
    
    syphonServer.publishScreen();
    
    int linePitch = 20;
    
    ofDrawBitmapString("Plane Pos: " + ofToString(position.x)+", "+ofToString(position.y)+", "+ofToString(position.z),  10, height-(linePitch*4));
    ofDrawBitmapString("Light Pos: " + ofToString(lightPosition.x)+", "+ofToString(lightPosition.y)+", "+ofToString(lightPosition.z),  10, height-(linePitch*3));
    ofDrawBitmapString("Syphon Server: " + syphonName, 10, height-(linePitch*2));
    string tcpString = "";
    if (tcpClient.isConnected()) {
        tcpString = "TCP client is connected to ip " + ofToString(tcpClient.getIP()) + " at port: " + ofToString(tcpClient.getPort());
    }
    else{
        tcpString = "TCP client couldn't connect to ip " + ofToString(IP) + " at port: " + ofToString(PORT);
    }
    
    ofDrawBitmapString("fps: " + ofToString(ofGetFrameRate()), 10, height-linePitch);
    ofDrawBitmapString(tcpString, width-470, height-linePitch);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if (key==OF_KEY_UP) {
        offsetZ++;
    }
    if (key==OF_KEY_DOWN) {
        offsetZ--;
    }
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

void ofApp::mouseDragged(int x, int y, int button){
}

void ofApp::exit(){
    tcpClient.close();
    cout << "tcpClient closed." << endl;
}



