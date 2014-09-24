//
//  testBoard.h
//  Mutation_080
//
//  Created by Martin Widyanata on 18.09.14.
//
//

#ifndef __Mutation_080__testBoard__
#define __Mutation_080__testBoard__

#include <iostream>
#include "ofMain.h"
#include "board.h"

class testBoard : public board{
public:
    testBoard(ofFbo *fbo);
    void update();
    ofTrueTypeFont font;
    string mString;
};

#endif /* defined(__Mutation_080__testBoard__) */
