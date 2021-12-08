import numpy as np
from numpy.core.numeric import indices

board_size = 5

with open('input.txt', 'r') as f:
    orders = f.readline()
    orders = [int(v) for v in orders[:-1].split(',')]
    
    lines = f.readlines()
    lines = list(filter(lambda x : x[0] != '\n', lines))
    n_boards = len(lines) // board_size
    boards = [[int(v) for v in line[:-1].split()] for line in lines]
    
    boards = np.asarray(boards).reshape(n_boards, board_size, board_size)

def Part1():
    idx = -1
    boards_check = np.full_like(boards, False, dtype=bool)
    for v in orders:
        boards_check |= np.where(boards == v, True, False)
        for i in range(n_boards):
            for j in range(board_size):
                if np.sum(boards_check[i, j, :]) == board_size or \
                   np.sum(boards_check[i, :, j]) == board_size:
                    idx = i
        if idx != -1:
            return v * np.sum(boards[idx, ~boards_check[idx, :, :]])

    return 0
    
def Part2():
    remains = { i for i in range(n_boards) }
    ans = -1, -1, -1
    boards_check = np.full_like(boards, False, dtype=bool)
    for v in orders:
        boards_check |= np.where(boards == v, True, False)
        idx = set()
        for i in remains:
            for j in range(board_size):
                if np.sum(boards_check[i, j, :]) == board_size or \
                   np.sum(boards_check[i, :, j]) == board_size:
                   idx.add(i) 
        
        if len(idx) > 0:
            for i in idx:
                ans = v * np.sum(boards[i, ~boards_check[i, :, :]])
            remains = remains - idx
    return ans

print('Part1 :', Part1())
print('Part2 :', Part2())
    