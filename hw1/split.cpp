/*
CSCI 104: Homework 1 Problem 1

Write a recursive function to split a sorted singly-linked
list into two sorted linked lists, where one has the even 
numbers and the other contains the odd numbers. Students 
will receive no credit for non-recursive solutions. 
**Do NOT add main() to this file**.

To test your program write a separate .cpp file and #include
split.h, but do not submit it.  When you submit, the function
below should be the only one in this file.
*/

#include "split.h"

/* Add a prototype for a helper function here if you need */

void split(Node*& in, Node*& odds, Node*& evens)
{
  //The procedure is the recursive calls eat the head of via (in=in->next), until in becomes NULL
  // odds and evens are being built by being set to in and then having their next node be inplemented into the recursion.
  // For example if an even number appears, evens will be set to in, and then split(in->next, odds, evens->next)
  // will be called. Eventually evens->next will be replaced by a new list starting at an even number until 
  // the list ends, in which case it will be set to nullptr.

  if(!in){
    // if the last thing is even, odds will point to an even thing unless if set to NULL.
    // and vice versa
    odds = nullptr; // don't know why I can't set these to NULL. Have to use nullptr instead.
    evens = nullptr;
    return;
  }
  if(in->value%2==0){
    evens = in;
    in = in->next;
    return split(in, odds, evens->next);
  }else{
    odds = in;
    in = in->next;
    return split(in, odds->next, evens);
  }
}

/* If you needed a helper function, write it here */
