//
//  parkInfo.cpp
//  nationalParkGui
//
//  Created by Alex Drewno on 4/25/18.
//

#include "parkInfo.hpp"
#include <math.h>

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

tuple<double,double> parkInfo::getLatLong() {
    return latLong;
}

parkInfo parkInfo::closestPark(vector<parkInfo> parks){
    float radius_of_earth = 6371 * 10^3;
    parkInfo closest_park = parks[0];
    double shortest_dist = distanceBetweenParks(*this, parks[0]);
    
    for(auto park : parks) {
        double next_dist = distanceBetweenParks(*this, park);
        if (next_dist < shortest_dist) {
            shortest_dist = next_dist;
            closest_park = park;
        }
    }
    
    return closest_park;
}

parkInfo parkInfo::closestParkToLocation(tuple<double,double> location, vector<parkInfo> parks) {
    float radius_of_earth = 6371 * 10^3;
    parkInfo closest_park = parks[0];
    double shortest_dist = distanceBetweenLatLong(location, parks[0].getLatLong());
    
    for(auto park : parks) {
        double next_dist = distanceBetweenLatLong(location, park.getLatLong());
        if (next_dist < shortest_dist) {
            shortest_dist = next_dist;
            closest_park = park;
        }
    }
    
    return closest_park;
}

double parkInfo::distanceBetweenParks(parkInfo park_one, parkInfo park_two) {
    double this_lat_radians = (get<0>(park_one.getLatLong()) * M_PI) / 180;
    double this_long_radians = (get<1>(park_one.getLatLong()) * M_PI) / 180;
    double other_lat_radians = (get<0>(park_two.getLatLong()) * M_PI) / 180;
    double other_long_radians = (get<1>(park_two.getLatLong()) * M_PI) / 180;
    double delta_lat = this_lat_radians - other_lat_radians;
    double delta_long = this_long_radians - other_long_radians;
    double dist = sin(this_lat_radians) * sin(other_lat_radians) + cos(this_lat_radians) * cos(other_lat_radians) * cos(delta_long);
    dist = acos(dist);
    dist = (dist*180) / M_PI;
    dist = dist * 60 * 1.1515;
    
    return dist;
}

double parkInfo::distanceBetweenLatLong(tuple<double,double> this_lat_long, tuple<double,double> other_lat_long) {
    double this_lat_radians = (get<0>(this_lat_long) * M_PI) / 180;
    double this_long_radians = (get<1>(this_lat_long) * M_PI) / 180;
    double other_lat_radians = (get<0>(other_lat_long) * M_PI) / 180;
    double other_long_radians = (get<1>(other_lat_long) * M_PI) / 180;
    double delta_lat = this_lat_radians - other_lat_radians;
    double delta_long = this_long_radians - other_long_radians;
    double dist = sin(this_lat_radians) * sin(other_lat_radians) + cos(this_lat_radians) * cos(other_lat_radians) * cos(delta_long);
    dist = acos(dist);
    dist = (dist*180) / M_PI;
    dist = dist * 60 * 1.1515;
    
    return dist;
}

vector<parkInfo> parkInfo::shortestPathBetweenNParks(tuple<double,double> starting_location, int n_parks) {
    
}
