import os
import numpy as np

inputs = np.loadtxt('input.txt')

def Part1():
    ans = 0
    for idx in range(len(inputs)):
        if idx == 0:
            continue
        if inputs[idx] > inputs[idx - 1]:
            ans += 1
    return ans

def Part2():
    ans = 0
    prev_sum = inputs[0] + inputs[1] + inputs[2]
    for idx in range(3, len(inputs)):
        curr_sum = prev_sum + inputs[idx] - inputs[idx - 3]
        if curr_sum > prev_sum:
            ans += 1
        prev_sum = curr_sum
    return ans

print('Part1 :', Part1())
print('Part2 :', Part2())
