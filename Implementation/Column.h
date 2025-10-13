#pragma once

#include "header.h"

using namespace std;


class Column{

	string m_name;
	int m_type; // equals to 1 if STRING and 0 if INT.
	vector<pair<int, string>> column_data;
	int m_size;

	public:
		Column(const string& name, int type);
		Column(const Column& other);
		string getName() const;
		int getSize() const;
		int getType() const;
		void addData(int int_data, const string& string_data);
		const vector<pair<int, string>>& getData() const;
		int update_data(int index,int int_data ,string& string_data);
		int remove_data(int index);
		~Column() = default;
};
