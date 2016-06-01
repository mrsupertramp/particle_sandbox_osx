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
		vector <Particle> particles;
		
		void setParticlesCollisionMult(float val);
		void setParticlesColorDiffMult(float val);
		
		float paraCollisionMultOld;
		float paraColorDiffMultOld;
		
		ofxFloatSlider paraCollisionMult;
		ofxFloatSlider paraColorDiffMult;
		//checkboxes for next generated particle attribubutes
		ofxPanel gui;
		
		void updateParameter();
		
		bool isMousePressed = false;
		
		
		

		
		
			
};
