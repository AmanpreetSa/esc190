import numpy as np

# we have 1c, 4c, 5c
# target: 8c
# Want: the smallest number of coins that make up the target

# OPT(i): the smallest number of coins that make up the target i
# if use 1c, OPT(i) = OPT(i-1) + 1
# if use 4c, OPT(i) = OPT(i-4) + 1
# if use 5c, OPT(i) = OPT(i-5) + 1
# OPT(i) = min(OPT(i-1), OPT(i-4), OPT(i-5)) + 1

def least_num_coins_rec(target, coins):
    if target == 0:
        return 0, []
    if target < 0:
        return float('inf'), []
    coin_used = None 
    coins_used = []
    min_coins = float('inf')

    for coin in coins:
        num_coins_req, cur_coins = least_num_coins_rec(target - coin, coins)
        num_coins_req += 1
        if num_coins_req < min_coins:
            min_coins = num_coins_req
            coins_used = cur_coins
            coin_used = coin
    return min_coins, coins_used + [coin_used]




def num_coins_rec_memo(target, coins, memo=None):
    # Initialize memo dictionary on first call
    if memo is None:
        memo = {}
    
    # Check if we've already solved this problem
    if target in memo:
        return memo[target]
    
    # Base cases remain the same
    if target == 0:
        return 0, []
    if target < 0:
        return float('inf'), []
        
    min_coins = float('inf')
    coins_used = []
    coin_used = None
    
    for coin in coins:
        num_reqd, current_coins = num_coins_rec_memo(target - coin, coins, memo)
        num_reqd += 1
        if num_reqd < min_coins:
            min_coins = num_reqd
            coin_used = coin
            coins_used = current_coins
    
    # Store result in memo before returning
    result = (min_coins, coins_used + [coin_used])
    memo[target] = result
    return result




def making_change(t, denominations):
    OPT = np.inf * np.ones(t+1)  # initializing the array w/ infinity values
    OPT[0] = 0  # base case: at 0 target, then 0 denomination
    
    # If we want to track which coins were used
    coins_used = [[] for _ in range(t+1)]
    
    for amount in range(1, t + 1):
        for d in denominations: 
            if amount - d >= 0:                                 # if denomination is less than or equal to amount
                if OPT[amount - d] + 1 < OPT[amount]:           # best possible way to make this amount
                    OPT[amount] = OPT[amount - d] + 1  
                    coins_used[amount] = coins_used[amount-d] + [d]
    
    if OPT[t] == np.inf:
        return -1, []  # No solution possible
    else:
        return int(OPT[t]), coins_used[t]




# smae idea as coins: take away one word from the wordDict
# check new string:
# can another word in wordDict take out a segment of S
# yes: do it, if not: then whole string is invalidated

# if word in wordDict is an prefix of S
# and s[len(word):] can be segmented, return True

def canBeSegmented(s, wordDict):
    if s == "":
        return True
    for word in wordDict:
        if s.startswith(word):
            if canBeSegmented(s[len(word):], wordDict):
                return True
    return False

