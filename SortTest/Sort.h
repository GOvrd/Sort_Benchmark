#pragma once
#include <iostream>
#include <fstream>

//определение конца блока
bool End_Range(std::fstream& f) {
    int tmp;
    tmp = f.get();
    tmp = f.get();
    if (tmp != '\'') f.seekg(-2, 1);
    else f.seekg(1, 1);
    return tmp == '\'' ? true : false;
}
template<typename Type>
void Natural_Merging_Sort(std::string name) {
    Type a1, a2;
    int s1, s2, mark;
    std::fstream f, f1, f2;
    s1 = s2 = 1;
    std::uint64_t stats[] = {0, 0, 0};
    //std::cout << "time\tfile_read\tfile_write\tcompare\n";
    while (s1 > 0 && s2 > 0) {
        mark = 1;
        s1 = 0;
        s2 = 0;
        f.open(name, std::ios::in);
        f1.open("nmsort_1.txt", std::ios::out);
        f2.open("nmsort_2.txt", std::ios::out);
        f >> a1;
        stats[0]++;
        if (!f.eof()) {
            f1 << a1 << ' ';
            stats[1]++;
        }
        
        if (!f.eof()) { 
            f >> a2; 
            stats[0]++;
        }
        
        while (!f.eof()) {
            if (a2 < a1) {
                
                switch (mark) {
                case 1: {
                    f1 << "' ";
                    stats[1]++;
                    mark = 2;
                    s1++;
                    break;
                }
                case 2: {
                    f2 << "' ";
                    stats[1]++;
                    mark = 1;
                    s2++;
                    break;
                }
                }
            }
            stats[2]++;
            if (mark == 1) {
                f1 << a2 << ' ';
                stats[1]++;
                s1++;
            }
            else {
                f2 << a2 << ' ';
                stats[1]++;
                s2++;
            }
            a1 = a2;
            f >> a2;
            stats[1]++;
        }

        if (s2 > 0 && mark == 2) { 
            f2 << "'"; 
            stats[1]++;
        }
        if (s1 > 0 && mark == 1) { 
            f1 << "'"; 
            stats[1]++;
        }
        f2.close();
        f1.close();
        f.close();

        //std::cout << std::endl;
        //Print_File(name);
        //Print_File("nmsort_1");
        //Print_File("nmsort_2");
        //std::cout << std::endl;

        f.open(name, std::ios::out);
        f1.open("nmsort_1.txt", std::ios::in);
        f2.open("nmsort_2.txt", std::ios::in);
        if (!f1.eof()) { 
            f1 >> a1;
            stats[0]++;
        };
        if (!f2.eof()) {
            f2 >> a2;
            stats[0]++;
        }
        bool file1, file2;

        while (!f1.eof() && !f2.eof()) {
            file1 = file2 = false;
            while (!file1 && !file2) {
                if (a1 <= a2) {
                    stats[2]++;
                    f << a1 << ' ';
                    stats[1]++;
                    file1 = End_Range(f1);
                    f1 >> a1;
                    stats[0]++;
                }
                else {
                    f << a2 << ' ';
                    stats[1]++;
                    file2 = End_Range(f2);
                    f2 >> a2;
                    stats[0]++;
                }
            }
            while (!file1) {
                f << a1 << ' ';
                stats[1]++;
                file1 = End_Range(f1);
                f1 >> a1;
                stats[0]++;
            }
            while (!file2) {
                f << a2 << ' ';
                stats[1]++;
                file2 = End_Range(f2);
                f2 >> a2;
                stats[0]++;
            }
        }

        file1 = file2 = false;
        while (!file1 && !f1.eof()) {
            f << a1 << ' ';
            stats[1]++;
            file1 = End_Range(f1);
            f1 >> a1;
            stats[0]++;
        }
        while (!file2 && !f2.eof()) {
            f << a2;
            stats[1]++;
            file2 = End_Range(f2);
            f2 >> a2;
            stats[0]++;
        }
        f2.close();
        f1.close();
        f.close();
    }
    std::fstream result_file("result.txt", std::ios::out);
    for (int i = 0; i < 3; i++) {
        result_file << stats[i] << " ";
    }
    result_file.close();
    remove("nmsort_1.txt");
    remove("nmsort_2.txt");
}