#include "../include/table.h"

Table::Table(const string& name):
   m_name(name)
{}

Table::Table(const string& name, const vector<Column*>& columns, const map<string, int>& identifier, int number_columns):
   m_name(name),
   m_columns(columns),
   m_identifier(identifier),
   m_num_columns(number_columns)
{}

const vector<Column*>& Table::get_columns() const{
  return m_columns;
}

const map<string,int>& Table::get_identifier() const{
  return m_identifier;
}

int Table::get_num_columns() const{
  return m_num_columns;
}

string Table::getName() const{
  return m_name;
}

Table::~Table(){
  for(int i = 0; i < m_num_columns; ++i){
    delete m_columns[i];
  }
}

std::ostream& operator<<(std::ostream& os, const Table& obj){
  int num_col = obj.m_num_columns;
  int num_row = obj.m_columns[0]->getSize();
  os << "This table's name is: " << obj.getName() << endl;

  for(int j = 0; j < num_col; j++){
    vector<pair<int,string>>  c = obj.m_columns[j]->getData();
    string name = obj.m_columns[j]->getName();
    os << name << "\t" << "\t";
  }
  os << endl;


  for(int i = 0; i < num_row; i++){
    for(int j = 0; j < num_col; j++){
      vector<pair<int,string>>  c = obj.m_columns[j]->getData();
      int type = obj.m_columns[j]->getType();
      if(type)
        os << c[i].second << "\t" << "\t";
      else
        os << c[i].first << "\t" << "\t";
    }
    os << endl;
  }
  return os;
}
