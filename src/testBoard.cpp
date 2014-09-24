//
//  testBoard.cpp
//  Mutation_080
//
//  Created by Martin Widyanata on 18.09.14.
//
//

#include "testBoard.h"

testBoard::testBoard(ofFbo *fbo){
}

void testBoard::update(){
    
    ofSetColor(ofColor::gray);
    ofRect(0, 0, mFbo->getWidth(), mFbo->getHeight());
    
    ofSetColor(255,122,220);
    
    mString = "Channel No. " + ofToString(mChannelNumber);
    font.drawString(mString, 0, mFbo->getHeight());
    
}