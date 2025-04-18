import numpy as np
import heapq

class Node:
    def __init__(self, value):
        self.value = value
        self.connections = []
        self.distance_from_start = np.inf

class Con:
    def __init__(self, node, weight):
        self.node = node
        self.weight = weight

def dijkstra(start, end):
    start.distance_from_start = 0
    visited = set()
    to_be_considered = [(0, start)]
    
    while to_be_considered:
        cur_dist, current = heapq.heappop(to_be_considered)
        if current in visited:
            continue
        
        if current == end:
            return cur_dist
            
        visited.add(current)
        for con in current.connections:
            if con.node in visited:
                continue
            heapq.heappush(to_be_considered, (cur_dist + con.weight, con.node))
    
    return float('inf')  # No path found

# Create graph
yyz = Node("YYZ")
lax = Node("LAX")
yul = Node("YUL")
yyz.connections.append(Con(lax, 1000))
yyz.connections.append(Con(yul, 300))
lax.connections.append(Con(yul, 500))

# Run algorithm
print(dijkstra(yyz, yul))
