#include "Particle.h"

Particle::Particle(vector <Particle> * pptr, ofVec3f pos_, ofVec3f vel_)
{
	particlesPtr = pptr;
	prevPtr = NULL;
	nextPtr = NULL;
	id = particlesPtr->size();
	cout << "num particles " << id << endl;

	position = pos_;
	velocity = vel_;
	
	drag = 0.995;
	
	radius = 0;
	
	attributes = 0;
	enableAttribute(ATTR_BORDER_XY);
	changeState(STATE_BIRTH);	
	
	
	//------------TESTING-------------
	color = ofColor(0);
	color.setHsb(ofRandom(0,255),150,ofRandom(220,255),50);
	if (id%3 == 0) {
		color.setHue(ofRandom(45,50));
		velocity = ofVec3f(ofRandomf(),0,0);
	} else if (id%3 == 1){
		color.setHue(ofRandom(160,165));
		velocity = ofVec3f(ofRandomf(),0,0);
	} else {
		color.setHue(ofRandom(80,82));
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
			radius = 0.006*time;
			if (time > CONST_TIME_BIRTH) {
				radius = radiusBirth;
				mass = ofRandomf()*3.0 + 0.2;
				radius = 4*mass + 2;
				enableAttribute(ATTR_COLLISION);
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
	velocity.limit(CONST_MAX_SPEED);
	position += velocity;
	force = ofVec3f(0,0,0);
}

void Particle::draw()
{
	ofFill();

	if (checkAttribute(ATTR_CONNECT_NEXT)) {
		ofSetColor(0,100,255); //blau
		ofDrawCircle(position, radius);
	}

	ofSetColor(color);
	ofDrawCircle(position, radius);
	
	if (checkAttribute(ATTR_SPRING_PREV)) {
		ofSetColor(200,0,0);	//rot
		ofDrawCircle(position, radius*0.6);
	}
	
	
	if (prevPtr != NULL) {
		ofSetColor(30);
		
		/*
		float size = min(position.distance(prevPtr->position) * 0.3,50);
		//draw arrow with p1,p2,p3 and tip at p2
		
		ofVec3f dirNorm = prevPtr->position - position;
		dirNorm.normalize();
		
		ofVec3f toTheLeft = dirNorm.getRotated( 90, ofVec3f( 0, 0, 1 ) );
		ofVec3f toTheRight = dirNorm.getRotated( -90, ofVec3f( 0, 0, 1 ) );
		
		ofVec3f p1 = prevPtr->position - dirNorm*radius - dirNorm*size*0.7 + toTheRight*size*0.3;
		ofVec3f p2 = prevPtr->position - dirNorm*radius;
		ofVec3f p3 = prevPtr->position - dirNorm*radius - dirNorm*size*0.7 + toTheLeft*size*0.3;
		
		ofDrawLine(p1,p2);
		ofDrawLine(p3,p2);
		ofDrawLine(position, p2);
		*/
	}	
}

//---------------------------------------------------------------------------------------------
void Particle::updateAttributes()
{
	ofSetColor(0);
	//mirror at borders
	ofVec3f borderMin(ofGetWidth()/2-300,ofGetHeight()/2-100,0);
	ofVec3f borderMax(ofGetWidth()/2+300,ofGetHeight()/2+100,0);
	if (checkAttribute(ATTR_BORDER_XY)) {
		if (position.x < borderMin.x) {
			force.x += CONST_BORDER_MULT * (borderMin.x - position.x);
		}
		if (position.x > borderMax.x) {
			force.x += CONST_BORDER_MULT * (borderMax.x - position.x);
		}
		if (position.y < borderMin.y) {
			force.y += CONST_BORDER_MULT * (borderMin.y - position.y);
		}
		if (position.y > borderMax.y) {
			force.y += CONST_BORDER_MULT * (borderMax.y - position.y);
		}
	}
	
	//pair if distance to another particle is less than  
	if (checkAttribute(ATTR_CONNECT_PAIR)) {
	
	}
	
	if (checkAttribute(ATTR_CONNECT_GROUP)) {
	
	}
	
	if (checkAttribute(ATTR_CONNECT_NEXT)) {	//TODO:Namen überdenken
		int index = getIdClosestParticle(ATTR_CONNECT_NEXT, false, true);
		
		float dist = particlesPtr->at(index).position.distance(position);
		if (dist < CONST_CONNECT_DIST) {
			nextPtr = &(particlesPtr->at(index));
			nextPtr->prevPtr = &(particlesPtr->at(id));
			nextPtr->drag = 0.999;
			nextPtr->mass = 5.0;
			
			disableAttribute(ATTR_CONNECT_NEXT);
			enableAttribute(ATTR_SPRING_NEXT);
			
			nextPtr->enableAttribute(ATTR_SPRING_PREV);
			
			nextPtr->changeState(STATE_PAIRING);
			changeState(STATE_PAIRING);
			
		}
		
	}
	
	//
	if (checkAttribute(ATTR_GRAV_PAIR)) {
		float dist = position.distance(nextPtr->position);
		if (dist < radius*2) {
			force -= 0.1 * (nextPtr->position - position);
		} else if (dist > radius*10) {
			force += 0.0005 * (nextPtr->position - position);
		}
	}
	
	if (checkAttribute(ATTR_SPRING_PREV)) {
		if (prevPtr != NULL) {
			force += 0.2 * (prevPtr->position - position);
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
			float dist = particlesPtr->at(i).position.distance(position);
			if (dist < particlesPtr->at(i).getRadius() + radius) {
				force -= CONST_COLLISION_MULT * (particlesPtr->at(i).position - position);
				particlesPtr->at(i).force += CONST_COLLISION_MULT * (particlesPtr->at(i).position - position);
			}
			
			double colDiff = abs( color.getHue()-particlesPtr->at(i).color.getHue() );
			if (colDiff > 255/2) {
				colDiff -= abs(colDiff-255);
			}
			colDiff = max(1.0, colDiff);
			double forceMag = CONST_COLOR_DIFF_MULT / pow(colDiff,2);
			ofVec3f dir = position - particlesPtr->at(i).position;
			force -= forceMag * dir.getNormalized();
			particlesPtr->at(i).force += forceMag * dir.getNormalized();
		}
	}
	
	
	
	
}

void Particle::changeState(unsigned int newState)
{
	//cout << "P" << id << ": changed state to " << newState << endl;
	tLastStateChange = ofGetElapsedTimeMillis();
	state = newState;
}

void Particle::enableAttribute(int attribute)
{
	attributes |= attribute;
	//cout << "P" << id << ": enabled attr" << attribute << endl;
}

void Particle::disableAttribute(int attribute)
{
	//attributes &= ~(1 << attribute);
	attributes &= ~attribute;
	//cout << "P" << id << ": disabled attr" << attribute << endl;
}

bool Particle::checkAttribute(int attribute){
	return attribute & attributes;
}

int Particle::getIdClosestParticle(int attributes, bool checkNextPtr, bool checkPrevPtr){
		int index = 0;
		double dist = 2000.0;
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
					float newDist = particlesPtr->at(i).position.distance(position);
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
		double dist = 2000.0;
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
					float newDist = particlesPtr->at(i).position.distance(position);
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
