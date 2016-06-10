/*
COPYRIGHT ENRICO STEINFELD. ALL RIGHTS RESERVED
*/

#pragma once

#include "ofMain.h"
#include "Particle.h"
#include "ofxGui.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void println(string s);

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
	
		void generateParticle(ofVec3f pos, ofVec3f vel);
		void generateParticle(ofVec3f pos, ofVec3f vel, int attributes);
		vector <Particle> particles;
		
		vector <Particle> staticParticles;
		
		
		//-----------------------------------------------------PARAMETER---
		void setParticlesDrag(float val);
		void setParticlesMass(float val);
		void setParticlesSpringStiffness(float val);
		void setParticlesCollisionMult(float val);
		void setParticlesColorDiffMult(float val);
		void setParticlesBorderX(ofVec2f val);
		void setParticlesBorderY(ofVec2f val);
		void setParticlesBorderZ(ofVec2f val);
		
		void drawBorders();
		
		float para_drag_last;	//TODO:alle nach diesem muster
		float para_mass_last;
		float para_spring_stiffness_last;
		float paraCollisionMultOld;
		float paraColorDiffMultOld;
		ofVec2f paraBorderXOld;
		ofVec2f paraBorderYOld;
		ofVec2f paraBorderZOld;
		
		//------------------------------------------------GUI--------------
		ofxFloatSlider para_drag;
		ofxFloatSlider para_mass;
		ofxFloatSlider para_spring_stiffness;
		
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
		
		ofxPanel gui;
		
		bool hideGui = false;
		
		void updateParameter();
		int attributesNextParticle;
		
		void setAttributesAllParticles();
		
		
		
		//--------------------------------------------------------------------
		
		
		//------------------------------------------------------CAMERA--------
		
		//Easy Cam vs ofCamera
		ofEasyCam camera;
		
		//--------------------------------------------------------------------
		
		bool isMousePressed = false;
		
		//----------------------------------------------------SHOW STATS--------
		bool hideStats = false;
		
		//----------------------------------------------------------------------
		string getBit(int k);
		
			
};
