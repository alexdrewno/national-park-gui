//
//  ParkInfoTest.cpp
//  nationalParkGui
//
//  Created by Alex Drewno on 5/2/18.
//

#include "ParserTest.hpp"
#include "catch.hpp"
#include "../src/parkInfoParser.h"
#include "../src/parkInfo.hpp"

TEST_CASE("TEST_PARK_INFO") {
    vector<parkInfo> park_info_in_state = parkInfoParser::getJsonFromString(parkInfoParser::getJsonString("IL"));
    
    REQUIRE(park_info_in_state.size() != 0);
    REQUIRE(park_info_in_state[0].getName() != "");
    
    REQUIRE(park_info_in_state[0].getName() == "Trail of Tears");
    
    REQUIRE(parkInfo::closestParkToLocation(make_tuple(-70,30), park_info_in_state).getName() == "Trail of Tears");
}
