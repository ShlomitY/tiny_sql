#include "Column.h"


//Column implementation

Column::Column(const string& name) : 
	m_name(name) {}


string Column::getName() const {
	return m_name; 
}

int Column::getSize() const { 
	return m_size; 
}



//column_string implementation
Column_string::Column_string(const string& name) :
	Column(name) {}


void Column_string::addData(const string& data) {
	this->size++;
	column_data.push_back(data); 
}


const vector<string>& Column_string::getData() const { 
	return this->column_data;
}

//column_int implementation
Column_int::Column_int(const string& name) :
	Column(name) {}


void Column_int::addData(const int& data) {
	this->size++;
	column_data.push_back(data);
}


const vector<int>& Column_int::getData() const {

	return this->column_data;
}