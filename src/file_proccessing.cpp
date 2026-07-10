#include "../include/header.h"
#include "../include/table.h"

using namespace std;

//a function that gets a long string and returns a vector of string (devides the sentence into word)
void devider(const string& command, vector<string>& words){
  int start = 0, len = 0;
  for(int i = 0; i <= command.size(); ++i){
    if(i != command.size() && command[i] == ' '){
      string word = command.substr(start, len);
      len = 0;
      start = i + 1;
      words.push_back(word);
    }
    else if(command[i] == '\n' || command[i] == '\r' || i == command.size()){
      if(start < i){
        string word = command.substr(start, len);
        start = i + 1;
        len = 0;
        words.push_back(word);
      }
    }
    else
      len++;

  }
}

void printTables(const vector<Table*> &tables , std::ofstream& file, int command){
  file << "                                     These are the tables after command number: " << command << endl;
  if(tables.size() == 0){
    file << "Sorry! But there aren't any tables saved" << endl;
    return;
  }
  for(int i = 0 ; i < tables.size(); ++i){
    file << *tables[i] << endl << endl ;
  }
}

void upper(string& word){
  for(int i = 0 ; i < word.size(); ++i){
    if(i == word.size() - 1 && word[i] == ','){
      word = word.substr(0, word.size() - 1);
    }
    else if(i == word.size() - 2 && word[i] == ')'){
      word = word.substr(0, word.size() - 2);
    }
    word[i] = toupper(word[i]);
  }
}

bool word_is_number(string& word){
  for(int i = 0 ; i < word.size(); ++i){
    if(i == word.size() - 1 && word[i] == ','){
      word = word.substr(0, word.size() - 1);
    }
    else if(i == word.size() - 2 && word[i] == ')'){
      word = word.substr(0, word.size() - 2);
    }
    if(!isdigit(word[i])){
      return false;
    }
  }
  return true;
}

bool word_is_legal(string& word){
  if(!isalpha(word[0]))
    return false;
  for(int i = 0 ; i < word.size(); ++i){
    if(i == word.size() - 1 && word[i] == ','){
      word = word.substr(0, word.size() - 1);
    }
    else if(i == word.size() - 2 && word[i] == ')'){
      word = word.substr(0, word.size() - 2);
    }
  }
  return true;
}


