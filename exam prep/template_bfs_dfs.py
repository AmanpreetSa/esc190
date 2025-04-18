class Node:
    def __init__(self, data):
        self.data = data
        self.neighbours = []

class Graph:
    def __init__(self):
        self.nodes = []
        
    def add_node(self, data):
        node = Node(data)
        self.nodes.append(node)
        return node
        
    def add_edge(self, node1, node2):
        node1.neighbours.append(node2)

def bfs(graph, start_name):
    # 1. SETUP - Find start node
    start_node = None
    for node in graph.nodes:
        if node.data == start_name:
            start_node = node
            break
    
    if not start_node:
        return "Start node not found"
    
    # 2. INITIALIZE - Create data structures
    visited = set([start_node])
    queue = [start_node]
    result = []  # Store results if needed
    
    # 3. BFS CORE ALGORITHM
    while queue:
        node = queue.pop(0)  # Get next node (FIFO)
        
        # *** PROCESS STEP - CUSTOMIZE THIS PART ***
        result.append(node.data)  # Example: collect nodes
        print(node.data)  # Example: print node
        # If looking for a specific node:
        # if node.data == target: return "Found at position " + str(len(result))
        # *** END PROCESS STEP ***
        
        # Add unvisited neighbors to queue
        for neighbor in node.neighbours:
            if neighbor not in visited:
                visited.add(neighbor)
                queue.append(neighbor)
    
    return result  # Return whatever result you need

def dfs_iterative(graph, start_name):
    # 1. SETUP - Find start node
    start_node = None
    for node in graph.nodes:
        if node.data == start_name:
            start_node = node
            break
    
    if not start_node:
        return "Start node not found"
    
    # 2. INITIALIZE - Create data structures
    visited = set()
    stack = [start_node]
    result = []
    
    # 3. DFS CORE ALGORITHM
    while stack:
        node = stack.pop()  # Get next node (LIFO)
        
        if node not in visited:
            visited.add(node)
            
            # *** PROCESS STEP - CUSTOMIZE THIS PART ***
            result.append(node.data)  # Example: collect nodes
            print(node.data)  # Example: print node
            # *** END PROCESS STEP ***
            
            # Add unvisited neighbors to stack (in reverse to maintain order)
            for neighbor in reversed(node.neighbours):
                if neighbor not in visited:
                    stack.append(neighbor)
    
    return result


def dfs_recursive(graph, start_name):
    # 1. SETUP - Find start node
    start_node = None
    for node in graph.nodes:
        if node.data == start_name:
            start_node = node
            break
    
    if not start_node:
        return "Start node not found"
    
    visited = set()
    result = []
    
    # 2. RECURSIVE HELPER
    def dfs_helper(node):
        if node in visited:
            return
        
        visited.add(node)
        
        # *** PROCESS STEP - CUSTOMIZE THIS PART ***
        result.append(node.data)  # Example: collect nodes
        print(node.data)  # Example: print node
        # *** END PROCESS STEP ***
        
        for neighbor in node.neighbours:
            dfs_helper(neighbor)
    
    # 3. START RECURSION
    dfs_helper(start_node)
    return result

