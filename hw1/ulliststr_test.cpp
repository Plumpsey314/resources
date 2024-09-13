/* Write your test code for the ULListStr in this file */

#include <iostream>
#include "ulliststr.h"
using namespace std;

bool failCheck(std::string expected, std::string actual){
  if(expected != actual){
    cout << "An error has occured" << expected << " " << actual << endl;
    return true;
  }
  cout << "Test Passed" << endl;
  return false;
}

int main(int argc, char* argv[])
{
  // free tests from bytes:
  ULListStr* dat = new ULListStr();
  dat->push_back("7");
  dat->push_front("8");
  dat->push_back("9");
  if(failCheck(dat->get(0) + " " + dat->get(1) + " " + dat->get(2), "8 7 9")) return 1;
  if(failCheck(to_string(dat->size()), "3")) return 1;
  delete dat;

  // test empty
  // is empty
  // set/get exceptions
  // No pop back/front

  // push front
  // pop back
  // (empty again)
  // push front
  // pop front
  // (empty again)
  // push back
  // pop back
  // (empty again)
  // push back
  // pop front

  // push back then push front 
  // test new item creation

  // push front then push back 
  // test new item creation
  // (pushing/poping/geting/seting)

  // push back then push back 
  // (pushing/poping/geting/seting)

  // push front then push front 
  // (pushing/poping/geting/seting)

  // making sure delete works well (hope you did your job, Aaron)

  return 0;
}