int check_condition_and_return(vector<string>& condition, Table& table, vector<Column*>& selected_columns, map<string, int>& selected_identifier,
                                int number_command, std::ofstream& UnsuccessfulFile, std::ofstream& SelectOutputFile){


  vector<Column*> dup;
  for(Column* c: selected_columns){
    Column* s = new Column(*c);
    dup.push_back(s);
  }

    if(condition.size() != 0){
    Column* current_column;
    for(int i = 0; i < condition.size(); i += 4){
      int num_column = selected_identifier[condition[i]];
      current_column = dup[num_column];
      vector<pair<int, string>> current_column_data = current_column->getData();
      int type = current_column->getType();
      if(i + 2 >= condition.size()){
        UnsuccessfulFile << "WARNING: Command number " << number_command << " wasn't excecuted due to wrong syntax!" << endl;
        return 1;
      }
      if(type == 1){
        if(condition[i+2][0] != '\"' || condition[i+2][condition[i+2].size() - 1] != '\"'){
          UnsuccessfulFile << "WARNING: Command number " << number_command << " wasn't excecuted due to wrong syntax!" << endl;
          UnsuccessfulFile << "the type of the column is TEXT" << endl;
          return 1;
        }
        condition[i+2] = condition[i+2].substr(1, condition[i+2].size()-2);
      }
      pair<int, string> comparison;
      if (type)
        comparison = pair<int, string>(-1, condition[i+2]);
      else
        comparison = pair<int, string>(stoi(condition[i+2]), "");
      if(condition[i + 1] == "="){
        for(int j = 0 ; j < current_column->getSize(); ++j){
          if(type == 0 && current_column->getData()[j].first != comparison.first){
            for(Column* c: dup) {
              c->remove_data(j);
            }
            j--;
          }
          if(type == 1 && current_column->getData()[j].second != comparison.second){
            for(Column* c: dup) {
              c->remove_data(j);
            }
            j--;
          }
        }
      }
      else if(condition[i + 1] == "<"){
        for(int j = 0 ; j < current_column->getSize(); ++j){
          if(type == 0 && current_column->getData()[j].first >= comparison.first){
            for(Column* c: dup) {
              c->remove_data(j);
            }
            j--;
          }
          if(type == 1){
            UnsuccessfulFile << "WARNING: Command number " << number_command << " wasn't excecuted due to wrong syntax!" << endl;
            UnsuccessfulFile<< "TEXT cant be with < condition" << endl;
            return 1;
          }
        }

      }
      else if(condition[i + 1] == ">"){
        for(int j = 0 ; j < current_column->getSize(); ++j){
          if(type == 0 && current_column->getData()[j].first <= comparison.first){
            for(Column* c: dup) {
              c->remove_data(j);
            }
            j--;
          }
          if(type == 1){
            UnsuccessfulFile << "WARNING: Command number " << number_command << " wasn't excecuted due to wrong syntax!" << endl;
            UnsuccessfulFile<< "TEXT cant be with < condition" << endl;
            return 1;
          }
        }


      }
      else if(condition[i + 1] == "!="){
        for(int j = 0 ; j < current_column->getSize(); ++j){
          if(type == 0 && current_column->getData()[j].first == comparison.first){
            for(Column* c: dup) {
              c->remove_data(j);
            }
            j--;
          }
          if(type == 1 && current_column->getData()[j].second == comparison.second){
            for(Column* c: dup) {
              c->remove_data(j);
            }
            j--;
          }
        }


      }
      else if(condition[i + 1] == "<="){
        for(int j = 0 ; j < current_column->getSize(); ++j){
          if(type == 0 && current_column->getData()[j].first > comparison.first){
            for(Column* c: dup) {
              c->remove_data(j);
            }
            j--;
          }
          if(type == 1){
            UnsuccessfulFile << "WARNING: Command number " << number_command << " wasn't excecuted due to wrong syntax!" << endl;
            UnsuccessfulFile<< "TEXT cant be with < condition" << endl;
            return 1;
          }
        }
      }
      else if(condition[i + 1] == ">="){
        for(int j = 0 ; j < current_column->getSize(); ++j){
          if(type == 0 && current_column->getData()[j].first < comparison.first){
            for(Column* c: dup) {
              c->remove_data(j);
            }
            j--;
          }
          if(type == 1){
            UnsuccessfulFile << "WARNING: Command number " << number_command << " wasn't excecuted due to wrong syntax!" << endl;
            UnsuccessfulFile<< "TEXT cant be with < condition" << endl;
            return 1;
          }
        }
      }

      if (i + 4 < condition.size() && condition[i + 3] == ")"){
        upper(condition[i+4]);
        if(condition[i+4] != "AND"){
          UnsuccessfulFile << "WARNING: Command number " << number_command << " wasn't excecuted due to wrong syntax!" << endl;
          UnsuccessfulFile<< "condition should have only AND between two conditions" << endl;
          return 1;
        }
      }

      else if(i + 3 < condition.size()){
        upper(condition[i+3]);
        if(condition[i+3] != "AND"){
          UnsuccessfulFile << "WARNING: Command number " << number_command << " wasn't excecuted due to wrong syntax!" << endl;
          UnsuccessfulFile<< "condition should have only AND between two conditions" << endl;
          return 1;
        }
      }

    }
  }

  //print the selected
  int num_col = dup.size();
  int num_row = dup[0]->getSize();
  SelectOutputFile << "                                     These are the tables after command number: " << number_command << endl;
  SelectOutputFile << "This table's name is: " << table.getName() << endl;

  for(int j = 0; j < num_col; j++){
    vector<pair<int,string>>  c = dup[j]->getData();
    string name = dup[j]->getName();
    SelectOutputFile << name << "\t" << "\t" ;
  }
  SelectOutputFile << endl;


  for(int i = 0; i < num_row; i++){
    for(int j = 0; j < num_col; j++){
      vector<pair<int,string>>  c = dup[j]->getData();
      int type = dup[j]->getType();
      if(type)
        SelectOutputFile << c[i].second << "\t" << "\t";
      else
        SelectOutputFile << c[i].first << "\t" << "\t";
    }
    SelectOutputFile << endl;
  }

  SelectOutputFile << endl << endl;


  return 0;
}


