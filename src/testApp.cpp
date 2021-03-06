#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
	string configFile;

	// setup to load the correct shaders
	// based on GPU
	#ifdef TARGET_OPENGLES
		configFile = "production.json";
		shader.load("shadersES2/shader");
	#else
		configFile = "development.json";
		shader.load("shadersGL2/shader");
	#endif

	

	configLoaded = config.open("config/"+configFile);
	
	// load the json config
	if(configLoaded) {

		cout << "config file loaded:" << endl;
		cout << config.getRawString() << endl;

		// set up our sizes from the config
		cameraWidth	= config["cameraWidth"].asInt();
		cameraHeight = config["cameraHeight"].asInt();
	
	
		// this will be our initial cycle period
		period = config["period"].asFloat();
		showHud = config["showHud"].asBool();


	    // get a list of devices 
		vector<ofVideoDevice> devices = camera.listDevices();
		
		// check available devices and out and log their status
	    for(int i = 0; i < devices.size(); i++){
			cout << devices[i].id << ": " << devices[i].deviceName; 
	        if( devices[i].bAvailable ){
	            cout << endl;
	        }else{
	            cout << " - unavailable " << endl; 
	        }
		}

		// can't remember what this does but it's in the example
		ofSetVerticalSync(true);
	    
	    // setup the camera
		camera.setDeviceID(0);
		camera.setDesiredFrameRate(60);
		camera.initGrabber(cameraWidth, cameraHeight);


		// sensor setup
		#ifdef TARGET_RASPBERRY_PI
			cout << "setup wiring pi" << endl;
			wiringPiSetup();
			inputPin = config["inputPin"].asInt();
			cout << "set proximityActive" << endl;
			proximityActive = 0;
		#else
			inputPin = config["inputPin"].asInt();
			proximityActive = 1;			
		#endif


	} else {
		// throw an error if loading fails
		throw std::runtime_error( "Failed to load config file" );
	}
}


//--------------------------------------------------------------
void testApp::update(){
	#ifdef TARGET_RASPBERRY_PI
		// we will get a HIGH (1) if the proximity sensor is NOT triggered,
		// and a LOW (0) if it is. To make this more semantically meaningful
		// these values are inverted (so 1 is on, 0 is off)
		int newProximityState = getProximityValue(inputPin);

		// update the value if different
		if(newProximityState != proximityActive) {
			cout << "update proximityActive: " << newProximityState << endl;
			proximityActive = newProximityState;
		}
	#endif
	camera.update();
}

//--------------------------------------------------------------
void testApp::draw(){

	// set the background color
	ofBackground(0,0,0);


    // this is in seconds
    float t = ofGetElapsedTimef();
    // @todo move this to setup
    // this is also in seconds

    // start the shader
	shader.begin();
    	
    	// set uniforms
    	shader.setUniform1f("time", t);
    	shader.setUniform1f("period", period);
    	shader.setUniform1i("active", proximityActive);

    	// draw our image plane
    	ofPushMatrix();	
    		camera.draw(0, 0, ofGetWidth(), ofGetHeight());
    	ofPopMatrix();
    
    // end the shader
    shader.end();

    if(showHud) {
    	ofDrawBitmapString(ofToString(t) + " / " + ofToString(ofGetFrameRate()), 10, 20);   
	}

}

/**
 * Get the proximity value using wiringPi
 * @param  pin GPIO pin
 * @return 1 or 0 based on input value
 */
int testApp::getProximityValue (int pin) {
	#ifdef TARGET_RASPBERRY_PI
		return !!digitalRead(pin) ? 0 : 1; 
	#else
		return proximityActive;
	#endif
}


//--------------------------------------------------------------
void testApp::keyPressed  (int key){ 

	// space bar to toggle HUD
	if(key == 32) {
		showHud = !showHud;
	}
	// "a" key to toggle active state for dev mode
	if(key == 97) {
		proximityActive = proximityActive ? 0 : 1;
	}
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){ 
	
}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){
	
}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){
	
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
	
}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}
