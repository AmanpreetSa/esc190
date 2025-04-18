#6 
class PQ:
    def __init__(self):
        self.queue = []

    def insert(self, data, priority):
        self.queue.append((data, priority))

    def extract_min(self):
        min_index = 0
        for i in range(len(self.queue)):
            if self.queue[i][1] < self.queue[min_index][1]:
                min_index = i
        return self.queue.pop(min_index)[0]

#7
class MyList(list):
    def __init__(self, data):
        self.data = data

    def average(self):
        if not self.data:
            return 0
        
        count = 0
        sum = 0
        for num in self.data:
            sum += num
            count += 1
        return int(sum/count)
    
    def __lt__(self, other):
        return self.average() < other.average()
    
    def __repr__(self):
        return str(self.average())
    
#9
def steps(cost):
    n = len(cost)

    dp = [0] * n
    steps = [0] * n
    
    dp[0] = cost[0]
    dp[1] = dp[0] + cost[1]
    steps[1] = 1
    dp[2] = min(dp[0] + cost[2], dp[1] + cost[2])

    if dp[2] == (dp[1] + cost[2]):
        steps[2] = 1
    else:
        steps[2] = 2

    # find thet min cost to get to subsequent steps in the staircase
    for i in range(3, n):
        options = [dp[i-1] + cost[i], dp[i-2] + cost[i], dp[i-3] + cost[i]]
        dp[i] = min(options)
        steps[i] = options.index(dp[i]) + 1     # index will be off by 1, so add 1

    full_path = []
    i = n-1
    while i >=0:
        full_path.append(steps[i])
        i -= steps[i]

    return full_path[::-1]

#10:

#use dfs
def longest_friendship_chain(friends):
    max_chain_length = 0

    for person in friends:
        # stack will hold tuples: (current_person, path_so_far_as_set, length)
        stack = [(person, set([person]), 1)]

        while stack:
            current, visited, length = stack.pop()
            max_chain_length = max(max_chain_length, length)

            for neighbour in friends[current]:
                if neighbour not in visited:
                    new_visited = visited.copy()
                    new_visited.add(neighbour)
                    stack.append(neighbour, new_visited, length + 1)

    return max_chain_length