int check_condition_and_delete(vector<string>& condition, Table& table, int number_command, std::ofstream& UnsuccessfulFile){
  vector<Column*> given_columns = table.get_columns();
  map<string, int> maped = table.get_identifier();
  Column* current_column = table.get_columns()[0];

  if (condition.empty()) {
    for(int j = 0 ; j < current_column->getSize(); ++j){
        for(Column* c: given_columns) {
          c->remove_data(j);
        }
        j--;
    }
    return 0;
  }


  for(int i = 0; i < condition.size(); i += 4){
    int num_column = maped[condition[i]];
    Column* current_column = table.get_columns()[num_column];
    int type = current_column->getType();
    if(i + 2 >= condition.size()){
      UnsuccessfulFile << "WARNING: Command number " << number_command << " wasn't excecuted due to wrong syntax!" << endl;
      return 1;
    }
    if(type == 1){
      if(condition[i+2][0] != '\"' || condition[i+2][condition[i+2].size() - 1] != '\"'){
        UnsuccessfulFile << "WARNING: Command number " << number_command << " wasn't excecuted due to wrong syntax!" << endl;
        UnsuccessfulFile << "the type of the column is TEXT" << endl;
        return 1;
      }
      condition[i+2] = condition[i+2].substr(1, condition[i+2].size()-2);
    }
    pair<int, string> comparison;
    if (type)
      comparison = pair<int, string>(-1, condition[i+2]);
    else
      comparison = pair<int, string>(stoi(condition[i+2]), "");

    if(condition[i + 1] == "="){
      for(int j = 0 ; j < current_column->getSize(); ++j){
        if(type == 0 && current_column->getData()[j].first == comparison.first){
          for(Column* c: given_columns) {
            c->remove_data(j);
          }
          j--;
        }
        if(type == 1 && current_column->getData()[j].second == comparison.second){
          for(Column* c: given_columns) {
            c->remove_data(j);
          }
          j--;
        }
      }


    }
    else if(condition[i + 1] == "<"){
      for(int j = 0 ; j < current_column->getSize(); ++j){
        if(type == 0 && current_column->getData()[j].first < comparison.first){
          for(Column* c: given_columns) {
            c->remove_data(j);
          }
          j--;
        }
        if(type == 1){
          UnsuccessfulFile << "WARNING: Command number " << number_command << " wasn't excecuted due to wrong syntax!" << endl;
          UnsuccessfulFile<< "TEXT cant be with < condition" << endl;
          return 1;
        }
      }


    }
    else if(condition[i + 1] == ">"){
      for(int j = 0 ; j < current_column->getSize(); ++j){
        if(type == 0 && current_column->getData()[j].first > comparison.first){
          for(Column* c: given_columns) {
            c->remove_data(j);
          }
          j--;
        }
        if(type == 1){
          UnsuccessfulFile << "WARNING: Command number " << number_command << " wasn't excecuted due to wrong syntax!" << endl;
          UnsuccessfulFile<< "TEXT cant be with > condition" << endl;
          return 1;
        }
      }


    }
    else if(condition[i + 1] == "!="){
      for(int j = 0 ; j < current_column->getSize(); ++j){
        if(type == 0 && current_column->getData()[j].first != comparison.first){
          for(Column* c: given_columns) {
            c->remove_data(j);
          }
          j--;
        }
        if(type == 1 && current_column->getData()[j].second != comparison.second){
          for(Column* c: given_columns) {
            c->remove_data(j);
          }
          j--;
        }
      }



    }
    else if(condition[i + 1] == "<="){
      for(int j = 0 ; j < current_column->getSize(); ++j){
        if(type == 0 && current_column->getData()[j].first <= comparison.first){
          for(Column* c: given_columns) {
            c->remove_data(j);
          }
          j--;
        }
        if(type == 1){
          UnsuccessfulFile << "WARNING: Command number " << number_command << " wasn't excecuted due to wrong syntax!" << endl;
          UnsuccessfulFile<< "TEXT cant be with <= condition" << endl;
          return 1;
        }
      }


    }
    else if(condition[i + 1] == ">="){
      for(int j = 0 ; j < current_column->getSize(); ++j){
        if(type == 0 && current_column->getData()[j].first >= comparison.first){
          for(Column* c: given_columns) {
            c->remove_data(j);
          }
          j--;
        }
        if(type == 1){
          UnsuccessfulFile << "WARNING: Command number " << number_command << " wasn't excecuted due to wrong syntax!" << endl;
          UnsuccessfulFile<< "TEXT cant be with >= condition" << endl;
          return 1;
        }
      }


    }

    if (i + 4 < condition.size() && condition[i + 3] == ")"){
      upper(condition[i+4]);
      if(condition[i+4] != "OR"){
        UnsuccessfulFile << "WARNING: Command number " << number_command << " wasn't excecuted due to wrong syntax!" << endl;
        UnsuccessfulFile<< "condition should have only OR between two conditions" << endl;
        return 1;
      }
    }

    else if(i + 3 < condition.size()){
      upper(condition[i+3]);
      if(condition[i+3] != "OR"){
        UnsuccessfulFile << "WARNING: Command number " << number_command << " wasn't excecuted due to wrong syntax!" << endl;
        UnsuccessfulFile<< "condition should have only OR between two conditions" << endl;
        return 1;
      }
    }

  }
  return 0;
}


