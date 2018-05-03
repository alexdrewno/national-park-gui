//
//  parkInfo.cpp
//  nationalParkGui
//
//  Created by Alex Drewno on 4/25/18.
//

#include "parkInfo.hpp"
#include <math.h>
#include <iostream>
#include <map>

using namespace std;

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

void parkInfo::setLatLong(tuple<double,double> lat_long_to_set) {
    this->latLong = lat_long_to_set;
}

//Gets the closest park to the cur park
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

//Gets the closest park to the location
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

//Gets the distance between two parks
double parkInfo::distanceBetweenParks(parkInfo park_one, parkInfo park_two) {
    return distanceBetweenLatLong(park_one.getLatLong(), park_two.getLatLong());
}

//Gets the distance between two lat-long
double parkInfo::distanceBetweenLatLong(tuple<double,double> this_lat_long, tuple<double,double> other_lat_long) {
    double radius_of_earth = 6371 * 10^3;
    double this_lat_radians = (get<0>(this_lat_long) * M_PI) / 180;
    double this_long_radians = (get<1>(this_lat_long) * M_PI) / 180;
    double other_lat_radians = (get<0>(other_lat_long) * M_PI) / 180;
    double other_long_radians = (get<1>(other_lat_long) * M_PI) / 180;
    double delta_lat = abs(this_lat_radians - other_lat_radians);
    double delta_long = abs(this_long_radians - other_long_radians);
    double a = sin(delta_lat/2) * sin(delta_lat/2) + cos(this_lat_radians) * cos(other_lat_radians) * sin(delta_long/2) * sin(delta_long/2);
    double dist = 2 * atan2(sqrt(a), sqrt(1-a));
    return dist * radius_of_earth;
}

//Sums up the path lengths between parks
double parkInfo::sumEdgeWeights(vector<tuple<parkInfo,parkInfo>> paths) {
    double total = 0;
    
    for (auto path : paths) {
        total += distanceBetweenParks(get<0>(path), get<1>(path));
    }
    
    return total;
}

//Recursive start to find the minimum path length involving k national parks
vector<tuple<parkInfo,parkInfo>> parkInfo::mainMinKCycle(vector<parkInfo> vertices, parkInfo start, parkInfo end, int k) {
    cout<<"calledstart"<<endl;
    vector<bool> visited;
    for (auto element : vertices) {
        visited.push_back(false);
    }
    
    return minKCycle(vertices,start,start,k,visited);
}

//Recursive method to find the minimum path length involving k national parks
vector<tuple<parkInfo,parkInfo>> parkInfo::minKCycle(vector<parkInfo> vertices, parkInfo start, parkInfo end, int k, vector<bool> visited) {
    if (k == 1) {
        vector<tuple<parkInfo,parkInfo>> singleton_park_path;
        singleton_park_path.push_back(make_tuple(start,end));
        return singleton_park_path;
    } else {
        double min = INT_MAX;
        vector<tuple<parkInfo,parkInfo>> min_v_cycle;
        parkInfo min_vertex;
        int min_vertex_index = -1;
        
        for (int i = 0; i < vertices.size(); i++) {
            if (!visited[i]) {
                vector<tuple<parkInfo,parkInfo>> u_cycle;
                u_cycle.push_back(make_tuple(end,vertices[i]));
                vector<tuple<parkInfo,parkInfo>> to_add = minKCycle(vertices, start, vertices[i], k-1, visited);
                u_cycle.insert(u_cycle.end(), to_add.begin(), to_add.end());
                if (sumEdgeWeights(u_cycle) < min) {
                    min = sumEdgeWeights(u_cycle);
                    min_v_cycle = u_cycle;
                    min_vertex = vertices[i];
                    min_vertex_index = i;
                }
            }
        }
        
        visited[min_vertex_index] = true;
        return min_v_cycle;
    }
}

//Gets the n number of closest parks to the location
vector<parkInfo> parkInfo::closestParksTo(tuple<double,double> location, vector<parkInfo> parks, int n) {
    map<double,parkInfo> distance_park_map;
    vector<parkInfo> closest_parks;
    
    for (auto park : parks) {
        distance_park_map[distanceBetweenLatLong(location, park.getLatLong())] = park;
    }
    
    map<double, parkInfo>::iterator it;
    
    for(it = distance_park_map.begin(); it != distance_park_map.end(); it++) {
        if (closest_parks.size() < n) {
            closest_parks.push_back(it->second);
        } else {
            break;
        }
    }
    
    return closest_parks;
}





