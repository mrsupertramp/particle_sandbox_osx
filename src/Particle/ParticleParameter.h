#pragma once

#include "ofMain.h"
#include "ofParameter.h"


class ParticleParameter{
	public:
		ParticleParameter();
		
		ofParameterGroup group;
		ofParameter<float> color_diff_mult;
		ofParameter<float> collision_mult;
		
		ofParameter<ofVec2f> border_x_range;
		ofParameter<ofVec2f> border_y_range;
		ofParameter<ofVec2f> border_z_range;
		
		ofParameter<float> drag;
		ofParameter<float> mass;
		
		ofParameter<float> spring_stiffness;
		ofParameter<float> spring_damping;
		
	private:

		

	
};