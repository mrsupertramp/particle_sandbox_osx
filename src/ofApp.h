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
		void setParticlesCollisionMult(float val);
		void setParticlesColorDiffMult(float val);
		void setParticlesBorderX(ofVec2f val);
		void setParticlesBorderY(ofVec2f val);
		void setParticlesBorderZ(ofVec2f val);
		
		float paraCollisionMultOld;
		float paraColorDiffMultOld;
		ofVec2f paraBorderXOld;
		ofVec2f paraBorderYOld;
		ofVec2f paraBorderZOld;
		
		//------------------------------------------------GUI--------------
		ofxFloatSlider paraCollisionMult;
		ofxFloatSlider paraColorDiffMult;
		ofxVec2Slider paraBorderX;
		ofxVec2Slider paraBorderY;
		ofxVec2Slider paraBorderZ;
		//checkboxes for next generated particle attribubutes
		ofxToggle attr_collision;
		ofxToggle attr_spring_prev;
		ofxToggle attr_color_diff;
		
		void setAttributeCollision(bool &attr_collision);	
		void setAttributeColorDiff(bool &attr_color_diff);
		void setAttributeSpringPrev(bool &attr_spring_prev);
		
		ofxPanel gui;
		
		bool hideGui = false;
		
		void updateParameter();
		int attributesNextParticle;
		
		
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