int handle_create(vector<string>& words, int number_command, vector<Table*>& tables, std::ofstream& UnsuccessfulFile){
  upper(words[1]);

  //all the checks needed.

  if(words[1] != "TABLE"){
    UnsuccessfulFile << "WARNING: Command number " << number_command << " wasn't excecuted due to wrong syntax!" << endl;
    UnsuccessfulFile << "Should be \"CREATE TABLE\"" << endl;
    return 1;
  }

  if(!isalpha(words[2][0])){
    UnsuccessfulFile << "WARNING: Command number " << number_command << " wasn't excecuted due to wrong syntax!" << endl;
    UnsuccessfulFile << "Names need to start with a letter" << endl;
    return 1;
  }
  //ending of starting checks.

  string name = words[2];
  vector<Column*> columns;
  int num_columns = 0;
  map<string, int> identifier;
  for (Table* t: tables) {
    if (name == t->getName() ){
      UnsuccessfulFile << "WARNING: Command number " << number_command << " wasn't excecuted due to wrong syntax!" << endl;
      UnsuccessfulFile << "Each table name should be unique" << endl;
      return 1;
    }
  }


  for(int i = 3; i < words.size(); ++i){

    if(i == 3){
      if(words[i] == "(" )
        i++;
      else if(words[i][0] == '('){
        words[i] = words[i].substr(1,words[i].size() - 1);
      }
    }
    string word = words[i];
    if(word[word.size() - 1] == ',' || word[word.size() - 1] == ')'){
      word = word.substr(0, word.size() - 1);
      words[i] = word;
    }
    if(words[i] == ",")
      i++;

    upper(words[i + 1]);
    int type = 0;
    if(words[i + 1] == "INT" || words[i + 1] == "INT)")
       type = 0;
    else if(words[i + 1] == "TEXT" || words[i + 1] == "TEXT)")
       type = 1;
    else{
      UnsuccessfulFile << "WARNING: Command number " << number_command << " wasn't excecuted due to wrong syntax!" << endl;
      UnsuccessfulFile << "TYPES should be INT or TEXT" << endl;
      return 1;
    }
    Column* c = new Column(words[i], type);
    i++;
    columns.push_back(c);
    if(identifier[c->getName()] != 0){
      UnsuccessfulFile << "WARNING: Command number " << number_command << " wasn't excecuted due to wrong syntax!" << endl;
      UnsuccessfulFile << "All columns should have different names" << endl;
      return 1;
    }
    identifier[c->getName()] = num_columns;
    num_columns++;
  }
  Table* t = new Table(name, columns, identifier, num_columns);
  tables.push_back(t);
  return 0;

}


