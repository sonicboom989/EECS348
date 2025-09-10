
'''
Program:MaxHeap Class
Description: Defines max heap class
Inputs: test file input
Outputs: Extract heap and get max
Collaborators: None
Sources: None
Name: Luke Coffman
Creation Date: 8/28/25
'''

class MaxHeap:
    def __init__(self):
        self.heap = []

    def insert(self, key): # Insert method
        '''
        Inserts new item into the ehap and maintains the max-heap property.
        '''
        self.heap.append(key)# inserts key into MaxHeap's list
        self._upheap(len(self.heap)-1) # Upheaps the rest of the list to be in the correct spot

    def extract_max(self):
        '''
        Pops the top item from the max heap and maintains the order
        '''
        if len(self.heap) == 0: # if the heap is empty, reutrn nothing
            return None # Returns None
        if len(self.heap) ==1: #If there is one item on the heap
            return self.heap.pop() # Pop
        root = self.heap[0] # Change root "pointer" to be the actual root
        self.heap[0] = self.heap.pop() # temporary root
        self._downheap(0) # takes the last element and replaces the root, then downheaps
        return root
    
    def _upheap(self, index):
        '''
        Moves the item at index up the heap until the max-heap is properly restored
        '''
        parent_index = (index-1) //2 # finds the active parent of the provided index
        while index > 0 and self.heap[index] > self.heap[parent_index]:
            self.heap[index], self.heap[parent_index] = self.heap[parent_index], self.heap[index] # Flips the parent inedx with provided index
            index = parent_index # chages index to be the parent index, which it swapped with
            parent_index = (index-1)//2  # rededicates parent index to keep upheaping

    def _downheap(self, index):
        '''
        Moves the item at index down the heap until the max-heap property is restored
        '''

        largest = index # Sets largest to the index provided(Starts as the top value, recursively downheaped to its)
        left_child_index = 2*index+1 # Finds the left child of the index provided
        right_child_index = 2*index+2 # Finds the right child of the index provided

        if left_child_index < len(self.heap) and self.heap[left_child_index] >self.heap[largest]: # If the left child's index is less than the length of the heap(not outside), and the left childs index is greater than the largest value
            largest = left_child_index

        if right_child_index < len(self.heap) and self.heap[right_child_index] > self.heap[largest]: # If right child is larger than the downheaped value
            largest = right_child_index # Move right child above the value

        if largest != index: # If largest is not larger than any child, then downheap
            self.heap[index], self.heap[largest] = self.heap[largest], self.heap[index]
            self._downheap(largest) ## Recurse through the downheap method

    def get_max(self):
        '''
        Returns the maximum item from the heap without removing it 
        '''
        return None if len(self.heap) == 0 else self.heap[0] # If heap is empty return none, else return index 0
    
    def is_empty(self):
        '''
        Returns True if the heap is empty, False otherwise.
        '''
        return len(self.heap) == 0

    def size(self):
        '''
        Returns the number of items in the heap.
        '''
        return len(self.heap)