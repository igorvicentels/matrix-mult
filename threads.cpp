#include <iostream>
#include <chrono>
#include <vector>
#include <iomanip>
#include <unistd.h> 
#include <thread>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>
#include <utility>

#include "funcs.h"

using namespace std;

void runner(int x, int p, vector<vector<int>> m1, vector<vector<int>> m2, vector<vector<int>>& res) {
    int start = x * p;
    int m_size = m1.size() * m2[0].size();
    int end = min(p * (x + 1), m_size);

    for (int i = 0; i < m1[0].size(); i++) {
        res.push_back(vector<int>());
        for (int j = 0; j < m2.size(); j++) {
            res[i].push_back(0);
        }
    }

    int i = start;
    while (i < end) {
        int y = i % res.size();
        int x = i / res.size();

        for(int j = 0; j < m1[0].size(); j++) {
            res[x][y] += m1[x][j] * m2[j][y];
        }    
        i++;
    }
}

int main(int argc, char* argv[]) {
    if (argc < 4)
        return 1; 

    int dim_n1, dim_m1, dim_n2, dim_m2;

    string str1 = argv[1];
    string str2 = argv[2];
    int p = stoi(argv[3]);

    string line;

    vector<string> vec1;
    vector<string> vec2;

    ifstream file1(str1);
    ifstream file2(str2);

    vector<vector<int>> matrix1;
    vector<vector<int>> matrix2;
    // vector<vector<int>> res;

    tie(dim_n1, dim_m1) = read_dims(file1);
    tie(dim_n2, dim_m2) = read_dims(file2);

    if (dim_n1 != dim_n2) // check if matrices can be multiplied
        return 2;

    int n_elems = dim_n1 * dim_m2; 
    int n_threads = div_ceil(n_elems, p);
    cout << "Número de threads: " << n_threads << endl;

    read_matrix(file1, matrix1, dim_n1, dim_m1);
    read_matrix(file2, matrix2, dim_n2, dim_m2);
    
    thread threads[n_threads];

    chrono::steady_clock::time_point start_times[n_threads];
    chrono::steady_clock::time_point end_times[n_threads];

    vector<vector<int>> res[n_threads];

    for(int i = 0; i < n_threads; i++) {
        start_times[i] = chrono::steady_clock::now();
        threads[i] = std::thread(runner, i, p, matrix1, matrix2, ref(res[i]));
    }

    for(int i = 0; i < n_threads; i++) {
        threads[i].join();
        end_times[i] = chrono::steady_clock::now();
    }

    for (int i = 0; i < n_threads; i++) {
        int start = i * p;
        int m_size = matrix1.size() * matrix2[0].size();
        int end = min(p * (i + 1), m_size);
        int time = chrono::duration_cast<chrono::milliseconds>(end_times[i] - start_times[i]).count();
        write_matrix_p(res[i], i, start, end, time);
    }

    return 0;
}
