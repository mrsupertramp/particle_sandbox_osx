#include "Particle.h"

Particle::Particle(vector <Particle> * pptr, int attributes_, ofVec3f pos_, ofVec3f vel_)
{
	particlesPtr = pptr;
	prevPtr = NULL;
	nextPtr = NULL;
	id = particlesPtr->size();

	setPosition(pos_);
	velocity = vel_;
	
	mass = 1.0;
	drag = 1.0;
	radius = 0;
	
	attributes = attributes_;
	changeState(STATE_BIRTH);
	
	
	//------------TESTING-------------
	radiusBirth = 9;

	
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
				mass = ofRandom(0.2,4);
				changeState(STATE_IDLE);
			}
			break;
		case STATE_IDLE:
			
			break;
		case STATE_PAIRING:
			
			changeState(STATE_IDLE);
			break;
			
	}
	
	updateAttributes();
	
	acceleration = force / mass;
	velocity += acceleration;
	velocity *= drag;
	velocity.limit(PARAM_MAX_SPEED);
	setPosition(getPosition() + velocity);
	force = ofVec3f(0,0,0);
}

void Particle::draw(ofVec3f lookAt)
{
	ofFill();

	if (checkAttribute(ATTR_CONNECT_NEXT)) {
		ofSetColor(0,100,255); //blau
		ofDrawCircle(getPosition(), radius);
	}

	ofPushMatrix();
	ofSetColor(color);
	
	ofTranslate(getPosition());
	
	//ofVec3f normal = -getPosition();
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
	
	ofPopMatrix();
	
	if (checkAttribute(ATTR_SPRING_PREV)) {
		//ofSetColor(200,0,0);	//rot
		//ofDrawCircle(getPosition(), radius*0.6);
		
	}
	
	
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
		
		
	}	
}

void Particle::draw()
{
	draw(ofVec3f(0,0,0));
}


