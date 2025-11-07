#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <cctype>
#include <stdexcept>
using namespace std;

using Grid = vector<vector<int>>; // Helper type for grid representation

class PuzzleSolver{ // Class to solve the puzzle
    public:
        vector<Grid> solutions; // Vector to store all found solutions
        
        PuzzleSolver(const Grid& initial)
         : grid(initial){}     

    void solveAll(){
    backtrack(); // Start the backtracking process
    }

    
    static void printGrid(const Grid& g){
        for (int r = 0; r < 9; ++r){
            for (int c = 0; c < 9; ++c){
                if (g[r][c] == 0) cout << "_ ";
                else               cout << g[r][c] << ' ';
                if (c == 2 || c == 5) cout << "| ";
            }
            cout << "\n";
            if (r == 2 || r == 5) cout << "------+-------+------\n";
        }
    }


private:

    Grid grid; // current working grid

    bool findEmpty(int& r, int& c){
        for(int i=0; i<9;++i){
            for(int j=0; j<9; ++j){
                if(grid[i][j] == 0){
                    r =i; c =j;
                    return true;
                }
            }
        }
        return false;
    }

    bool isValid(int r, int c, int val){
        //Check row r
        for(int j =0; j<9; ++j){
            if(grid[r][j] == val) return false;
        }

        //check column c
        for(int i = 0; i <9; ++i){
            if(grid[i][c] == val) return false;
        }
        int br = (r / 3) *3; // top left row of the block
        int bc = (c / 3) *3; // top left column of block
        for (int i = 0; i <3; ++i){
            for (int j = 0; j < 3; ++j){
                if(grid[br + i][bc + j] == val) return false;
            }
        }
        return true; // If no conflicts, the placement is valid
    }

    void backtrack(){
        int r,c; //Initialize variables r and c
        if(!findEmpty(r, c)){ // base case: grid is full
            solutions.push_back(grid);
            return;
        }

        for (int val = 1; val <=9; ++val){
            if(isValid(r,c,val)){ //only proceed if value is 
                grid[r][c] = val; //place value
                backtrack(); //recurse to fill the next empty cell
                grid[r][c] = 0; //undo for the next backtrack
            }
        }
    }
};



Grid loadFile(const string& filename){
    ifstream in(filename);
    if (!in) throw runtime_error("Failed to open " + filename);

    Grid g(9, vector<int>(9, 0));
    int filled = 0;
    char ch;

    for (int r = 0; r < 9; ++r){
        for (int c = 0; c < 9; ++c){
            while (in.get(ch)){
                if (std::isdigit(static_cast<unsigned char>(ch))){
                    int d = ch - '0';
                    if (d == 0) g[r][c] = 0;
                    else if (1 <= d && d <= 9) g[r][c] = d;
                    ++filled;
                    break; // move to next cell
                } else if (ch == '_'){      // underscore = blank
                    g[r][c] = 0;
                    ++filled;
                    break;
                } else if (!std::isspace(static_cast<unsigned char>(ch))){
                    // junk char: ignore and keep scanning
                    continue;
                } else {
                    // whitespace: keep scanning
                    continue;
                }
            }
            if (!in && filled < (r * 9 + c + 1)){
                throw runtime_error("Puzzle not formatted correctly");
            }
        }
    }
    return g;  // <-- here, AFTER finishing all 81 cells
}


void printHeader(const string& title){
    cout << "\n==== " << title << " ====\n";
}


int main(){
    string filename;
    string choice;
    cout << "Choose your Puzzle!" << endl;
    cout << "1) Puzzle 1" << endl;
    cout << "2) Puzzle 2" << endl;
    cout << "3) Puzzle 3" << endl;
    cout << "4) Puzzle 4" << endl;
    cout << "5) Puzzle 5" << endl;
    cout << "6) Input other file" << endl;
    cout << "Enter choice (1-6): ";
    cin >> choice;
    if (choice == "6"){
        cout << "Enter filename: ";
        cin >> filename;
    }
    else
    filename = "puzzle" + choice + ".txt";

    try{
        Grid puzzle = loadFile(filename);

        printHeader("Puzzle File");
        cout << filename << "\n";

        printHeader("Original Puzzle");
        PuzzleSolver::printGrid(puzzle);

        //Solve
        PuzzleSolver solver(puzzle);
        solver.solveAll();

        //Display Results
        if(solver.solutions.empty()){
            printHeader("Result");
            cout << "No solution found" << endl;
        }else{
            printHeader("Solutions Found: " + to_string(solver.solutions.size()));
            for(size_t i =0; i < solver.solutions.size(); ++i){
                cout << "\n-- Solution " << (i+1) << " --\n";
                PuzzleSolver::printGrid(solver.solutions[i]);
            }
        }

    } catch (const exception& ex){
        cerr << "\nError: " << ex.what() << "\n";
        cerr << "Make sure the file exists and has 81 entries";
        return 1;
    }
    


    return 0;

}