#pragma once
#include <iostream>
#include <fstream>
void file_fill(std::string filename, int number) {
	std::fstream file(filename, std::ios::out);
	srand(time(0));
	for (int i = 0; i < number; i++) {
		file << rand() % 10000 - 5000 << " ";
	}
	file.close();
}
bool check(std::string filename) {
	std::fstream file(filename, std::ios::in);
	int tmp1, tmp2;
	file >> tmp1;
	while (file.eof()) {
		file >> tmp2;
		if (tmp1 > tmp2)return false;
		tmp1 = tmp2;
	}
	return true;
}