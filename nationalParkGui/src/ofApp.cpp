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
vector<tuple<parkInfo,parkInfo>> shortest_path;

using namespace std;

//--------------------------------------------------------------
void ofApp::setup(){
    //gui.setup();
    map.load("map.png");
    setupParkInfo();
    setupRedDots();
    
}

//Makes all of the API calls to get all the info for each state code
void ofApp::setupParkInfo() {
    if (park_infos_in_states.size() == 0) {
        for (auto state_code : STATE_CODES) {
            vector<parkInfo> park_info_in_state = parkInfoParser::getJsonFromString(parkInfoParser::getJsonString(state_code));
            park_infos_in_states[state_code] = park_info_in_state;
            all_park_info.insert(end(all_park_info), begin(park_info_in_state), end(park_info_in_state));
        }
    }
}

//Sets up each park location with a red dot (takes a while because does it everytime the program is run)
void ofApp::setupRedDots() {
    for (auto park_info : all_park_info) {
        ofImage red_dot;
        
        red_dot.load("red_dot.png");
        red_dot_vect.push_back(red_dot);
        tuple<double,double> scaled_lat_long = scaleLatLong(park_info.getLatLong());
        red_dot_locations.push_back(scaled_lat_long);
    }
}

//--------------------------------------------------------------
void ofApp::update(){

}

//draws the graphics of the gui; lengthy but understandable
void ofApp::draw(){
    float x_pos = 25;
    float y_pos = 25;
    
    
    // Setting up the user options on the map
    // --------------------------------------------------------------------------------------
    ofDrawBitmapString("Press n for parks in state-code",x_pos,y_pos);
    y_pos+=25;
    ofDrawBitmapString("Press m for closest park to cur_location", x_pos, y_pos);
    y_pos+=25;
    ofDrawBitmapString("Press b for shortest path between N parks", x_pos, y_pos);
    y_pos+=25;
    //gui.draw();
    x_pos = 800;
    y_pos = 25;
    // --------------------------------------------------------------------------------------

    //Draws names of parks in state
    // --------------------------------------------------------------------------------------
    for(auto park_info : park_info_state) {
        y_pos += 20;
        ofDrawBitmapString(park_info.getName().c_str(), x_pos, y_pos);
    }
    // --------------------------------------------------------------------------------------
    
    map.draw(0, 200);
    map.resize(ofGetWidth(), ofGetHeight()-200);
    
    //Draws red dots in park locations
    // --------------------------------------------------------------------------------------
    for (int i = 0; i < red_dot_locations.size() && i < red_dot_vect.size(); i++) {
        tuple<double,double> scaled_location = red_dot_locations[i];
        red_dot_vect[i].resize(5, 5);
        red_dot_vect[i].setAnchorPoint(2.5, 2.5);
        red_dot_vect[i].draw(get<0>(scaled_location), get<1>(scaled_location));
    }
    // --------------------------------------------------------------------------------------
    
    //Draws shortest path from location
    // --------------------------------------------------------------------------------------
    x_pos = 800;
    y_pos = 25;
    for (auto path : shortest_path) {
        ofDrawBitmapString(get<1>(path).getName(), x_pos, y_pos);
        y_pos += 25;
    }
    // --------------------------------------------------------------------------------------
    
    
    ofDrawBitmapString("Closest Park: " + closest_park.getName(), 500, 50);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if (key == 'n'){
        userInputStateCodeHandler();
    }
    
    if (key == 'm') {
        userInputClosestPark();
    }
    
    if (key == 'b') {
        userInputShortestPath();
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

//Input a state code to get parks within that state
void ofApp::userInputStateCodeHandler() {
    state_code = ofSystemTextBoxDialog("Input State-Code", state_code);
    park_info_state = park_infos_in_states[state_code];
    closest_park = parkInfo();
    draw();
}

//Input a lat-long to get the closest park to you
void ofApp::userInputClosestPark() {
    string cur_lat_string;
    string cur_long_string;
    
    cur_lat = stod(ofSystemTextBoxDialog("Input Current Latitude", cur_lat_string));
    cur_long = stod(ofSystemTextBoxDialog("Input Current Longitude", cur_long_string));
    closest_park = parkInfo::closestParkToLocation(make_tuple(cur_lat,cur_long), all_park_info);
    
    vector<parkInfo> empty_park_info_state;
    park_info_state = empty_park_info_state;
}

//Input a lat-long and number of parks to get the shortest path between n-parks
void ofApp::userInputShortestPath() {
    string cur_lat_string;
    string cur_long_string;
    string num_parks_string;
    int num_parks;
    
    cur_lat = stod(ofSystemTextBoxDialog("Input Current Latitude", cur_lat_string));
    cur_long = stod(ofSystemTextBoxDialog("Input Current Longitude", cur_long_string));
    num_parks = stoi(ofSystemTextBoxDialog("Input num parks wanting to visit", num_parks_string));
    
    parkInfo cur_location;
    cur_location.setLatLong(make_tuple(cur_lat,cur_long));
    
    shortest_path = parkInfo::mainMinKCycle(parkInfo::closestParksTo(cur_location.getLatLong(), all_park_info, 50), cur_location, cur_location, num_parks);
}

//Scales lat-long so that it can be located on the map within the gui
tuple<double,double> ofApp::scaleLatLong(tuple<double,double> lat_long_to_scale) {
    //these numbers should be changed if using a diff map image
    double zero_position_lat = -129.53;
    double zero_position_long = 48.8961;
    double delta_lat = 64.5;
    double delta_long = 23.7669;
    double lat_step = ofGetWidth()/delta_lat;
    double long_step = (ofGetHeight()-200)/delta_long;
    
    double this_lat = get<0>(lat_long_to_scale);
    double this_long = get<1>(lat_long_to_scale);
    
    double normalized_lat = this_lat-zero_position_lat;
    double normalized_long = zero_position_long-this_long;
    
    return make_tuple(normalized_lat * lat_step, normalized_long * long_step + 200);
}
