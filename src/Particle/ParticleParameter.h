#pragma once

#include "ofMain.h"
#include "ofParameter.h"


class ParticleParameter{
	public:
		ParticleParameter();
		
		ofParameterGroup attributes_bool;
		ofParameterGroup parameter_double;
		
		
	private:

		
		ofParameter<float> PARAM_COLOR_DIFF_MULT;
		ofParameter<float> PARAM_COLLISION_MULT;
		
		ofParameter<ofVec2f> PARAM_BORDER_X;
		ofParameter<ofVec2f> PARAM_BORDER_Y;
		ofParameter<ofVec2f> PARAM_BORDER_Z;
		
		ofParameter<float> drag;
		ofParameter<float> mass;
		
		ofParameter<float> springStiffness;
		ofParameter<float> springDamping;
	
};