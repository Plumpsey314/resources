/* Write your test code for the ULListStr in this file */

#include <iostream>
#include "ulliststr.h"
using namespace std;

std::string show_dat(ULListStr* dat){
  std::string rv = "";
  for(size_t i = 0; i < dat->size(); i++){
    if(i) rv += " ";
    rv += dat->get(i);
  } 
  return rv;
}

bool matchCheck(std::string expected, ULListStr* dat){
  std::string actual = show_dat(dat);
  if(expected != actual){
    cout << "A match error has occured" << expected << " " << actual << endl;
    return true;
  }
  cout << "Match Test Passed" << endl;
  return false;
}

bool sizeCheck(size_t expected,ULListStr* dat){
  // checks size of data and makes sure it updates when adding/removing elements.
  size_t actual = dat->size();
  if(expected==0){
    if(!dat->empty()){
      cout << "expected empty but wasn't" << endl;
      return true;
    }
    // This code should do nothing and not produce an error:
    for(int _ = 0; _ < 9; _++){
      dat->pop_back();
      dat->pop_front();
      dat->pop_front();
    }
  }else if(actual != expected){
    cout << "size is not what was expected. Expected " << expected << " but actually " << actual << endl;
    return true;
  }else if(dat->empty()){
    cout << "dat should not be empty." << endl;
    return true;
  }

  // testing if changing the ULL changes size
  if(expected == 1){
    std::string front = dat->front();
    dat->pop_front();
    if(dat->size() != 0 || !dat->empty()){
      cout << "expected size to decrese when removing an element" << endl;
      return true;
    }
    dat->push_back(front);
      if(dat->size() != 1 || dat->empty()){
      cout << "expected size to go back to one when an element" << endl;
      return true;
    }
  } else if(expected > 1){
    std::string back = dat->back();
    bool failed = false;
    dat->pop_back();
    if(dat->size() != expected-1){failed = true;}
    dat->push_front(back);
    if(dat->size() != expected){failed = true;}
    dat->push_back(back);
    if(dat->size() != expected+1){failed = true;}
    dat->pop_front();
    if(dat->size() != expected){failed = true;}
    if(failed){
      cout << "failed to adjust size when adjusting dat" << endl;
      return true;
    }
  }

  cout << "Size Test Passed" << endl;
  return false;
}

bool setCheck(std:: string val, size_t loc, ULListStr* dat){
  // also checks get
  std::string curVal = dat->get(loc);
  if(loc <= dat->size()){
    try{
      dat->get(loc);
      cout << "expectied setting to return an error." << endl;
      return true;
    }catch(std::invalid_argument e){
      //correctly received an error
    }
  }else{
    dat->set(loc, val);
    if(dat->get(loc) != val){
      cout << "expected setting to work. Was really set to " << dat->get(loc) << " expected " << val << endl;
      return true;
    }
    dat->set(loc, curVal);
    if(dat->get(loc) != curVal){
      cout << "expected setting to work. Was really set to " << dat->get(loc) << " expected " << curVal << endl;
      return true;
    }
  }
  return false;
}


int main(int argc, char* argv[])
{
  // free test from bytes:
  ULListStr* dat = new ULListStr();


  dat->push_back("7");
  dat->push_front("8");
  dat->push_back("9");
  if(matchCheck("8 7 9", dat)) return 1;
  if(sizeCheck(3, dat)) return 1;
  dat->pop_back();
  if(matchCheck("8 7", dat)) return 1;
  if(sizeCheck(2, dat)) return 1;
  dat->pop_back();
  if(matchCheck("8", dat)) return 1;
  if(sizeCheck(1, dat)) return 1;
  dat->pop_front();

  // test empty
  // is empty
  // No pop back/front
  // set/get exceptions
  if(matchCheck("", dat)) return 1;
  if(sizeCheck(0, dat)) return 1;
  if(setCheck("Nathan", 0, dat)) return 1;
  delete dat;

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
