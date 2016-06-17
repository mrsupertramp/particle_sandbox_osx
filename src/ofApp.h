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
		//void generateParticle(ofVec3f pos, ofVec3f vel, int attributes);
		vector <Particle> particles;
		//Particle nextParticle;
		
		vector <Particle> staticParticles;
		
		
		void drawBorders();
		
		//ofParameterGroup parameters;

		
		ofxButton but_overwriteAttributes;
		ofxButton but_overwriteParameters;
		
		ofxPanel guiAttributes;
		ofxPanel guiParameters;
		
		bool hideGui = false;
		
		int attributesNextParticle;
		
		void overwriteAttributes();
		void overwriteParameters();
		
		
		
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
		
	private:

		Particle nextParticle;
			
};
