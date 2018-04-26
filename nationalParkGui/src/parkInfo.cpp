//
//  parkInfo.cpp
//  nationalParkGui
//
//  Created by Alex Drewno on 4/25/18.
//

#include "parkInfo.hpp"

parkInfo::parkInfo(vector<string> states,
                   tuple<double,double> latLong,
                   string description,
                   string designation,
                   string parkCode,
                   string id,
                   string directionsInfo,
                   string directionsUrl,
                   string fullName,
                   string url,
                   string weatherInfo,
                   string name) {
    this->states = states;
    this->latLong = latLong;
    this->description = description;
    this->parkCode = parkCode;
    this->id = id;
    this->directionsInfo = directionsInfo;
    this->directionsUrl = directionsUrl;
    this->fullName = fullName;
    this->url = url;
    this->weatherInfo = weatherInfo;
    this->name = name;
}

parkInfo::parkInfo() {
    
}

string parkInfo::getName() {
    return name;
}
