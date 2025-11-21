/* 
EECS 348 Assignment 7
Program connects to the KU MySQL server, creates tables from .SQL files,
and runs the 12 required queries from the assignment.

Input: the .SQL table files in the Assignment7SQLTables folder.
Output: printed tables and results from each query.

Collaborators: none
Other sources: ChatGPT (used for explanations and debugging help)
Author: Luke Coffman
Creation Date: 11/20/2025
*/


#include <mysql_driver.h>
#include <mysql_connection.h>
#include <cppconn/statement.h>
#include <cppconn/resultset.h>
#include <cppconn/exception.h>
#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>  
#include <sstream>

//Connect to MySQL server

using namespace std;
sql::ResultSet *res; // pointer to hold query results

//Prints a result set in a table format
void printResultSet(sql::ResultSet *res) {
    sql::ResultSetMetaData *rsmd = res->getMetaData(); //gets metadata
    int columnsNumber = rsmd->getColumnCount(); //number of columns

    // Print column names
    for (int i = 1; i <= columnsNumber; i++) { //loop columns
        cout << setw(15) << left << rsmd->getColumnName(i);
    } //print column name
    cout << endl;

    // Print rows
    while (res->next()) {
        for (int i = 1; i <= columnsNumber; i++) { //loop columns again
            cout << setw(15) << left << res->getString(i); 
        }
        cout << endl;
    }
}

string loadSQLFile(const string& filePath) {
    ifstream file(filePath); //open file
    stringstream buffer; //string stream to hold file contents
    buffer << file.rdbuf(); //read file into buffer
    return buffer.str(); //return as string
}

void executeSQLFile(sql::Statement* stmt, const string& filePath) {
    string sql = loadSQLFile(filePath); //load file contents
    string statement = ""; //to hold individual statements

    for (char c : sql) { //iterate through each character
        statement += c; //build statement

        if (c == ';') { //end of statement
            // Trim whitespace
            string trimmed = statement; //make a copy to trim
            trimmed.erase(0, trimmed.find_first_not_of(" \t\r\n")); //left trim
            trimmed.erase(trimmed.find_last_not_of(" \t\r\n") + 1); //right trim

            if (!trimmed.empty() && trimmed.substr(0, 2) != "--") { //not empty or comment
                stmt->execute(trimmed); //execute statement
            }
            statement = ""; //reset for next statement
        }
    }
}



