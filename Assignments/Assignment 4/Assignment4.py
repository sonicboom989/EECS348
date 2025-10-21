'''
Program: EECS 348 Assignment 1
Description: Uses Property objectgs to print each truth table of boolean properties
Inputs: None
Outputs: Boolean property tables
Collabortors: None
Sources: Module05 and ChatGPT for debugging and partial TableGenerator logic
Author: Luke Coffman
Creation Date: 10/8/25
'''
def bool_to_bin(b):
    return 1 if b else 0

class Property:
    def __init__(self, id, LHS_symbol, RHS_symbol, LHS_str, RHS_str,left_func, right_func, vars):
        '''
        Takes in arguments for a property object to be used multiple times
        id is the property number
        Both symbols are the symbolic form of the RHS and LHS
        Both str are the python form of the equation
        left and right func are the inline lambda functions to do the actual computing
        '''



        self.id = id
        self.LHS_symbol = LHS_symbol
        self.RHS_symbol = RHS_symbol
        self.LHS_str = LHS_str
        self.RHS_str = RHS_str
        self.left_func = left_func
        self.right_func = right_func
        self.vars = vars



class TableGenerator:
    def print_table(self, prop: Property):
        print(f'Boolean Property {prop.id}: {prop.LHS_symbol} = {prop.RHS_symbol}') # Prints the header, boolean id and both sides of the equation
        print(f'LHS = {prop.LHS_str}') # Shows python code for LHS
        print(f'RHS = {prop.RHS_str}') # Shows python code for RHS

        #Create table headers(varables + LHS + RHS)
        headers = list(prop.vars) + [prop.LHS_symbol, prop.RHS_symbol]

        rows = []                           #List to store all rows of truth tables
        n = len(prop.vars)                  #Number of variables(used for determining how many rows)
        total = 1 << n if n > 0 else 1      #Total rows = 2^n, or 1 if there are no variables
        
        #Loop through all possible variable combinations
        for i in range(total):
            env = {}                        #Creates a dictionary to store variables for this row
            bit_cells = []                  #list of 0 or 1 strings

            #Generate 0 and 1 for each variable
            for k,name in enumerate(prop.vars):
                bit = (i >> (n-1-k)) & 1    #Extract the bit for the current variable
                env[name] = bool(bit)       #Stores True/False for the variable
                bit_cells.append(str(bit))  #Stores 0/1 for printing

            #Evaluate both sides of the property
            if n >0:
                lhs_val = prop.left_func(**env) #Calls the stored function and giving lambda variables
                rhs_val = prop.right_func(**env) #Calls the stored function and giving lambda variables
            else:
                lhs_val = prop.left_func() #Calls the stored function with no variables
                rhs_val = prop.right_func() #Calls the stored function with no variables
            rows.append(bit_cells + [str(bool_to_bin(lhs_val)), str(bool_to_bin(rhs_val))])


        #Determine column widths for formatting
        col_widths = [len(h) for h in headers]
        for r in rows:
            for j, cell in enumerate(r):
                if len(cell) > col_widths[j]:
                    col_widths[j] = len(cell)

        #Function to format a row based on column widths
        def format_row(cells):
            return "|".join(f"{c:>{w}}" for c, w in zip(cells,col_widths)) # Right allignts the numbers to keep bits lined up
        
        header_str = format_row(headers) #Formats the header row
        print(header_str) #Prints the header row
        print("-" * len(header_str))   #Prints a separator line
        for r in rows:
            print(format_row(r)) #Prints each row of the truth table
        print()


        

