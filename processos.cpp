#include <sys/types.h>
#include <iostream>
#include <iomanip>
#include <sys/wait.h>
#include <chrono>
#include <stdio.h>
#include <unistd.h>
#include <vector>
#include <fstream>
#include <functional>

#include "funcs.h"

using namespace std;

int main(int argc, char* argv[]){
    if (argc < 4)
        return 1; 

    int dim_n1, dim_m1, dim_n2, dim_m2;

    chrono::steady_clock::time_point start_time;
    chrono::steady_clock::time_point end_time;

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
    //vector<vector<int>> res;

    tie(dim_n1, dim_m1) = read_dims(file1);
    tie(dim_n2, dim_m2) = read_dims(file2);

    if (dim_n1 != dim_n2) // check if matrices can be multiplied
        return 2;

    int n_elems = dim_n1 * dim_m2; 
    int n_processos = div_ceil(n_elems, p);
    cout << "Número de processos: " << n_processos << endl;

    read_matrix(file1, matrix1, dim_n1, dim_m1);
    read_matrix(file2, matrix2, dim_n2, dim_m2);

    /* SÓ PRA VISUALIZAR A MATRIX1
    for (int i = 0; i < dim_n1 ; i++){
        for (int j = 0; j < dim_m1; j++){
            cout<<(matrix1[i][j]);
        }
        printf("\n");
    }*/


    pid_t pid[n_processos];
    pid_t wpid;
    int status = 0;

    for (int i = 0; i < n_processos; i++){
        pid[i] = fork();
        if (pid[i] < 0){
            printf("Erro ao criar o processo %d", i);
            exit(-1);
        }
        else if (pid[i] == 0){  //o que tá aqui é o processo filho
            start_time = chrono::steady_clock::now();
            sleep(3);
            //MULTIPLICAÇÃO DE MATRIZ AQUI
            end_time = chrono::steady_clock::now(); 
            int time = chrono::duration_cast<chrono::milliseconds>(end_time - start_time).count();
            printf("%d \n", time);
            printf("PID FILHO: %d PID PAI: %d \n", getpid(), getppid());
            exit(0);
        }
        while ((wpid = wait(&status)) > 0);
    }
    exit(0);
}
