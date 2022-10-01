#ifndef FUNCS_H
#define FUNCS_H

#include <utility>
#include <vector>
#include <string>

using namespace std;

// prints matrix in console (used to debug)
void print_matrix(vector<vector<int>> matrix);

// split a string into a vector of strings
vector<string> split(string const &str, const char delim);

// retunr a pair (n, m) where n and m are the matrix dimensions
pair<int, int> read_dims(ifstream& file);

// Read matrix from a txt file to a vector<vector<int>>
void read_matrix(ifstream& file, vector<vector<int>>& matrix, int dim_n, int dim_m);

// multiply matrices
vector<vector<int>> mul_matrix(vector<vector<int>>& matrix1, vector<vector<int>>& matrix2, int dim_n1, int dim_m1, int dim_m2);

// write matrix to txt file
void write_matrix(ofstream& file, vector<vector<int>>& matrix, int dim_n, int dim_m);


#endif