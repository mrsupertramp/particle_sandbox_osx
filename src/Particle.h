/*
COPYRIGHT ENRICO STEINFELD. ALL RIGHTS RESERVED
*/

#pragma once

#include "ofMain.h"
#include "ofNode.h"

//ein partikel befindet sich in EINEM state
//kann als aufgabe interpretiert werden. wenn keine aufgabe vorhanden dann idle.
#define STATE_IDLE			0
#define STATE_BIRTH			1
#define STATE_DEATH			2
#define STATE_GO_TO_POS			3
#define STATE_PAIRING			4
#define STATE_SEPERATE			5

// ein Partikel kann mehrere Attribute besitzen
#define ATTR_DRAG				1 << 0	// TODO: TODO: TODO: KOMMENTARE!!!!!!!
#define ATTR_BORDER_XYZ			1 << 1
#define ATTR_BORDER_CIRCLE		1 << 2
#define ATTR_CENTRAL_FORCE		1 << 3
#define ATTR_GRAVITATION		1 << 4
//#define ATTR_CONNECT_PAIR		1 << 5
#define ATTR_CONNECT_NEXT		1 << 6
#define ATTR_CONNECT_PREV		1 << 7
#define ATTR_CONNECT_GROUP		1 << 8
#define ATTR_GRAV_PAIR			1 << 9
#define ATTR_GRAV_GROUP			1 << 10
#define ATTR_SPRING_NEXT		1 << 11
#define ATTR_SPRING_PREV		1 << 12
#define ATTR_SPRING				1 << 13
#define ATTR_INVISIBLE			1 << 14
#define ATTR_COLLISION			1 << 15
#define ATTR_COLOR_DIFF			1 << 16

#define ATTR_DRAW_LINE_DIST		1 << 17
#define ATTR_DRAW_LINE_NEXT		1 << 18
#define ATTR_DRAW_LINE_PREV		1 << 19



//TODO: Oberklasse Swarm
//TODO: Alter einführen 

#define NUM_ATTRIBUTES			20

#define CONST_TIME_BIRTH		1000


class Particle : public ofNode {
	public:
		Particle(vector <Particle> * pptr, int attributes_, ofVec3f pos_, ofVec3f vel_);
		void setup();
		void resetLinks();
		void update();
		void draw();
		void draw(ofVec3f lookAt);
		
		void changeState(unsigned int newState);
		
		void enableAttribute(int attribute); 
		void disableAttribute(int attribute);
		void setAttributes(int newAttributes);
		void setAttribute(int attribute);
		void toggleAttribute(int attribute);
		
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
		
		float 		PARAM_CONNECT_DIST 		= 60;
		float 		PARAM_MAX_SPEED 		= 10;
		float 		PARAM_BORDER_MULT 		= 0.4;
		float 		PARAM_COLOR_DIFF_MULT 	= 0.0;
		double 		PARAM_COLLISION_MULT 	= 0.0;
		
		ofVec2f PARAM_BORDER_X = ofVec2f(-100,100);
		ofVec2f PARAM_BORDER_Y = ofVec2f(-100,100);
		ofVec2f PARAM_BORDER_Z = ofVec2f(-100,100);

		
		ofColor color;
		
		string getBit(int k);
		
	
	private:
		void updateAttributes();
		
		int getIdClosestParticle(int attributes_, bool checkNextPtr=false, bool checkPrevPtr=false);
		double getDistanceClosestParticle(int attributes_, bool checkNextPtr=false, bool checkPrev=false);
		
		vector <Particle>* particlesPtr;
		
		Particle* prevPtr;
		Particle* nextPtr;
		
		vector <Particle*> groupPtr;
		
		unsigned int state;
		unsigned int attributes;
		unsigned int tLastStateChange;
		
		double distanceToClosestParticle = -1;
		
		float drag;
		float mass;
		
		float springStiffness;
		float springDamping;
		
		bool grouped;
		
		//appearance
		float radius;
		float radiusBirth;
						
		
				
};
