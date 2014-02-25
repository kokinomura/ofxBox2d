//
//  ofxBox2dBody.cpp
//
//  Created by Koki Nomura on 2014/02/25.
//

//  This currently supports only dynamicBody

#include "ofxBox2dBody.h"

//----------------------------------------
ofxBox2dBody::ofxBox2dBody() : ofxBox2dBaseShape() {
    ;
}

//----------------------------------------
ofxBox2dBody::~ofxBox2dBody() {
    ofLog(OF_LOG_VERBOSE, "~ofxBox2dBody(%p)\n", body);
    destroy();
}

//----------------------------------------
void ofxBox2dBody::setup(b2World *b2dworld, float x, float y) {
    
    if(b2dworld == NULL) {
		ofLog(OF_LOG_NOTICE, "ofxBox2dBody :: setup : - must have a valid world -");
		return;
	}
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(x/OFX_BOX2D_SCALE, y/OFX_BOX2D_SCALE);
    body = b2dworld->CreateBody(&bodyDef);
}

//----------------------------------------
void ofxBox2dBody::addRect(ofxBox2dRect &rect) {
    ofVec2f rectPosition = rect.getPosition();
    rectPosition /= OFX_BOX2D_SCALE;
    b2Vec2 relativePosition = b2Vec2(rectPosition.x, rectPosition.y) - body->GetPosition();
    
    b2PolygonShape shape;
    float width = rect.getWidth() / OFX_BOX2D_SCALE;
    float height = rect.getHeight() / OFX_BOX2D_SCALE;
    shape.SetAsBox(width, height, relativePosition, rect.getRotation());
    
    b2FixtureDef fixture;
    fixture.shape = &shape;
    fixture.density = rect.density;
    fixture.friction = rect.friction;
    fixture.restitution = rect.bounce;
    
    body->CreateFixture(&fixture);
}

void ofxBox2dBody::addCircle(ofxBox2dCircle &circle) {

    ofVec2f circlePosition = circle.getPosition();
    circlePosition /= OFX_BOX2D_SCALE;
    
    b2Vec2 relativePosition = b2Vec2(circlePosition.x, circlePosition.y) - body->GetPosition(); 
    
    b2CircleShape shape;
    shape.m_p = relativePosition;
	shape.m_radius = circle.getRadius() / OFX_BOX2D_SCALE;
    
    b2FixtureDef fixture;
    fixture.shape = &shape;
    fixture.density = circle.density;
    fixture.friction = circle.friction;
    fixture.restitution = circle.bounce;
    
    body->CreateFixture(&fixture);
}

//----------------------------------------
void ofxBox2dBody::draw() {
    
    ofPushMatrix();
    
    b2Vec2 p = body->GetPosition();
    p *= OFX_BOX2D_SCALE;
    ofTranslate(p.x, p.y);
    
    float angle = body->GetAngle();
    ofRotate(ofRadToDeg(angle));
    
    for (b2Fixture* f=body->GetFixtureList(); f; f = f->GetNext()) {
        switch (f->GetType()) {
            case b2Shape::e_circle:
            {
                b2CircleShape* shape = dynamic_cast<b2CircleShape*>(f->GetShape());
                b2Vec2 position = shape->m_p;
                float radius = shape->m_radius;
                _drawCircle(position, radius);
                break;
            }
            case b2Shape::e_polygon:
            {
                b2PolygonShape* shape = dynamic_cast<b2PolygonShape*>(f->GetShape());
                _drawPolygon(shape->m_vertices, shape->m_count);
                break;
            }
            default:
                break;
        }
    }
    
    ofPopMatrix();
}

//----------------------------------------
void ofxBox2dBody::destroy() {
	
	if(getWorld() == NULL) {
		ofLog(OF_LOG_NOTICE, "ofxBox2dBody:: - must have a valid world -");
		return;
	}
	else if(body == NULL) {
		ofLog(OF_LOG_NOTICE, "ofxBox2dBody:: - null body -");
		return;
	}
    
	getWorld()->DestroyBody(body);
	body  = NULL;
	alive = false;
}

//----------------------------------------
void ofxBox2dBody::_drawCircle(b2Vec2 center, float radius) {
	
    if(!isBody()) {return;}
    
    center *= OFX_BOX2D_SCALE;
    radius *= OFX_BOX2D_SCALE;
    
    ofPushMatrix();
    ofTranslate(center.x, center.y);
    ofCircle(0, 0, radius);
    
    ofPushStyle();
    ofEnableAlphaBlending();
    ofSetColor(0);
    ofLine(0, 0, radius, 0);
    if(isSleeping()) {
        ofSetColor(255, 100);
        ofCircle(0, 0, radius);
    }
    ofPopStyle();
    
    ofPopMatrix();
    
}

void ofxBox2dBody::_drawPolygon(b2Vec2 *vertices, int count) {
    
    if(!isBody()) {return;}
    
    ofBeginShape();
    for (int i=0; i<count; i++) {
        b2Vec2 vertex = vertices[i];
        vertex *= OFX_BOX2D_SCALE;
        ofVertex(vertex.x, vertex.y);
    }
    ofEndShape();
}








