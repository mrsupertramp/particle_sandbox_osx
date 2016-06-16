/*
COPYRIGHT ENRICO STEINFELD. ALL RIGHTS RESERVED
*/

#pragma once

#include "ofMain.h"
#include "ofNode.h"
#include "ofParameter.h"

//ein partikel befindet sich in EINEM state
//kann als aufgabe interpretiert werden. wenn keine aufgabe vorhanden dann idle.
#define STATE_IDLE			0
#define STATE_BIRTH			1
#define STATE_DEATH			2
#define STATE_GO_TO_POS			3
#define STATE_PAIRING			4
#define STATE_SEPERATE			5

// ein Partikel kann mehrere Attribute besitzen




//TODO: Oberklasse Swarm
//TODO: Alter einführen 

#define NUM_ATTRIBUTES			20

#define CONST_TIME_BIRTH		1000


class Particle : public ofNode {
	public:
		Particle();
		Particle(ofVec3f pos_, ofVec3f vel_, ofParameterGroup *parameters_=NULL, int attributes_=0, vector <Particle> * pptr = NULL);
		void setup();
		void resetLinks();
		virtual void update();
		virtual void draw();
		void draw(ofVec3f lookAt);
		
		void changeState(unsigned int newState);
		

		
		bool checkAttribute(int attribute);
		bool checkAttributes(int attributes_);
		
		void setRadius(float val);
		void setDrag(float val);
		void setMass(float val);
		void setSpringStiffness(float val);
		void setSpringDamping(float val);
		
		double getRadius();
		int getState();
		
		ofVec3f velocity;
		ofVec3f acceleration;
		ofVec3f force;
		
		unsigned int id;
		

		ParticleParameter parameters;
		
		
		float 		PARAM_CONNECT_DIST 		= 30;	//TODO: Umbenennen
		float 		PARAM_MAX_SPEED 		= 10;	//TODO: Umbenennen
		float 		PARAM_BORDER_MULT 		= 0.4;	//TODO: Umbenennen
		
		ofColor color;
		
		string getBit(int k);
		
	
	private:
		
		int getIdClosestParticle(int attributes_, bool checkNextPtr=false, bool checkPrevPtr=false);
		double getDistanceClosestParticle(int attributes_, bool checkNextPtr=false, bool checkPrev=false);
		
		vector <Particle>* particlesPtr;
		//beliebig viele Verbindungen
		
		Particle* prevPtr;
		Particle* nextPtr;
		vector <Particle*> groupPtr;
		
		unsigned int state;
		unsigned int tLastStateChange;
		
		double distanceToClosestParticle = -1;
		
		
		void setParameters(ofParameterGroup *parameters_);
		
		bool grouped;
		
		//appearance
		float radius;
		float radiusBirth;
						
		
				
};
