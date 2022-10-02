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

void print_matrix(vector<vector<int>> matrix) {
    for (int i = 0; i < matrix.size(); i++) {
        for (int j = 0; j < matrix[i].size(); j++) {
            cout << setw(5) << matrix[i][j] << " ";
        }
        cout << endl;
    }
}

vector<string> split(string const &str, const char delim){
    size_t start;
    size_t end = 0;
    vector<string> out;
 
    while ((start = str.find_first_not_of(delim, end)) != string::npos)
    {
        end = str.find(delim, start);
        out.push_back(str.substr(start, end - start));
    }
    return out;
}

pair<int, int> read_dims(ifstream& file) {
    string line;
    vector<string> vec;
    pair<int, int> p;
    getline(file, line);
    vec = split(line, ' ');
    p.first = stoi(vec[0]); 
    p.second = stoi(vec[1]); 
    return p;
}

void read_matrix(ifstream& file, vector<vector<int>>& matrix, int dim_n, int dim_m) {
    vector<string> vec;
    string line; 
    
    for (int i = 0; i < dim_n; i++) {
        matrix.push_back(vector<int>());
        for (int j = 0; j < dim_m; j++) {
            getline(file, line);
            vec = split(line, ' ');
            matrix[i].push_back(stoi(vec[1]));
        }
    }
}

vector<vector<int>> mul_matrix(vector<vector<int>>& matrix1, vector<vector<int>>& matrix2, int dim_n1, int dim_m1, int dim_m2) {
    vector<vector<int>> res;
    for(int i = 0; i < dim_n1; i++) {
        res.push_back(vector<int>());
        for (int j = 0; j < dim_m2; j++) {
            res[i].push_back(0);
            for(int k = 0; k < dim_m1; k++) {
                res[i][j] += matrix1[i][k] * matrix2[k][j];
            }
        }
    }
    return res;
}

void write_matrix(ofstream& file, vector<vector<int>>& matrix, int dim_n, int dim_m) {
    file << dim_n << " " << dim_m << endl;

    for (int i = 0; i < dim_n; i++) {
        for (int j = 0; j < dim_m; j++) {
            file << "c" << i << j << " " << matrix[i][j] << endl; 
        }
    }
}

int div_ceil(int x, int y) {
    return x / y + (x % y > 0);
}

void write_matrix_p(vector<vector<int>> matrix, int t, int start, int end, int time) {
    int i = start;
    string str = std::string("thread") + to_string(t) + ".txt";
    ofstream file;
    file.open(str);
    file << matrix[0].size() << " " << matrix.size() << endl;
    while (i < end) {
        int y = i % matrix.size();
        int x = i / matrix.size();
        file << "c" << x << y << " " << matrix[x][y] << endl;
        i++;
    }
    file << time;
    file.close();
}

void write_matrix_pp(vector<vector<int>> matrix, int t, int start, int end, int time) {
    int i = start;
    string str = std::string("processo") + to_string(t) + ".txt";
    ofstream file;
    file.open(str);
    file << matrix[0].size() << " " << matrix.size() << endl;
    while (i < end) {
        int y = i % matrix.size();
        int x = i / matrix.size();
        file << "c" << x << y << " " << matrix[x][y] << endl;
        i++;
    }
    file << time;
    file.close();
}