int main() {
    sql::mysql::MySQL_Driver *driver; // pointer to MySQL driver
    sql::Connection *con; // pointer to MySQL connection
    sql::Statement *stmt; // pointer to SQL statement

    driver = sql::mysql::get_mysql_driver_instance(); //driver object
    con = driver->connect("mysql.eecs.ku.edu", "348f25_l633c023","raiX4Tu9"); //connect to server
    stmt = con->createStatement(); //create statement object
    stmt->execute("USE 348f25_l633c023"); //select database

    //drop tables if they exist
    stmt->execute("DROP TABLE IF EXISTS Enrollment7;"); 
    stmt->execute("DROP TABLE IF EXISTS Offering7;");  
    stmt->execute("DROP TABLE IF EXISTS Student7;");
    stmt->execute("DROP TABLE IF EXISTS Faculty7;");
    stmt->execute("DROP TABLE IF EXISTS Course7;");

    //load and execute SQL files
    executeSQLFile(stmt, "Assignment7SQLTables/course.SQL"); 
    executeSQLFile(stmt, "Assignment7SQLTables/student.SQL");
    executeSQLFile(stmt, "Assignment7SQLTables/enrollment.SQL");
    executeSQLFile(stmt, "Assignment7SQLTables/faculty.SQL");
    executeSQLFile(stmt, "Assignment7SQLTables/offering.SQL");



    //Execute all query statements

    cout << "1: " <<endl;
    res = stmt->executeQuery("SELECT * FROM Student7 WHERE StdMajor = 'IS'");
    printResultSet(res);
    delete res;


    cout << "2. Student numbers of students who have enrolled in more than two courses\n";

    res = stmt->executeQuery(
        "SELECT StdNo "
        "FROM Enrollment7 "
        "GROUP BY StdNo "
        "HAVING COUNT(DISTINCT OfferNo) > 2;"
    );
    printResultSet(res);
    delete res;
    cout << endl;

    cout << "3. Faculty employed more than 15 years as of 2025\n";

    res = stmt->executeQuery(
        "SELECT FacFirstName, FacLastName "
        "FROM Faculty7 "
        "WHERE YEAR(FacHireDate) <= 2010;"
    );
    printResultSet(res);
    delete res;
    cout << endl;

    cout << "4. Courses offered in Summer 2020\n";

    res = stmt->executeQuery(
        "SELECT DISTINCT CourseNo "
        "FROM Offering7 "
        "WHERE OffTerm = 'SUMMER' AND OffYear = 2020;"
    );
    printResultSet(res);
    delete res;
    cout << endl;

    cout << "5. Faculty who live in ZIP code 98114\n";

    res = stmt->executeQuery(
        "SELECT FacFirstName, FacLastName "
        "FROM Faculty7 "
        "WHERE FacZipCode LIKE '98114%';"
    );
    printResultSet(res);
    delete res;
    cout << endl;


    cout << "6. Second highest GPA from Student7\n";

    res = stmt->executeQuery(
        "SELECT MAX(StdGPA) AS SecondHighestGPA "
        "FROM Student7 "
        "WHERE StdGPA < (SELECT MAX(StdGPA) FROM Student7);"
    );
    printResultSet(res);
    delete res;
    cout << endl;

    cout << "7. Individuals appearing in both Student7 and Faculty7\n";

    res = stmt->executeQuery(
        "SELECT s.StdFirstName, s.StdLastName "
        "FROM Student7 s "
        "JOIN Faculty7 f "
        "ON s.StdFirstName = f.FacFirstName "
        "AND s.StdLastName = f.FacLastName;"
    );
    printResultSet(res);
    delete res;
    cout << endl;

    cout << "8. Student information and number of selected courses\n";

    res = stmt->executeQuery(
        "SELECT s.StdNo, s.StdFirstName, s.StdLastName, "
        "       COUNT(e.OfferNo) AS NumCourses "
        "FROM Student7 s "
        "JOIN Enrollment7 e ON s.StdNo = e.StdNo "
        "GROUP BY s.StdNo, s.StdFirstName, s.StdLastName;"
    );
    printResultSet(res);
    delete res;
    cout << endl;

    cout << "9. Top 3 highest-paid professors\n";

    res = stmt->executeQuery(
        "SELECT FacFirstName, FacLastName, FacSalary "
        "FROM Faculty7 "
        "ORDER BY FacSalary DESC "
        "LIMIT 3;"
    );
    printResultSet(res);
    delete res;
    cout << endl;

    cout << "10. Students with no enrollment records\n";

    res = stmt->executeQuery(
        "SELECT * "
        "FROM Student7 s "
        "WHERE NOT EXISTS ("
        "    SELECT 1 FROM Enrollment7 e "
        "    WHERE e.StdNo = s.StdNo"
        ");"
    );
    printResultSet(res);
    delete res;
    cout << endl;

    cout << "11. Insert Alice Smith then show updated Student7\n";

    stmt->execute(
        "INSERT INTO Student7 "
        "(StdNo, StdFirstName, StdLastName, StdCity, StdState, StdMajor, StdClass, StdGPA, StdZip) "
        "VALUES ('888-88-8888','ALICE','SMITH','TOPEKA','KS','CS','JR',3.85,'66610');"
    );

    res = stmt->executeQuery("SELECT * FROM Student7;");
    printResultSet(res);
    delete res;
    cout << endl;

    cout << "12. Update Bob Norbert to Overland Park, KS then show Student7\n";

    stmt->execute(
        "UPDATE Student7 "
        "SET StdCity = 'OVERLAND PARK', StdZip = '66212' "
        "WHERE StdFirstName = 'BOB' AND StdLastName = 'NORBERT';"
    );

    res = stmt->executeQuery("SELECT * FROM Student7;");
    printResultSet(res);
    delete res;
    cout << endl;











}



