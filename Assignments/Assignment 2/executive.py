

class Executive:
    def __init__(self, filename):
        self.file = filename

    def load_puzzle(self):
            with open(self.file, "r") as f:
                lines = f.read().splitlines()
            grid = [[int(ch) if ch.isdigit() else 0 for ch in line] for line in lines]
            return grid