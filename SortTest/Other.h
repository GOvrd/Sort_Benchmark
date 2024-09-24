#pragma once
#include <iostream>
#include <fstream>

#define SRC_FILE_PATH "src.txt"

void file_fill(std::string filename, int number) {
	std::fstream src_file(SRC_FILE_PATH, std::ios::out);
	std::fstream file(filename, std::ios::out);
	srand(time(0));
	for (int i = 0; i < number; i++) {
		int num = rand() % 10000 - 5000;
		file << num << " ";
		src_file << num << " ";
	}
	file.close();
	src_file.close();
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