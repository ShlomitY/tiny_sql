#pragma once
#include <iostream>
#include <string>
#include <vector>

class Column{
private:
	string m_name;
	int m_size

public:
	Column(const string& name);
	string getName() const;
	int getSize() const;
	virtual ~Column() {}
}

class Column_string : public Column {
	vector<string> column_data;

public:
	Column_string(const string& name);
	void addData(const string& data);
	const vector<string>& getData();
}

class Column_int : public Column {
	vector<int> column_data;

public:
	Column_int(const string& name);
	void addData(const int& data);
	const vector<string>& getData() const;
}