#include "dna_strand.hpp"

#include <cassert>
#include <stdexcept>

//  make it to c strings
//  we can get pattern size by reaching \0
//  try when first gets replace

int DNAstrand::SequenceStringSize(Node* head_) {
  Node* sequence_getter = head_;
  int sequence_size = 0;
  while (sequence_getter != nullptr) {
    sequence_size++;
    sequence_getter = sequence_getter->next;
  }
  return sequence_size;
}
char* DNAstrand::SequenceToCstring(Node* head_, int sequence_size) {
  Node* sequence_getter = head_;
  char* sequence = new char[sequence_size];
  for (int i = 0; i < sequence_size; i++) {
    sequence[i] = sequence_getter->data;
    sequence_getter = sequence_getter->next;
  }
  return sequence;
}

int DNAstrand::StartingPosition(const char* sequence,
                                int sequence_size,
                                const char* pattern,
                                int pattern_size) {
  int start_position = 0;
  int equal_counter = 0;
  int j = 0;
  int pattern_occurences = 0;
  for (int i = 0; i < sequence_size; i++) {
    if (sequence[i] == pattern[j]) {
      equal_counter++;
      j++;
    } else if (sequence[i] == pattern[0]) {
      equal_counter = 1;
      j = 1;
    } else {
      equal_counter = 0;
      j = 0;
    }
    if (equal_counter == pattern_size) {
      start_position = i - pattern_size + 1;
      j = 0;
      equal_counter = 0;
      pattern_occurences++;
    }
  }
  if (pattern_occurences == 0) {
    delete[] sequence;
    throw std::runtime_error("exception?");
  }
  return start_position;
}
void DNAstrand::SpliceIn(const char* pattern, DNAstrand& to_splice_in) {
  int sequence_size = SequenceStringSize(head_);
  char* sequence = SequenceToCstring(head_, sequence_size);
  int pattern_size = 0;
  while (pattern[pattern_size] != '\0') pattern_size++;
  if (pattern_size == 0 || to_splice_in.head_ == nullptr ||
      &to_splice_in == this)
    return;
  int start_position = 0;
  start_position =
      StartingPosition(sequence, sequence_size, pattern, pattern_size);
  int end_position = start_position + pattern_size;
  Node* start_replace = head_;
  for (int i = 0; i < start_position - 1; i++)
    start_replace = start_replace->next;
  Node* end_replace = head_;
  for (int i = 0; i < end_position; i++) end_replace = end_replace->next;
  Node* deleter = head_;
  for (int i = 0; i < start_position; i++) deleter = deleter->next;
  for (int i = start_position; i < end_position; i++) {
    Node* next = deleter->next;
    delete deleter;
    deleter = next;
  }
  if (start_position == 0)
    head_ = to_splice_in.head_;
  else
    start_replace->next = to_splice_in.head_;
  if (start_position + pattern_size == sequence_size) {
    tail_ = to_splice_in.tail_;
    tail_->next = nullptr;
  } else
    to_splice_in.tail_->next = end_replace;
  to_splice_in.head_ = nullptr;
  to_splice_in.tail_ = nullptr;
  start_replace = nullptr;
  end_replace = nullptr;
  deleter = nullptr;
  delete[] sequence;
  sequence = nullptr;
}

DNAstrand::~DNAstrand() {
  while (head_ != nullptr) {  // while not nullptr
    Node* next = head_->next;
    delete head_;
    head_ = next;
  }
  head_ = nullptr;
  tail_ = nullptr;
}
void DNAstrand::PushBack(char value) {
  if (head_ == nullptr) {
    head_ = tail_ = new Node(value);
  } else {
    Node* temp = new Node(value);
    tail_->next = temp;
    tail_ = temp;
  }
}