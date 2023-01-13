#include <cstddef>
#include <stdexcept>
//#include <iostream>
#include "ulliststr.h"

//using namespace std;
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

// WRITE YOUR CODE HERE
void ULListStr::push_back(const std::string& val) 
{
  size_++;
  //cout<<"size: "<<size_<<endl;
  if(tail_!=NULL && tail_->last!=ARRSIZE)
  {
    tail_->val[tail_->last] = val;
    tail_->last++;
  } else 
  {
    Item* temp = new Item();
    temp->last = 1;
    temp->first = 0;
    temp->val[0] = val;
    temp->prev = tail_;
    if(tail_!=NULL) tail_->next = temp;
    tail_= temp;
    //std::cout<<tail_->last<<std::endl;
    if(head_==NULL) 
    {
      head_ = temp;
      //cout<<"headwasnull"<<endl;
    }
    //std::cout<<back()<<"should match: "<<temp->val[0]<<std::endl;
    
  }
}

void ULListStr::pop_back() 
{
  if(tail_ != NULL)
  {
    size_--;
    if(tail_->last == tail_->first + 1) 
    {
      Item* temp = tail_->prev;
      delete tail_;
      tail_ = temp;
      if(tail_ == NULL) head_ = NULL;
    } else 
    {
      tail_->last--;
    }
  }
}

void ULListStr::pop_front() 
{
  if(head_ != NULL)
  {
    size_--;
    if(head_->last == head_->first + 1) 
    {
      Item* temp = head_->next;
      delete head_;
      head_ = temp;
      if(head_ == NULL) tail_ = NULL;
    } else 
    {
      head_->first++;
    }
  }
}

void ULListStr::push_front(const std::string& val)
{
  size_++;
  if(head_!=NULL && head_->first!=0)
  {
    head_->first--;
    head_->val[head_->first] = val;
  } else 
  {
    Item* temp = new Item();
    temp->last = ARRSIZE;
    temp->first = ARRSIZE-1;
    temp->val[ARRSIZE-1] = val;
    temp->next = head_;
    if(head_ != NULL) head_->prev = temp;
    head_= temp;
    if(tail_==NULL) 
    {
      tail_ = temp;
    }
  }
}

std::string const & ULListStr::back() const 
{
  if(tail_!=NULL) 
  {
    return (tail_->val[tail_->last-1]);
  }
  return NULL;
}

std::string const & ULListStr::front() const 
{
  if(head_!=NULL) 
  {
    return (head_->val[head_->first]);
  }
  return NULL;
}
std::string* ULListStr::getValAtLoc(size_t loc) const 
{
  //std::cout<<"loc: "<<loc<<", size_: "<<size_<<std::endl;
  if(size_ < loc || loc < 0) return NULL;
  if(size_ == loc) return &tail_->val[tail_->last-1];
  //if(loc<0) return NULL;

  Item* dummy = head_;
  /*
  size_t currSize = dummy->last - dummy->first;       
    if(currSize > loc) 
    {
      return &dummy->val[dummy->first + loc];      
    } else 
    {
      loc -= currSize;      
    }
  while(dummy!=NULL) 
  {

  }
  */
  int i = 0;
  while(dummy!=NULL) 
  {
    //cout<<"i: "<<i<<endl;
    size_t currSize = dummy->last - dummy->first;  
    //std::cout<<"Curr: "<<currSize<<std::endl;     
    if(currSize > loc) 
    {
      return &dummy->val[dummy->first + loc];      
    } else 
    {
      loc -= currSize;      
    }
    dummy = dummy->next;
    
  }
  //std::cout<<"got val. loc: "<<loc<<", size_: "<<size_<<std::endl;
  
  //cout<<"loc:"<<loc<<endl;
  //cout<<"size:"<<size_<<endl;

  
  
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
