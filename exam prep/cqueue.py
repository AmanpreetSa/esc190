# Stack (LIFO): 
    # push (adds items to the end of array)
    # pop (removes items from end of the array)
# Queue (FIFO): Enqueue to end of the array, dequeue from start of array
# Ciricular Queue: two pointers
    # front: points to current front element
    # rear: points to next free position

class Stack: 
    def __init__(self):
        self.data = []
    
    def push(self, item):
        self.data.append(item)

    def pop(self):
        return self.data.pop()

class Queue:
    def __init__(self):
        self.data = []

    def enqueue(self, item):
        self.data.append(item)
    
    def dequeue(self):
        return self.data.pop(0)


class CircularQueue:
    def __init__(self, size):
        self.data = [None] * size
        self.size = size
        self.start = 0
        self.end = 0
        self.num_elements = 0

    def enqueue(self, value):
        if self.num_elements == self.size:
            return None
        
        self.data[self.end] = value
        self.end = (self.end + 1) % self.size
        self.num_elements += 1

    def dequeue(self):
        if self.num_elements == 0:
            return None

        value = self.data[self.start]
        self.start = (self.start + 1) % self.size
        self.num_elements -= 1
        return value

    def to_list(self):
        res = []
        i = self.start
        count = 0
        while count < self.num_elements:
            res.append(self.data[i])
            i = (i + 1) % self.size
            count += 1
        return res
    
    def __repr__(self):
        return str(self.to_list())
    
    # compar less than
    def __lt__(self, other):
        L1 = self.to_list()
        L2 = other.to_list()
        return L1 < L2

