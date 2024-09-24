#ifndef UTIL_H
#define UTIL_H

#include <string>
#include <iostream>
#include <set>


/** Complete the setIntersection and setUnion functions below
 *  in this header file (since they are templates).
 *  Both functions should run in time O(n*log(n)) and not O(n^2)
 */
template <typename T>
std::set<T> setIntersection(std::set<T>& s1, std::set<T>& s2)
{
    //n_1= size s1 n_2=size s2
    // using the copy constructor which is O(n_1)
    // We can use erase() which is log(n) on s2, making O(n_1+n_2*log(n_1+n_2))
    // comparing the sizes to improve preformance. Best to copy down the big one and then erace from the smaller one
    size_t size1 = s1.size();
    size_t size2 = s2.size();
    std::set<T>* bigger = size1>size2? &s1: &s2;
    std::set<T>* smaller = size1>size2? &s2: &s1;

    std::set<T> rv = *bigger; // calling copy constructor
    for(typename std::set<T>::iterator it = smaller->begin(); it != smaller->end(); ++it){
        rv.erase(*it);
    }
    return rv;
}
template <typename T>
std::set<T> setUnion(std::set<T>& s1, std::set<T>& s2)
{
    // Similar to intersection but relplace erace() with insert()
    size_t size1 = s1.size();
    size_t size2 = s2.size();
    std::set<T>* bigger = size1>size2? &s1: &s2;
    std::set<T>* smaller = size1>size2? &s2: &s1;

    std::set<T> rv = *bigger; // calling copy constructor
    for(typename std::set<T>::iterator it = smaller->begin(); it != smaller->end(); ++it){
        rv.insert(*it);
    }
    return rv;
}

/***********************************************/
/* Prototypes of functions defined in util.cpp */
/***********************************************/

std::string convToLower(std::string src);

std::set<std::string> parseStringToWords(std::string line);

// Used from http://stackoverflow.com/questions/216823/whats-the-best-way-to-trim-stdstring
// Removes any leading whitespace
std::string &ltrim(std::string &s) ;

// Removes any trailing whitespace
std::string &rtrim(std::string &s) ;

// Removes leading and trailing whitespace
std::string &trim(std::string &s) ;
#endif
