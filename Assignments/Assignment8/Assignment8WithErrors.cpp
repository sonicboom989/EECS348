/*
Program: 
Description: This program calculates the average of three numbers,
Author: 

*/


#include <iostream>

int main() {
    int num1 = 10; //initialize integer value of num1 to 10
    int num2 = 20; //initialize integer value of num2 to 20
    int num3 = 30; //initialize integer value of num3 to 30
    //D double average = (num1 + num2 + num3) / 3;
    double average = (num1 + num2 + num3) / 3.0; //A use floating-point division for correct average

    std::cout << "Average: " << average << std::endl; //Prints calculated average

    int sum_even = 0;
    //D for (int i = 0; i <= 5; i++) {
    for (int i =2; i <=6; i++){ //A start from 2 to include positive even numbers only and go until 6 to match the print statement
        if (i % 2 == 0) { 
            sum_even += i;
        }
    }
    std::cout << "Sum of positive even numbers <= 6: " << sum_even << std::endl;

    int value = -5;
    //Dif (value > 0 || value == 0) {
    if (value > 0) { //A check if value is strictly positive
        std::cout << value << " is positive." << std::endl;
    } else {
        std::cout << value << " is not positive." << std::endl;
    }

    return 0;
}
