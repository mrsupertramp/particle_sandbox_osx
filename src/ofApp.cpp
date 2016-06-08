/*
COPYRIGHT ENRICO STEINFELD. ALL RIGHTS RESERVED
*/

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
	cout << "Done Setup" << endl;
	particles.reserve(20000);
	
	staticParticles.reserve(2000);
	
	
	//-------------------------------------------------------------------------GUI----------
	attr_border_xyz.addListener(this, &ofApp::setAttributeBorderXYZ);
	
	attr_collision.addListener(this, &ofApp::setAttributeCollision);
	attr_color_diff.addListener(this, &ofApp::setAttributeColorDiff);
	attr_spring_prev.addListener(this, &ofApp::setAttributeSpringPrev);
	attr_connect_next.addListener(this, &ofApp::setAttributeConnectNext);
	attr_connect_prev.addListener(this, &ofApp::setAttributeConnectPrev);
	overrideAttributes.addListener(this, &ofApp::setAttributesAllParticles);

	gui.setup();
	gui.add(para_drag.setup("drag", 1.0, 0.1, 1.0));
	gui.add(para_mass.setup("mass", 1.0, 0.01, 10.0));
	gui.add(para_spring_stiffness.setup("spring stiffness", 1.0, 0.01, 4.0));
	gui.add(paraCollisionMult.setup("collision mult", 0.03, 0.0, 0.08));
	gui.add(paraColorDiffMult.setup("color diff mult", 0.2, 0.0, 0.04));
	gui.add(paraBorderX.setup("border x",ofVec2f(-200,200),ofVec2f(-1000,-1000),ofVec2f(1000,1000)));
	gui.add(paraBorderY.setup("border y",ofVec2f(-200,200),ofVec2f(-1000,-1000),ofVec2f(1000,1000)));
	gui.add(paraBorderZ.setup("border z",ofVec2f(-150,150),ofVec2f(-1000,-1000),ofVec2f(1000,1000)));
	
	gui.add(attr_border_xyz.setup("attr_border_xyz",false));
	gui.add(attr_collision.setup("attr_collision",false));
	gui.add(attr_spring_prev.setup("attr_spring_dev",false));
	gui.add(attr_connect_next.setup("attr_connect_next",false));
	gui.add(attr_connect_prev.setup("attr_connect_prev",false));
	gui.add(attr_color_diff.setup("attr_color_diff",false));
	
	gui.add(overrideAttributes.setup("override"));
	//---------------------------------------------------------------------------------------
	

	//-------------------------------------CAMERA--------------
	camera.setDistance(100);
	
	//---------------------------------------------------------
	
	
	//----------------------------STATIC PARTICLES---------------
	int num = 400;
	for (unsigned int i=0; i<num; ++i){
		//spherical
		float a1 = ofRandom(0, TWO_PI);
		float a2 = ofRandom(0, TWO_PI);
		
		float dist = ofRandom(1800, 2500);
		ofVec3f pos( dist*cos(a1)*cos(a2), dist*sin(a1)*cos(a2), dist*sin(a2));
		staticParticles.push_back(Particle(&staticParticles, 0, pos, ofVec3f(0,0,0)));
		staticParticles[i].lookAt(ofVec3f(0, 0, 0));
		staticParticles[i].color = ofColor(0, 50);
		staticParticles[i].setRadius(6);
	}
	
	//----------------------------------------------------------
	
}

//---------------------------------------------------------------------------------------

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
	/*
	ofDisableDepthTest();
	for (unsigned int i=0; i<staticParticles.size(); ++i){
		staticParticles[i].draw(-staticParticles[i].getPosition());
	}
	*/
	
	//ofEnableDepthTest();
	//ofEnableAlphaBlending();
	glEnable(GL_DEPTH_TEST); 
	
	//drawBorders();		//TODO: fix alpha blending issue
	for (unsigned int i=0 ; i<particles.size(); ++i){
		particles[i].draw(camera.getPosition());
	}

	//ofDrawAxis(32);
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

