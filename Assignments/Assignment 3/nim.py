'''
Program: EECS 348 Assignment 3
Description: Terminal Nim game with two players
Inputs: User terminal input, row number and stars to remove
Output: Game board state, player prompt, winner message, error messages
Collaborators: Lucas Root
Sources: ChatGPT for debugging and testing
Author: Luke Coffman
Creation Date: 9/21/25
'''


import time #Used for delaying error messages to make them easier to read

class Nim:
    def __init__(self):
        self.board = [ # Defines the board each time a Nim game is initilized
            " * * * * *",
            " * * * *",
            " * * *",
            " * *",
            " *"
        ]
        self.player1 = True #If True, player 1's turn. If False, player 2's turn.
        
    def run(self):
        while True: #Goes until the game is not playable
            
            if self.is_Playable(): #If is playable is true
                self.take_turn() # Start the next turn
            else:
                break # breaks the loop
        print("Player 2 wins!") if self.player1 else print("Player 1 wins!")


    def is_Playable(self): #Checks if the game is playable
        for row in range(len(self.board)):
            if len(self.board[row]) != 0: #If any row still has stars
                return True
        return False

    def take_turn(self):
        print()
        print("|-Player 1-|" if self.player1 else "|-Player 2-|") # Prints the correct player name
        print()

        taking_turn=True

        while taking_turn: # runs while loop until the turn is done and valid
            print(self)
            if self.is_Playable():
                try:
                    row = int(input("Enter a row number(1-5): ")) -1 #-1 So the index is lined up
                    stars = int(input("Stars to remove: "))  
                except ValueError: # Catches and invalid input for row and stars
                    print("Please enter numbers only. \n ") 
                    continue

                if row < 0 or row > 4: # Checks if the row input is valid (1-5)
                    print("Invalid Row! \n")
                    time.sleep(.5)
                    continue

                if stars <=0: # Makes sure they remove at least 1 star
                    print("Please remove at least 1 star.\n")
                    time.sleep(.5)
                    continue
                
                if self.board[row].count('*') >= stars: # If the number of stars in the row is enough to take away
                    self.board[row] = self.board[row][:stars*-2] # Removes two spaces of characters for each star to account for spaces
                    taking_turn = False # If the turn is over, reset to the next player

                else:
                    print("INVALID MOVE")
                    time.sleep(.5)
                    print("Try again.")
                    time.sleep(.5)
                    print()

            self.player1 = not self.player1 # Changes player value after a valid move

    def __str__(self):
        return "\n".join(f"{i+1}: {elem}" for i,elem in enumerate(self.board)) # Prints a line for each element in an array
    
if __name__ == "__main__":
    Nim().run()