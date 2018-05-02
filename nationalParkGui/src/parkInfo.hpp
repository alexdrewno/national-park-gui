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
    parkInfo closestPark(vector<parkInfo> parks);
    tuple<double,double> getLatLong();
    double distanceBetweenParks(parkInfo park_one, parkInfo park_two);
    static double distanceBetweenLatLong(tuple<double,double> this_lat_long, tuple<double,double> other_lat_long);
    static parkInfo closestParkToLocation(tuple<double,double> location, vector<parkInfo> parks);
    static vector<parkInfo> shortestPathBetweenNParks(tuple<double,double> starting_location, int n_parks);
};


#endif /* parkInfo_hpp */
