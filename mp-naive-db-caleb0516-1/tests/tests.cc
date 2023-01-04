// clang-format off
/////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////
//  Written By : Student Name                    Environment : ubuntu:bionic               //
//  Date ......: 2022/10/13                      Compiler ...: clang-14                  //
/////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////
// clang-format on
/////////////////////////////////////////////////////////////////////////////////////////////
//                             Framework Set-up //
/////////////////////////////////////////////////////////////////////////////////////////////
#ifndef CATCH_CONFIG_MAIN
#  define CATCH_CONFIG_MAIN
#endif
#include <catch/catch.hpp>

/////////////////////////////////////////////////////////////////////////////////////////////
//                                 Includes //
/////////////////////////////////////////////////////////////////////////////////////////////
#include <stdexcept>

#include "db.hpp"
#include "db_table.hpp"

/////////////////////////////////////////////////////////////////////////////////////////////
//                             Helpers/Constants //
/////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////
//                                Test Cases //
/////////////////////////////////////////////////////////////////////////////////////////////

TEST_CASE("True == True", "") { REQUIRE(true == true); }

/////////////////////////////////////////////////////////////////////////////////////////////

TEST_CASE("Add columns", "") {
  std::vector<std::pair<std::string, DataType>> col_descs;
  table.AddColumn(std::pair<std::string, DataType>("id-0", DataType::kDouble));
  table.AddColumn(std::pair<std::string, DataType>("id-1", DataType::kDouble));
  table.AddColumn(std::pair<std::string, DataType>("id-2", DataType::kDouble));
  // table.AddColumn(std::pair<std::string, DataType>("id-3",
  // DataType::kDouble));
  col_descs = table.GetColDescs();
  col_descs = table.GetColDescs();
  cout << "before remove\n"
       << "current size " << col_descs.size() << endl;
  for (unsigned long i = 0; i < col_descs.size(); i++) {
    std::cout << col_descs.at(i).first << std::endl;
  }
  table.DeleteColumnByIdx(2);
  col_descs = table.GetColDescs();
  std::cout << "current size " << col_descs.size() << std::endl;
  cout << "after remove\n";
  for (unsigned long i = 0; i < col_descs.size(); i++) {
    std::cout << col_descs.at(i).first << std::endl;
    // std::cout << col_descs.size() << std::endl;
  }
}

TEST_CASE("if there is 1 row and 1 colm delte all") {
  // std::pair<std::string, DataType> col1 =
  //     std::pair<std::string, DataType>("id", DataType::kDouble);
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
}

TEST_CASE("rest of removing column counting 0 when row exists") {
  DbTable table;
  std::vector<std::pair<std::string, DataType>> col_descs;
  std::map<unsigned int, void**> rows;
  table.AddColumn(std::pair<std::string, DataType>("Name", DataType::kString));
  table.AddColumn(std::pair<std::string, DataType>("id", DataType::kDouble));
  table.AddRow(std::initializer_list<std::string>{"Caleb", "5"});
  table.AddRow(std::initializer_list<std::string>{"Emily", "4"});
  table.AddRow(std::initializer_list<std::string>{"Isaiah", "3"});
  table.AddRow(std::initializer_list<std::string>{"Genuine", "2"});
  col_descs = table.GetColDescs();
  rows = table.GetRows();
  cout << "row size = " << rows.size() << " col size = " << col_descs.size()
       << endl;
  table.DeleteColumnByIdx(0);
  col_descs = table.GetColDescs();
  rows = table.GetRows();
  cout << "row size = " << rows.size() << " col size = " << col_descs.size()
       << endl;
  DisplayColumns(col_descs);
  DisplayRows(col_descs, rows);
}