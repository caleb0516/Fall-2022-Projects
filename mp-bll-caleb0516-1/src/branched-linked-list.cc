#include "branched-linked-list.hpp"

/*
  To do
  constructor
  assignment operator
  isBLLacyclic
*/
BLL::BLL(const BLL& to_copy) {
  // DEFINITELY WRONG

  head_ = new Node(to_copy.head_->data_);
  if (to_copy.head_->next_bll_ != nullptr) {
    head_->next_bll_->operator=(*(to_copy.head_->next_bll_));
    BLL(*(to_copy.head_->next_bll_));
  }
  Node* to_copy_traverse = to_copy.head_->next_node_;
  Node* this_traverse = head_;
  while (to_copy_traverse != nullptr) {
    Node* new_node = new Node(to_copy_traverse->data_);
    this_traverse->next_node_ = new_node;
    if (to_copy_traverse->next_bll_ != nullptr) {
      this_traverse->next_bll_->operator=(*(to_copy_traverse->next_bll_));
    }
    to_copy_traverse = to_copy_traverse->next_node_;
    this_traverse = this_traverse->next_node_;
  }
}
BLL::~BLL() {
  ;
  // format
}

BLL& BLL::operator=(const BLL& rhs) {
  if (this == &rhs) {
    return *this;
  }
  while (head_ != nullptr) {
    Node* traverse = head_->next_node_;
    // if(head_->next_bll_==nullptr)
    delete head_->next_bll_;
    // this will call destructor and just delete everything right?
    // or do we have to recursively call?
    // prob have to recursively call otherwise we can just do delete this.
    // maybe call operator = again so we delete head_ ->next_bill
    // but have parameter =nulptr?
    // or just set next_bill= to rhs_.head_next_bill
    // and end of function here
    delete head_;
    head_ = traverse;
  }
  head_ = new Node(rhs.head_->data_);
  if (rhs.head_->next_bll_ != nullptr) {
    head_->next_bll_->operator=(*(rhs.head_->next_bll_));
  }
  Node* rhs_traverse = rhs.head_->next_node_;
  Node* this_traverse = head_;
  while (rhs_traverse != nullptr) {
    Node* new_node = new Node(rhs_traverse->data_);
    this_traverse->next_node_ = new_node;
    if (rhs_traverse->next_bll_ != nullptr) {
      this_traverse->next_bll_->operator=(*(rhs_traverse->next_bll_));
    }
    rhs_traverse = rhs_traverse->next_node_;
    this_traverse = this_traverse->next_node_;
  }
  return *this;
}

Node* BLL::PushBack(char dat) {
  Node* traverse = head_;
  Node* new_node = new Node(dat);
  while (traverse->next_node_ != nullptr) {
    traverse = traverse->next_node_;
  }
  Node* before_new_node = traverse;
  before_new_node->next_node_ = new_node;
  new_node->next_node_ = nullptr;  // redundant
  new_node->next_bll_ = nullptr;   // redundant
  return new_node;
}

char BLL::GetAt(size_t idx) const {
  if (idx >= this->Size()) {
    throw std::runtime_error("GetAt() out of bounds");
  }
  Node* traverse = head_;
  for (size_t i = 0; i < idx; i++) {
    traverse = traverse->next_node_;
    // traverse until traverse points to
    // the node at idx
  }
  return traverse->data_;
}
void BLL::SetAt(size_t idx, char dat) {
  if (idx >= this->Size()) {
    throw std::runtime_error("SetAt() out of bounds");
  }
  Node* traverse = head_;
  for (size_t i = 0; i < idx; i++) {
    traverse = traverse->next_node_;
  }
  traverse->data_ = dat;
}
void BLL::Join(size_t idx, BLL* list) {
  if (idx >= this->Size()) {
    throw std::runtime_error("Join() out of bounds");
  }
  // if(iscyclic) throw runtime error
  Node* traverse = head_;
  for (size_t i = 0; i < idx; i++) {
    traverse = traverse->next_node_;
  }
  traverse->next_bll_ = list;
  /*
    I think this is saying we are given an index and a BLL address
    and we go to that index in the this bll and take that index's next_bll
    and make it point to the given BLL

    double check tho
  */
}
std::string BLL::ToString() const {
  std::string bll_string;
  Node* traverse = head_;
  while (traverse != nullptr) {
    bll_string.push_back(traverse->data_);
    if (traverse->next_bll_ != nullptr) {
      bll_string.append(traverse->next_bll_->ToString());
    }
    traverse = traverse->next_node_;
  }
  return bll_string;
  /*
    ALRIGHT SO HERE IS THE LOGIC
    WE APPEND CHARACTERS UNTIL WE SEE THAT next_bll ISN'T NULLPTR
    IN THAT CASE WE CALL THE FUNCITON AGAIN RECUSIVELY AND SINCE THE FUNCTION
    RETURNS A STRING WE DO APPEND INSTEAD OF PUSHBACK
    DRAW OUT THE CODE OR TRACE THROUGH PROVIDED EXAMPLE PRETTY SIMPLE ACTUALLY
  */
}
size_t BLL::Size() const {
  // does this get the size of just 1 bll
  //  or the size of every bll combined
  // gonna assume it is one for now
  size_t size = 0;
  if (head_ == nullptr) {
    return size;
  }
  Node* traverse = head_;
  while (traverse != nullptr) {
    size++;
    traverse = traverse->next_node_;
  }
  return size;
  // if all bll size
  // then we just do if node.next_bll!=nullptr recursion
  // then we have to change pushback and everything
  // maybe not because last node called is hte first bll's last element
  // so maybe pushback stays the same
}
bool BLL::IsBLLAcyclic() const {
  if (head_ == nullptr) {
    return true;
  }
  // case of a node pointing back to an old node
  Node* start = head_;
  Node* start_plus = head_->next_node_;
  while (start != nullptr && start_plus != nullptr &&
         start_plus->next_node_ != nullptr) {
    if (start == start_plus) {
      return false;
    }
    start = start->next_node_;
    start_plus = start_plus->next_node_->next_node_;
  }
  // case of next_bll pointing to a previous bll
  // not exactly sure how to do this one

  // if it is cyclic return false
  // if it isn't cyclic return true
  return true;
}