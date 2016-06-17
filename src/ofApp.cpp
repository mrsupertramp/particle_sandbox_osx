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

	particles.reserve(20000);
	
	staticParticles.reserve(2000);
	
	
	//-------------------------------------------------------------------------GUI----------
	
	but_overwriteAttributes.addListener(this, &ofApp::overwriteAttributes);
	but_overwriteParameters.addListener(this, &ofApp::overwriteParameters);

	//nextParticle = new Particle();
	Particle particle;
	
	guiAttributes.setup(nextParticle.attributes.group);
	guiAttributes.add(but_overwriteAttributes.set("Overwrite"));
	guiParameters.setup(nextParticle.parameters.group);
	guiAttributes.add(but_overwriteParameter.set("Overwrite"));
	
	//gui.setup();
	
		
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
		/*
		staticParticles.push_back(Particle(&staticParticles, 0, pos, ofVec3f(0,0,0)));
		staticParticles[i].lookAt(ofVec3f(0, 0, 0));
		staticParticles[i].color = ofColor(0, 50);
		staticParticles[i].setRadius(6);
		*/
	}
	
	//----------------------------------------------------------
	
}

//---------------------------------------------------------------------------------------

//--------------------------------------------------------------
void ofApp::update()
{
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
	
	ofEnableDepthTest();
	//ofEnableAlphaBlending();
	//glEnable(GL_DEPTH_TEST); 
	
	//drawBorders();		//TODO: fix alpha blending issue
	for (unsigned int i=0 ; i<particles.size(); ++i){
		particles[i].draw(camera.getPosition());
	}

	//ofDrawAxis(32);
	//ofPopMatrix();
	camera.end();
	
	if (!hideGui) {
		ofDisableDepthTest();
		guiAttributes.draw();
		guiParameters.draw();
	}
	
	if (!hideStats) {
		ofSetColor(0);
		ofDrawBitmapString("framerate: " + ofToString(ofGetFrameRate()),ofGetWidth() - 160, 20);
	}
}


//--------------------------------------------------------------


//--------------------------------------------------------------GUI FUNCTIONS------------

void ofApp::overwriteAttributes()
{
	for (unsigned int i=0; i<particles.size(); ++i){
		particles[i].resetLinks();	//TODO: make this line not necessary
		particles[i].setAttributes(&(nextParticle.attributes));
	}
}
void ofApp::overwriteParameters()
{
	for (unsigned int i=0; i<particles.size(); ++i){
		particles[i].setParameters(&(nextParticle.parameters));
	}
}
void ofApp::generateParticle(ofVec3f pos, ofVec3f vel)
{	
	particles.push_back(Particle(pos, vel, &(nextParticle.parameters), &(nextParticle.attributes), &particles));
}

void ofApp::drawBorders()
{
	
	ofPushMatrix();
	//ofTranslate(paraBorderX->x,paraBorderY->x,paraBorderZ->x);
	//ofBoxPrimitive box(paraBorderX->y-paraBorderX->x, paraBorderY->y-paraBorderY->x, paraBorderZ->y-paraBorderZ->x);
	/*box.setSideColor(0, ofColor(0,30));
	box.setSideColor(1, ofColor(0,30));
	box.setSideColor(2, ofColor(0,30));
	box.setSideColor(3, ofColor(0,30));
	box.setSideColor(4, ofColor(0,30));
	*/
	/*
	ofMesh sideXYMin;
	sideXYMin.addVertex(ofVec3f(paraBorderX->x,paraBorderY->x,paraBorderZ->x));
	sideXYMin.addVertex(ofVec3f(paraBorderX->y,paraBorderY->x,paraBorderZ->x));
	sideXYMin.addVertex(ofVec3f(paraBorderX->y,paraBorderY->y,paraBorderZ->x));
	sideXYMin.addVertex(ofVec3f(paraBorderX->x,paraBorderY->y,paraBorderZ->x));
	
	ofSetColor(20,20);
	sideXYMin.draw();
	//box.draw();
	ofPopMatrix();
	*/
}

//---------------------------------------------------------------------------


void ofApp::keyPressed(int key)
{

	if (key == '1') {

	} else if (key == '2') {
	} else if (key == '3') {
	} else if (key == '4') {
	} else if (key == 'h') {
		hideGui = !hideGui;
	} else if (key == 's') {
		hideStats = !hideStats;
	} else {
		generateParticle(	ofVec3f(ofGetMouseX()-ofGetWidth()/2, ofGetMouseY()-ofGetHeight()/2, ofRandomf()*100), 
							ofVec3f(ofRandomf()*2,ofRandomf()*2,ofRandomf()*2));
							
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
