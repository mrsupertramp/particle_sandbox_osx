/*
COPYRIGHT ENRICO STEINFELD. ALL RIGHTS RESERVED
*/

#pragma once

#include "ofMain.h"
#include "ofNode.h"
#include "ofParameter.h"
#include "ParticleParameter.h"
#include "ParticleAttributes.h"

//ein partikel befindet sich in EINEM state
//kann als aufgabe interpretiert werden. wenn keine aufgabe vorhanden dann idle.
#define STATE_IDLE			0
#define STATE_BIRTH			1
#define STATE_DEATH			2
#define STATE_GO_TO_POS			3
#define STATE_PAIRING			4
#define STATE_SEPERATE			5

// ein Partikel kann mehrere Attribute besitzen

//TODO: Alter einführen 

#define NUM_ATTRIBUTES			20

#define CONST_TIME_BIRTH		1000
#define CONST_CONNECT_DIST 		30		//TODO: Umbenennen
#define CONST_MAX_SPEED 		10		//TODO: Umbenennen
#define CONST_BORDER_MULT 		0.4		//TODO: Umbenennen
#define CONST_DRAW_LINE_DIST	100

class Particle : public ofNode {
	public:
		Particle();
		Particle(ofVec3f pos_, ofVec3f vel_, ParticleParameter *parameters_=NULL, ParticleAttributes *attributes_=NULL, vector <Particle> * pptr = NULL);
		void setup();
		void resetLinks();
		virtual void update();
		virtual void draw();
		virtual void draw(ofVec3f lookAt);
		
		void changeState(unsigned int newState);
	
		int getState();
		double getRadius();
		
		ofVec3f velocity;
		ofVec3f acceleration;
		ofVec3f force;
		
		unsigned int id;

		ParticleParameter parameters;
		ParticleAttributes attributes;
		
		void setParameters(ParticleParameter *parameters_);
		void setAttributes(ParticleAttributes *attributes_);
		
		ofColor color;
		
		bool isDead = false;
		
		void printBits(int k);
		
	
	private:
		void evaluateAttributes();
		int getIdClosestParticle(int attributes_, bool checkNextPtr=false, bool checkPrevPtr=false);
		double getDistanceClosestParticle(int attributes_, bool checkNextPtr=false, bool checkPrev=false);
		
		vector <Particle>* particlesPtr;
		
		//beliebig viele Verbindungen
		Particle* prevPtr;
		Particle* nextPtr;
		
		//vector <Particle*> groupPtr;
		
		unsigned int state;
		unsigned int tLastStateChange;
		
		double distanceToClosestParticle = -1;
		
				
		//appearance
		float radius;
		float radiusBirth;
						
		
				
};
