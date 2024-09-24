#include <iostream>
#include <sstream>
#include <cctype>
#include <algorithm>
#include "util.h"

using namespace std;
std::string convToLower(std::string src)
{
    std::transform(src.begin(), src.end(), src.begin(), ::tolower);
    return src;
}

/** Complete the code to convert a string containing a rawWord
    to a set of words based on the criteria given in the assignment **/
std::set<std::string> parseStringToWords(string rawWords)
{
    // This will split words by any punctuation
    // an effective way of doing this is by going through each char
    // and adding it to the set iff it is an alphanumeric of length >= 2

    // making sure nothing starts/ends with spaces and everything is lowercase. 
    // can change rawWords like this because it is pass by value, so won't affect user
    rawWords = convToLower(trim(rawWords));

    std::set<std::string> rv = std::set<std::string>();
    size_t curLen = 0;
    std::string curStr = "";
    std::string legalChars = "0123456789abcdefghijklmnopqrstuvwxyz";

    for(size_t i = 0; i < rawWords.length(); i++){
        char c = rawWords[i];
        // "cat" is 4 characters long, so i goes up to 3.
        if(c=='\0' && curLen >= 2){
            rv.insert(curStr);
        }
        if(legalChars.find(c) == std::string::npos){
            //was punctuation
            if(curLen >= 2){
                rv.insert(curStr);
            }
            curLen = 0;
            curStr = "";
        }else{
            curLen++;
            curStr += c;
        }
    }
    return rv;
}

/**************************************************
 * COMPLETED - You may use the following functions
 **************************************************/

// Used from http://stackoverflow.com/questions/216823/whats-the-best-way-to-trim-stdstring
// trim from start
std::string &ltrim(std::string &s) {
    s.erase(s.begin(), 
	    std::find_if(s.begin(), 
			 s.end(), 
			 std::not1(std::ptr_fun<int, int>(std::isspace))));
    return s;
}

// trim from end
std::string &rtrim(std::string &s) {
    s.erase(
	    std::find_if(s.rbegin(), 
			 s.rend(), 
			 std::not1(std::ptr_fun<int, int>(std::isspace))).base(), 
	    s.end());
    return s;
}

// trim from both ends
std::string &trim(std::string &s) {
    return ltrim(rtrim(s));
}
