#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup()
{
	ofSetVerticalSync(true);
	ofEnableSmoothing();
	ofEnableAlphaBlending();
	ofSetFrameRate(60);
	println("Done Setup");
	particles.reserve(20000);
	
	gui.setup(); // most of the time you don't need a name
	gui.add(paraCollisionMult.setup("paraCollisionMult", 0.0, 0.0, 0.08));
	gui.add(paraColorDiffMult.setup("paraColorDiffMult", 0.0, 0.0, 0.04));
}

//--------------------------------------------------------------
void ofApp::update()
{
	updateParameter();
	for (unsigned int i=0; i<particles.size(); ++i){
		particles[i].update();
	}
	if (isMousePressed) {
		ofVec3f vel = ofVec3f(0,0,0);
		for (int i=0; i<1 ; ++i){
			generateParticle(	ofVec3f(ofGetMouseX(), ofGetMouseY(), 0.0), 
								vel);
		}
	}
}

//--------------------------------------------------------------
void ofApp::draw()
{
	ofBackground(240);
	ofDrawBitmapString(ofToString(ofGetFrameRate()),10,10);
	for (unsigned int i=0 ; i<particles.size(); ++i){
		particles[i].draw();
	}
	
	gui.draw();
}

//--------------------------------------------------------------
void ofApp::println(string s)
{
	cout << s << endl;
}

void ofApp::updateParameter()
{
	if (paraCollisionMult != paraCollisionMultOld) {
		setParticlesCollisionMult(paraCollisionMult);
		paraCollisionMultOld = paraCollisionMult;
	}
	if (paraColorDiffMult != paraColorDiffMultOld) {
		setParticlesColorDiffMult(paraColorDiffMult);
		paraColorDiffMultOld = paraColorDiffMult;
	}
}

//--------------------------------------------------------------
void ofApp::generateParticle(ofVec3f pos, ofVec3f vel)
{
	particles.push_back(Particle(&particles, pos, vel));
}

void ofApp::setParticlesCollisionMult(float val)
{
	for (unsigned int i=0; i<particles.size(); ++i){
		particles[i].CONST_COLLISION_MULT = val;
	}
}
void ofApp::setParticlesColorDiffMult(float val)
{
	for (unsigned int i=0; i<particles.size(); ++i){
		particles[i].CONST_COLOR_DIFF_MULT = val;
	}
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key)
{

	if (key == '1') {
		for (unsigned int i=0; i<particles.size(); ++i){
			particles[i].enableAttribute(1 << 14);
			particles[i].disableAttribute(1 << 11);

		}
	} else if (key == '2') {
		particles[0].disableAttribute(ATTR_SPRING_PREV);
	} else if (key == '3') {
		particles[0].enableAttribute(ATTR_CONNECT_NEXT);
	} else if (key == '4') {
		particles[0].disableAttribute(ATTR_CONNECT_NEXT);
	} else {
		generateParticle(	ofVec3f(ofGetMouseX(), ofGetMouseY(), 0.0), 
								ofVec3f(0.0, 4.0, 0.0));
	}

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
	isMousePressed = true;
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
	isMousePressed = false;
}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
