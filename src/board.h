//
//  board.h
//  Mutation
//
//  Created by Martin Widyanata on 29.08.14.
//
//

#ifndef __Mutation__board__
#define __Mutation__board__

#include <iostream>
#include "ofMain.h"
#include "marker.h"

class channel;

class board{ 
public:
    void clear();
    void triggerAtPoint(int x, int y, string event);
    
    auto_ptr<channel> mChannel;
    
    ofFbo *mFbo;
    marker *mMarker;
    int mChannelNumber;
    
    board *mAscendantBoard;
    board *mDescendantBoard;
};

#endif /* defined(__Mutation__board__) */
