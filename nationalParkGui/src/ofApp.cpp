#include "ofApp.h"
#include "parkInfoParser.h"
#include "curl/curl.h"
#include <string>
#include <iostream>
#include <vector>

const string STATE_CODES[50] = {"AL","AK","AZ","AR","CA","CO","CT","DE","FL","GA","HI","ID","IL","IN","IA","KS","KY","LA","ME","MD","MA","MI","MN","MS","MO","MT","NE","NV","NH","NJ","NM","NY","NC","ND","OH","OK","OR","PA","RI","SC","SD","TN","TX","UT","VT","VA","WA","WV","WI","WY"};
map<string, vector<parkInfo>> park_infos_in_states;
vector<tuple<double,double>> red_dot_locations;
string state_code;
vector<parkInfo> park_info_state;
vector<parkInfo> all_park_info;
parkInfo closest_park;
double cur_long;
double cur_lat;

using namespace std;

//--------------------------------------------------------------
void ofApp::setup(){
    //gui.setup();
    map.load("map.png");
    setupParkInfo();
    setupRedDots();
    
}

void ofApp::setupParkInfo() {
    if (park_infos_in_states.size() == 0) {
        for (auto state_code : STATE_CODES) {
            vector<parkInfo> park_info_in_state = parkInfoParser::getJsonFromString(parkInfoParser::getJsonString(state_code));
            park_infos_in_states[state_code] = park_info_in_state;
            all_park_info.insert(end(all_park_info), begin(park_info_in_state), end(park_info_in_state));
        }
    }
}

void ofApp::setupRedDots() {
    for (auto park_info : all_park_info) {
        ofImage red_dot;
        
        red_dot.load("red_dot.png");
        red_dot_vect.push_back(red_dot);
        tuple<double,double> scaled_lat_long = scaleLatLong(make_tuple(get<1>(park_info.getLatLong()), get<0>(park_info.getLatLong())));
        cout << get<0>(park_info.getLatLong()) << endl;
        red_dot_locations.push_back(scaled_lat_long);
    }
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
    float x_pos = 100;
    float y_pos = 50;
    
    
    //gui.draw();
    ofDrawBitmapString(state_code.c_str(), x_pos, y_pos);
    
    for(auto park_info : park_info_state) {
        y_pos += 50;
        ofDrawBitmapString(park_info.getName().c_str(), x_pos, y_pos);
    }
    
    ofDrawBitmapString(closest_park.getName().c_str(), x_pos, y_pos+100);
    map.draw(0, 0);
    map.resize(ofGetWidth(), ofGetHeight());
    //red_dot.resize(10, 10);
    
    for (int i = 0; i < red_dot_locations.size() && i < red_dot_vect.size(); i++) {
        tuple<double,double> scaled_location = red_dot_locations[i];
        red_dot_vect[i].resize(5, 5);
        red_dot_vect[i].setAnchorPoint(2.5, 2.5);
        red_dot_vect[i].draw(get<0>(scaled_location), get<1>(scaled_location));
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if (key == 'n'){
        
        state_code = ofSystemTextBoxDialog("Input State-Code", state_code);
        park_info_state = park_infos_in_states[state_code];
        draw();
    }
    
    if (key == 'm') {
        string cur_lat_string;
        string cur_long_string;
        
        cur_lat = stod(ofSystemTextBoxDialog("Input Latitude", cur_lat_string));
        cur_long = stod(ofSystemTextBoxDialog("Input Longitude", cur_long_string));
        closest_park = parkInfo::closestParkToLocation(make_tuple(cur_lat,cur_long), all_park_info);
        
        red_dot_locations.push_back(make_tuple(cur_lat,cur_long));
        
        cout << all_park_info.size() << endl;
        cout << closest_park.getName() << endl;
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}

tuple<double,double> ofApp::scaleLatLong(tuple<double,double> lat_long_to_scale) {
    //these numbers should be changed if using a diff map image
    double zero_position_lat = -129.53;
    double zero_position_long = 48.8961;
    double delta_lat = 64.5;
    double delta_long = 23.7669;
    double lat_step = ofGetWidth()/delta_lat;
    double long_step = ofGetHeight()/delta_long;
    
    double this_lat = get<0>(lat_long_to_scale);
    double this_long = get<1>(lat_long_to_scale);
    
    double normalized_lat = this_lat-zero_position_lat;
    double normalized_long = zero_position_long-this_long;
    
    return make_tuple(normalized_lat * lat_step, normalized_long * long_step);
}
