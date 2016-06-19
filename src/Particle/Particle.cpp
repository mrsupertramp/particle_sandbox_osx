/*
COPYRIGHT ENRICO STEINFELD. ALL RIGHTS RESERVED
*/

#include "Particle.h"

Particle::Particle()
{
	setPosition(ofVec3f(0,0,0));
	velocity = ofVec3f(0,0,0);
	prevPtr = NULL;
	nextPtr = NULL;
}

Particle::Particle(ofVec3f pos_, ofVec3f vel_, ParticleParameter *parameters_, ParticleAttributes *attributes_, vector <Particle> * pptr)
{	
	particlesPtr = pptr;
	prevPtr = NULL;
	nextPtr = NULL;
	id = particlesPtr->size();

	setPosition(pos_);
	velocity = vel_;	//TODO: veloctiy -> private
	
	radius = 0;
	
	
	setParameters(parameters_);
	setAttributes(attributes_);
		
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
			evaluateAttributes();
			break;
		case STATE_PAIRING:
			
			changeState(STATE_IDLE);
			break;	
	}
	if (radius < radiusBirth && radius > 0.0) {
		cout << "id" << id << "  state " << state << endl;
	}
	acceleration = force / parameters.mass;
	velocity += acceleration;
	
	if (attributes.spring_next || attributes.spring_prev) {
		velocity *= parameters.spring_damping;
	}
	
	velocity *= parameters.drag;
	velocity.limit(CONST_MAX_SPEED);
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
	
	if (attributes.spring_prev) {
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
void Particle::evaluateAttributes()
{
	//mirror at borders
	if (attributes.border_xyz) {
		if (getPosition().x < parameters.border_x_range->x) {
			force.x += CONST_BORDER_MULT * (parameters.border_x_range->x - getPosition().x);
		}
		if (getPosition().x > parameters.border_x_range->y) {
			force.x += CONST_BORDER_MULT * (parameters.border_x_range->y - getPosition().x);
		}
		if (getPosition().y < parameters.border_y_range->x) {
			force.y += CONST_BORDER_MULT * (parameters.border_y_range->x - getPosition().y);
		}
		if (getPosition().y > parameters.border_y_range->y) {
			force.y += CONST_BORDER_MULT * (parameters.border_y_range->y - getPosition().y);
		}
		if (getPosition().z < parameters.border_z_range->x) {
			force.z += CONST_BORDER_MULT * (parameters.border_z_range->x - getPosition().z);
		}
		if (getPosition().z > parameters.border_z_range->y) {
			force.z += CONST_BORDER_MULT * (parameters.border_z_range->y - getPosition().z);
		}
	}
	
	//connect to particle if distance is less than  PARAM_CONNECT_DIST
	if (attributes.connect_next) {
		int index = getIdClosestParticle(ATTR_CONNECT_PREV, false, true);
		cout << index << endl;
		if (index != -1) {
			float dist = particlesPtr->at(index).getPosition().distance(getPosition());
			if (dist < CONST_CONNECT_DIST) {
				nextPtr = &(particlesPtr->at(index));
				nextPtr->prevPtr = &(particlesPtr->at(id));
				//nextPtr->drag = 0.9999;
				//nextPtr->mass = 5.0;
		
				attributes.connect_next.set(false);
				cout << attributes.connect_next << endl;
		
				nextPtr->attributes.spring_prev.set(true);
				nextPtr->attributes.connect_prev.set(false);
		
				nextPtr->changeState(STATE_PAIRING);
				changeState(STATE_PAIRING);
			}
		}
	}
	
	if (0) {	//gravitation
		float dist = getPosition().distance(nextPtr->getPosition());
		if (dist < radius*2) {
			force -= 0.1 * (nextPtr->getPosition() - getPosition());
		} else if (dist > radius*10) {
			force += 0.0005 * (nextPtr->getPosition() - getPosition());
		}
	}
	
	if (attributes.spring_prev) {
		if (prevPtr != NULL) {
			force += parameters.spring_stiffness * (prevPtr->getPosition() - getPosition());
		}
	}
	
	if (attributes.spring_next) {
		if (nextPtr != NULL) {
			force += parameters.spring_stiffness * (nextPtr->getPosition() - getPosition());
		}
	}
	
	//new attribute
	if (nextPtr != NULL) {
		//force -= 0.1 / pow(position.distance(nextPtr->position),2) * (position-nextPtr->position).getNormalized();
	}
	
	//new attribute
	if (nextPtr != NULL) {
		
	}
	
	if (attributes.collision) {
		for (unsigned int i=id+1; i<particlesPtr->size(); ++i){
			float dist = particlesPtr->at(i).getPosition().distance(getPosition());
			if (dist < particlesPtr->at(i).getRadius() + radius) {
				force -= parameters.collision_mult * (particlesPtr->at(i).getPosition() - getPosition());
				particlesPtr->at(i).force += particlesPtr->at(i).parameters.collision_mult * (particlesPtr->at(i).getPosition() - getPosition());
			}
			//TODO: eine for schleife für alle attributes die es brauchen
			//		Attributes nochmal trennen zwischen fremdeinwirkung und selbstwirkung
		}
	}
	if (attributes.attraction_color) {
		for (unsigned int i=id+1; i<particlesPtr->size(); ++i){
			//TODO: eine for schleife für alle attributes die es brauchen
			//		Attributes nochmal trennen zwischen fremdeinwirkung und selbstwirkung
			double colDiff = abs( color.getHue()-particlesPtr->at(i).color.getHue() );
			if (colDiff > 255/2) {
				colDiff -= abs(colDiff-255);
			}
			colDiff = max(1.0, colDiff);
			double forceMag = parameters.color_diff_mult / pow(colDiff,2);
			
			ofVec3f dir = getPosition() - particlesPtr->at(i).getPosition();
			force -= forceMag * dir.getNormalized();
			particlesPtr->at(i).force += forceMag * dir.getNormalized();
		}
	}
}
//--------------------------------------------------------write things-----------------------------
void Particle::changeState(unsigned int newState)
{
	//cout << "P" << id << ": changed state to " << newState << endl;
	tLastStateChange = ofGetElapsedTimeMillis();
	state = newState;
}

void Particle::resetLinks()
{
	prevPtr = NULL;
	nextPtr = NULL;
}

void Particle::setParameters(ParticleParameter *parameters_)
{
	for (unsigned int i=0; i<parameters.group.size(); ++i){
		if (parameters.group.getType(i).compare("11ofParameterI7ofVec2fE")){
			parameters.group.getVec2f(i).set(parameters_->group.getVec2f(i));
		} 
		else if (parameters.group.getType(i).compare("11ofParameterIfE")){
			parameters.group.getFloat(i).set(parameters_->group.getFloat(i));
		}
	}
}
void Particle::setAttributes(ParticleAttributes *attributes_)
{
	if (attributes_ != NULL) {		
		for (unsigned int i=0; i<attributes.group.size(); ++i){
			attributes.group.getBool(i) = attributes_->group.getBool(i);//TODO: segmentation faul
		}
		attributes.bits = attributes_->bits;
	}
}

//------------------------------------------------------read/get things------------


int Particle::getIdClosestParticle(int attributes_, bool checkNextPtr, bool checkPrevPtr){
		int index = -1;
		double dist = 10000.0;
		for (unsigned int i=0; i<particlesPtr->size(); ++i){			
			if (particlesPtr->at(i).id != id) {				
				bool checkDist = true;
			    checkDist &= particlesPtr->at(i).attributes.checkAttributes(attributes_);
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
			    checkDist &= particlesPtr->at(i).attributes.checkAttributes(attributes_);
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

int Particle::getState()
{
	return state;
}

double Particle::getRadius(){
	return radius;
}
//----------------------------------------------------------------------------------------
