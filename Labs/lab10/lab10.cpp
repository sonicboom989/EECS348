#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <cctype>

using namespace std;

bool checkDouble(string d1){
    
    int length = d1.size();
    int i = 0;

    if (d1[i] == '+' or d1[i] =='-') i++;
    if(i>=length) return false;

    bool digitsBeforeDot = false;
    bool dot = false;
    bool digitsAfterDot = false;
    

    for(; i < length; i++){
        char c = d1[i];
        
        if(isdigit(c)){
            if(!dot) digitsBeforeDot = true; //If there is no decimal yet, then there are digits before the decimal
            else digitsAfterDot = true; // If there is dot, then there are digits after it
        }
        else if(c == '.'){
            if(dot) return false;
            dot = true;
        }
        else{
            return false;
        }
    }

    if(!digitsAfterDot && !digitsBeforeDot) return false;
    if(dot && !digitsAfterDot) return false;

    return true;


}

int main(){
    string filename;
    string line;
    cout << "Enter input file name: ";
    cin >> filename;
    ifstream file(filename);
    if(!file.is_open()){
        cerr << "Error opening file: " << filename << endl;
        return 1;
    }
    string d1,d2;
    while(getline(file, line)){
        istringstream iss(line);
        iss >> d1 >> d2;
        cout << d1 << ", " << d2 << endl;

        if(!checkDouble(d1) || !checkDouble(d2)){
            cout << "ERROR: " << d1 << " and/or " << d2 << " is not a double!" << endl;
            continue;;
        }

    } 

    return 0;
}