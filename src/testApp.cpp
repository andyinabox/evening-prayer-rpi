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

		// create a plane the width & height of the screen
	    plane.set(ofGetWidth(), ofGetHeight(), 30, 30);
	    // map the plane's texture coordinates to the camera
	    // width / height
	    plane.mapTexCoords(0, 0, cameraWidth, cameraHeight);

	} else {
		// throw an error if loading fails
		throw std::runtime_error( "Failed to load config file" );
	}
}


//--------------------------------------------------------------
void testApp::update(){
	camera.update();
}

//--------------------------------------------------------------
void testApp::draw(){

	// set the background color
	ofBackground(0,0,0);

	// find the center of the screen
	// @todo might just want to move this to setup
	// since screen size is not expected to change
    float cx = ofGetWidth() / 2.0;
    float cy = ofGetHeight() / 2.0;

    // this is in seconds
    float t = ofGetElapsedTimef();
    // @todo move this to setup
    // this is also in seconds

    // start the shader
	shader.begin();
    	
    	// set uniforms
    	shader.setUniformTexture("camera", camera.getTextureReference(), 1);
    	shader.setUniform1f("time", t);
    	shader.setUniform1f("period", period);

    	// draw our image plane
    	ofPushMatrix();	
    		// place coordinate center in the cente of the screen
    		ofTranslate(cx, cy);
    		plane.draw();
    	ofPopMatrix();
    
    // end the shader
    shader.end();

    if(showHud) {
    	ofDrawBitmapString(ofToString(t) + " / " + ofToString(ofGetFrameRate()), 10, 20);   
	}

}


//--------------------------------------------------------------
void testApp::keyPressed  (int key){ 

	// space bar to toggle HUD
	if(key == 32) {
		showHud = !showHud;
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
