#include <vector>
#include <iostream>
using namespace std;

bool fail_lecture(const vector<int>& attendance_records){
    int absent_count = 0;

    /*1.
    FAULT LOCATED: i begins at 1, causing the first attendace to be skipped
    */
    for (int i =1; i < attendance_records.size(); ++i){
        absent_count += attendance_records[i] == 0;
    }

    return absent_count >=3;
}

bool new_fail_lecture(const vector<int>& attendance_records){
    int absent_count = 0;
    for (int i = 0; i < attendance_records.size(); ++i){

        absent_count += attendance_records[i] == 0;
    }

    return absent_count >=3;
}

void printVector(const vector<int>& v){
    cout << "{ ";
    for (int x: v){
        cout << x << " ";
    }
    cout << "}";
}

int main(){

    vector<vector<int>> tests = {
        {1},                    /* 2. Does not execute fault as size = 1 and i =1 so 1 < 1 does not execute the loop
                                HOWEVER, this cannot be done with an attendance record of 10 as it will always execute the loop*/
        {1,1,1,1,1,1,1,1,1,1},  // 3. Executes fault without error
        {0,0,0,0,1,1,1,1,1,1},  // 4. Error state but not failre
        {0,0,0,1,1,1,1,1,1,1}   // 5. Failure
    };

    
    for(int i = 0; i < tests.size(); ++i){
        cout << "Test Case " << i + 1 << endl;
        printVector(tests[i]);
        cout << endl;

        cout << "Result : ";
        cout << (fail_lecture(tests[i]) ? "FAIL" : "PASS" )<< endl;
        cout << "Expected: ";
        cout << (new_fail_lecture(tests[i]) ? "FAIL" : "PASS" ) << endl;
        cout << endl;

    }
    


}