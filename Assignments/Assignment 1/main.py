'''
Program: Main Class
Description:Main class passes files to valid input and executive
Inputs:Usder file input
Outputs: Executive output
Collaborators: None
Sources:None
Name: Luke Coffman
Creation Date: 8/28/25
'''

from validinput import *
from executive import Executive
def main():
    filename = ValidInput.get_file_input()
    my_exec = Executive(filename)
    my_exec.run()


main()