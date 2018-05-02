#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include <vector>

class ofApp : public ofBaseApp{
    
    ofxPanel gui;
    ofImage map;
    vector<ofImage> red_dot_vect;
    

	public:
		void setup();
        void setupParkInfo();
        void setupRedDots();
		void update();
		void draw();

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
        tuple<double,double> scaleLatLong(tuple<double,double> lat_long_to_scale);
};
