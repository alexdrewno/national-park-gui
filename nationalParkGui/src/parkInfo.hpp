//
//  parkInfo.hpp
//  nationalParkGui
//
//  Created by Alex Drewno on 4/25/18.
//

#ifndef parkInfo_hpp
#define parkInfo_hpp

#include <stdio.h>
#include <vector>
#include <tuple>
#include <string>

using namespace std;

class parkInfo {
    vector<string> states;
    tuple<double,double> latLong;
    string description;
    string designation;
    string parkCode;
    string id;
    string directionsInfo;
    string directionsUrl;
    string fullName;
    string url;
    string weatherInfo;
    string name;
    
public:
    parkInfo();
    parkInfo(vector<string> states,
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
             string name);
    string getName();
};


#endif /* parkInfo_hpp */
