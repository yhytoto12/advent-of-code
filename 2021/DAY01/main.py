import os
import numpy as np

inputs = np.load('input.txt', type=int)

def Part1():
    ans = 0
    for idx in range(len(inputs)):
        if idx == 0:
            continue
        if inputs[idx] > inputs[idx - 1]:
            ans += 1
    return ans

def Part2():
    pass


print('Part1 : ', Part1())
print('Part2 : ', Part2())