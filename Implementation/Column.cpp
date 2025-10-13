#include "Column.h"


//Column implementation

Column::Column(const string& name, int type) :
	m_name(name),
	m_type(type),
	m_size(0)
{}

Column::Column(const Column& other) :
	m_name(other.m_name),
	m_type(other.m_type),
	m_size(0) {
	for (pair<int, string> a : other.column_data) {
		this->addData(a.first, a.second);
	}

}

string Column::getName() const {
	return m_name;
}

int Column::getSize() const {
	return m_size;
}

int Column::getType() const {
	return m_type;
}


void Column::addData(int int_data, const string& string_data) {
	this->m_size++;
	pair<int, string> b(int_data,string_data);
	column_data.push_back(b);
}


const vector<pair<int, string>>& Column::getData() const {
	return this->column_data;
}

int Column::update_data(int index,int int_data ,string& string_data) {
	if (index < 0 || index >= this->m_size) {//out of bounds or negative
		cout << "failed to update the data" << endl;
		return -1;
	}
	pair<int, string> b(int_data,string_data);
	this->column_data[index] = b;
	return 0;
}

int Column::remove_data(int index) {
	if (index < 0 || index >= this->m_size) {//out of bounds or negative
		cout << "failed to update the data" << endl;
		return -1;
	}
	this->column_data.erase(this->column_data.begin() + index);
	this->m_size--;
	return 0;

}

