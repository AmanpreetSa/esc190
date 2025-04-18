#6
def is_winning_position(position):
    if position >= 21:
        return False
    moves = [1, 2, 3]
    for move in moves:
        next_position = position + move
        if next_position == 21:
            return True
        if not is_winning_position(next_position):  # the function checks if opponent can win form that position, if not, then you win
            return True
    return False

def find_best_move(position):
    winning_moves = []
    
    for move in [1, 2, 3]:
        next_position = position + move
        if next_position == 21 or not is_winning_position(next_position):
            winning_moves.append(move)
    
    if winning_moves != []:
        return min(winning_moves)


def is_winning_position_iterative(start_position):
    memo = {}

    for pos in range(21, 25):
        memo[pos] = (False, 0)
        
    stack = [(start_position, False)] # (position, have_we_expanded?)

    while stack:
        pos, expanded = stack.pop()

        if pos in memo:
            continue

        if not expanded:
            stack.append((pos, True))   
            moves = [1, 2, 3]
            for move in moves:
                child = pos + move
                if child not in memo:
                    stack.append((child, False))

        else:
            moves = [1, 2, 3]
            can_win = False
            winning_move = 0
            
            for move in moves:
                child = pos + move
                childIsWinning, _ = memo[child]
                if not childIsWinning:
                    can_win = True
                    winning_move = move
                    break
            
            memo[pos] = (can_win, winning_move)

    return memo[start_position], memo

#8
def canBeSegmented(s, wordDict, memo={}):
    if s in memo:
        return memo[s]
    
    if s == "":
        return True

    for word in wordDict:
        if s.startswith(word):
            if canBeSegmented(s[len(word):], wordDict, memo):
                memo[s] = True
                return True
    memo[s] = False
    return False

#9

class Node:
    def __init__(self, value):
        self.value = value
        self.left = None
        self.right = None
#a)
def make_tree():
    root = Node(1)
    root.left = Node(4)
    root.right = Node(5)
    root.right.left = Node(7)
    return root

#b)
def sum_tree(root):
    if root is None:
        return 0
    return root.val + sum_tree(root.left) + sum_tree(root.right)

def sum_tree_dfs(root):
    if root is None:
        return 0
    
    stack = [root]
    total = 0

    while stack:
        node = stack.pop()
        total += node.value

        if node.right:
            stack.append(node.right)
        if node.left:
            stack.append(node.left)

    return total