'''
Below is a list of Property() objects in the form of
id =              #ID of the property
LHS =             #Left hand side of the equation
RHS =             #Right side of the equation
LHS_code =        #Written Code segment of the left-hand side code
RHS_code =        #Written Code segment of the right-hand side code
left_function =   #Left side of the property
right_function =  #Right Side of the property
variables =       #Variables used in the property

Both equations use lambda for in line function calls

Each properrty is printed using the TableGenerator
'''
properties = [

    Property(
        "1a",
        "0*0",
        "0",
        "0 and 0",
        "0",
        lambda: (0 and 0),
        lambda: 0,
        (),
    ),
    
    Property(
        "1b",
        "1+1",
        "1",
        "1 or 1",
        "1",
        lambda: (1 or 1),
        lambda: 1,
        (),
    ),
    Property(
        "1a",
        "0*0",
        "0",
        "0 and 0",
        "0",
        lambda: (0 and 0),
        lambda: 0,
        (),
    ),
    Property(
        "2a",
        "1*1",
        "1",
        "1 and 1",
        "1",
        lambda: (1 and 1),
        lambda: 1,
        (),
    ),
    Property(
        "2b",
        "0+0",
        "0",
        "0 or 0",
        "0",
        lambda: (0 or 0),
        lambda: 0,
        (),
    
    ),
    Property(
        "3a",
        "0*1",
        "1*0 = 0",
        "0 and 1",
        "(1 and 0)",
        lambda: (0 and 1),
        lambda: (1 and 0),
        (),
    ),
    Property(
       "3b",
        "0+1",
        "1+0 = 1",
        "0 or 1",
        "(1 or 0)",
        lambda: (0 or 1),
        lambda: (1 or 0),
        (), 
    ),
    Property(
        "4a",
        "if x= 0",
        "!x = 1",
        "not 0",
        "1",
        lambda: (not 0),
        lambda: (1),
        (), 
    ),
    Property(
        "4b",
        "if x= 1",
        "!x = 0",
        "not 1",
        "0",
        lambda: (not 1),
        lambda: (0),
        (),
    ),
    Property(
        "5a",
        "x*0",
        "0",
        "x and 0",
        "0",
        lambda x: (x and 0),
        lambda x: (0),
        ("x",),
    ),
    Property(
        "5b",
        "x+1",
        "1",
        "x or 1",
        "1",
        lambda x: (x or 1),
        lambda x: (1),
        ("x",),
    ),
    Property(
        "6a",
        "x*1",
        "x",
        "x and 1",
        "x",
        lambda x: (x and 1),
        lambda x: (x),
        ("x",),
    ),
    Property(
        "6b",
        "x+0",
        "x",
        "x or 0",
        "x",
        lambda x: (x or 0),
        lambda x: (x),
        ("x",),
    ),
    Property(
        "7a",
        "x*x",
        "0x",
        "x and x",
        "x",
        lambda x: (x and x),
        lambda x: (x),
        ("x",),
    ),
    Property(
        "7b",
        "x+x",
        "x",
        "x or x",
        "x",
        lambda x: (x or x),
        lambda x: (x),
        ("x",),
    ),
    Property(
        "8a",
        "x*!x",
        "0",
        "x and not x",
        "0",
        lambda x: (x and not x),
        lambda x: (0),
        ("x",),
    ),
    Property(
        "8b",
        "x+!x",
        "1",
        "x or not x",
        "1",
        lambda x: (x or not x),
        lambda x: (1),
        ("x",),
    ),
    Property(
        "9",
        "!!x",
        "x",
        "not not x",
        "x",
        lambda x: (not not x),
        lambda x: (x),
        ("x",),
    ),
    Property(
        "10a",
        "x*y",
        "y*x",
        "x and y",
        "y and x",
        lambda x,y: (x and y),
        lambda x,y: (y and x),
        ("x","y",),
    ),
    Property(
        "10b",
        "x+y",
        "y+x",
        "x or y",
        "y or x",
        lambda x,y: (x or y),
        lambda x,y: (y or x),
        ("x","y",),
    ),
    Property(
        "11a",
        "x*(y*z)",
        "(x*y)*z",
        "x and (y and z)",
        "(x and y) and z",
        lambda x,y,z: x and (y and z),
        lambda x,y,z: (x and y) and z,
        ("x","y","z",),
    ),
    Property(
        "11b",
        "x+(y+z)",
        "(x+y)+z",
        "x or (y or z)",
        "(x or y) or z",
        lambda x,y,z: x or (y or z),
        lambda x,y,z: (x or y) or z,
        ("x","y","z",),
    ),
    Property(
        "12a",
        "x*(y+z)",
        "(x*y)+(x*z)",
        "x and (y+z)",
        "(x and y) or (x and z)",
        lambda x,y,z: x and (y or z),
        lambda x,y,z: (x and y) or (x and z),
        ("x","y","z",),
    ),
    Property(
        "12b",
        "x+(y*z)",
        "(x+y)*(x+z)",
        "x or (x and z)",
        "(x or y) and (x or z)",
        lambda x,y,z: x or (y and z),
        lambda x,y,z: (x or y) and (x or z),
        ("x","y","z",),
    ),
    Property(
        "13a",
        "x+(x*y)",
        "x",
        "x or (x and y)",
        "x",
        lambda x,y: x or (x and y),
        lambda x,y: x,
        ("x","y",),
    ),
    Property(
        "13b",
        "x*(x+y)",
        "x",
        "x and (x or y)",
        "x",
        lambda x,y: x and (x or y),
        lambda x,y: x,
        ("x","y",),
    ),
    Property(
        "14a",
        "(x*y)+(x*!y)",
        "x",
        "(x and y) or (x and not y)",
        "x",
        lambda x,y: (x and y) or (x and not y),
        lambda x,y: x,
        ("x","y",),
    ),
    Property(
      "14b",
        "(x+y)*(x+!y)",
        "x",
        "(x or y) and (x or not y)",
        "x",
        lambda x,y: (x or y) and (x or not y),
        lambda x,y: x,
        ("x","y",),  
    ),
    Property(
        "15a",
        "!(x*y)",
        "!x + !y",
        "not (x and y)",
        "not x or not y",
        lambda x,y: not (x and y),
        lambda x,y: not x or not y,
        ("x","y",),  
    ),
    Property(
        "15b",
        "!(x+y)",
        "!x*!y",
        "not (x or y)",
        "not x and not y",
        lambda x,y: not (x or y),
        lambda x,y: not x and not y,
        ("x","y",),  
    ),
    Property(
        "16a",
        "x+(!x*y)",
        "x+y",
        "x or (not x and y)",
        "x or y",
        lambda x,y: x or (not x and y),
        lambda x,y: x or y,
        ("x","y",),  
    ),
    Property(
        "16b",
        "x*(!x+y)",
        "x*y",
        "x and (not x or y)",
        "x and y",
        lambda x,y: x and (not x or y),
        lambda x,y: x and y,
        ("x","y",),  
    ),
    Property(
        "17a",
        "(x*y)+(y*z)+(!x*z)",
        "(x*y)+(!x*z)",
        "(x and y) or (y and z) or (not x and z)",
        "(x and y) or (not x and z)",
        lambda x,y,z: (x and y) or (y and z) or (not x and z),
        lambda x,y,z: (x and y) or (not x and z),
        ("x","y","z",),  
    ),
    Property(
        "17b",
        "(x+y)*(y+z)*(!x+z)",
        "(x+y)*(!x+z)",
        "(x or y) and (y or z) and (not x or z)",
        "(x or y) and (not x or z)",
        lambda x,y,z: (x or y) and (y or z) and (not x or z),
        lambda x,y,z: (x or y) and (not x or z),
        ("x","y","z",),  
    )
    

]
def main():
    printer = TableGenerator()
    for p in properties:
        printer.print_table(p)

main()