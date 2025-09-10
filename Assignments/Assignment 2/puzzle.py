
class PuzzleSolver:
    def __init__(self, grid, filename):
        self.grid = grid
        self.filename = filename
        self.solutions = []

    def print_grid(self,grid):
        for row in grid:
            print(" ".join(str(x)if x != 0 else "_" for x in row))
        print()

    def find_empty(self, grid):
        #Return (row, col) of first empty cell or None if full
        for i in range(9):
            for j in range(9):
                if grid[i][j] == "_":
                    return i,j

    def is_valid(self, grid, row, col, num):
        #Check if placing num at a certain row,col is valid

        if num in grid[row]:
            return False
        
        if num in [grid[i][col] for i in range(9)]:
            return False
        
        box_row, box_col = 3*(row//3), 3*(col//3)
        for i in range(box_row, box_row+3):
            for j in range(box_col, box_col+3):
                if grid[i][j] == num:
                    return False
        return True
    
    def solve(self, grid = None):
        #Recursive method for backtrack solving
        if grid is None:
            grid = [row[:] for row in self.grid] #copy

        empty = self.find_empty(grid)
        if not empty: # no empty cells left
            self.solutions.append([row[:] for row in grid])
            return

        row, col = empty
        for num in range(1,10):
            if self.is_valid(grid, row, col, num):
                grid[row][col] = num
                self.solve(grid) #Recurse
                grid[row][col] = 0 # backtrack

        

    
        
        