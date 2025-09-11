"""
Assignment: EECS 348 Lab 3
Description: Executive class, takes the file from the user and parses through to turn it into a 2d list of ints, then passes to solver
Outputs: List of solution grids
Collaborators: Lucas Root
Sources: Previous 268 Labs and lectures
Author: Luke Coffman
Creation Date: 9/10/25
"""
from puzzle import PuzzleSolver


class Executive:
    def __init__(self, filename):
        self.file = filename

    def _parse_grid(self, lines):
        
        rows = []
        for raw in lines: 
            #Replaces underscores with szeros and splits the grid by spaces
            tokens = raw.replace("_", "0").split()
            if not tokens: # if a row is empty, fall back and parse each char
                keep = [ch for ch in raw if ch in "0123456789_"] # Keeps only valid characters
                tokens = [("0" if ch == "_" else ch) for ch in keep] # Replaces underscores with zeros


            if tokens:# If a row has numbers
                try:
                    row = [int(tok) for tok in tokens] #convert to integers
                except: 
                    ValueError 
                    filtered = [ch for ch in raw if ch in "0123456789"] # Keeps only valid characters 
                    row = [int(ch) for ch in filtered] # Convert to integers
                rows.append(row) # appends the new row of ints to the rows list

        #Validates the 9x9 grid to make sure it is imported correctly
        if len(rows) !=9 or any(len(r)!= 9 for r in rows): 
            raise ValueError("Invalid shape")
        
        return rows # returns grid of ints
    
    def _load_puzzle(self):
        #opens a puzzle file and reads line by line
        with open(self.file, 'r') as f: 
            lines = f.read().splitlines() # Reads each line and splits by line
            
        return self._parse_grid(lines) #uses parse grid to create the grid
    
    def _print_grid(self, grid):
        #Prints the grid in a neat format
        for row in grid:
            print(" ".join(str(x) if x !=0 else "_" for x in row)) # Converts int into strings and prints row by row
        print()
    
    def run(self):
        grid = self._load_puzzle()

        #Prints the grid unsolved first
        print(f"File: {self.file}")
        print("------------------------") 
        self._print_grid(grid) 

        #Uses the recursive solver to solve the puzzle
        solver = PuzzleSolver(grid, self.file) # Initializes puzzle object
        solver.solve() # Runs recursive solver

        #Print Results
        print("------------------------")
        print()
        if not solver.solutions: #If no solutions appear in the solutions list
            print("No solution found")
        else:
            print(f"Found {len(solver.solutions)} solution(s).")
            for i, sol in enumerate(solver.solutions, start=1): #Prints each solution in the solutions list
                print("-" * 30) #Prints a line of dashes to separate solutions
                print(f"Solution #{i}")
                # print the grid for THIS solution
                for row in sol:
                    print(" ".join(str(x) for x in row))
                print()  # blank line after each solution
        