void ofApp::updateParameter()
{
	if (para_drag != para_drag_last) {
		setParticlesDrag(para_drag);
		para_drag_last = para_drag;
	}
	if (para_mass != para_mass_last) {
		setParticlesMass(para_mass);
		para_mass_last = para_mass;
	}
	if (para_spring_stiffness != para_spring_stiffness_last) {
		setParticlesSpringStiffness(para_spring_stiffness);
		para_spring_stiffness_last = para_spring_stiffness;
	}
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


//--------------------------------------------------------------GUI FUNCTIONS------------
void ofApp::setAttributeBorderXYZ(bool &attr_border_xyz)
{
	if (attr_border_xyz) {
		attributesNextParticle |= ATTR_BORDER_XYZ;
	} else {
		attributesNextParticle &= ~(ATTR_BORDER_XYZ);
	}
}

void ofApp::setAttributeCollision(bool &attr_collision)
{
	if (attr_collision) {
		attributesNextParticle |= ATTR_COLLISION;
	} else {
		attributesNextParticle &= ~(ATTR_COLLISION);
	}
}
void ofApp::setAttributeColorDiff(bool &attr_color_diff)
{
	if (attr_color_diff) {
		attributesNextParticle |= ATTR_COLOR_DIFF;
	} else {
		attributesNextParticle &= ~(ATTR_COLOR_DIFF);
	}	
}
void ofApp::setAttributeSpringPrev(bool &attr_spring_prev)
{
	if (attr_spring_prev) {
		attributesNextParticle |= ATTR_SPRING_PREV;
	} else {
		attributesNextParticle &= ~(ATTR_SPRING_PREV);
	}
}
void ofApp::setAttributeConnectNext(bool &attr_connect_next)
{
	if (attr_connect_next) {
		attributesNextParticle |= ATTR_CONNECT_NEXT;
	} else {
		attributesNextParticle &= ~(ATTR_CONNECT_NEXT);
	}
}
void ofApp::setAttributeConnectPrev(bool &attr_connect_prev)
{
	if (attr_connect_prev) {
		attributesNextParticle |= ATTR_CONNECT_PREV;
	} else {
		attributesNextParticle &= ~(ATTR_CONNECT_PREV);
	}
}
void ofApp::setAttributesAllParticles()
{
	for (unsigned int i=0; i<particles.size(); ++i){
		particles[i].resetLinks();	//TODO: make this line not necessary
		particles[i].setAttributes(attributesNextParticle);
	}
}

void ofApp::generateParticle(ofVec3f pos, ofVec3f vel, int attributes)
{
	generateParticle(pos,vel);
}
void ofApp::generateParticle(ofVec3f pos, ofVec3f vel)
{
	particles.push_back(Particle(&particles,attributesNextParticle, pos, vel));
}

void ofApp::setParticlesDrag(float val)
{
	for (unsigned int i=0; i<particles.size(); ++i){
		particles[i].setDrag(val);
	}
}
void ofApp::setParticlesMass(float val)
{
	for (unsigned int i=0; i<particles.size(); ++i){
		particles[i].setMass(val);
	}
}
void ofApp::setParticlesSpringStiffness(float val)
{
	for (unsigned int i=0; i<particles.size(); ++i){
		particles[i].setSpringStiffness(val);
	}
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

void ofApp::drawBorders()
{
	ofPushMatrix();
	//ofTranslate(paraBorderX->x,paraBorderY->x,paraBorderZ->x);
	ofBoxPrimitive box(paraBorderX->y-paraBorderX->x, paraBorderY->y-paraBorderY->x, paraBorderZ->y-paraBorderZ->x);
	/*box.setSideColor(0, ofColor(0,30));
	box.setSideColor(1, ofColor(0,30));
	box.setSideColor(2, ofColor(0,30));
	box.setSideColor(3, ofColor(0,30));
	box.setSideColor(4, ofColor(0,30));
	*/
	
	ofMesh sideXYMin;
	sideXYMin.addVertex(ofVec3f(paraBorderX->x,paraBorderY->x,paraBorderZ->x));
	sideXYMin.addVertex(ofVec3f(paraBorderX->y,paraBorderY->x,paraBorderZ->x));
	sideXYMin.addVertex(ofVec3f(paraBorderX->y,paraBorderY->y,paraBorderZ->x));
	sideXYMin.addVertex(ofVec3f(paraBorderX->x,paraBorderY->y,paraBorderZ->x));
	
	ofSetColor(20,20);
	sideXYMin.draw();
	//box.draw();
	ofPopMatrix();
}

//---------------------------------------------------------------------------


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
