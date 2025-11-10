
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
        Matrix operator+(const Matrix& other) const;
        Matrix operator*(const Matrix& other) const;



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


int main(){
   string filename;
   cout << "Enter filename: ";
   cin >> filename;

   auto [A,B] = readTwoMatrices(filename);

   A.printM();
   B.printM(); 

}