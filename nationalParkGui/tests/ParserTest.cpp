//
//  ParserTest.cpp
//  nationalParkGui
//
//  Created by Alex Drewno on 5/2/18.
//

#include "catch.hpp"
#include "../src/parkInfoParser.h"
#include "../src/parkInfo.hpp"


TEST_CASE("TEST_PARSER") {
    vector<parkInfo> park_info_in_state = parkInfoParser::getJsonFromString(parkInfoParser::getJsonString("IL"));

    REQUIRE(park_info_in_state.size() != 0);
    REQUIRE(park_info_in_state[0].getName() != "");
    
    
    park_info_in_state = parkInfoParser::getJsonFromString(parkInfoParser::getJsonString("AR"));
    
    REQUIRE(park_info_in_state.size() != 0);
    REQUIRE(park_info_in_state[0].getName() != "");
    
    park_info_in_state = parkInfoParser::getJsonFromString(parkInfoParser::getJsonString("BANANAS"));
    
    REQUIRE(park_info_in_state.size() == 0);
    REQUIRE(park_info_in_state[0].getName() == "");
}
