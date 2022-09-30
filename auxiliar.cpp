#include <iostream>
#include <chrono>
#include <vector>
#include <iomanip>
#include <iostream>
#include <fstream>

using namespace std;

void print_matrix(vector<vector<int>> matrix) {
    for (int i = 0; i < matrix.size(); i++) {
        for (int j = 0; j < matrix[i].size(); j++) {
            cout << setw(5) << matrix[i][j] << " ";
        }
        cout << endl;
    }
}

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

    matrix_file1 << dim_n1 << " " << dim_m1 << endl;
    matrix_file2 << dim_n2 << " " << dim_m2 << endl;

    for (int i = 0; i < dim_n1; i++) {
        for (int j = 0; j < dim_m1; j++) {
            matrix_file1 << "c" << i << j << " " << matrix1[i][j] << endl; 
        }
    }

    for (int i = 0; i < dim_n2; i++) {
        for (int j = 0; j < dim_m2; j++) {
            matrix_file2 << "c" << i << j << " " << matrix2[i][j] << endl; 
        }
    }

    matrix_file1.close();
    matrix_file2.close();

    return 0;
}