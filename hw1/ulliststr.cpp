#include <cstddef>
#include <stdexcept>
#include "ulliststr.h"

ULListStr::ULListStr()
{
  head_ = NULL;
  tail_ = NULL;
  size_ = 0;
}

ULListStr::~ULListStr()
{
  clear();
}

bool ULListStr::empty() const
{
  return size_ == 0;
}

size_t ULListStr::size() const
{
  return size_;
}

void ULListStr::push_back(const std::string& val){
  // If the list starts as empty, Using Redekop's idea of inserting an Item with the string at the 
  // front for push back and at the back for push front.    
  if(!tail_){
    // list is empty
    tail_ = head_ = new Item(val, true);
  }else if(tail_->last == ARRSIZE){
    // If tail is full
    Item* toAdd = new Item(val, true);
    //connecting the items
    toAdd -> prev = tail_;
    tail_ -> next = toAdd;
    // resetting tail
    tail_ = toAdd;
  }else{
    // Ideally, we add val to an existing item
    tail_->val[tail_->last]=val;
    // change the last reference too
    tail_->last++;
  }
  size_++;
}

void ULListStr::push_front(const std::string& val){
  // Similar to push_back
  if(!tail_){
    tail_ = head_ = new Item(val, false);
  }else if(head_->first == 0){
    Item* toAdd = new Item(val, false);
    toAdd -> next = head_;
    head_ -> prev = toAdd;
    head_ = toAdd;
  }else{
    head_->val[head_->first-1]=val;
    head_->first--;
  }
  size_++;
}

void ULListStr::pop_back(){
  // we are working in the back, so we care about the tail pointer.
  
  // do nothing if the list is empty.
  if(!tail_) return;
  
  if(tail_->last-tail_->first == 1){
    // we need to delete tail. 
    Item* temp = tail_->prev;
    delete tail_;
    tail_ = temp;
    if(tail_){
      tail_->next = NULL;
    }else{
      // head_ becomes a garbage value if tail_ equals head_
      head_ = NULL;
    }
  }else{
    // no point in reseting val.
    tail_->last --;
  }
  size_ --;
}

void ULListStr::pop_front(){
  // Similar to pop_back  
  if(!head_) return;
  if(head_->last-head_->first == 1){
    Item* temp = head_->next;
    delete head_;
    head_ = temp;
    if(head_){
      head_->prev = NULL;
    }else{
      tail_ = NULL;
    }
  }else{
    head_->first++;
  }
  size_ --;
}

std::string const & ULListStr::back() const{ 
  if(empty()){
    throw std::invalid_argument("Can not call back or front on an empty ULL");
  }
  return tail_->val[tail_->last-1]; 
}

std::string const & ULListStr::front() const{ 
  if(empty()){
    throw std::invalid_argument("Can not call back or front on an empty ULL");
  }
  return head_->val[head_->first];
}

void ULListStr::set(size_t loc, const std::string& val)
{
  std::string* ptr = getValAtLoc(loc);
  if(ptr == NULL){
    throw std::invalid_argument("Bad location");
  }
  *ptr = val;
}

std::string& ULListStr::get(size_t loc)
{
  std::string* ptr = getValAtLoc(loc);
  if(ptr == NULL){
    throw std::invalid_argument("Bad location");
  }
  return *ptr;
}

std::string const & ULListStr::get(size_t loc) const
{
  std::string* ptr = getValAtLoc(loc);
  if(ptr == NULL){
    throw std::invalid_argument("Bad location");
  }
  return *ptr;
}

void ULListStr::clear()
{
  while(head_ != NULL){
    Item *temp = head_->next;
    delete head_;
    head_ = temp;
  }
  tail_ = NULL;
  size_ = 0;
}

std::string* ULListStr::getValAtLoc(size_t loc) const{
  // No way we can get a location value larger than the size of the array.
  if(size_ <= loc){return NULL;}
  Item* curItem = head_;
  // The number of strings in the current and all previous Items
  size_t numCovered = curItem->last-curItem->first;
  while(numCovered <= loc){
    // jumping through the items.
    curItem = curItem->next;
    numCovered += curItem->last-curItem->first;
  }
  // now finding the particular element that coorisponds to loc.
  // note if numCovered is a lot bigger than loc, we overshot by a lot, 
  // meaning loc is near the beginnig of the Item.

  // loc = numCovered-(numCovered-loc). since numCovered coorisponds to curItem->last
  // this is the formula:
  return &curItem->val[curItem->last-numCovered+loc];
}
