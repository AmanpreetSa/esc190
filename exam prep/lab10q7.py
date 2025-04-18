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

def dfs(graph, start_name):
    start_node = None
    for node in graph.nodes:
        if node.data == start_name:
            start_node = node
            break

    visited = set([start_node])    
    stack = [start_node]
    traversal = []

    while stack:
        node = stack.pop()
        traversal.append(node.data)

        for neighbour in node.neighbours:
            if neighbour not in visited:
                visited.add(neighbour)
                stack.append(neighbour)

    return traversal


def bfs(graph, start_name):
    start_node = None
    for node in graph.nodes:
        if node.data == start_name:
            start_node = node
            break

    visited = set([start_node])
    queue = [start_node]
    traversal = [] 

    while queue:
        node = queue.pop(0)
        traversal.append(node.data)

        for neighbour in node.neighbours:
            if neighbour not in visited:
                visited.add(neighbour)
                queue.append(neighbour)
    
    return traversal


def position(graph, start_name, target_name):
    order = bfs(graph, start_name) # or dfs ig
    if target_name in order:
        return order.index(target_name) + 1
    return -1














def dfs_recursive(graph, start, visited=None, result=None):
    # First-call initialization
    if visited is None:
        visited = set()
        result = []
        # Find the node if we got a string
        if isinstance(start, str):
            for node in graph.nodes:
                if node.data == start:
                    start = node
                    break
            else:  # Node not found
                return []
    
    # Skip if already visited
    if start in visited:
        return result
    
    # Mark as visited and process
    visited.add(start)
    result.append(start.data)
    print(start.data)  # Process step
    
    # Visit all neighbors
    for neighbor in start.neighbours:
        dfs_recursive(graph, neighbor, visited, result)
    
    return result