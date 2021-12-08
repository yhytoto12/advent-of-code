import numpy as np

with open('input.txt', 'r') as f:
    lines = f.readlines()

inputs = [[int(v) for v in line[:-1]] for line in lines]
inputs = np.array(inputs)
N, L = inputs.shape

def Part1():
    num_ones = np.zeros(L)
    for s in inputs:
        for j in range(L):
            if s[j] == 1:
                num_ones[j] += 1
    
    gamma, epsilon = 0, 0
    for j in range(L):
        if num_ones[j] < N // 2:
            epsilon += 2 ** (L - 1 - j)
        else:
            gamma += 2 ** (L - 1 - j)
    
    return gamma * epsilon

def RateO2():
    remains = np.copy(inputs)
    
    for i in range(L):
        one_mask = np.where(remains[:, i] == 1, True, False)
        num_ones = np.sum(one_mask)
        if num_ones < remains.shape[0] / 2:
            # bit -> zero
            remains = remains[~one_mask, :]
        else:
            remains = remains[one_mask, :]
        
        if remains.shape[0] == 1:
            break
    
    print(remains[0])
    ans = 0
    for i in range(L):
        ans += remains[0, i] * (2 ** (L - 1 - i))
    return ans
        
    
def RateCO2():
    remains = np.copy(inputs)
    
    for i in range(L):
        zero_mask = np.where(remains[:, i] == 0, True, False)
        num_zeros = np.sum(zero_mask)
        if num_zeros > remains.shape[0] / 2:
            # bit -> one
            remains = remains[~zero_mask, :]
        else:
            remains = remains[zero_mask, :]
        
        if remains.shape[0] == 1:
            break
    
    print(remains[0])
    ans = 0
    for i in range(L):
        ans += remains[0, i] * (2 ** (L - 1 - i))
    return ans

def Part2():
    return RateO2() * RateCO2()

print('Part1 :', Part1())
print('Part2 :', Part2())