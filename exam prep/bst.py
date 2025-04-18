# BST

# Here is how you construct the tree:

class Node:
    def __init__(self, val):
        self.val = val    # Store the value in val (to match in_tree)
        self.left = None  # Left child reference 
        self.right = None # Right child reference

def make_tree():
    root = Node(X)
    root.left = Node(X)

    # etc....
    return root

# looking up whether an element is within the BST or not

def in_tree(root, elem):
    if root is None:
        return False
    
    if root.val == elem:
        return True
    
    if root.val < elem:
        return in_tree(root.right, elem)
    else:
        return in_tree(root.left, elem)

# get the name that corresponds to the key
# assume that root is the root of a BST
# same algorithm as before

def make_tree():
    root = Node((3, "alice"))
    root.left = Node((2, "Bob"))
    root.right = Node((5, "as"))
    root.left.left = Node((0, 'dave'))
    root.right.right = Node((2.5, "Eve"))


def get_val(key, root):
    if root is None:
        return False
    
    if key == root.val[0]:
        return root.val[1]
    
    if key < root.val[0]:
        return get_val(key, root.left)
    else:
        return get_val(key, root.right)
    
# implement dictionaries (tuples) with O(logn) retrieval
# assuming we can make a balanced bst using the keys