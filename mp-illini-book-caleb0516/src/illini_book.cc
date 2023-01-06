#include "illini_book.hpp"

IlliniBook::IlliniBook(const std::string& people_fpath,
                       const std::string& relations_fpath) {
  std::ifstream people{people_fpath};
  if (!people.is_open()) throw std::runtime_error("People file not open\n");
  int uin = 0;
  while (people.good()) {
    people >> uin;
    AddVertex(uin);
  }
  std::ifstream relations{relations_fpath};
  if (!relations.is_open())
    throw std::runtime_error("Relation file not open\n");
  int uin_1 = 0;
  int uin_2 = 0;
  std::string relation;
  std::string line;
  std::vector<std::string> vec;
  while (relations.good()) {
    relations >> line;
    vec = utilities::Split(line, ',');
    uin_1 = stoi(vec.at(0));
    uin_2 = stoi(vec.at(1));
    relation = vec.at(2);
    AddEdge(uin_1, uin_2, relation);
  }
}
void IlliniBook::AddVertex(int uin) {
  if (graph_.contains(uin)) {
    throw std::runtime_error("UIN Already Exists");
  }
  graph_.insert({uin, std::list<std::pair<int, std::string>>()});
  no_vertices_++;
}
void IlliniBook::AddEdge(int uin_1, int uin_2, const std::string& relation) {
  if (!graph_.contains(uin_1) || !graph_.contains(uin_2)) {
    throw std::runtime_error("UIN does not exist");
  }
  // if (AreRelated(uin_1, uin_2)) {
  //   throw std::runtime_error("Edge Already exists");
  // }
  graph_.at(uin_1).push_back(std::pair<int, std::string>(uin_2, relation));
  graph_.at(uin_2).push_back(std::pair<int, std::string>(uin_1, relation));
  no_edges_++;
}
bool IlliniBook::AreRelated(int uin_1, int uin_2) const {
  std::queue<int> q;
  std::set<int> visited;
  q.push(uin_1);
  visited.insert(uin_1);
  while (!q.empty()) {
    int current = q.front();
    q.pop();
    if (current == uin_2) return true;
    for (const std::pair<int, std::string>& neighbor : graph_.at(current)) {
      if (!visited.contains(neighbor.first)) {
        q.push(neighbor.first);
        visited.insert(neighbor.first);
      }
    }
  }
  return false;
}
bool IlliniBook::AreRelated(int uin_1,
                            int uin_2,
                            const std::string& relationship) const {
  std::queue<int> q;
  std::set<int> visited;
  q.push(uin_1);
  visited.insert(uin_1);
  while (!q.empty()) {
    int current = q.front();
    q.pop();
    if (current == uin_2) return true;
    for (const std::pair<int, std::string>& neighbor : graph_.at(current)) {
      if ((!visited.contains(neighbor.first)) && (neighbor.second == relationship)) {
        q.push(neighbor.first);
        visited.insert(neighbor.first);
      }
    }
  }
  return false;
}

int IlliniBook::GetRelated(int uin_1, int uin_2) const {
  if(!AreRelated(uin_1,uin_2) ){
    return -1;
  }
  std::queue<int> q;
  std::set<int> visited;
  std::map<int,int> size;
  q.push(uin_1);
  visited.insert(uin_1);
  size.insert({uin_1,0});
  while (!q.empty()) {
    int current = q.front();
    q.pop();
    if (current == uin_2) return size.at(current);
    for (const std::pair<int, std::string>& neighbor : graph_.at(current)) {
      if (!visited.contains(neighbor.first)) {
        q.push(neighbor.first);
        visited.insert(neighbor.first);
        size.insert({neighbor.first, size.at(current)+1 });
      }
    }
  }
  return -1;
}
int IlliniBook::GetRelated(int uin_1,
                           int uin_2,
                           const std::string& relationship) const {
     if(!AreRelated(uin_1,uin_2) ){
    return -1;
  }
  std::queue<int> q;
  std::set<int> visited;
  std::map<int,int> size;
  q.push(uin_1);
  visited.insert(uin_1);
  size.insert({uin_1,0});
  while (!q.empty()) {
    int current = q.front();
    q.pop();
    if (current == uin_2) return size.at(current);
    for (const std::pair<int, std::string>& neighbor : graph_.at(current)) {
      if ((!visited.contains(neighbor.first)) && (neighbor.second==relationship)) {
        q.push(neighbor.first);
        visited.insert(neighbor.first);
        size.insert({neighbor.first, size.at(current)+1});
      }
    }
  }
  return -1;
}
std::vector<int> IlliniBook::GetSteps(int uin, int n) const {
  std::vector<int> matches;
  std::queue<int> q;
  std::set<int> visited;
  std::map<int,int> size;
  q.push(uin);
  visited.insert(uin);
  size.insert({uin,0});
  while (!q.empty()) {
    int current = q.front();
    q.pop();
    for (const std::pair<int, std::string>& neighbor : graph_.at(current)) {
      if (!visited.contains(neighbor.first)) {
        q.push(neighbor.first);
        visited.insert(neighbor.first);
        size.insert({neighbor.first, size.at(current)+1});
      }
    }
  }
   for (const auto& i : size){
        if (i.second==n){
          matches.push_back(i.first);
        }
   }         
  return matches;
}
size_t IlliniBook::CountGroups() const {
  size_t groups=0;
  std::queue<int> q;
  std::set<int> visited;
  std::map<int,int> size;
  int uin=0;
  for (const auto& i : graph_){
      if(!visited.contains(i.first)){
          uin=i.first;
          q.push(uin);
          visited.insert(uin);
          while (!q.empty()) {
              int current = q.front();
              q.pop();
              for (const std::pair<int, std::string>& neighbor : graph_.at(current)) {
                  if (!visited.contains(neighbor.first)) {
                  q.push(neighbor.first);
                  visited.insert(neighbor.first);
                  }
              }
          }
        groups++;
      }
    }
  return groups;
}
size_t IlliniBook::CountGroups(const std::string& relationship) const {
  size_t groups=0;
  std::queue<int> q;
  std::set<int> visited;
  std::map<int,int> size;
  int uin=0;
  for (const auto& i : graph_){
      if(!visited.contains(i.first)){
          uin=i.first;
          q.push(uin);
          visited.insert(uin);
          while (!q.empty()) {
              int current = q.front();
              q.pop();
              for (const std::pair<int, std::string>& neighbor : graph_.at(current)) {
                  if ((!visited.contains(neighbor.first))&&(neighbor.second==relationship)) {
                  q.push(neighbor.first);
                  visited.insert(neighbor.first);
                  }
              }
          }
        groups++;
      }
    }
  return groups;
}
bool Contains(const std::string& relationship, const std::vector<std::string>& relationships){
    for(int i=0; i<int(relationships.size());i++){
      if(relationship == relationships.at(i))
      return true;
    }
    return false;
}
size_t IlliniBook::CountGroups(
    const std::vector<std::string>& relationships) const {
 size_t groups=0;
  std::queue<int> q;
  std::set<int> visited;
  std::map<int,int> size;
  int uin=0;
  for (const auto& i : graph_){
      if(!visited.contains(i.first)){
          uin=i.first;
          q.push(uin);
          visited.insert(uin);
          while (!q.empty()) {
              int current = q.front();
              q.pop();
              for (const std::pair<int, std::string>& neighbor : graph_.at(current)) {
                  if ((!visited.contains(neighbor.first))&&(Contains(neighbor.second,relationships))){
                  q.push(neighbor.first);
                  visited.insert(neighbor.first);
                  }
              }
          }
        groups++;
      }
    }
  return groups;
}
