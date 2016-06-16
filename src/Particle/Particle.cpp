/*
COPYRIGHT ENRICO STEINFELD. ALL RIGHTS RESERVED
*/

#include "Particle.h"

Particle::Particle()
{
	setPosition(ofVec3f(0,0,0));
	velocity = ofVec3f(0,0,0);

	
}

Particle::Particle(ofVec3f pos_, ofVec3f vel_, ofParameterGroup *parameters_, int attributes_, vector <Particle> * pptr)
{	
	particlesPtr = pptr;
	prevPtr = NULL;
	nextPtr = NULL;
	id = particlesPtr->size();

	setPosition(pos_);
	velocity = vel_;
	
	radius = 0;
	
	//cout << (*parameters_)[0] << endl;
	parameters.setName("Particles Parameter");
	parameters.add(PARAM_COLOR_DIFF_MULT.set("colorDiffMult", 0.1, 0.0, 1.0));
	parameters.add(PARAM_COLLISION_MULT.set("collisionMult", 0.1, 0.0, 1.0));
	
	parameters.add(PARAM_BORDER_X.set("borderX", ofVec2f(-200,200), ofVec2f(-1000,-1000), ofVec3f(1000,1000)));
	parameters.add(PARAM_BORDER_Y.set("borderY", ofVec2f(-200,200), ofVec2f(-1000,-1000), ofVec3f(1000,1000)));
	parameters.add(PARAM_BORDER_Z.set("borderZ", ofVec2f(-200,200), ofVec2f(-1000,-1000), ofVec3f(1000,1000)));
	
	parameters.add(drag.set("drag", 1.0, 0.0, 1.0));
	parameters.add(mass.set("mass", 1.0, 0.0, 1.0));
	
	parameters.add(springStiffness.set("springStiffness", 0.1, 0.0, 1.0));
	parameters.add(springDamping.set("springDamping", 0.1, 0.0, 1.0));
	//parameters = parameters_;
	
	attributes = attributes_;

	changeState(STATE_IDLE);
	
	
	
	//------------TESTING-------------
	radiusBirth = 9;
	radius = 9;
	
	color = ofColor(0);
	color.setHsb(ofRandom(0,255),150, ofRandom(220,255), 250);
	if (id%3 == 0) {
		color.setHue(ofRandom(45, 50));
		velocity = ofVec3f(ofRandomf(), 0, 0);
	} else if (id%3 == 1){
		color.setHue(ofRandom(160, 165));
		velocity = ofVec3f(ofRandomf(), 0, 0);
	} else {
		color.setHue(ofRandom(80, 82));
	}
}


void Particle::setup()
{

}

void Particle::update()
{
	unsigned int time = ofGetElapsedTimeMillis() - tLastStateChange;
	
	switch (state){
		case STATE_BIRTH:
			radius = 0.011*time;
			if (time > CONST_TIME_BIRTH) {
				radius = radiusBirth;
				changeState(STATE_IDLE);
			}
			break;
		case STATE_IDLE:
			updateAttributes();
			break;
		case STATE_PAIRING:
			
			changeState(STATE_IDLE);
			break;	
	}
	if (radius < radiusBirth && radius > 0.0) {
		cout << "id" << id << "  state " << state << endl;
	}
	acceleration = force / mass;
	velocity += acceleration;
	
	if (checkAttribute(ATTR_SPRING_NEXT | ATTR_SPRING_PREV))
	{
		velocity *= springDamping;
	}
	
	velocity *= drag;
	velocity.limit(PARAM_MAX_SPEED);
	setPosition(getPosition() + velocity);
	force = ofVec3f(0,0,0);
}

void Particle::draw(ofVec3f lookAt)
{
	ofFill();

	ofPushMatrix();
	ofSetColor(color);
	
	ofTranslate(getPosition());
	
	ofVec3f normal = lookAt;
	normal.normalize();
	
	float rotationAmount;
	ofVec3f rotationAngle;
	ofQuaternion rotation;
	
	ofVec3f axis(0, 0, 1);
	rotation.makeRotate(axis, normal);
	rotation.getRotate(rotationAmount, rotationAngle);
	ofRotate(rotationAmount, rotationAngle.x, rotationAngle.y, rotationAngle.z);
	ofDrawCircle(ofVec3f(0,0,0), radius);
	
	if (checkAttribute(ATTR_SPRING_PREV)) {
		//ofSetColor(200,0,0);	//rot
		//ofDrawCircle(getPosition(), radius*0.6);
	}
	ofPopMatrix();
	
	if (prevPtr != NULL) {
		ofSetColor(30);
		
		//draw arrow with p1,p2,p3 and tip at p2
		
		float size = getPosition().distance(prevPtr->getPosition()) * 0.3;
		if (size > 50)
			size = 50;
		ofVec3f dirNorm = prevPtr->getPosition() - getPosition();
		dirNorm.normalize();
		
		ofVec3f toTheLeft = dirNorm.getRotated( 90, ofVec3f( 0, 0, 1 ) );
		ofVec3f toTheRight = dirNorm.getRotated( -90, ofVec3f( 0, 0, 1 ) );
		
		ofVec3f p1 = prevPtr->getPosition() - dirNorm*radius - dirNorm*size*0.7 + toTheRight*size*0.3;
		ofVec3f p2 = prevPtr->getPosition() - dirNorm*radius;
		ofVec3f p3 = prevPtr->getPosition() - dirNorm*radius - dirNorm*size*0.7 + toTheLeft*size*0.3;
		
		ofDrawLine(p1,p2);
		ofDrawLine(p3,p2);
		ofDrawLine(getPosition(), p2);
		
		//ofDrawLine(getPosition(),prevPtr->getPosition());
		
	}
	
}

