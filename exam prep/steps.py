# Q9 Exam

def steps(cost):
    n = len(cost)

    # set up strutures to store out information - 1D list for min cost to get to a particular step
    opt = [0] * n
    steps = [0] * n

    # set up the first couple of steps
    opt[0] = cost[0]
    steps[1] = 1
    opt[1] = opt[0] + cost[1]
    opt[2] = min(opt[1] + cost[2], opt[0], cost[2])

    if opt[2] == opt[1] + cost[2]:
        steps[2] = 1
    else:
        steps[2] = 2

    # find the min cost to get to subsequent steps in the staircase
    for i in range(3, n):
        options = [opt[i-1] + cost[i], opt[i-2] + cost[i], opt[i-3] + cost[i]]
        opt[i] = min(options)
        steps[i] = options.index(opt[i]) + 1    # index will be off by 1, so add 1


    # work our way back through the staircase to get the least-cost plan
    full_path = []
    i = n - 1
    while i>=0:
        full_path = [steps[i]] + full_path
        i -= steps[i]

    return full_path


# try coding this recursively as well, HAVE to have memoziation as well



# Question like this graded:
# 10 points:
# 6 marks for clearly showing dynamic programming: 2 pts setup and base case, 2 pts for entire solution  