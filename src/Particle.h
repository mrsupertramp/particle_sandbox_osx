

#pragma once

#include "ofMain.h"

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
#define ATTR_BORDER_XY			1 << 1
#define ATTR_BORDER_CIRCLE		1 << 2
#define ATTR_CENTRAL_FORCE		1 << 3
#define ATTR_GRAVITATION		1 << 4
#define ATTR_CONNECT_PAIR		1 << 5
#define ATTR_CONNECT_NEXT		1 << 6
#define ATTR_CONNECT_GROUP		1 << 7
#define ATTR_GRAV_PAIR			1 << 8
#define ATTR_GRAV_GROUP			1 << 9
#define ATTR_SPRING_NEXT		1 << 10
#define ATTR_SPRING_PREV		1 << 11
#define ATTR_SPRING				1 << 12
#define ATTR_INVISIBLE			1 << 13
#define ATTR_COLLISION			1 << 14
//#define ATTR_DRAW_LINE_DIST
//#define ATTR_DRAW_LINE_NEXT
//#define ATTR_DRAW_LINE_PREV


//TODO: seperate physics/behavior attributes and drawing attributes

#define NUM_ATTRIBUTES			15

#define CONST_TIME_BIRTH		1000


class Particle{
	public:
		Particle(vector <Particle> * pptr, ofVec3f pos_, ofVec3f vel_);
		void setup();
		void update();
		void draw();
		
		void changeState(unsigned int newState);
		
		void enableAttribute(int attribute);
		void disableAttribute(int attribute);
		void setAttributes(int attributes_);
		
		double getRadius();
		
		ofVec3f position;
		ofVec3f velocity;
		ofVec3f acceleration;
		ofVec3f force;
		
		unsigned int id;
		
		float CONST_CONNECT_DIST = 30;
		float CONST_MAX_SPEED = 10;
		float CONST_BORDER_MULT = 0.4;
		float CONST_COLOR_DIFF_MULT = 0.0;
		double CONST_COLLISION_MULT = 0.0;
	
	private:
		void updateAttributes();
		
		bool checkAttribute(int attribute);
		
		
		int getIdClosestParticle(int attributes, bool checkNextPtr=false, bool checkPrevPtr=false);
		double getDistanceClosestParticle(int attributes, bool checkNextPtr=false, bool checkPrev=false);
		
		vector <Particle>* particlesPtr;
		
		Particle* prevPtr;
		Particle* nextPtr;
		
		vector <Particle*> groupPtr;
		
		unsigned int state;
		unsigned int attributes;
		unsigned int tLastStateChange;
		
		double distanceToClosestParticle = -1;
		
		float drag = 1.0;
		float mass = 1.0;
		
		
		bool grouped = false;
		
		//appearance
		float radius;
		float radiusBirth = 8;
		
		ofColor color;
		
		string getBit(int k);
		
				
};
