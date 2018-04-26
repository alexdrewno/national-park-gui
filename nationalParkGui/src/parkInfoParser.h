//
//  parkInfoParser.h
//  nationalParkGui
//
//  Created by Alex Drewno on 4/25/18.
//

#ifndef parkInfoParser_h
#define parkInfoParser_h

#include <string>
#include "parkInfo.hpp"

using namespace std;

class parkInfoParser {
public:
    static string getJsonString(string for_state_code);
    static size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp);
    static vector<parkInfo> getJsonFromString(string json_string);
private:
    static vector<string> vectorFromString(string from_string);
    static tuple<double,double> tupleFromString(string from_string);
    
};

#endif /* parkInfoParser_h */
