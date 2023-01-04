#include <iostream>
#include <map>
using namespace std;

#include "db.hpp"
#include "db_table.hpp"

//#include "db_table.cc"
//#include "db.cc"

void DisplayColumns(const vector<pair<std::string, DataType>>& col_descs) {
  for (unsigned long i = 0; i < col_descs.size(); i++) {
    std::cout << col_descs.at(i).first << std::endl;
  }
}
void DisplayRows(const vector<pair<std::string, DataType>>& col_descs,
                 std::map<unsigned int, void**> rows) {
  for (unsigned long row = 0; row < rows.size(); row++) {
    for (unsigned long row_ele = 0; row_ele < col_descs.size(); row_ele++) {
      if (col_descs.at(row_ele).second == DataType::kInt)
        cout << *(static_cast<int*>(rows.at(row)[row_ele])) << " ";

      if (col_descs.at(row_ele).second == DataType::kDouble)
        cout << *(static_cast<double*>(rows.at(row)[row_ele])) << " ";

      if (col_descs.at(row_ele).second == DataType::kString)
        cout << *(static_cast<string*>(rows.at(row)[row_ele])) << " ";
    }
    cout << endl;
  }
}
void DisplaySizes(const vector<pair<std::string, DataType>>& col_descs,
                  const std::map<unsigned int, void**>& rows) {
  cout << "row size = " << rows.size() << " col size = " << col_descs.size()
       << endl;
}

int main() {
  DbTable table;
  std::vector<std::pair<std::string, DataType>> col_descs;
  std::map<unsigned int, void**> rows;
  table.AddColumn(std::pair<std::string, DataType>("name", DataType::kInt));
  table.AddColumn(std::pair<std::string, DataType>("id", DataType::kInt));
  table.AddColumn(std::pair<std::string, DataType>("Gpa", DataType::kInt));
  table.AddColumn(std::pair<std::string, DataType>("age", DataType::kInt));
  table.AddRow(std::initializer_list<std::string>{"23", "501", "3", "21"});
  table.AddRow(std::initializer_list<std::string>{"32", "232", "3", "20"});
  table.AddRow(std::initializer_list<std::string>{"4", "142", "3", "23"});
  table.AddRow(std::initializer_list<std::string>{"42", "527", "4", "23"});
  col_descs = table.GetColDescs();
  rows = table.GetRows();
  /*cout << "before delete rows\n";
  DisplayRows(col_descs, rows);
  //  table.DeleteRowById(2);
  col_descs = table.GetColDescs();
  rows = table.GetRows();
  cout << "after delete rows\n";
  // DisplayRows(col_descs, rows);*/

  cout << table;
}

/* DbTable table;
  std::vector<std::pair<std::string, DataType>> col_descs;
  std::map<unsigned int, void**> rows;
  table.AddColumn(std::pair<std::string, DataType>("id-0", DataType::kDouble));
  table.AddRow(std::initializer_list<std::string>{"12"});
  col_descs = table.GetColDescs();
  rows = table.GetRows();
  cout << "row size = " << rows.size() << " col size = " << col_descs.size()
       << endl;
  table.DeleteColumnByIdx(0);
  col_descs = table.GetColDescs();
  rows = table.GetRows();
  cout << "row size = " << rows.size() << " col size = " << col_descs.size()
       << endl;
  DisplayRows(col_descs, rows);
  cout << "if nothing prints then empty";*/