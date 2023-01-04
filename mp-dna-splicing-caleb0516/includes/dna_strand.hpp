#ifndef DNA_STRAND_HPP
#define DNA_STRAND_HPP

#include "node.hpp"

class DNAstrand {
public:
  DNAstrand() = default;
  DNAstrand(const DNAstrand& rhs) = delete;
  DNAstrand& operator=(const DNAstrand& rhs) = delete;
  ~DNAstrand();

  void SpliceIn(const char* pattern, DNAstrand& to_splice_in);
  /*
    SpliceIn is a function we call in an already existing sequence.
    In this sequence we check for pattern. Pattern is a cstring meaning
    it is an array of characters in the free store and the last character
    is a null character so we have to get rid of that when checkign pattern
    exists in the sequence.  After we check if sequence contains pattern,
    we replace pattern with to_splice_in. if there is multiple we only replace
    the one that is closest to the tail of the sequence.
    EXAMPLE:
    Sequence = AAGGTACTBTAAG pattern = 't' 'a' '\0' to_splice_in = GTT
    sequence.Splicein = AAGGTACTBGTTAG
  */
 
private:
  Node* head_ = nullptr;
  Node* tail_ = nullptr;
};
/*
  since we are only given the head and tail nodes for the linked list
  we have to iterate
*/

#endif