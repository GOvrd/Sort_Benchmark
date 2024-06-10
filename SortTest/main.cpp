#include <iostream>
#include <chrono>
#include <fstream>
#include "Sort.h"
#include "Other.h"

int main() {
	std::string filename = "input.txt";
	std::string result_filename = "result.txt";
	for (int i = 10; i < 1000000; i = i * 5) {
		std::cout << i << " elements in file\n";
		std::uint64_t stats[3] = { 0, 0, 0 };
		double sum = 0.0;
		double time = 0;
		std::chrono::steady_clock::time_point start;
		std::fstream result_file(result_filename, std::ios::out);
		result_file.close();
		std::cout << "\ttime,ms\t\tfile_read\tfile_write\tcompare\n";
		for (int j = 0; j < 10; j++) {
			
			file_fill(filename, i);
			start = std::chrono::high_resolution_clock::now();
			Natural_Merging_Sort<int>(filename);
			time = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now() - start).count();
			//if (j == 0) continue;
			//std::cout << "Check: " << std::boolalpha << check(filename) << "\n";
			std::cout << "\t" << j + 1 << ". " << time / 1000 << "\t";
			stats[0] += time / 1000;
			std::fstream result_file(result_filename, std::ios::in);
			for (int i = 0; i < 3; i++) {
				std::uint64_t count;
				result_file >> count;
				std::cout << count << "\t\t";
				stats[i] += count;
			}
			std::cout << "\n";
			sum += time / 1000;

			result_file.close();
		}
		remove("result.txt");
		std::cout << "Avg stats: ";
		std::cout << sum / 10 << "     \t";
		for (int j = 0; j < 3; j++) {
			std::cout << stats[j] / 10 << "     \t";
		}
		
		std::cout << "\n--------------------------------------------------------------\n";
		
	}
	return 0;
}