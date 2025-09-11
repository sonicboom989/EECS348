"""
Assignment: EECS 348 Lab 3
Description: Sudoku solver class, deals with solving recursively
Inputs: text files of empty sudoku puzzles
Outputs: Rows and colmns of each empty squares on a grid
Collaborators: Lucas Root
Sources: Previous 268 Labs adn lectures
Author: Luke Coffman
Creation Date: 9/10/25
"""



class PuzzleSolver:
    def __init__(self, grid, filename):
        self.grid = grid
        self.filename = filename 
        self.solutions = [] #Set of solutions, if there are multiple, will be printed after

    def print_grid(self,grid):
        for row in grid:
            print(" ".join(str(x)if x != 0 else "_" for x in row)) #Prints each line nicely
        print()

    def find_empty(self, grid):
        #Return (row, col) of first empty cell or None if full
        for i in range(9): 
            for j in range(9): 
                if grid[i][j] == 0: # If cell is empty
                    return i,j # Return row,col

    def is_valid(self, grid, row, col, num):
        #Check if placing num at a certain row,col is valid

        if num in grid[row]: # Checks if num is in the row, if so, means it is not a valid place to solve
            return False
        
        if num in [grid[i][col] for i in range(9)]: # Checks if num is in the column, if so, means it is not a valid place to solve
            return False
        
        box_row, box_col = 3*(row//3), 3*(col//3)
        for i in range(box_row, box_row+3): # Checks if num is in the 3x3 box, if so, means it is not a valid place to solve
            for j in range(box_col, box_col+3): 
                if grid[i][j] == num:
                    return False
        return True # If all checks are passed, it is a valid place to solve
    
    def solve(self, grid = None):
        #Recursive method for backtrack solving
        if grid is None:
            grid = [row[:] for row in self.grid] #copy

        empty = self.find_empty(grid)
        if not empty: # no empty cells left
            self.solutions.append([row[:] for row in grid]) # add a copy of the solved grid to solutions
            return

        row, col = empty
        for num in range(1,10):
            if self.is_valid(grid, row, col, num): # If num is valid in that row,col
                grid[row][col] = num # Place num
                self.solve(grid) #Recurse
                grid[row][col] = 0 # backtrack

        

    
        
        