import sys
from executive import Executive
from validinput import ValidInput

def main():
    filename = ValidInput.get_file_input()
    my_exec = Executive(filename)
    my_exec.run()
    
main()