int handle_insert(vector<string>& words, int number_command, vector<Table*>& tables, std::ofstream& UnsuccessfulFile){
  upper(words[1]);

  if(words.size() < 5){
    UnsuccessfulFile << "WARNING: Command number " << number_command << " wasn't excecuted due to wrong syntax!" << endl;
    return 1;
  }

  if(words[1] != "INTO"){
    UnsuccessfulFile << "WARNING: Command number " << number_command << " wasn't excecuted due to wrong syntax!" << endl;
    UnsuccessfulFile << "Should be \"INSERT INTO\"" << endl;
    return 1;
  }
  int index_table = -1;
  for(int i = 0 ; i < tables.size(); ++i){
    if(tables[i]->getName() == words[2]){
      index_table = i;
      break;
    }
  }
  if(index_table == -1){
    UnsuccessfulFile << "WARNING: Command number " << number_command << " wasn't excecuted due to wrong syntax!" << endl;
    UnsuccessfulFile << "The table name given doesn't exist!" << endl;
    return 1;
  }
  int index_values = 3;
  string w = words[index_values];
  upper(w);
  int column_num = 0;
  vector<Column*> columns = tables[index_table]->get_columns();
  while(w != "VALUES" && index_values < words.size()){
    w = words[index_values];
    if(words[index_values] == "("){
      index_values++;
      w = words[index_values];
    }
    if(words[index_values] == ")"){
      index_values++;
      w = words[index_values];
      upper(w);
      continue;
    }
    if(words[index_values][0] == '('){
      w = words[index_values].substr(1,words[index_values].size() - 1);
    }
    if(w[w.size() - 1] == ',' || w[w.size() - 1] == ')'){
      w = w.substr(0, w.size() - 1);
    }
    if(columns[column_num]->getName() != w){
      UnsuccessfulFile << "WARNING: Command number " << number_command << " wasn't excecuted due to wrong syntax!" << endl;
      UnsuccessfulFile << "The columns names given don't match the stored ones" << endl;
      return 1;
    }
    else{
      column_num++;
      index_values++;
    }
    w = words[index_values];
    upper(w);

  }
  if(w != "VALUES"){
    UnsuccessfulFile << "WARNING: Command number " << number_command << " wasn't excecuted due to wrong syntax!" << endl;
    UnsuccessfulFile << "REMINDER: should contain the word VALUES before the values" << endl;
    return 1;
  }
  index_values++;
  int number_given = 0;
  int start_values = index_values;

  while(index_values < words.size()){
    w = words[index_values];
    if(words[index_values] == "("){
      index_values++;
      w = words[index_values];
      start_values = index_values;
    }
    if(words[index_values] == ")" || words[index_values] == ");"){
      continue;
    }
    if(words[index_values][0] == '('){
      words[index_values] = words[index_values].substr(1,words[index_values].size() - 1);
      w = words[index_values];
    }
    if(w[w.size() - 1] == ',' || w[w.size() - 1] == ')'){
      words[index_values] = w.substr(0, w.size() - 1);
      w = words[index_values];
    }
    if(w[w.size()- 2] == ')' && w[w.size()- 1] == ';'){
      words[index_values] = w.substr(0, w.size() - 2);
      w = words[index_values];
    }

    int type_expected = columns[number_given]->getType();
    if(type_expected == 0 && !word_is_number(w)){
      UnsuccessfulFile << "WARNING: Command number " << number_command << " wasn't excecuted due to wrong syntax!" << endl;
      UnsuccessfulFile << "The value " << w << " doesnt match the type of value of its column" << endl;
      return 1;
    }

    if(type_expected == 1 && word_is_number(w)){
      UnsuccessfulFile << "WARNING: Command number " << number_command << " wasn't excecuted due to wrong syntax!" << endl;
      UnsuccessfulFile << "The value " << w << " doesnt match the type of value of its column" << endl;
      return 1;
    }


    if(type_expected == 0 && word_is_legal(w)){
      UnsuccessfulFile << "WARNING: Command number " << number_command << " wasn't excecuted due to wrong syntax!" << endl;
      UnsuccessfulFile << "The value " << w << " doesnt match the type of value of its column" << endl;
      return 1;
    }

    if(type_expected == 1 && !word_is_legal(w)){
      UnsuccessfulFile << "WARNING: Command number " << number_command << " wasn't excecuted due to wrong syntax!" << endl;
      UnsuccessfulFile << "The value " << w << " doesnt match the type of value of its column" << endl;
      return 1;
    }
    index_values++;
    number_given++;
  }
  if(number_given != tables[index_table]->get_num_columns()){
    UnsuccessfulFile << "WARNING: Command number " << number_command << " wasn't excecuted due to wrong syntax!" << endl;
    UnsuccessfulFile << "number of values doesnt match the number of columns" << endl;
    return 1;
  }
  int index = 0;
  for(int i = start_values; i < words.size(); ++i){
    int type = columns[index]->getType();
    pair<int,string> b;
    if(type)
      columns[index]->addData(-1,words[i]);
    else
      columns[index]->addData(stoi(words[i]), "");
    index++;
  }
  return 0;
}
//SUPPORT ONLY OR.
int handle_delete(vector<string>& words, int number_command, vector<Table*>& tables , std::ofstream& UnsuccessfulFile){
  if(words.size() < 3){
    UnsuccessfulFile << "WARNING: Command number " << number_command << " wasn't excecuted due to wrong syntax!" << endl;
    return 1;
  }

  upper(words[1]);


  if(words[1] != "FROM"){
    UnsuccessfulFile << "WARNING: Command number " << number_command << " wasn't excecuted due to wrong syntax!" << endl;
    UnsuccessfulFile << "REMAINDER: the command should start with \"DELETE FROM\" and then mantion the name of the table"<< endl;
    return 1;
  }

  int index_table = -1;
  if(words[2][words[2].size() - 1] == ';' ){
    words[2] = words[2].substr(0, words[2].size() -1);
  }
  for(int i = 0 ; i < tables.size(); ++i){
    if(tables[i]->getName() == words[2]){
      index_table = i;
      break;
    }
  }
  if(index_table == -1){
    UnsuccessfulFile << "WARNING: Command number " << number_command << " wasn't excecuted due to wrong syntax!" << endl;
    UnsuccessfulFile << "The table name given doesn't exist!" << endl;
    return 1;
  }

  if(words.size() == 3){
    vector<string> con;
    int ret = check_condition_and_delete(con, *tables[index_table], number_command, UnsuccessfulFile);
    return ret;
  }

  if(words[3] != "WHERE"){
    UnsuccessfulFile << "WARNING: Command number " << number_command << " wasn't excecuted due to wrong syntax!" << endl;
    UnsuccessfulFile << "REMAINDER: the command should be  \"DELETE FROM tablename WHERE condition\""<< endl;
    return 1;
  }

  //implement a condition checking func
  vector<string> condition;
  bool is_column = true;
  for(int i = 4; i < words.size(); ++i){
    string word = words[i];

    if(word == "("){
      continue;
    }
    if(word == ")" || word == ");" || word == ")"){
      continue;
    }
    char temp = word[0];
    if(temp == '(' || temp == ','){
      word = word.substr(1,word.size() - 1);
    }
    temp = word[word.size() - 1];
    if(temp == ',' || temp == ')'){
      word = word.substr(0, word.size() - 1);
    }


    map<string, int> all_columns = tables[index_table]->get_identifier();
    if(is_column){
      if(all_columns.count(word) != 1){
        UnsuccessfulFile << "WARNING: Command number " << number_command << " wasn't excecuted due to wrong syntax!" << endl;
        UnsuccessfulFile << "The columns names given don't match the stored ones" << endl;
        return 1;
      }
      is_column = false;
    }
    words[i] = word;
    upper(word);
    if(word == "OR"){
      words[i] = word;
      is_column = true;
    }
    condition.push_back(words[i]);
  }

  int ret = check_condition_and_delete(condition, *tables[index_table], number_command, UnsuccessfulFile );
  if(ret){
    return 1;
  }

  return 0;
}

