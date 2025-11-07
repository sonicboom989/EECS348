#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <cctype>
#include <algorithm>

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
    bool neg1 = false, neg2 = false;

    if(!d1.empty() && d1[0] =='-'){
        neg1=true;
        d1.erase(0,1); //remove sign
    }else if(!d1.empty() && d1[0] == '+'){
        d1.erase(0,1);
    }

    if(!d2.empty() && d2[0] =='-'){
        neg2=true;
        d2.erase(0,1); //remove sign
    }else if(!d2.empty() && d2[0] == '+'){
        d2.erase(0,1);
    }
    
    auto pos1 = d1.find('.');
    auto pos2 = d2.find('.');

    //If there is no .
    string int1 = (pos1 == string::npos) ? d1 : d1.substr(0, pos1);
    string frac1 = (pos1 == string::npos) ? "" : d1.substr(pos1+1);
    string int2 = (pos2 == string::npos) ? d2 : d2.substr(0, pos2);
    string frac2 = (pos2 == string::npos) ? "" : d2.substr(pos2+1);

    //Make fractions the same length by putting 0 to the end until they are
    while (frac1.size() < frac2.size()) frac1.push_back('0');
    while (frac2.size() < frac1.size()) frac2.push_back('0');

    //Make Int parts equal length
    while (int1.size() < int2.size()) int1.insert(int1.begin(), '0');
    while (int2.size() < int1.size()) int2.insert(int2.begin(), '0');

   

    string intResult, fracResult;
    if (neg1 == neg2){
        int carry = 0;
        

        //Add fractional parts
        for(int i = frac1.size() -1; i>=0; --i){
            int sum = (frac1[i] - '0') + (frac2[i] - '0') + carry;
            carry = sum/10;
            fracResult.push_back('0' + sum % 10);
        }

        reverse(fracResult.begin(), fracResult.end());

        

        for (int i = int1.size() -1; i >=0; --i){
            int sum = (int1[i] - '0') + (int2[i] - '0') + carry;
            carry = sum/10;
            intResult.push_back('0' + sum % 10);
        }

        if (carry) intResult.push_back('0' + carry);
        reverse(intResult.begin(), intResult.end());

        //Add sign back
        if(neg1 && intResult != "0") intResult.insert(intResult.begin(), '-');

    }else{

        int cmp = 0;
        string int1cmp = int1, int2cmp = int2, frac1cmp = frac1, frac2cmp = frac2;
        if (int1cmp != int2cmp) cmp = (int1cmp < int2cmp) ? -1 : 1;
        else if (frac1cmp != frac2cmp) cmp = (int1cmp < int2cmp) ? -1 : 1;
        else return "0";

        string mI, mF, sI, sF;
        bool resultNegative = false;
        if (cmp > 0){
            mI = int1; mF = frac1; sI = int2; sF = frac2;
            resultNegative = neg1;
        }
        else{
            mI = int2; mF = frac2; sI = int1; sF = frac2;
            resultNegative = neg2;
        }

        int borrow= 0;

        for (int i = (int)mF.size() -1; i >= 0; --i){
            int x = (mF[i] - '0') - borrow;
            int y = (sF[i] - '0');
            if(x<y) {x += 10; borrow =1;} else borrow =0;
            fracResult.push_back(char('0' + (x-y)));

        }
        reverse(fracResult.begin(), fracResult.end());

        for (int i = (int)mF.size() - 1; i >= 0; --i){
            int x = (mF[i] - '0') - borrow;
            int y = (sF[i] - '0');
            if (x < y) { x+=10; borrow =1;} else borrow =0;
            intResult.push_back(char('0' + (x-y)));
        }
        reverse(intResult.begin(), intResult.end());
        if(resultNegative && intResult != "0") intResult.insert(intResult.begin(), '-');

    } 
    return fracResult.empty() ? intResult : (intResult + '.' + fracResult);

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
        

        if(!checkDouble(d1) || !checkDouble(d2)){
            cout << "ERROR: " << d1 << " and/or " << d2 << " is not a double!" << endl;
            continue;
        }

        //Add function
        cout << endl;
        cout << addDouble(d1, d2) << endl;

    } 

    return 0;
}