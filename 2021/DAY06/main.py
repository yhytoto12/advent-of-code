import numpy as np

with open('input.txt', 'r') as f:
    inputs = f.read().split(',')
    init_state = np.asarray([int(v) for v in inputs], dtype=int)
    
def Part1():
    state_cnt = np.zeros(9, dtype=int)
    for s in init_state:
        state_cnt[s] += 1
    
    for day in range(1, 80 + 1):
        zeros = state_cnt[0]
        state_cnt = np.roll(state_cnt, -1)
        state_cnt[6] += zeros
        
    return np.sum(state_cnt)

def Part2():
    state_cnt = np.zeros(9, dtype=int)
    for s in init_state:
        state_cnt[s] += 1
    
    for day in range(1, 256 + 1):
        zeros = state_cnt[0]
        state_cnt = np.roll(state_cnt, -1)
        state_cnt[6] += zeros
        
    return np.sum(state_cnt)

print(Part1())
print(Part2())