//---------------------------------------------------------------------------------------------
void Particle::updateAttributes()
{
	//mirror at borders
	if (checkAttribute(ATTR_BORDER_XYZ)) {
		if (getPosition().x < PARAM_BORDER_X.x) {
			force.x += PARAM_BORDER_MULT * (PARAM_BORDER_X.x - getPosition().x);
		}
		if (getPosition().x > PARAM_BORDER_X.y) {
			force.x += PARAM_BORDER_MULT * (PARAM_BORDER_X.y - getPosition().x);
		}
		if (getPosition().y < PARAM_BORDER_Y.x) {
			force.y += PARAM_BORDER_MULT * (PARAM_BORDER_Y.x - getPosition().y);
		}
		if (getPosition().y > PARAM_BORDER_Y.y) {
			force.y += PARAM_BORDER_MULT * (PARAM_BORDER_Y.y - getPosition().y);
		}
		if (getPosition().z < PARAM_BORDER_Z.x) {
			force.z += PARAM_BORDER_MULT * (PARAM_BORDER_Z.x - getPosition().z);
		}
		if (getPosition().z > PARAM_BORDER_Z.y) {
			force.z += PARAM_BORDER_MULT * (PARAM_BORDER_Z.y - getPosition().z);
		}
	}
	
	//connect to particle if distance is less than  PARAM_CONNECT_DIST

	
	if (checkAttribute(ATTR_CONNECT_NEXT)) {	//TODO:Namen überdenken
		int index = getIdClosestParticle(ATTR_CONNECT_NEXT, false, true);
		float dist = particlesPtr->at(index).getPosition().distance(getPosition());
		if (dist < PARAM_CONNECT_DIST) {
			nextPtr = &(particlesPtr->at(index));
			nextPtr->prevPtr = &(particlesPtr->at(id));
			nextPtr->drag = 0.9999;
			nextPtr->mass = 5.0;
			
			disableAttribute(ATTR_CONNECT_NEXT);
			enableAttribute(ATTR_SPRING_NEXT);
			
			nextPtr->enableAttribute(ATTR_SPRING_PREV);
			
			nextPtr->changeState(STATE_PAIRING);
			changeState(STATE_PAIRING);
			
		}
		
	}

	if (checkAttribute(ATTR_GRAV_PAIR)) {
		float dist = getPosition().distance(nextPtr->getPosition());
		if (dist < radius*2) {
			force -= 0.1 * (nextPtr->getPosition() - getPosition());
		} else if (dist > radius*10) {
			force += 0.0005 * (nextPtr->getPosition() - getPosition());
		}
	}
	
	if (checkAttribute(ATTR_SPRING_PREV)) {
		if (prevPtr != NULL) {
			force += 0.2 * (prevPtr->getPosition() - getPosition());
		}
	}
	
	if (checkAttribute(ATTR_SPRING_NEXT)) {
		if (nextPtr != NULL) {
			//force += 0.9 * (nextPtr->position - position);
		}
	}
	
	
	
	//new attribute
	if (nextPtr != NULL) {
		//force -= 0.1 / pow(position.distance(nextPtr->position),2) * (position-nextPtr->position).getNormalized();
	}
	
	//new attribute
	if (nextPtr != NULL) {
		
	}
	
	if (checkAttribute(ATTR_COLLISION)) {
		for (unsigned int i=id+1; i<particlesPtr->size(); ++i){
			float dist = particlesPtr->at(i).getPosition().distance(getPosition());
			if (dist < particlesPtr->at(i).getRadius() + radius) {
				force -= PARAM_COLLISION_MULT * (particlesPtr->at(i).getPosition() - getPosition());
				particlesPtr->at(i).force += PARAM_COLLISION_MULT * (particlesPtr->at(i).getPosition() - getPosition());
			}
			//TODO: eine for schleife für alle attributes die es brauchen
			//		Attributes nochmal trennen zwischen fremdeinwirkung und selbstwirkung

		}
	}
	if (checkAttribute(ATTR_COLOR_DIFF)) {
		for (unsigned int i=id+1; i<particlesPtr->size(); ++i){
			//TODO: eine for schleife für alle attributes die es brauchen
			//		Attributes nochmal trennen zwischen fremdeinwirkung und selbstwirkung
			double colDiff = abs( color.getHue()-particlesPtr->at(i).color.getHue() );
			if (colDiff > 255/2) {
				colDiff -= abs(colDiff-255);
			}
			colDiff = max(1.0, colDiff);
			double forceMag = PARAM_COLOR_DIFF_MULT / pow(colDiff,2);

			ofVec3f dir = getPosition() - particlesPtr->at(i).getPosition();
			force -= forceMag * dir.getNormalized();
			particlesPtr->at(i).force += forceMag * dir.getNormalized();
		}
	}
	
	
	
	
}

//--------------------------------------------------------write things------------
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

void Particle::setRadius(float r)
{
	radius = r;
}
void Particle::setDrag(float d)
{
	drag = d;
}
//------------------------------------------------------read/get things------------
bool Particle::checkAttribute(int attribute){
	return attribute & attributes;
}

int Particle::getIdClosestParticle(int attributes, bool checkNextPtr, bool checkPrevPtr){
		int index = 0;
		double dist = 10000.0;
		for (unsigned int i=0; i<particlesPtr->size(); ++i){
			if (particlesPtr->at(i).id != id) {
				bool checkDist = true;
			    checkDist &= particlesPtr->at(i).checkAttribute(attributes);
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

double Particle::getDistanceClosestParticle(int attributes, bool checkNextPtr, bool checkPrevPtr){
		double dist = 10000.0;
		for (unsigned int i=0; i<particlesPtr->size(); ++i){
			if (particlesPtr->at(i).id != id) {
				bool checkDist = true;
			    checkDist &= particlesPtr->at(i).checkAttribute(attributes);
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
