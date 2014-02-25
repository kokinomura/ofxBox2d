#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup() {
	ofSetVerticalSync(true);
	ofBackgroundHex(0xfdefc2);
	ofSetLogLevel(OF_LOG_NOTICE);
	
	box2d.init();
	box2d.setGravity(0, 10);
	box2d.createBounds();
	box2d.setFPS(30.0);
	box2d.registerGrabbing();
	
	body.setup(box2d.getWorld(), ofGetWidth()/2, ofGetHeight()/2);
    for (int i=0; i<3; i++) {
        ofxBox2dCircle circle;
        circle.setPhysics(3.0, 0.53, 0.1);
        circle.setup(box2d.getWorld(), ofGetWidth()/2 + i*20, ofGetHeight()/2, 10);
        body.addCircle(circle);
    }
    
    for (int i=0; i<3; i++) {
        ofxBox2dRect rect;
        rect.setPhysics(3.0, 0.53, 0.1);
        rect.setup(box2d.getWorld(), ofGetWidth()/2 + i*20, ofGetHeight()/2-20, 8, 8);
        body.addRect(rect);
    }
}

//--------------------------------------------------------------
void testApp::update() {
	box2d.update();	
}


//--------------------------------------------------------------
void testApp::draw() {
	
    ofFill();
    ofSetHexColor(0xf6c738);
	body.draw();

    ofSetColor(255, 200, 200);
    for (int i=0; i<circles.size(); i++) {
        circles[i]->draw();
    }
    
	// draw the ground
	box2d.drawGround();
	
	string info = "";
	info += "Press [c] for circles\n";
	info += "Press [b] for blocks\n";
	info += "Total Bodies: "+ofToString(box2d.getBodyCount())+"\n";
	info += "Total Joints: "+ofToString(box2d.getJointCount())+"\n\n";
	info += "FPS: "+ofToString(ofGetFrameRate(), 1)+"\n";
	ofSetHexColor(0x444342);
	ofDrawBitmapString(info, 30, 30);
}

//--------------------------------------------------------------
void testApp::keyPressed(int key) {
	
	if(key == 'c') {
		float r = ofRandom(4, 20);
		circles.push_back(ofPtr<ofxBox2dCircle>(new ofxBox2dCircle));
		circles.back().get()->setPhysics(3.0, 0.53, 0.1);
		circles.back().get()->setup(box2d.getWorld(), mouseX, mouseY, r);
		
	}
//	
//	if(key == 'b') {
//		float w = ofRandom(4, 20);
//		float h = ofRandom(4, 20);
//		boxes.push_back(ofPtr<ofxBox2dRect>(new ofxBox2dRect));
//		boxes.back().get()->setPhysics(3.0, 0.53, 0.1);
//		boxes.back().get()->setup(box2d.getWorld(), mouseX, mouseY, w, h);
//	}
	
	if(key == 't') ofToggleFullscreen();
}

//--------------------------------------------------------------
void testApp::keyReleased(int key) {
}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ) {
	
}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button) {
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button) {
	
}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button) {
}

//--------------------------------------------------------------
void testApp::resized(int w, int h){
}

