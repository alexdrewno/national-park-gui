//
//  parkInfoParser.cpp
//  nationalParkGui
//
//  Created by Alex Drewno on 4/25/18.
//

#include "parkInfoParser.h"
#include "curl/curl.h"
#include "json.h"
#include "json-forwards.h"
#include <string>
#include <iostream>
#include <map>
#include "parkInfo.hpp"

using namespace std;

//https://gist.github.com/alghanmi/c5d7b761b2c9ab199157
size_t parkInfoParser::WriteCallback(void *contents, size_t size, size_t nmemb, void *userp) {
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

string parkInfoParser::getJsonString(string for_state_code) {
    auto curl = curl_easy_init();
    string response_string;
    
    if (curl) {
        string url = "https://developer.nps.gov/api/v1/parks?stateCode=" + for_state_code + "&api_key=knbpdf8LwcmTPaY6rigCxQJRFxP6zDRKRbCRSFp7";
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response_string);
        
        curl_easy_perform(curl);
        curl_easy_cleanup(curl);
        
        return response_string;
    }
}

vector<parkInfo> parkInfoParser::getJsonFromString(string json_string) {
    Json::Value root;
    Json::Reader reader;
    vector<parkInfo> park_info_objects;
    
    bool success = reader.parse(json_string, root, false);
    
    for (auto element : root["data"]) {
        vector<string> states;
        states = vectorFromString(element["states"].asString());
        
        tuple<double,double> latLong_tuple;
        latLong_tuple = tupleFromString(element["latLong"].asString());
        
        string description = element["description"].asString();
        string designation = element["designation"].asString();
        string park_code = element["parkCode"].asString();
        string id = element["id"].asString();
        string directions_info = element["directionsInfo"].asString();
        string directions_url = element["directionsUrl"].asString();
        string full_name = element["fullName"].asString();
        string url = element["url"].asString();
        string weather_info = element["weatherInfo"].asString();
        string name = element["name"].asString();
        
        park_info_objects.push_back(parkInfo(states,
                                         latLong_tuple,
                                         description,
                                         designation,
                                         park_code,
                                         id,
                                         directions_info,
                                         directions_url,
                                         full_name,
                                         url,
                                         weather_info,
                                             name));
    }
    
    cout << park_info_objects.size() << endl;
    return park_info_objects;
}

vector<string> parkInfoParser::vectorFromString(string from_string) {
    string cur_string = "";
    vector<string> string_vector;
    
    for(auto element : from_string) {
        if (element == ',') {
            string_vector.push_back(cur_string);
            cur_string = "";
        } else {
            cur_string += element;
        }
    }
    
    if(cur_string != "") {
        string_vector.push_back(cur_string);
    }
    
    return string_vector;
}

tuple<double,double> parkInfoParser::tupleFromString(string from_string) {
    vector<string> latLong_vector = vectorFromString(from_string);
    
    double num_lat = 0;
    double num_long = 0;
    
    if(latLong_vector.size() == 2) {
        int lat_index = latLong_vector[0].find(':');
        int long_index = latLong_vector[1].find(':');
        num_lat = stod(latLong_vector[0].substr(lat_index+1));
        num_long = stod(latLong_vector[1].substr(long_index+1));
    
    }
    
    tuple<double,double> latLong_tuple(num_lat,num_long);
    return latLong_tuple;
}



