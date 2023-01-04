#include <iostream>

#include "dna_strand.cc"
#include "dna_strand.hpp"
using namespace std;
int main() {
  DNAstrand sequence;
  sequence.PushBack('h');
  sequence.PushBack('h');
  sequence.PushBack('g');
  sequence.PushBack('a');
  sequence.PushBack('b');
  sequence.PushBack('a');
  sequence.PushBack('f');

  DNAstrand to_splice_in;
  to_splice_in.PushBack('k');
  to_splice_in.PushBack('r');
  to_splice_in.PushBack('r');
  to_splice_in.PushBack('p');
  to_splice_in.PushBack('p');
  // char* pattern = new char[3];
  // pattern[0] = 'g';
  // pattern[1] = 'a';
  // pattern[2] = 'b';
  // pattern[3] = '\0';
  char pattern[] = "gab";
  Node* test = sequence.GetHead();
  while (test != nullptr) {
    cout << test->data;
    test = test->next;
  }
  cout << endl;

  cout << sequence.GetHead() << endl;
  sequence.SpliceIn(pattern, to_splice_in);

  test = sequence.GetHead();
  while (test != nullptr) {
    cout << test->data;
    test = test->next;
  }
  cout << endl;

  cout << sequence.GetHead() << endl;
}