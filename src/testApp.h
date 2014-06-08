#pragma once

#include "ofMain.h"
#include "ofxJSONElement.h"

#ifdef TARGET_RASPBERRY_PI
	#include "wiringPi.h"
#endif

class testApp : public ofBaseApp{
	
	public:
		
		void setup();
		void update();
		void draw();

		int getProximityValue(int pin);

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);		
		
		// config loading
		ofxJSONElement config;
		bool configLoaded;

		// sensor
		int inputPin;
		int proximityActive;

		// camera stuff
		ofVideoGrabber camera;
		int cameraWidth;
		int cameraHeight;
		int screenWidth;
		int screenHeight;

		// gl stuff
	    ofPlanePrimitive plane;
        ofShader shader;
        int period;
        bool showHud;

};
