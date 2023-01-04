#include "db.hpp"
// std::map<std::string, DbTable*> tables_;  // maps table name -> table
void Database::CreateTable(const std::string& table_name) {
  // auto* db_table = new DbTable();
  tables_.insert({table_name, new DbTable()});
}
void Database::DropTable(const std::string& table_name) {
  if (!tables_.contains(table_name))
    throw std::invalid_argument("Table name does not exist");
  DbTable deleter = *tables_.at(table_name);
  //*tables_.at(table_name).
  for (unsigned int i = 0; i < deleter.GetUniqueID(); i++) {
    if (deleter.GetRows().contains(i)) {
      deleter.DeleteRowById(i);
    }
  }
  delete[] tables_.at(table_name);
  tables_.at(table_name) = nullptr;
  tables_.erase(table_name);
}
DbTable& Database::GetTable(const std::string& table_name) {
  return *tables_.at(table_name);
}

Database::Database(const Database& rhs) {
  for (const auto& [table_name, table] : rhs.tables_) {
    auto* db_table = new DbTable(*table);
    tables_.insert({table_name, db_table});
  }
}

Database& Database::operator=(const Database& rhs) {
  if (this == &rhs) {
    return *this;
  }
  std::vector<std::string> table_names;
  for (const auto& [table_name, table] : tables_) {
    table_names.push_back(table_name);
  }
  for (const auto& table_name : table_names) {
    DropTable(table_name);
  }
  return *this;
}

Database::~Database() {
  for (auto& [key, value] : tables_) {
    delete[] tables_.at(key);
  }
}
