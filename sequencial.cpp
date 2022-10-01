#include <iostream>
#include <chrono>
#include <vector>
#include <iomanip>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <utility>

#include "funcs.h"

using namespace std;

int main(int argc, char* argv[]) {
    int dim_n1, dim_m1, dim_n2, dim_m2;

    string str1 = argv[1];
    string str2 = argv[2];

    string line;

    vector<string> vec1;
    vector<string> vec2;

    ifstream file1(str1);
    ifstream file2(str2);

    vector<vector<int>> matrix1;
    vector<vector<int>> matrix2;
    vector<vector<int>> res;

    tie(dim_n1, dim_m1) = read_dims(file1);
    tie(dim_n2, dim_m2) = read_dims(file2);

    read_matrix(file1, matrix1, dim_n1, dim_m1);
    read_matrix(file2, matrix2, dim_n2, dim_m2);

    file1.close();
    file2.close();

    chrono::steady_clock::time_point begin = chrono::steady_clock::now();

    res = mul_matrix(matrix1, matrix2, dim_n1, dim_m1, dim_m2);
    
    chrono::steady_clock::time_point end = chrono::steady_clock::now();

    cout << "Tempo " << chrono::duration_cast<chrono::milliseconds>(end - begin).count() << "ms" << endl;
    
    ofstream file3("seq_res.txt");

    write_matrix(file3, res, dim_n1, dim_m2);
    
    file3 << chrono::duration_cast<chrono::milliseconds>(end - begin).count() << endl;

    file3.close();
    
    return 0;
    // 3200 X 3200 = 461052ms
    // 1600 x 1600 = 37522ms
}