//in where i support only AND
int handle_select(vector<string>& words, int number_command, vector<Table*>& tables , std::ofstream& UnsuccessfulFile , std::ofstream& SelectOutputFile){
  if(words.size() < 4){
    UnsuccessfulFile << "WARNING: Command number " << number_command << " wasn't excecuted due to wrong syntax!" << endl;
    return 1;
  }

  int end;
  for(end = 1; end < words.size(); ++end){
    string word = words[end];
    upper(word);
    if(word == "FROM"){
      break;
    }
  }
  if(end == words.size()){
    UnsuccessfulFile << "WARNING: Command number " << number_command << " wasn't excecuted due to wrong syntax!" << endl;
    return 1;
  }

  int index_table = -1;
  if(words[end + 1][words[end + 1].size() - 1] == ';' ){
    words[end + 1] = words[end + 1].substr(0, words[end + 1].size() -1);
  }
  for(int i = 0 ; i < tables.size(); ++i){
    if(tables[i]->getName() == words[end + 1]){
      index_table = i;
      break;
    }
  }
  if(index_table == -1){
    UnsuccessfulFile << "WARNING: Command number " << number_command << " wasn't excecuted due to wrong syntax!" << endl;
    UnsuccessfulFile << "The table name given doesn't exist!" << endl;
    return 1;
  }

  vector<Column*> given_columns = tables[index_table]->get_columns();
  map<string, int> given_identifier = tables[index_table]->get_identifier();

  int index_identifier = 0;
  vector<Column*> selected_columns;
  map<string, int> selected_identifier;


  for(int i = 1; i < end; ++i){
    string word = words[i];

    if(word == "("){
      continue;
    }
    if(word == ")" || word == ");" || word == ")"){
      continue;
    }
    char temp = word[0];
    if(temp == '(' || temp == ','){
      word = word.substr(1,word.size() - 1);
    }
    temp = word[word.size() - 1];
    if(temp == ',' || temp == ')'){
      word = word.substr(0, word.size() - 1);
    }


    words[i] = word;

    if(word == "*"){
      selected_columns = given_columns;
      selected_identifier = given_identifier;
      break;
    }

    if(given_identifier.count(word) != 1){
      UnsuccessfulFile << "WARNING: Command number " << number_command << " wasn't excecuted due to wrong syntax!" << endl;
      UnsuccessfulFile << "The columns names given don't match the stored ones" << endl;
      return 1;
    }

    Column* c = given_columns[given_identifier[word]];
    selected_columns.push_back(c);
    selected_identifier[word] = index_identifier;
    index_identifier++;

  }

  if(words[end + 2] != "WHERE" && (end + 2) < words.size() ){
    UnsuccessfulFile << "WARNING: Command number " << number_command << " wasn't excecuted due to wrong syntax!" << endl;
    return 1;
  }
  if(words[end + 2] != "WHERE" && (end + 2) >= words.size()){
    vector<string> condition;
    int ret = check_condition_and_return(condition, *tables[index_table], selected_columns, selected_identifier, number_command, UnsuccessfulFile, SelectOutputFile);
    if(ret)
      return 1;
  }

  else{
    vector<string> condition;
    bool is_column = true;
    for(int i = end + 3; i < words.size(); ++i){
      string word = words[i];

      if(word == "("){
        continue;
      }
      if(word == ")" || word == ");"){
        continue;
      }
      if(word[0] == '('){
        word = word.substr(1,word.size() - 1);
      }
      if(word[word.size() - 1] == ',' || word[word.size() - 1] == ')'){
        word = word.substr(0, word.size() - 1);
      }
      if(word[word.size()- 2] == ')' && word[word.size()- 1] == ';'){
        word = word.substr(0, word.size() - 2);;
      }
      map<string, int> all_columns = tables[index_table]->get_identifier();
      if(is_column){
        if(all_columns.count(word) != 1){
          UnsuccessfulFile << "WARNING: Command number " << number_command << " wasn't excecuted due to wrong syntax!" << endl;
          UnsuccessfulFile << "The columns names given don't match the stored ones" << endl;
          return 1;
        }
        is_column = false;
      }
      words[i] = word;
      upper(word);
      if(word == "AND"){
        words[i] = word;
        is_column = true;
      }
      condition.push_back(words[i]);
    }

    int ret = check_condition_and_return(condition, *tables[index_table], selected_columns, selected_identifier, number_command, UnsuccessfulFile, SelectOutputFile);
    if(ret){
      return 1;
    }
  }



  return 0;

}



