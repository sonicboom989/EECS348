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

string addDouble(string d1, string d2){
    cout << "Adding " << d1 << " and " << d2 <<endl;
    
    int pos1 = d1.find('.');
    int pos2 = d2.find('.');

    //If there is no .
    string int1 = (pos1 == npos) ? d1 : d1.substr(0, pos1);
    string frac1 = (pos1 == npos) ? "" : d1.substr(pos1+1);
    string int2 = (pos2 == npos) ? d2 : d2.substr(0, pos2);
    string frac2 = (pos2 == npos) ? "" : d2.substr(pos2+1);

    //Make fractions the same length by putting 0 to the end until they are
    while (frac1.size() < frac2.size()) frac1.push_back('0');
    while (frac2.size() < frac1.size()) frac2.push_back('0');

    //Make Int parts equal length
    while (int1.size() < int2.size()) int1.insert(int1.begin(), '0');
    while (int2.size() < int1.size()) int2.insert(int2.begin(), '0');

    int carry = 0;
    string fracResult;

    //Add fractional parts
    for(int i = frac1.size() -1, i>=0; --i){
        int sum = (frac1[i] - '0') + (frac2[i] - '0') + carry;
        carry = sum/10;
        fracResult.push_back('0' + sum % 10);
    }

    reverse(fracResult.begin(), fracResult.end());

    string intResult;

    for (int i = int1.size() -1; i >=0; --i){
        int sum = (int1[i] - '0') + (int2[i] - '0') + carry;
        carry = sum/10;
        intResult.push_back('0' + sum % 10)
    }

    if (carry) intResult.push_back('0' + carry);
    reverse(intResult.begin(), intResult.end)

    if (fracResult.empty())
        return intResult;
    else 
        return intResult + '.' + fracResult;


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

        //Add function
        cout << addDouble(d1, d2) << endl;

    } 

    return 0;
}