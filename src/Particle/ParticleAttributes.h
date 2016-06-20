#pragma once

#include "ofMain.h"
#include "ofParameter.h"

#define ATTR_BORDER_XYZ			1 << 1
#define ATTR_BORDER_CIRCLE		1 << 2
#define ATTR_CENTRAL_FORCE		1 << 3
#define ATTR_GRAVITATION		1 << 4
#define ATTR_CONNECT_PAIR		1 << 5
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
#define ATTR_ATTRACTION_COLOR			1 << 16

#define ATTR_DRAW_LINE_DIST		1 << 17		//draw line to other particle in range
#define ATTR_DRAW_LINE_NEXT		1 << 18		//draw line to closest particle
#define ATTR_DRAW_LINE_PREV		1 << 19		//draw line to prev particle


class ParticleAttributes{
	public:
		ParticleAttributes();
		
		ofParameterGroup group;
		
		ofParameter<bool> border_xyz;
		ofParameter<bool> connect_next;
		ofParameter<bool> connect_prev;
		ofParameter<bool> spring_next;
		ofParameter<bool> spring_prev;
		ofParameter<bool> collision;
		ofParameter<bool> attraction_color;
		ofParameter<bool> draw_line_dist;
		
		unsigned int bits = 0;
		
		bool checkAttribute(int attribute);
		bool checkAttributes(int bits_);
		
	private:
		void set_border_xyz(bool &b_);
		void set_border_circle(bool &b_);
		void set_connect_next(bool &b_);
		void set_connect_prev(bool &b_);
		void set_spring_next(bool &b_);
		void set_spring_prev(bool &b_);
		void set_collision(bool &b_);
		void set_attraction_color(bool &b_);
		
		void set_draw_line_dist(bool &b_);
		void set_draw_line_next(bool &b_);		
		
};