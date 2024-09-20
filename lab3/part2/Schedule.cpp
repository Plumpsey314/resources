#include <iostream>
#include <map>
#include "Schedule.h"

using namespace std;

Schedule::Schedule(string name)
{
    mName = name;
}

bool Schedule::dropCourse(std::string name)
{
    // TO DO: if the course was not already in the map, return false
    // otherwise, remove it from the map and return true!
    std::map<std::string, Course*>::iterator course = courseMap.find(name);
    if(course == courseMap.end()) return false; // If it is not in courseMap
    courseMap.erase(course);
    return true;
}

bool Schedule::addCourse(Course* c)
{
    // finding course 
    std::string name = c->getCourseName();
    std::map<std::string, Course*>::iterator course = courseMap.find(name);
    if(course != courseMap.end()){ //If already in courseMap
        return false;
    }
    courseMap.insert(std::make_pair(name, c));
    return true;
}

void Schedule::printAllAssignments()
{
    // TO DO: print out the name of each course, followed by the set of assignments.
    // for each assignment, display its name, its type (essay vs hw vs exam), and whether or not it was completed.
    // formatting is up to you, but make sure it's easy to read!
    std::map<std::string, Course*>::iterator it;
    for(it = courseMap.begin(); it != courseMap.end(); ++it){
        Course* course = it->second;
        std::set<Assignment*> assignments = course->getAssignmentSet();
        cout << course->getCourseName() << ":\n";
        std::set<Assignment*>::iterator asIt;
        for(asIt = assignments.begin(); asIt != assignments.end(); ++asIt){
            Assignment* assignment = *asIt;
            cout << assignment->getName() << ":\n";
            cout << assignment->getType() << ". Status: " << (assignment->isComplete()?"Complete.":"Incomplete.");
            cout << "\n";
        }
    }
    cout << endl;
}

std::map<std::string, Course*> Schedule::getCourses()
{
    return courseMap;
}