void Particle::draw()
{
	draw(ofVec3f(0,0,0));
}

//--------------------------------------------------------------------------------------------

//--------------------------------------------------------write things-----------------------------
void Particle::changeState(unsigned int newState)
{
	//cout << "P" << id << ": changed state to " << newState << endl;
	tLastStateChange = ofGetElapsedTimeMillis();
	state = newState;
}

void Particle::setAttributes(int newAttributes)
{
	attributes = newAttributes;
}
void Particle::enableAttribute(int attribute)
{
	attributes |= attribute;
}
void Particle::disableAttribute(int attribute)
{
	attributes &= ~attribute;
}
void Particle::toggleAttribute(int attribute)
{
	cout << getBit(attributes) << endl;
	attributes ^= (-attribute ^ attributes) & (1 << attribute);
	cout << getBit(attributes) << endl;
}


void Particle::resetLinks()
{
	prevPtr = NULL;
	nextPtr = NULL;
}

void Particle::setParameters(ofParameterGroup *parameters_)
{
	for (unsigned int i=0; i<parameters_->size(); ++i){
		if (parameters.getType(i).compare("11ofParameterI7ofVec2fE")){
			parameters.getVec2f(i).set(parameters_->getVec2f(i));
		} else if (parameters.getType(i).compare("11ofParameterIfE")){
			parameters.getFloat(i).set(parameters_->getFloat(i));
		}
		}
}


//------------------------------------------------------read/get things------------
bool Particle::checkAttribute(int attribute){
	return attribute & attributes;
}
bool Particle::checkAttributes(int attributes_)
{
	bool check = false;
	for (unsigned int i=0; i<NUM_ATTRIBUTES; ++i){
		if (attributes_ & (1<<i))
			check = checkAttribute(1<<i);
	}
	return check;
}

int Particle::getIdClosestParticle(int attributes_, bool checkNextPtr, bool checkPrevPtr){
		int index = -1;
		double dist = 10000.0;
		for (unsigned int i=0; i<particlesPtr->size(); ++i){			
			if (particlesPtr->at(i).id != id) {				
				bool checkDist = true;
			    checkDist &= particlesPtr->at(i).checkAttributes(attributes_);
			    if (checkNextPtr) {
			    	checkDist &= (particlesPtr->at(i).nextPtr == NULL);
			    }
			    if (checkPrevPtr) {
			    	checkDist &= (particlesPtr->at(i).prevPtr == NULL);
			    }
			    
			    if (checkDist) {
					float newDist = particlesPtr->at(i).getPosition().distance(getPosition());
					if (newDist < dist) {
						dist = newDist;
						index = i;
					}
				}
			}
		}
		distanceToClosestParticle = dist;
		return index;
}

double Particle::getDistanceClosestParticle(int attributes_, bool checkNextPtr, bool checkPrevPtr){
		double dist = 10000.0;
		for (unsigned int i=0; i<particlesPtr->size(); ++i){
			if (particlesPtr->at(i).id != id) {
				bool checkDist = true;
			    checkDist &= particlesPtr->at(i).checkAttributes(attributes_);
			    if (checkNextPtr) {
			    	checkDist &= (particlesPtr->at(i).nextPtr == NULL);
			    }
			    if (checkPrevPtr) {
			    	checkDist &= (particlesPtr->at(i).prevPtr == NULL);
			    }
			    if (checkDist) {
					float newDist = particlesPtr->at(i).getPosition().distance(getPosition());
					if (newDist < dist) {
						dist = newDist;
					}
				}
			}
		}
		distanceToClosestParticle = dist;
		return dist;
}

double Particle::getRadius(){
	return radius;
}

int Particle::getState()
{
	return state;
}
//----------------------------------------------------------------------------------------

string Particle::getBit(int k)
{
	string s;
	for (int i=0; i<20; ++i){
		if (k & (1 << i)) {
			s = "1" + s;
		} else {
			s = "0" + s;
		}
	}
	return s;
}
