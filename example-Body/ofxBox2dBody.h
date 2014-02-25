//
//  ofxBox2dBody.h
//
//  Created by nomura on 2014/02/25.
//
//

#pragma once

#include "ofMain.h"
#include "ofxBox2dBaseShape.h"
#include "ofxBox2dRect.h"
#include "ofxBox2dCircle.h"

class ofxBox2dBody : public ofxBox2dBaseShape {
public:
    
    ofxBox2dBody();
    ~ofxBox2dBody();
    
    //----------------------------------------
    void setup(b2World * b2dworld, float x, float y);
    
    //----------------------------------------    
    void addRect(ofxBox2dRect & rect);
    void addCircle(ofxBox2dCircle & circle);
    
    //----------------------------------------    
    void draw();
    void destroy();
    
private:
    void _drawCircle(b2Vec2 center, float radius);
    void _drawPolygon(b2Vec2* vertices, int count);
};