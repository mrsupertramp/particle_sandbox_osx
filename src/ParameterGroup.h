#pragma once

#include "ofMain.h"
#include "ofParameterGroup.h"
#include "ofxGui.h"


class ParameterGroup : public ofxPanel{
	public:
		ParameterGroup();
	private:
		//------------------------------------------------GUI--------------
		void setParticlesDrag(float val);
		void setParticlesMass(float val);
		void setParticlesSpringStiffness(float val);
		void setParticlesSpringDamping(float val);
		void setParticlesCollisionMult(float val);
		void setParticlesColorDiffMult(float val);
		void setParticlesBorderX(ofVec2f val);
		void setParticlesBorderY(ofVec2f val);
		void setParticlesBorderZ(ofVec2f val);
		ofxFloatSlider para_drag;
		ofxFloatSlider para_mass;
		ofxFloatSlider para_spring_stiffness;
		ofxFloatSlider para_spring_damping;
		
		ofxFloatSlider paraCollisionMult;
		ofxFloatSlider paraColorDiffMult;
		ofxVec2Slider paraBorderX;
		ofxVec2Slider paraBorderY;
		ofxVec2Slider paraBorderZ;
		//checkboxes for next generated particle attribubutes
		ofxToggle attr_border_xyz;
		ofxToggle attr_collision;
		ofxToggle attr_spring_prev;
		ofxToggle attr_connect_next;
		ofxToggle attr_connect_prev;
		ofxToggle attr_color_diff;
		
		ofxButton overrideAttributes;
		
		void setAttributeBorderXYZ(bool &attr_border_xyz);	
		void setAttributeCollision(bool &attr_collision);	
		void setAttributeColorDiff(bool &attr_color_diff);
		void setAttributeSpringPrev(bool &attr_spring_prev);
		void setAttributeConnectNext(bool &attr_connect_next);
		void setAttributeConnectPrev(bool &attr_connect_prev);
			
};