#include <iostream>
#include <chrono>
#include <vector>
#include <iomanip>
#include <iostream>
#include <fstream>

#include "funcs.h"

using namespace std;

int main(int argc, char* argv[]) {
    int dim_n1 = atoi(argv[1]);
    int dim_m1 = atoi(argv[2]);
    int dim_n2 = atoi(argv[3]);
    int dim_m2 = atoi(argv[4]);

    vector<vector<int>> matrix1;
    for (int i = 0; i < dim_n1; i++) {
        matrix1.push_back(vector<int>());
        for (int j = 0; j < dim_m1; j++) {
            matrix1[i].push_back(rand() % 10 + 1);
        }
    }

    vector<vector<int>> matrix2;
    for (int i = 0; i < dim_n2; i++) {
        matrix2.push_back(vector<int>());
        for (int j = 0; j < dim_m2; j++) {
            matrix2[i].push_back(rand() % 10 + 1);
        }
    }

    ofstream matrix_file1("matrix1.txt");
    ofstream matrix_file2("matrix2.txt");

    write_matrix(matrix_file1, matrix1, dim_n1, dim_m1);
    write_matrix(matrix_file2, matrix2, dim_n2, dim_m2);

    matrix_file1.close();
    matrix_file2.close();

    return 0;
}