int handle(vector<string>& words, int number_command, vector<Table*>& tables, std::ofstream& UnsuccessfulFile , std::ofstream& SelectOutputFile){
  //upper case all the letters in the first word.
  upper(words[0]);
  int c = 0;

  //command is only one line and ends with;
  if(words[words.size() - 1][words[words.size() - 1].size() - 1] != ';' ){
    UnsuccessfulFile << "WARNING: Command number " << number_command << " wasn't excecuted due to wrong syntax!" << endl;
    UnsuccessfulFile << "REMAINDER: command should be only on one line and end with \";\"" << endl;
    return 2;
  }
  words[words.size() - 1] = words[words.size() - 1].substr(0, words[words.size() - 1].size() - 1);

  if(words[0] == "CREATE"){
     c = handle_create(words, number_command, tables, UnsuccessfulFile);
    return c;
  }

  else if(words[0] == "INSERT"){
     c = handle_insert(words, number_command, tables, UnsuccessfulFile);
    return c;
  }

  else if(words[0] == "DELETE"){
     c = handle_delete(words, number_command, tables, UnsuccessfulFile);
    return c;
  }

  else if(words[0] == "SELECT"){
     c = handle_select(words, number_command, tables, UnsuccessfulFile, SelectOutputFile);
    return c;
  }
  else{
    UnsuccessfulFile << "WARNING: Command number " << number_command << " wasn't excecuted due to wrong syntax!" << endl;
    return 1;
  }
  return 0;

}



