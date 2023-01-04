#include "db_table.hpp"

#include <initializer_list>
#include <iostream>
#include <string>

const unsigned int kRowGrowthRate = 2;

void DbTable::AddColumn(const std::pair<std::string, DataType>& col_desc) {
  if (col_descs_.size() == row_col_capacity_) {
    row_col_capacity_ = row_col_capacity_ * kRowGrowthRate;
    // double capacity
    for (unsigned int i = 0; i < next_unique_id_; i++) {
      // go through each void** in rows_
      void** updated_row = new void*[row_col_capacity_];
      // create new void** with updated capacity
      // each row requires new address
      for (unsigned int j = 0; j < col_descs_.size(); j++) {
        // go through each pointer in the array void** points to
        updated_row[j] = static_cast<void*>(rows_.at(i)[j]);
        // this should make updated_row[j] point to whatever is at
        // rows_.at(i)[j] whether that is a int string or double.
      }
      delete[] rows_.at(i);  // gets rid of the old array of pointers
      rows_.at(i) = updated_row;
      updated_row = nullptr;  // gonna die cause in stack dont need
    }
  }
  for (unsigned int i = 0; i < next_unique_id_; i++) {
    if (col_desc.second == DataType::kInt)
      rows_.at(i)[col_descs_.size()] = static_cast<void*>(new int(0));
    else if (col_desc.second == DataType::kDouble)
      rows_.at(i)[col_descs_.size()] = static_cast<void*>(new double(0.0));
    else if (col_desc.second == DataType::kString)
      rows_.at(i)[col_descs_.size()] = static_cast<void*>(new std::string(""));
  }
  col_descs_.push_back(col_desc);
}

void DbTable::DeleteColumnByIdx(unsigned int col_idx) {
  if (col_idx >= col_descs_.size() || col_idx < 0) {
    throw std::out_of_range("invalid index size");
  }

  DataType data_type = col_descs_.at(col_idx).second;
  if (col_descs_.size() != 1) {
    col_descs_.erase(col_descs_.begin() + col_idx,
                     col_descs_.begin() + col_idx + 1);
  } else {
    // col_descs_.clear();
    // for (unsigned long i = 0; i < rows_.size(); i++) DeleteRowById(i);
    throw std::runtime_error("if there is a row there must be a column");
    // rows_.clear();
    return;
  }
  if (!rows_.empty()) {
    for (unsigned int i = 0; i < rows_.size(); i++) {
      void** temp = new void*[row_col_capacity_];
      for (unsigned int j = 0; j < col_idx; j++) {
        temp[j] = rows_.at(i)[j];
      }
      for (unsigned int j = col_idx; j < col_descs_.size(); j++) {
        temp[j] = rows_.at(i)[j + 1];
        // so temp[col_idx] == rows[j+1] skipping rows[j]
        // 0,1,2,3,4 col_idx = 2 //0,1,3,4
      }
      if (data_type == DataType::kInt)
        delete[] static_cast<int*>(rows_.at(i)[col_idx]);
      else if (data_type == DataType::kDouble)
        delete[] static_cast<double*>(rows_.at(i)[col_idx]);
      else if (data_type == DataType::kString)
        delete[] static_cast<std::string*>(rows_.at(i)[col_idx]);
      delete[] rows_.at(i);  // deletes the row void** is pointing to.
      rows_.at(i) = temp;    // gives
    }
  }
}

/*private:
  unsigned int next_unique_id_ = 0;
  unsigned int row_col_capacity_ = 2;
  std::map<unsigned int, void**> rows_;
  std::vector<std::pair<std::string, DataType>> col_descs_;*/

// col_data is just a vec of strings containing the values of the new
// row like a string, int double etc..
void DbTable::AddRow(const std::initializer_list<std::string>& col_data) {
  if (col_data.size() != col_descs_.size())
    throw std::invalid_argument("col_data and col_descs size different!");
  rows_[next_unique_id_] = new void*[row_col_capacity_];
  // rows_.insert(std::pair<unsigned int, void**> (next_unique_id_,new
  // void*[row_col_capacity_]));
  int i = 0;
  for (const auto& ele : col_data) {
    if (col_descs_.at(i).second == DataType::kInt) {
      int col_value = std::stoi(ele);
      rows_.at(next_unique_id_)[i] = static_cast<void*>(new int(col_value));
      // col_data[i].stoi(); using hte statci thing
    } else if (col_descs_.at(i).second == DataType::kDouble) {
      double col_value = std::stod(ele);
      rows_.at(next_unique_id_)[i] = static_cast<void*>(new double(col_value));
    } else if (col_descs_.at(i).second == DataType::kString) {
      rows_.at(next_unique_id_)[i] = static_cast<void*>(new std::string(ele));
    }
    i++;
  }
  next_unique_id_++;
}

void DbTable::DeleteRowById(unsigned int id) {
  if (!rows_.contains(id))
    throw std::invalid_argument("Given Unique ID does not exist");
  for (unsigned int j = 0; j < col_descs_.size(); j++) {
    if (col_descs_.at(j).second == DataType::kInt)
      delete[] static_cast<int*>(rows_.at(id)[j]);
    else if (col_descs_.at(j).second == DataType::kDouble)
      delete[] static_cast<double*>(rows_.at(id)[j]);
    else if (col_descs_.at(j).second == DataType::kString)
      delete[] static_cast<std::string*>(rows_.at(id)[j]);
  }
  delete[] rows_.at(id);
  rows_.at(id) = nullptr;
  rows_.erase(id);
}
/*std::map<unsigned int, void**> rows_;
  std::vector<std::pair<std::string, DataType>> col_descs_;*/
