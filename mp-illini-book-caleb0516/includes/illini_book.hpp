#ifndef ILLINI_BOOK_HPP
#define ILLINI_BOOK_HPP

#include <string>
#include <vector>
#include <map>
#include <list>
#include <fstream>
#include <queue>
#include <set>
#include <utility>
#include "utilities.hpp"
//uin = nodes
//relationships = edges
class IlliniBook {
public:
  IlliniBook(const std::string &people_fpath, const std::string &relations_fpath);
  IlliniBook(const IlliniBook &rhs) = delete;
  IlliniBook &operator=(const IlliniBook &rhs) = delete;
  ~IlliniBook() = default;
  bool AreRelated(int uin_1, int uin_2) const;
  bool AreRelated(int uin_1, int uin_2, const std::string &relationship) const;
  int GetRelated(int uin_1, int uin_2) const;
  int GetRelated(int uin_1, int uin_2, const std::string &relationship) const;
  std::vector<int> GetSteps(int uin, int n) const;
  void AddVertex(int uin);
  void AddEdge( int uin_1, int uin_2, const std::string &relation);
  size_t CountGroups() const;
  size_t CountGroups(const std::string &relationship) const;
  size_t CountGroups(const std::vector<std::string> &relationships) const;

private:
  std::map <int, std::list<std::pair<int, std::string>>> graph_;
  unsigned int no_vertices_ =0;
  unsigned int no_edges_ =0;
};

#endif

