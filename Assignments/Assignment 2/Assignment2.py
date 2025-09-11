

"""
Assignment: EECS 348 Lab 3
Description: Main class, lets user choose which file to parse and sends file to exec
Inputs: text files of empty sudoku puzzles
Outputs: Printed solutions grids
Collaborators: Lucas Root
Sources: Previous 268 Labs and lectures
Author: Luke Coffman
Creation Date: 9/10/25
"""
from executive import Executive
from validinput import ValidInput

def main():
    print("|--------Choose Your Puzzle--------|")
    print("1) Puzzle 1\n2) Puzzle 2\n3) Puzzle 3\n4) Puzzle 4\n5) Puzzle 5\n6) Input other file")
    choice = int(input("Enter Choice:")) # Asks user fora puzzle choice
    filename = None
    #Match case to help user decide which puzzle to pick and sets the filename as that
    match choice:
        case 1: # If choice ==1
            filename="puzzle1.txt"
        case 2: # If Choice == 2
            filename="puzzle2.txt"
        case 3: # If Choice ==3
            filename="puzzle3.txt"
        case 4: # If Choice ==4
            filename="puzzle4.txt"
        case 5: #If Choice ==5
            filename="puzzle5.txt"
        case 6: #If Choice ==6
            filename = ValidInput.get_file_input() # Gets valid file input from the user
   
    my_exec = Executive(filename) # initializies executive object and inputs filename variable
    my_exec.run()#runs executve object
    
main()