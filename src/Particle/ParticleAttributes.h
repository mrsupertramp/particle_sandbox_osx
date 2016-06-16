#pragma once

#include "ofMain.h"
#include "ofParameter.h"
/*
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

#define ATTR_DRAW_LINE_DIST		1 << 17		//draw line to other particle in range
#define ATTR_DRAW_LINE_NEXT		1 << 18		//draw line to closest particle
#define ATTR_DRAW_LINE_PREV		1 << 19		//draw line to prev particle
*/

#define ATTR_BORDER_XYZ			1
#define ATTR_BORDER_CIRCLE		2
#define ATTR_CENTRAL_FORCE		3
#define ATTR_GRAVITATION		4
//#define ATTR_CONNECT_PAIR		1 << 5
#define ATTR_CONNECT_NEXT		6
#define ATTR_CONNECT_PREV		7
#define ATTR_CONNECT_GROUP		8
#define ATTR_GRAV_PAIR			9
#define ATTR_GRAV_GROUP			10
#define ATTR_SPRING_NEXT		11
#define ATTR_SPRING_PREV		12
#define ATTR_SPRING				13
#define ATTR_INVISIBLE			1 << 14
#define ATTR_COLLISION			1 << 15
#define ATTR_COLOR_DIFF			1 << 16

#define ATTR_DRAW_LINE_DIST		1 << 17		//draw line to other particle in range
#define ATTR_DRAW_LINE_NEXT		1 << 18		//draw line to closest particle
#define ATTR_DRAW_LINE_PREV		1 << 19		//draw line to prev particle

class ParticleAttributes{
	public:
		ParticleAttributes();
			
		void enableAttribute(int attribute); 
		void disableAttribute(int attribute);
		void setAttributes(int newAttributes);
		void setAttribute(int attribute);
		void toggleAttribute(int attribute);
		
	private:
		ofParameter<bool> ATTR_BORDER_XYZ;
		ofParameter<bool> ATTR_CONNECT_NEXT;
		ofParameter<bool> ATTR_CONNECT_PREV;
		ofParameter<bool> ATTR_SPRING_NEXT;
		ofParameter<bool> ATTR_SPRING_PREV;
		ofParameter<bool> ATTR_COLLISION;
		ofParameter<bool> ATTR_COLOR_DIFF;
		
		
}