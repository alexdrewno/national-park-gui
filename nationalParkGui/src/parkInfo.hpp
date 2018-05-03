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
    static double distanceBetweenParks(parkInfo park_one, parkInfo park_two);
    static double distanceBetweenLatLong(tuple<double,double> this_lat_long, tuple<double,double> other_lat_long);
    static parkInfo closestParkToLocation(tuple<double,double> location, vector<parkInfo> parks);
    static double sumEdgeWeights(vector<tuple<parkInfo,parkInfo>> paths);
    static vector<tuple<parkInfo,parkInfo>> mainMinKCycle(vector<parkInfo> vertices, parkInfo start, parkInfo end, int k);
    static vector<tuple<parkInfo,parkInfo>> minKCycle(vector<parkInfo> vertices, parkInfo start, parkInfo end, int k, vector<bool> visited);
    void setLatLong(tuple<double,double> lat_long_to_set);
    static vector<parkInfo> closestParksTo(tuple<double,double> location, vector<parkInfo> parks, int n);
};


#endif /* parkInfo_hpp */
