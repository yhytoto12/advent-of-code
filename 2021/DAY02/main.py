import numpy as np

with open('input.txt', 'r') as f:
    lines = f.readlines()

inputs = [line.split() for line in lines]

def Part1():
    pos, depth = 0, 0
    for cmd in inputs:
        if cmd[0] == 'forward':
            pos += int(cmd[1])
        elif cmd[0] == 'up':
            depth -= int(cmd[1])
        else:
            depth += int(cmd[1])
        # depth = max(0, depth)
    return pos * depth


def Part2():
    pos, depth, aim = 0, 0, 0
    for (cmd, X) in inputs:
        X = int(X)
        if cmd == 'forward':
            pos += X
            depth += aim * X
        elif cmd == 'up':
            aim -= X
        else:
            aim += X
    return pos * depth

print('Part1 :', Part1())
print('Part2 :', Part2())
