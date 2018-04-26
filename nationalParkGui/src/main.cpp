#include "ofMain.h"
#include "ofApp.h"
#include "parkInfoParser.h"
#include "curl/curl.h"
#include <string>
#include <iostream>

//========================================================================
int main( ){
	ofSetupOpenGL(1024,768,OF_WINDOW);			// <-------- setup the GL context

    
    parkInfoParser::getJsonFromString(parkInfoParser::getJsonString("il"));
    
	// this kicks off the running of my app
	// can be OF_WINDOW or OF_FULLSCREEN
	// pass in width and height too:
	ofRunApp(new ofApp());
    
  
    
    return 0;
}


