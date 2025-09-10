'''
Program: Email object class
Description: Defines email and sets variabels as well as defines magic methods
Inputs: None
Outputs: None
Collaborators: None
Sources: None
Name: Luke Coffman
Creation Date: 8/28/25
'''

# Define the Email class to represent an email object
class Email:
    # Class variable to keep track of the total number of emails created
    emailcount = 0

    # Class variable to define priority levels for different senders
    PRIORITY = {
        "Boss": 5,            # Highest priority
        "Subordinate": 4,     # High priority
        "Peer": 3,            # Medium priority
        "ImportantPerson": 2, # Low priority
        "OtherPerson": 1,     # Lowest priority
    }
    def __init__(self, sender, subject, date):
        self.sender = sender.strip()
        self.priority = 0
        if self.sender == 'Boss': # If sender is Boss
            self.priority = 5 # Set priority to 5
        elif self.sender == 'Subordinate': # If sender is Subordinate
            self.priority = 4 #Set priority to 4
        elif self.sender == 'Peer': # If sender is Peer
            self.priority = 3 # Set Priority to 3
        elif self.sender == 'ImportantPerson': # If Sender is ImportantPerson
            self.priority = 2 # Set priority to 2
        elif self.sender == 'OtherPerson': # If sender is OtherPerson
            self.priority = 1 #Set priority to 1

        self.subject = subject
        self.date = date
        Email.emailcount +=1
        self.priority = self.PRIORITY.get(self.sender, 0)
        


    def __lt__(self, other): # Less than magic method
        return (self.priority) < (other.priority)
    def __eq__(self, other): # Equal to magic method
        return (self.priority) == (other.priority)
    def __gt__(self, other): # greater than magic method
        return (self.priority) > (other.priority)
    def __str__(self): # Print structure magic method
        return f'\tSender: {self.sender}\n\tSubject: {self.subject}\n\tDate: {self.date}'

        
