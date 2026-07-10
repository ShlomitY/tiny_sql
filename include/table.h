#pragma once

#include "column.h"



class Table {
	const string m_name;
	vector<Column*> m_columns;
	map<string, int> m_identifier; // a map to identify the index of a name column in the m_columns.
	int m_num_columns;


	public:
	Table(const string& name);
	Table(const string& name, const vector<Column*>& columns, const map<string, int>& identifier, int number_columns);
	const vector<Column*>& get_columns() const; //only getting the data.
	const map<string,int>& get_identifier() const;
	string getName() const;
	int get_num_columns() const; //get number of clumns in the table.
	~Table();
	friend std::ostream& operator<<(std::ostream& os, const Table& obj);






};