void DbTable::Rhs(const DbTable& rhs) {
  next_unique_id_ = rhs.next_unique_id_;
  row_col_capacity_ = rhs.row_col_capacity_;
  col_descs_ = rhs.col_descs_;

  for (unsigned int i = 0; i < next_unique_id_; i++) {
    void** copy = new void*[row_col_capacity_];
    for (unsigned long j = 0; j < col_descs_.size(); j++) {
      if (col_descs_.at(j).second == DataType::kInt) {
        copy[j] = static_cast<void*>(
            new int(*(static_cast<int*>(rhs.rows_.at(i)[j]))));
      } else if (col_descs_.at(j).second == DataType::kDouble) {
        copy[j] = static_cast<void*>(
            new double(*(static_cast<double*>(rhs.rows_.at(i)[j]))));
      } else if (col_descs_.at(j).second == DataType::kString) {
        copy[j] = static_cast<void*>(
            new std::string(*(static_cast<std::string*>(rhs.rows_.at(i)[j]))));
      }
    }
    rows_.insert({i, copy});
  }
}

DbTable::DbTable(const DbTable& rhs) {
  next_unique_id_ = rhs.next_unique_id_;
  row_col_capacity_ = rhs.row_col_capacity_;
  col_descs_ = rhs.col_descs_;

  for (unsigned int i = 0; i < next_unique_id_; i++) {
    void** copy = new void*[row_col_capacity_];
    for (unsigned long j = 0; j < col_descs_.size(); j++) {
      if (col_descs_.at(j).second == DataType::kInt) {
        copy[j] = static_cast<void*>(
            new int(*(static_cast<int*>(rhs.rows_.at(i)[j]))));
      } else if (col_descs_.at(j).second == DataType::kDouble) {
        copy[j] = static_cast<void*>(
            new double(*(static_cast<double*>(rhs.rows_.at(i)[j]))));
      } else if (col_descs_.at(j).second == DataType::kString) {
        copy[j] = static_cast<void*>(
            new std::string(*(static_cast<std::string*>(rhs.rows_.at(i)[j]))));
      }
    }
    rows_.insert({i, copy});
  }
}
// this is where we add delete
// this is saying when we do = we have to delete
DbTable& DbTable::operator=(const DbTable& rhs) {
  if (this == &rhs) {
    return *this;
  }
  if (!rows_.empty()) {
    for (unsigned int i = 0; i < rows_.size(); i++) {
      for (unsigned long j = 0; j < col_descs_.size(); i++) {
        if (col_descs_.at(i).second == DataType::kInt)
          delete[] static_cast<int*>(rows_.at(i)[j]);
        else if (col_descs_.at(i).second == DataType::kDouble)
          delete[] static_cast<double*>(rows_.at(i)[j]);
        else if (col_descs_.at(i).second == DataType::kString)
          delete[] static_cast<std::string*>(rows_.at(i)[j]);
      }
      delete[] rows_.at(i);
      // rows_.at(i) = nullptr;
    }
    rows_.clear();
  }
  col_descs_.clear();
  next_unique_id_ = rhs.next_unique_id_;
  row_col_capacity_ = rhs.row_col_capacity_;
  col_descs_ = rhs.col_descs_;

  for (unsigned int i = 0; i < next_unique_id_; i++) {
    void** copy = new void*[row_col_capacity_];
    for (unsigned long j = 0; j < col_descs_.size(); j++) {
      if (col_descs_.at(j).second == DataType::kInt) {
        copy[j] = static_cast<void*>(
            new int(*(static_cast<int*>(rhs.rows_.at(i)[j]))));
      } else if (col_descs_.at(j).second == DataType::kDouble) {
        copy[j] = static_cast<void*>(
            new double(*(static_cast<double*>(rhs.rows_.at(i)[j]))));
      } else if (col_descs_.at(j).second == DataType::kString) {
        copy[j] = static_cast<void*>(
            new std::string(*(static_cast<std::string*>(rhs.rows_.at(i)[j]))));
      }
    }
    rows_.insert({i, copy});
  }
  return *this;
}

DbTable::~DbTable() {
  for (unsigned int row_id = 0; row_id < next_unique_id_; ++row_id) {
    if (rows_.contains(row_id)) DeleteRowById(row_id);
  }
  rows_.clear();
  col_descs_.clear();
}
std::ostream& operator<<(std::ostream& os, const DbTable& table) {
  for (unsigned int i = 0; i < table.col_descs_.size(); ++i) {
    if (table.col_descs_.at(i).second == DataType::kString) {
      os << table.col_descs_.at(i).first << "(std::string)";
    }
    if (table.col_descs_.at(i).second == DataType::kInt) {
      os << table.col_descs_.at(i).first << "(int)";
    }
    if (table.col_descs_.at(i).second == DataType::kDouble) {
      os << table.col_descs_.at(i).first << "(double)";
    }
    if (i != table.col_descs_.size() - 1) {
      os << ", ";
    }
  }
  os << "\n";
  for (const auto& [key, value] : table.rows_) {
    for (unsigned int id = 0; id < table.col_descs_.size(); ++id) {
      if (table.col_descs_.at(id).second == DataType::kString) {
        os << *(static_cast<std::string*>(value[id]));
      }
      if (table.col_descs_.at(id).second == DataType::kInt) {
        os << *(static_cast<int*>(value[id]));
      }
      if (table.col_descs_.at(id).second == DataType::kDouble) {
        os << *(static_cast<double*>(value[id]));
      }
      if (id != table.col_descs_.size() - 1) {
        os << ", ";
      }
    }
    if (key < table.rows_.size()) {
      os << "\n";
    }
  }
  return os;
}