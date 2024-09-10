/*
CSCI 104: Homework 1 Problem 1

Use this file to test your split.cpp file.

Create linked lists and split them with your split() function.

You can compile this file like this:
g++ -g -Wall split.cpp split_test.cpp -o split_test
*/

#include <iostream>
#include "split.h"
using namespace std;

bool node_equals(Node* expected, Node* actual){
  // covers the base case if both are null pointers or the same memory adress
  if(expected == actual){
    return true;
  }
  if(expected && actual){
    if(expected->value == actual->value){
      return node_equals(expected->next, actual->next);
    }
  }
  // if this is the case, the values don't match or, expected or actual is NULL but not both
  return false;
}

void my_del(Node* n){
  // deletes a node n
  if(n){
    my_del(n->next);
    delete n;
  }
}

Node* from_arr(int* arr, int len){
  // goes from array to linked list
  if(len == 0){
    return NULL;
  }
  // arr[0] is first the tail of arr is after
  return new Node(arr[0], from_arr(arr+1, len-1));
}

void reset(Node*& odds, Node*& odds_exp, Node*&evens, Node*&evens_exp, Node*& in){
  my_del(odds);my_del(odds_exp);my_del(evens);my_del(evens_exp);my_del(in);
  odds = NULL; odds_exp = NULL; evens = NULL; evens_exp = NULL; in = NULL;
}

void print(Node* n){
  if(n){
    cout << n->value << " , ";
    print(n-> next);
  }else{
    cout << endl;
  }
}

bool fail_check(Node*& odds, Node*& odds_exp, Node*&evens, Node*&evens_exp, Node*& in){
  // calls split, then
  // checks if odds=odds_exp and evens=evens_exp
  // if not, the test failed, and true is returned
  // if everything is good, false is returned.

  split(in, odds, evens);
  if(!(node_equals(odds_exp, odds) && node_equals(evens_exp, evens) && in==NULL)){
    cout << "test failed" << endl;
    
    cout << "Odds:" << endl;
    print(odds);
    cout << "Evens:" << endl;
    print(evens);

    reset(odds, odds_exp, evens, evens_exp, in);
    return true;
  }
  reset(odds, odds_exp, evens, evens_exp, in);
  cout << "test passed" << endl;
  return false;
}

int main(int argc, char* argv[])
{
  Node* odds = NULL;
  Node* odds_exp = NULL;
  Node* evens = NULL;
  Node* evens_exp = NULL;
  Node* in = NULL;

  // Testing split_test
  
  {
  // when in is an empty list (NULL), even and odds should be NULL
  if(fail_check(odds, odds_exp, evens, evens_exp, in)) return 1;
  }

  {
  // when in is a list of length one, evens should be updated and odds should not.
  int arr[1] = {1};
  in = from_arr(arr, 1);
  odds_exp = from_arr(arr, 1);

  if(fail_check(odds, odds_exp, evens, evens_exp, in)) return 1;
  }

  {
  // testing length 2
  int arr[2] = {1,36};
  int arr_od[1] = {1};
  int arr_ev[1] = {36};
  in = from_arr(arr, 2);
  odds_exp = from_arr(arr_od, 1);
  evens_exp = from_arr(arr_ev, 1);

  if(fail_check(odds, odds_exp, evens, evens_exp, in)) return 1;
  }
  
  {
  // testing length 5
  int arr[5] = {-2,0,2,8,79};
  int arr_od[1] = {79};
  int arr_ev[4] = {-2,0,2,8};
  in = from_arr(arr, 5);
  odds_exp = from_arr(arr_od, 1);
  evens_exp = from_arr(arr_ev, 4);

  if(fail_check(odds, odds_exp, evens, evens_exp, in)) return 1;
  }

  {
  // testing length 14
  int arr[14] = {0,40,28,35,-65536, 100, 696969, 420, 9, -10, 11, 12, 7, 7};
  int arr_od[6] = {35,696969,9,11,7,7};
  int arr_ev[8] = {0, 40,28,-65536, 100, 420, -10, 12};
  in = from_arr(arr, 14);
  odds_exp = from_arr(arr_od, 6);
  evens_exp = from_arr(arr_ev, 8);

  if(fail_check(odds, odds_exp, evens, evens_exp, in)) return 1;
  }

  return 0;
}
