'''
Program: Executive Class
Description: Defines executive class and run methods
Inputs: Filename input
Outputs: Terminal output of emails
Collaborators: None
Sources: None
Name: Luke Coffman
Creation Date: 8/28/25
'''



from maxheap import MaxHeap  # Importing the MaxHeap class to manage emails based on priority
from email_class import Email  # Importing the Email class to represent individual emails

class Executive:
    def __init__(self, filename):
        # Initialize the Executive class with a filename and a MaxHeap instance
        self.filename = filename
        self.heap = MaxHeap()

    def run(self):
        # Open the file specified by the filename
        with open(self.filename, "r") as f:
            for raw in f:
                s = raw.strip()
                if not s:
                    continue

                if s.startswith("EMAIL "):
                    # EMAIL Sender, Subject, MM-DD-YYYY
                    _, rest = s.split(" ", 1)
                    sender, subject, date_str = [p.strip() for p in rest.split(",", 2)]
                    line = ["EMAIL", sender, subject, date_str]
                else:
                    # Leave NEXT / READ / COUNT as a single element
                    line = [s]
                # Handle the "EMAIL" command to insert a new email into the heap
                if line[0] == 'EMAIL':
                    self.heap.insert(Email(line[1], line[2], line[3]))  # Create and insert an Email object

                # Handle the "NEXT" command to display the highest-priority email
                if line[0] == 'NEXT':
                    
                    if self.heap.is_empty():
                        print("No emails left.")  # Notify if no emails are left
                    else:
                        print("Next email:")
                        print(self.heap.get_max())  # Display the next highest-priority email

                # Handle the "READ" command to remove the highest-priority email
                if line[0] == 'READ':
                    if self.heap.is_empty():
                        print("No emails in queue")  # Notify if no emails are in the queue
                    else:
                        self.heap.extract_max()  # Remove the highest-priority email

                # Handle the "COUNT" command to display the number of emails in the queue
                elif line[0] == 'COUNT':
                    if self.heap.is_empty():
                        print("No patients in queue.")  # Notify if the queue is empty
                    elif self.heap.size() == 1:
                        print("There is 1 email to read.")  # Notify if there is one email
                    else:
                        print(f'There are {self.heap.size()} emails to read.')  # Display the count of emails
