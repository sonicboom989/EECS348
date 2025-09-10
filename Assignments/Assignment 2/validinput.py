
import os

class ValidInput:

    def get_int_input(prompt):
        while True:
            try:
                uinput = int(input(prompt))
                return uinput
            except ValueError:
                print('Please enter an integer')

    def get_int_list_input(prompt):
        while True:
            try:
                lst = [int(num) for num in input(prompt).split(',')]
                return lst
            except ValueError:
                print('Please enter a list of integers.')

    def get_file_input():
        while True:
            filename = input("Enter the filename: ")  # Get user input
            if os.path.isfile(filename):  # Check if the file exists
                return filename  # Return valid filename
            else:
                print(f"Error: File '{filename}' not found. Please try again.")

    

