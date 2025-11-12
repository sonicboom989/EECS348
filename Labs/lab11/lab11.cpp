
#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>

using namespace std;


class Matrix{
    private:
        int size;
        int** matrix; //pointer to pointer 2d matrix
        std::string name;

        void allocate(int n){
            size = n;
            matrix = new int*[size];
            for (int i = 0; i < size; ++i){
                matrix[i] = new int[size]{};
            }
        }

        void release(){
            if(matrix){
                for(int i = 0; i< size; ++i) delete[] matrix[i];
                delete[] matrix;
            }
            matrix = nullptr;
            size = 0;
        }


    public:

        Matrix(const string& name = "") : size(0), matrix(nullptr), name(name){ }
        Matrix(int n, const string& name = "") : size(0), matrix(nullptr), name(name){
            allocate(n);
        }

        ~Matrix(){
            //Class Destructor
            //Frees memory dynamically allocated for the matrix
            //Called when the object goes out of scope

            //Only run if memory is allocated
            release();
        }

        Matrix(const Matrix& other) : size(0), matrix(nullptr), name(other.name){
            if(other.size > 0){
                allocate(other.size);
                for(int i = 0; i < size; ++i){
                    for(int j = 0; j < size; ++j){
                        matrix[i][j] = other.matrix[i][j];
                    }
                }
            }
        }

        //Allows the following to access privates like name and size while being passed by value
        friend Matrix swapRows(Matrix m, int row1, int row2);
        friend Matrix swapCols(Matrix m, int col1, int col2);
        friend Matrix updateElement(Matrix m, int r, int c, int value);




        void readData(ifstream& file){
            //Reads matrix from an already open file
            for(int i=0; i<size; ++i){
                for(int j=0; j <size; ++j){
                    file >> matrix[i][j]; //Fill each element
                }
            }
        }

        void printM() const{
            cout << string(size/2, '-') << "Matrix " << name << string(size/2, '-') << endl;
            
            for (int i = 0; i < size; ++i){
                for(int j =0; j <size; ++j){
                    cout << setw(2) << setfill('0') << matrix[i][j] << " ";
                }
                cout << endl;
            }
        }

        pair<int,int> diagonalSum() const{
            int mainDiag = 0, secondaryDiag = 0;

            for(int i = 0; i < size; ++i){
                mainDiag        += matrix[i][i];
                secondaryDiag   += matrix [i][size- 1 - i];
            }
            return {mainDiag, secondaryDiag};
        }

        Matrix operator+(const Matrix& other) const{
            if (size != other.size){
                throw std::runtime_error("Matrix sizes must match for addition");
            }

            Matrix out(size, name + "+" + other.name); //Allocate matrix with the same size as the two being added
            for(int i = 0; i < size; ++i){
                for(int j = 0; j< size; ++j)
                    out.matrix[i][j] = matrix[i][j] + other.matrix[i][j];
            }
            return out;
        }

        Matrix operator*(const Matrix& other) const{
            if (size != other.size){
                throw std::runtime_error("Matrix sizes must match for multipliction");
            }

            Matrix out(size, name + "*" + other.name); //Allocates NxN all zeros
            for (int i = 0; i < size; ++i){
                for(int j = 0; j < size; ++j){
                    for(int k=0; k < size; ++k)
                        out.matrix[i][j] += matrix[i][k] + other.matrix[k][j];
                }
            }
            return out;
        }
};


pair<Matrix, Matrix> readTwoMatrices(const string& path){
    ifstream file(path);
    if(!file) throw runtime_error("Error opening file " + path);

    int N = 0;
    if (!(file >> N) || N <= 0) throw runtime_error("Invalid N");

    Matrix A(N, "A"), B(N,"B");
    A.readData(file);
    B.readData(file);
    return{move(A), move(B)};

}

Matrix swapRows(Matrix m, int row1 = 0, int row2 =1){
    if(row1 == row2 || row1<0 || row2 <0 || row1 >= m.size || row2 >= m.size) return m;
    std::swap(m.matrix[row1], m.matrix[row2]);
    m.name += " [swap r" + std::to_string(row1) +"<->" + std::to_string(row2) + "]";
    return m;
}

Matrix swapCols(Matrix m, int col1, int col2){
    if(col1 == col2 || col1 <0 || col2 <0 || col1 >= m.size || col2 >=m.size) return m;
    for(int r = 0; r < m.size; ++r)
        std::swap(m.matrix[r][col1], m.matrix[r][col2]);
    
    m.name += " [swap c" + std::to_string(col1) + "<->" + std::to_string(col2) + "]";
    return m;
}

Matrix updateElement(Matrix m, int row, int col, int value){
    if(row >=0 && col >=0 && row < m.size && col < m.size)
        m.matrix[row][col] = value;
    m.name += " [set(" + std::to_string(row) + "," + std::to_string(col) + ")=" + std::to_string(value) + "]";
    return m;
}


int main(){
    string filename;
    cout << "Enter filename: ";
    cin >> filename;

    auto [A,B] = readTwoMatrices(filename);
    cout << "" << endl;
    cout << "Initialized the following two matrices: " << endl;
    cout << "" << endl;
    A.printM();
    cout << "" <<endl;
    B.printM(); 
    cout << "" << endl;
    cout << "Adding Matrix A and B" << endl;
    cout << "" << endl;

    Matrix C = A + B;

    C.printM();

    Matrix D = A * B;

    cout << "" << endl;
    cout << "Multiplying Matrix A and B" << endl;
    cout << "" << endl;

    D.printM();

    cout << "" << endl;
    cout << "Diagonal sum of" << endl;
    A.printM();

    auto [sumM, sumS] = A.diagonalSum();
    cout << "Main sum = " << sumM << endl;
    cout << "Secondary sum = " << sumS << endl;

    int row1, row2;
    cout << "" << endl;
    cout << "Swap rows of: " << endl;
    A.printM();

    cout << "" << endl;
    cout << "Choose a row to swap: ";
    cin >> row1;
    cout << "Choose row to swap with: ";
    cin >> row2;

    Matrix E = swapRows(A, row1,row2);

    cout << "" << endl;
    cout << "Swapped matrix: "<< endl;
    cout << "" << endl;

    E.printM();

    int col1, col2;
    cout << "" << endl;
    cout << "Swap columns of: " << endl;
    A.printM();

    cout << "" << endl;
    cout << "Choose a column to swap: ";
    cin >> col1;
    cout << "Choose column to swap with: ";
    cin >> col2;

    Matrix F = swapCols(A, col1, col2);
    cout << "" << endl;
    cout << "Swapped matrix: "<< endl;
    cout << "" << endl;

    F.printM();

    cout << "" << endl;
    cout << "Update a value in the matrix:" <<endl;

    A.printM();

    int row,col,value;
    cout << "" << endl;
    cout << "Update at row: ";
    cin >> row;
    cout << "Update at column: ";
    cin >> col;
    cout << "With value: ";
    cin >> value;

    Matrix G = updateElement(A, row, col, value);

    cout << "" << endl;
    cout << "Updated matrix:" << endl;

    G.printM();


}