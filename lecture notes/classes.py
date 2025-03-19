# a Python class is essentially like a struct in C
# there are fields 
# there are also methods and operators

class student:
    def __init__(self, name, grade): # initalizes
        self.name = name
        self.grade = grade
    def __lt__(self, other): # lt means less than, gt means greater than for comparisons
        return self.grade < other.grade
    def __repr__(self): # repr returns a string that represents the object
        return self.name + " " + str(self.grade)
    
bob = student("Bob", 52)
charlie = student("Charlie", 50)
david = student("David", 100)

# student.__lt__(bob, charlie) # False
# another way to call __lt__
print(bob < charlie) # calls student.__lt__ with self being bob, and other being charlie

print(sorted([david, bob, charlie]))

class Queue:
    def __init_(self):
        self.array = []
    def enqueue(self, item):
        self.array.append(item)
    def dequeue(self, item):
        ret = self.array[0]
        del self.array[0]
        return ret

if __name__ == "__main__":
    q = Queue()
    #Queue.enqueue(q, 5)
    #q.enqueue(5) # same as Queue.enqueue(q, 5)
    
    s = student("Bob", 52) # essentially: s.name = "Bob"; s.age = 52
    print(s.name, s.grade)