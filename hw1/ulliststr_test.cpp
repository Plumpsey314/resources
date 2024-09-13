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

bool getCheck(std::string expected, size_t loc, ULListStr* dat){
  if(loc >= dat->size()){
    try{
      dat->get(loc);
      cout << "expected getting to return an error." << endl;
      return true;
    }catch(std::invalid_argument& e){
      //correctly received an error
      return false;
    }
    return false;
  }
  std::string actual = dat->get(loc);
  if(expected != actual){
    cout << "Error with getting. Expected " << expected << " got " << actual << endl;
    return true;
  }
  return false;
}

bool frontBackCheck(std::string expected, bool isFront, ULListStr* dat){
  if(dat->empty()){
    try{
      if(isFront){
        dat->front();
      }else{
        dat->back();
      }
      cout << "Expected an error when dat was empty" << endl;
      return true;
    }catch(exception& e){
      // This is what is supposed to happen.
      return false;
    }
  }
  std::string actual;
  if(isFront){
    actual = dat->front();
  }else{
    actual = dat->back();
  }
  if(expected != actual){
    cout << "Error with first last. Expected " << expected << " got " << actual << endl;
    return true;
  }
  return false;
}

bool setCheck(std:: string val, size_t loc, ULListStr* dat){
  // also checks get
  std::string curVal = dat->get(loc);
  if(loc >= dat->size()){
    return getCheck("", loc, dat);
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


bool matchCheck(std::string expected, ULListStr* dat){
  std::string actual = show_dat(dat);
  if(expected != actual){
    cout << "A match error has occured. Expected " << expected << " got " << actual << endl;
    return true;
  }
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
  return false;
}

// This is a function that goes through all the check functions
// It has a lot of parameters because it cals all the helper functions.
/**
 * @param dat is the ULL
 * @param expVal is the expected string representation of the data
 * @param expSize is the expected size of the data
 * //The next parameters are for getting and setting
 * @param loc is the location of the item we are getting/setting
 * @param expLoc is the expected value in said location
 * @param expSet is what we are going to set expLoc to temporarily
 * // first and last check
 * @param expFront expected front value
 * @param expBack expected back value
 */
bool check(ULListStr* dat, std::string expVal, size_t expSize, size_t loc, std::string expLoc, std::string expSet, std::string expFront, std::string expBack){
  if(sizeCheck(expSize, dat)) return true;
  if(matchCheck(expVal, dat)) return true;
  if(expSize > loc){ // This if statement is because I can't (without googling) figure out try/catch
    if(getCheck(expLoc, loc, dat)) return true;
    if(setCheck(expSet, loc, dat)) return true; // set check does unset the value
    if(frontBackCheck(expFront, true, dat)) return true;
    if(frontBackCheck(expBack, false, dat)) return true;
  }
  cout << "Check passed" << endl;
  return false;
}

int main(int argc, char* argv[])
{
  // buffed test from bytes:
  ULListStr* dat = new ULListStr();
  dat->push_back("7");
  dat->push_front("8");
  dat->push_back("9");
  if(check(dat, "8 7 9", 3, 1, "7", "The Bee Movie:", "8", "9")) return 1;
  dat->pop_back();
  if(check(dat, "8 7", 2, 1, "7", "According to all known laws of aviation", "8", "7")) return 1;
  dat->pop_back();
  if(check(dat, "8", 1, 1, "This string doesn't matter", "there is no way a bee should be able to fly.", "8", "8")) return 1;
  dat->pop_front();
  
  // test empty
  // is empty
  // No pop back/front
  // set/get exceptions
  if(check(dat, "", 0, 0, "Doesn't matter:", "Its wings are too small to get its fat little body off the ground.", "The bee, of course, flies anyway", "because bees don't care what humans think is impossible.")) return 1;

  // push front
  dat->push_front("Yellow");
  if(check(dat, "Yellow", 1, 0, "Yellow", "Black", "Yellow", "Yellow")) return 1;
  // pop back
  dat->pop_back();
  // (empty again)
  if(check(dat, "", 0, 0, "Doesn't matter:", "", "", "")) return 1;

  // only using size check for the next ones:
  // push front
  dat->push_front("Black");
  if(sizeCheck(1, dat)) return 1;
  // pop front
  // (empty again)
  dat->pop_front();
  if(sizeCheck(0, dat)) return 1;

  // push back
  dat->push_back("Yellow");
  if(sizeCheck(1, dat)) return 1;
  // pop back
  // (empty again)
  dat->pop_front();
  if(sizeCheck(0, dat)) return 1;

  // push back
  dat->push_front("Black");
  if(sizeCheck(1, dat)) return 1;
  // pop front
  // (empty again)
  dat->pop_front();
  if(sizeCheck(0, dat)) return 1;

  // push back then push back 
  dat->push_back("Yellow");
  dat->push_back("Black");
  if(check(dat, "Yellow Black", 2, 1, "Black", "Black", "Yellow", "Black")) return 1;
  dat->pop_front();dat->pop_back();
  if(sizeCheck(0, dat)) return 1;

  // push front then push back 
  // test new item creation
  dat->push_front("Yellow");
  dat->push_back("Black");
  if(check(dat, "Yellow Black", 2, 0, "Yellow", "Black", "Yellow", "Black")) return 1;
  dat->pop_back();dat->pop_back();
  if(sizeCheck(0, dat)) return 1;

  // push front then push front 
  dat->push_front("Yellow");
  dat->push_front("Black");
  if(check(dat, "Black Yellow", 2, 100, "Ooh, black and yellow!", "Let's shake it up a little.", "Black", "Yellow")) return 1;
  dat->pop_front();dat->pop_front();
  if(sizeCheck(0, dat)) return 1;

  // push back then push front 
  // test new item creation
  dat->push_back("B");
  dat->push_back("B");
  if(check(dat, "B B", 2, 1, "B", "C", "B", "B")) return 1;
  dat->pop_back();dat->pop_front();
  if(sizeCheck(0, dat)) return 1;

  //free style testing (making the list large)
  dat->push_back("B");
  if(check(dat, "B", 1, 0, "B", "A perfect report card, all B's.", "B", "B")) return 1;
  dat->push_front("Barry");
  if(check(dat, "Barry B", 2, 1, "B", "Benson", "Barry", "B")) return 1;
  dat->push_back("B");
  if(check(dat, "Barry B B", 3, 0, "Barry", "", "Barry", "B")) return 1;
  dat->set(2, "Benson");
  if(check(dat, "Barry B Benson", 3, 1, "B", "bumblebee", "Barry", "Benson")) return 1;
  dat->pop_front();
  dat->pop_front();
  if(check(dat, "Benson", 1, 1, "", "", "Benson", "Benson")) return 1;
  dat->push_front("Barry");
  dat->push_back("intends");
  dat->push_back("to");
  dat->push_back("sue");
  dat->push_back("the");
  dat->push_back("human");
  dat->push_back("race");
  dat->push_front("fly");
  dat->push_back("for");
  dat->push_back("stealing");
  dat->push_front("tri-county");
  dat->set(1, "bee");
  dat->push_back("our");
  dat->push_back("honey");
  dat->push_back("packaging");
  dat->push_back("it");
  dat->push_back("and");
  dat->push_back("profiting");
  dat->push_back("from");
  dat->push_back("it");
  dat->push_back("illegally");
  dat->push_front("A");
  if(check(dat, "A tri-county bee Barry Benson intends to sue the human race for stealing our honey packaging it and profiting from it illegally", 22, 10, "race", "population", "A", "illegally")) return 1;

  for(int i = 0; i < 22; i++){
    dat->pop_front();
    if(sizeCheck(22-i-1, dat))return 1;
  }

  // making sure delete works well (hope you did your job, Aaron)
  delete dat;

  cout << "All checks passed" << endl;
  return 0;
}
