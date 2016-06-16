#include "ParticleAttributes.h"

void enableAttribute(int attribute); 
void disableAttribute(int attribute);
void setAttributes(int newAttributes);
void setAttribute(int attribute);
void toggleAttribute(int attribute);

void ParticleAttributes::evaluateAttribute()
{
	//mirror at borders
	if (checkAttribute(ATTR_BORDER_XYZ)) {
		if (getPosition().x < PARAM_BORDER_X->x) {
			force.x += PARAM_BORDER_MULT * (PARAM_BORDER_X->x - getPosition().x);
		}
		if (getPosition().x > PARAM_BORDER_X->y) {
			force.x += PARAM_BORDER_MULT * (PARAM_BORDER_X->y - getPosition().x);
		}
		if (getPosition().y < PARAM_BORDER_Y->x) {
			force.y += PARAM_BORDER_MULT * (PARAM_BORDER_Y->x - getPosition().y);
		}
		if (getPosition().y > PARAM_BORDER_Y->y) {
			force.y += PARAM_BORDER_MULT * (PARAM_BORDER_Y->y - getPosition().y);
		}
		if (getPosition().z < PARAM_BORDER_Z->x) {
			force.z += PARAM_BORDER_MULT * (PARAM_BORDER_Z->x - getPosition().z);
		}
		if (getPosition().z > PARAM_BORDER_Z->y) {
			force.z += PARAM_BORDER_MULT * (PARAM_BORDER_Z->y - getPosition().z);
		}
	}
	
	//connect to particle if distance is less than  PARAM_CONNECT_DIST
	if (checkAttribute(ATTR_CONNECT_NEXT)) {	//TODO:Namen überdenken
		int index = getIdClosestParticle(ATTR_CONNECT_PREV, false, true);
		if (index != -1) {
			float dist = particlesPtr->at(index).getPosition().distance(getPosition());
			if (dist < PARAM_CONNECT_DIST) {
				nextPtr = &(particlesPtr->at(index));
				nextPtr->prevPtr = &(particlesPtr->at(id));
				//nextPtr->drag = 0.9999;
				//nextPtr->mass = 5.0;
		
				disableAttribute(ATTR_CONNECT_NEXT);
				//enableAttribute(ATTR_SPRING_NEXT);
		
				nextPtr->enableAttribute(ATTR_SPRING_PREV);
				nextPtr->disableAttribute(ATTR_CONNECT_PREV);
		
				nextPtr->changeState(STATE_PAIRING);
				changeState(STATE_PAIRING);
			}
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
			force += springStiffness * (prevPtr->getPosition() - getPosition());
		}
	}
	
	if (checkAttribute(ATTR_SPRING_NEXT)) {
		if (nextPtr != NULL) {
			force += springStiffness * (nextPtr->getPosition() - getPosition());
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