#include "testApp.h"


//--------------------------------------------------------------
void testApp::setup(){
	this->useSine = false;
	this->clear();
}

//--------------------------------------------------------------
void testApp::update(){
	
	float time = ofGetElapsedTimef() - startTime;
	float value;
	
	if (this->useSine)
		value = (sin(ofGetElapsedTimef()) + 1.0f) * ofGetHeight() / 4.0f;
	else
		value = ofGetMouseY();
	
	pair<float, float> point(time, value);
	recordRaw.insert(point);
	recordTrace.add(point);
	
	if (time > 10.0f)
		this->clear();
}

//--------------------------------------------------------------
void testApp::draw(){
	
	ofBackgroundGradient(ofColor(50), ofColor(10));
	ofPushMatrix();
	
	//scale so screen width = 10 seconds
	ofScale(ofGetWidth() / 10.0f, 0.5f, 1.0f);
	
	this->recordTrace.draw();
	
	// draw the raw data on bottom half of screen
	ofTranslate(0.0f, ofGetHeight());
	ofPushStyle();
	ofSetColor(255);
	glPointSize(3.0f);
	ofMesh rawPoints;
	for (map<float, float>::const_iterator it = recordRaw.begin(); it != recordRaw.end(); it++) {
		rawPoints.addVertex(ofVec3f(it->first, it->second, 0.0f));
	}
	rawPoints.drawVertices();
	ofPopStyle();
	
	ofPopMatrix();
	float y = 20;
	ofDrawBitmapString("Press [SPACE] to reset recording", 20, y+=15);
	ofDrawBitmapString("Press [s] to toggle sine signal generator [" + string(useSine ? "x" : " ") + "]", 20, y+=15);
	
	ofDrawBitmapString("Click somewhere in the x direction to set the threshold [" + ofToString(recordTrace.getThreshold()) + "]", 20, y+=15);
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
	if (key == ' ')
		this->clear();
	if (key == 's')
		useSine ^= true;
}

//--------------------------------------------------------------
void testApp::clear() {
	this->startTime = ofGetElapsedTimef();
	this->recordTrace.clear();
	this->recordRaw.clear();
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y){
}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
	recordTrace.setThreshold(float(x) / ofGetWidth() * 0.3f);
}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}