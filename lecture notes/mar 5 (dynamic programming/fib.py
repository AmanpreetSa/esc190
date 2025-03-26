# Dynamic Programming: outline

# Divide a complex problem into a number of simpler overlapping problems
# Define a relationship between solutions to more complex problems and solutions to simpler problems
# Store solutions to each subproblem, solving each subproblem once
# Use stored solutions to solve the original problem

# -------------------------------------------------------------------------------------

# 0, 1, 1, 2, 3, 5, 8, 13
# fib(n) = fib(n-1) + fib(n-2)
# Tabulation method (storing in arrays)

def fib_iter(n):
    fib_list = [0] * (n+1) 
    fib_list[0:2] = [0, 1] 
    for i in range(2, n+1):
        fib_list[i] = fib_list[i-1] + fib_list[i-2]
    return fib_list[n]
# O(n) because we have to compute n entries in a list using a for loop
# subproblems: compute fib_list[:i] for i = 0, 1, 2, 3, .., k, ..., n

# create list full of 0s (if n = 5, then fib_list is [0, 0, 0, 0, 0, 0])
# replace first two elements with 0 and 1 (exclusive of 2), then fib_list is [0, 1, 0, 0, 0, 0]
# start for loop at index 2 (b/c first two indices have been initalized) and goes to n inclusive
# fib_list[i] = fib_list[i-1] + fib_list[i-2]: process for calculating fib sequence
# fib_list[n] returns fib sequence at n value (goes until n entries so O(n))


# Memoization recursive approach
def fib(n, mem = {}):
    if n in mem:
        return mem[n]
    if n <= 1:
        return n
    mem[n] = fib(n-1, mem) + fib(n-2, mem)
    return mem[n]

print(fib(6))

#fib(1)
#    \
#    ....
#
#        fib(n-3)       fib(n-4)
#                \      / /
#                fib(n-2)       fib(n-3)
#                        \     / /
#                        fib(n-1)     fib(n-2)
#                            \      / /
#                              fib(n)

# How many call to fib are there if we start with fib(n)?
# n levels, one call "to the right" from every level
# 2n - 1 calls (the -1 is because no calls to the left from fib(1))
# Complexity: O(n) sinc each call takes the same amount of time (approx)

# In other words:
# Only compute each entry in mem once
# fib(n-1) + fib(n-2) does not produce internal calls to fib
# Compute n enteries in mem, each taking constant time: O(n)
