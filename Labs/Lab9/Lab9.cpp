#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

vector<vector<int>> addMatrix(const vector<vector<int>> &a, const vector<vector<int>> &b, int n){

    vector<vector<int>> result(n, vector<int>(n));
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            result[i][j] = a[i][j] + b[i][j];
        }
    
    }
    return result;
}

vector<vector<long long>> multMatrix(const vector<vector<int>> &a, const vector<vector<int>> &b, int n){

    vector<vector<long long>> result(n, vector<long long>(n, 0));
    
    for (int i = 0; i <n; i++){
        for (int j = 0; j < n; j++){
            for (int k = 0; k < n; k++){
                result[i][j] += a[i][k] * b [k][j];
            }
        }
    }
    return result;
}
void diagonalSum(const vector<vector<int>> &a, int n){
    long long first_sum=0, sec_sum =0;
    for (int i = 0; i < n; ++i){
        first_sum += a[i][i];
        sec_sum += a[i][n-1-i];
    }
    
    cout << "Main Diagonal sum: " << first_sum << endl;
    cout << "Secondary diagonal sum: " << sec_sum << endl;

}

void swapRows(vector<vector<int>> &a, int R1, int R2){

    vector<int> temp = a[R1];
    a[R1] = a[R2];
    a[R2] = temp;

}
void swapCols(vector<vector<int>> &a, int C1, int C2, int n){

    for (int i =0; i < n; ++i){
        int temp = a[i][C1];
        a[i][C1] = a[i][C2];
        a[i][C2] = temp;
    }

}

void updateValue(vector<vector<int>> &a, int row, int col, int value){
    if (row < 0 || col < 0 || row >= (int)a.size() || col >= (int)a[0].size()) {
    cout << "Invalid indices!" << endl;
    return;
    }

    a[row][col] = value;
}


template <typename T>
void printMatrix(const vector<vector<T>>& mtx, int n){

    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            printf("%0lld ", (long long)mtx[i][j]);
        }
        printf("\n");
    }
}




int main(){
    string filename;
    cout << "Enter the input filename: ";
    cin >> filename;
    
    ifstream file(filename);
    if(!file.is_open()){
        cerr << "Error opening file: " << filename << endl;
        return 1;
    }

    int n;
    file >> n;
    vector<vector<int>> matrix1(n, vector<int>(n));
    vector<vector<int>> matrix2(n, vector<int>(n));
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            file >> matrix1[i][j];
        }
    }
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            file >> matrix2[i][j];
        }
    }
    file.close();

    auto added_result = addMatrix(matrix1, matrix2, n);
    printf("Matrix 1 + Matrix 2: \n");
    printMatrix(added_result, n);
    printf("\nMatrix 1 * Matrix 2: \n");
    auto mult_result = multMatrix(matrix1, matrix2, n);
    printMatrix(mult_result, n);

    diagonalSum(matrix1, n);


    printf("\nMatrix 1: \n");
    printMatrix(matrix1, n);
    printf("\n \n-Row Swapping-\n");

    int r1, r2;
    while (true){

        cout << "Select first row: ";
        cin >> r1;
        cout << "Select row to swap with: ";
        cin >> r2;
        if ((r1 <n && r1 >=0) && (r2 < n && r2>=0)){break;}
        else{printf("Invalid Input, Please enter a number between 0 and %c\n", n-1);}

    }

    swapRows(matrix1, r1, r2);
    printMatrix(matrix1,n);

    printf("\nMatrix 1: \n");
    printMatrix(matrix1, n);
    printf("\n \n-Column Swapping-\n");

    int c1, c2;
    while (true){

        cout << "Select first column: ";
        cin >> c1;
        cout << "Select column to swap with: ";
        cin >> c2;
        if ((c1 <n && c1 >=0) && (c2 < n && c2>=0)){break;}
        else{printf("Invalid Input, Please enter a number between 0 and %c\n",n-1 );}

    }

    swapCols(matrix1, c1, c2, n);
    printMatrix(matrix1, n);
    int row_ind, col_ind, value;


    printf("-Change an element in the matrix-\n");
    cout << "Enter the row index to change: ";
    cin >> row_ind;
    cout << "Enter the column index to change: ";
    cin >> col_ind;
    cout << "Enter the updated value: ";
    cin >> value;

    updateValue(matrix1, row_ind, col_ind, value);
    printf("\n");
    printf("Updated Matrix 1: \n");
    printMatrix(matrix1, n);



}