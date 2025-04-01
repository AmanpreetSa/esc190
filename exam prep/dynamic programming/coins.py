import numpy as np

# Recursive: Starts at target and breaks down
# Tabulation: Starts at 0 and builds up

# minimal number of coins to make the target, using recursion
# the coins used to make that target

def num_coins_rec_memo(target, coins, memo=None):
    if memo is None:            # initalize memo on first call
        memo = {}
    
    if target in memo:          # check if already solved
        return memo[target]
    
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
    
    # store result in memo before returning
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
            if amount - d >= 0:         # If coin can be used
                if OPT[amount - d] + 1 < OPT[amount]:   # If using this coin gives a better solution
                    OPT[amount] = OPT[amount - d] + 1   # Update min coins needed
                    coins_used[amount] = coins_used[amount-d] + [d] # Update coins used
    
    if OPT[t] == np.inf:
        return -1, []  # No solution possible
    else:
        return int(OPT[t]), coins_used[t]


def canBeSegmented(s, wordDict):
    # if word in wordDict is an prefix of s and s[len(word):] can be segmented
    if s == "":
        return True
    for word in wordDict:
        if s.startswith(word):
            if canBeSegmented(s[len(word):], wordDict):
                return True
    return False
