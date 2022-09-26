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

using namespace std;

void write_matrix(vector<vector<int>> matrix, int t, int start, int end) {
    int i = start;
    string str = std::string("thread") + to_string(t) + ".txt";
    ofstream file;
    file.open(str);
    file << matrix[0].size() << " " << matrix.size() << endl;
    while (i < end) {
        int x = i % matrix.size();
        int y = i / matrix.size();
        file << "c" << x << y << " " << matrix[x][y] << endl;
        i++;
    }
    file.close();
}

void print_matrix(vector<vector<int>> matrix) {
    for (int i = 0; i < matrix.size(); i++) {
        for (int j = 0; j < matrix[i].size(); j++) {
            cout << setw(5) << matrix[i][j] << " ";
        }
        cout << endl;
    }
}

void runner(int x, int p, vector<vector<int>> m1, vector<vector<int>> m2) {
    int start = x * p;
    int m_size = m1.size() * m2[0].size();
    int end = min(p * (x + 1), m_size);
    cout << "Esta é a execução da Thread " << x << endl;
    vector<vector<int>> res;

    for (int i = 0; i < m1[0].size(); i++) {
        res.push_back(vector<int>());
        for (int j = 0; j < m2.size(); j++) {
            res[i].push_back(0);
        }
    }
    int i = start;
    while (i < p * (x + 1) && i < m1.size() * m2[0].size()) {
        int x = i % res.size();
        int y = i / res.size();

        for(int j = 0; j < m1[0].size(); j++) {
            res[x][y] += m1[x][j] * m2[j][y];
        }    
        i++;
    }
    print_matrix(m1);
    print_matrix(m2);
    print_matrix(res);
    write_matrix(res, x, start, end);
}



int div_ceil(int x, int y) {
    return x / y + (x % y > 0);
}

int main(int argc, char* argv[]) {
    if (argc < 6)
        return 1; 

    int dim_n1 = atoi(argv[1]);
    int dim_m1 = atoi(argv[2]);
    int dim_n2 = atoi(argv[3]);
    int dim_m2 = atoi(argv[4]);
    int p = atoi(argv[5]);

    if (dim_n1 != dim_n2) // check if matrices can be multiplied
        return 2;

    int n_elems = dim_n1 * dim_m2; 
    int n_threads = div_ceil(n_elems, p);
    cout << "Número de threads: " << n_threads << endl;


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

    vector<vector<int>> res {};
    
    thread threads[n_threads];

    chrono::steady_clock::time_point begin = chrono::steady_clock::now();

    for(int i = 0; i < n_threads; i++) {
        threads[i] = std::thread(runner, i, p, matrix1, matrix2);
        sleep(1);
    }

    for(int i = 0; i < n_threads; i++) {
        threads[i].join();
        cout << "Thread " << i << " finalizada" << endl; 
    }

    
    chrono::steady_clock::time_point end = chrono::steady_clock::now();

    cout << "Tempo: " << chrono::duration_cast<chrono::milliseconds>(end - begin).count() << " ms" << endl;
    return 0;

    // 2350 = 122017 ms
}