#include "ofApp.h"

string ofApp::getBit(int k)
{
	string s;
	for (int i=0; i<22; ++i){
		if (k & (1 << i)) {
			s = "1" + s;
		} else {
			s = "0" + s;
		}
	}
	return s;
}
//--------------------------------------------------------------
void ofApp::setup()
{
	ofSetVerticalSync(true);
	ofEnableSmoothing();
	ofEnableDepthTest();
	ofSetFrameRate(60);
	println("Done Setup");
	particles.reserve(20000);
	
	staticParticles.reserve(2000);
	
	
	//-------------------------------------------------------------------------GUI----------
	//attr_collision.addListener(this, &(void(){}));
	
	attr_collision.addListener(this, &ofApp::setAttributeCollision);
	attr_color_diff.addListener(this, &ofApp::setAttributeColorDiff);
	attr_spring_prev.addListener(this, &ofApp::setAttributeSpringPrev);

	gui.setup();
	gui.add(paraCollisionMult.setup("paraCollisionMult", 0.0, 0.0, 0.08));
	gui.add(paraColorDiffMult.setup("paraColorDiffMult", 0.0, 0.0, 0.04));
	gui.add(paraBorderX.setup("paraBorderX",ofVec2f(-100,100),ofVec2f(-1000,-1000),ofVec2f(1000,1000)));
	gui.add(paraBorderY.setup("paraBorderY",ofVec2f(-100,100),ofVec2f(-1000,-1000),ofVec2f(1000,1000)));
	gui.add(paraBorderZ.setup("paraBorderZ",ofVec2f(-100,100),ofVec2f(-100,-100),ofVec2f(100,1000)));
	gui.add(attr_collision.setup("attr_collision",false));
	gui.add(attr_spring_prev.setup("attr_spring_dev",false));
	gui.add(attr_color_diff.setup("attr_color_diff",false));
	//---------------------------------------------------------------------------------------
	

	//-------------------------------------CAMERA--------------
	camera.setDistance(100);
	
	//---------------------------------------------------------
	
	
	//----------------------------STATIC PARTICLES---------------
	int num = 400;
	for (unsigned int i=0; i<num; ++i){
		//spherical
		float a1 = ofRandom(0,TWO_PI);
		float a2 = ofRandom(0,TWO_PI);
		
		float dist = 1500;
		ofVec3f pos( dist*cos(a1)*cos(a2), dist*sin(a1)*cos(a2), dist*sin(a2));
		staticParticles.push_back(Particle(&staticParticles,0, pos, ofVec3f(0,0,0)));
		staticParticles[i].lookAt(ofVec3f(0,0,0));
		staticParticles[i].color = ofColor(0,120);
		staticParticles[i].setRadius(10);
	}
	
	//----------------------------------------------------------
	
}

void ofApp::setAttributeCollision(bool &attr_collision)
{
	if (attr_collision) {
		attributesNextParticle |= ATTR_COLLISION;
	} else {
		attributesNextParticle &= ~ATTR_COLLISION;
	}
	cout << getBit(attributesNextParticle) << endl;
}
void ofApp::setAttributeColorDiff(bool &attr_color_diff)
{
	if (attr_color_diff) {
		attributesNextParticle |= ATTR_COLOR_DIFF;
	} else {
		attributesNextParticle &= ~ATTR_COLOR_DIFF;
	}
	cout << getBit(attributesNextParticle) << endl;
	
}
void ofApp::setAttributeSpringPrev(bool &attr_spring_prev)
{
	if (attr_spring_prev) {
		attributesNextParticle |= ATTR_SPRING_PREV;
	} else {
		attributesNextParticle &= ~ATTR_SPRING_PREV;
	}
	cout << getBit(attributesNextParticle) << endl;
	
}
//--------------------------------------------------------------
void ofApp::update()
{
	updateParameter();
	for (unsigned int i=0; i<particles.size(); ++i){
		particles[i].update();
	}
}

//--------------------------------------------------------------
void ofApp::draw()
{	
	camera.begin();
	ofBackground(240);
	//ofPushMatrix();
	//ofTranslate(ofGetWidth()/2, ofGetHeight()/2);
	ofDisableDepthTest();
	for (unsigned int i=0; i<staticParticles.size(); ++i){
		staticParticles[i].draw(-staticParticles[i].getPosition());
	}
	
	ofEnableDepthTest();
	for (unsigned int i=0 ; i<particles.size(); ++i){
		particles[i].draw(camera.getPosition());
	}

	ofDrawAxis(32);
	//ofPopMatrix();
	camera.end();
	
	if (!hideGui) {
		ofDisableDepthTest();
		gui.draw();
	}
	
	if (!hideStats) {
		ofSetColor(0);
		ofDrawBitmapString("framerate: " + ofToString(ofGetFrameRate()),ofGetWidth() - 160, 20);
	}
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
	if (paraBorderX->x != paraBorderXOld.x || paraBorderX->y != paraBorderXOld.x) {
		setParticlesBorderX(paraBorderX);
		paraBorderXOld = paraBorderX;
	}
	if (paraBorderY->x != paraBorderYOld.x || paraBorderY->y != paraBorderYOld.x) {
		setParticlesBorderY(paraBorderY);
		paraBorderYOld = paraBorderY;
	}
	if (paraBorderZ->x != paraBorderZOld.x || paraBorderZ->y != paraBorderZOld.x) {
		setParticlesBorderZ(paraBorderZ);
		paraBorderZOld = paraBorderZ;
	}
}


//------------GUI---------------------TODO: AUSLAGERN----------------
void ofApp::generateParticle(ofVec3f pos, ofVec3f vel, int attributes)
{
	generateParticle(pos,vel);
	cout << getBit(attributesNextParticle) << endl;
}
void ofApp::generateParticle(ofVec3f pos, ofVec3f vel)
{
	particles.push_back(Particle(&particles,attributesNextParticle, pos, vel));
}

void ofApp::setParticlesCollisionMult(float val)
{
	for (unsigned int i=0; i<particles.size(); ++i){
		particles[i].PARAM_COLLISION_MULT = val;
	}
}
void ofApp::setParticlesColorDiffMult(float val)
{
	for (unsigned int i=0; i<particles.size(); ++i){
		particles[i].PARAM_COLOR_DIFF_MULT = val;
	}
}
void ofApp::setParticlesBorderX(ofVec2f val)
{
	for (unsigned int i=0; i<particles.size(); ++i){
		particles[i].PARAM_BORDER_X = val;
	}
}
void ofApp::setParticlesBorderY(ofVec2f val)
{
	for (unsigned int i=0; i<particles.size(); ++i){
		particles[i].PARAM_BORDER_Y = val;
	}
}
void ofApp::setParticlesBorderZ(ofVec2f val)
{
	for (unsigned int i=0; i<particles.size(); ++i){
		particles[i].PARAM_BORDER_Z = val;
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
	} else if (key == 'h') {
		hideGui = !hideGui;
	} else if (key == 's') {
		hideStats = !hideStats;
	} else {
		generateParticle(	ofVec3f(ofGetMouseX()-ofGetWidth()/2, ofGetMouseY()-ofGetHeight()/2, ofRandomf()*100), 
							ofVec3f(ofRandomf()*2,ofRandomf()*2,ofRandomf()*2),
							attributesNextParticle);
							
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
