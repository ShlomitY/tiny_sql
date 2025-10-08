#include "Column.h"


int main() {
	Column_string Names("Names");
	Column_int Ages("Ages");

	Names.addData("Alice");
	Ages.addData(30);

	Names.addData("Bob");
	Ages.addData(25);

	for(int i = 0 ; i < Names.getSize(); i++) {
		std::cout << Names.getData()[i] << " is " << Ages.getData()[i] << " years old." << std::endl;
	}
	return 0;
}