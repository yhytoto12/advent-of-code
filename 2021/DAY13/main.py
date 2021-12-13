import numpy as np
import copy

with open('input.txt', 'r') as f:
    lines = f.readlines()
    data = [line[:-1] for line in lines]
    idx = data.index('')
    Dots = [[int(v) for v in line.split(',')] for line in data[:idx]]
    Folds = [(line[11], int(line[13:])) for line in data[idx+1:]]

def folded_x(x, y, base):
    if x < base:
        return x, y
    elif x == base:
        return -1, -1
    else:
        return 2 * base - x, y
    
def folded_y(x, y, base):
    if y < base:
        return x, y
    elif y == base:
        return -1, -1
    else:
        return x, 2 * base - y

def Part1():
    dots = copy.deepcopy(Dots)
    for fold in Folds[0:1]:
        if fold[0] == 'x':
            dots = [folded_x(*dot, fold[1]) for dot in dots]
        if fold[0] == 'y':
            dots = [folded_y(*dot, fold[1]) for dot in dots]
        
        dots = list(filter(lambda x : x[0] != -1, dots))
        dots = list(dict.fromkeys(dots))
        
    return len(dots)

def Part2():
    dots = copy.deepcopy(Dots)
    for fold in Folds:
        if fold[0] == 'x':
            dots = [folded_x(*dot, fold[1]) for dot in dots]
        if fold[0] == 'y':
            dots = [folded_y(*dot, fold[1]) for dot in dots]
        
        dots = list(filter(lambda x : x[0] != -1, dots))
        dots = list(dict.fromkeys(dots))
    
    max_x, max_y = max(dots)
    paper = np.zeros((max_y + 1, max_x + 1), dtype=int)
    for dot in dots:
        paper[dot[1], dot[0]] = 1
    for y in range(max_y + 1):
        for x in range(max_x + 1):
            print('#' if paper[y, x] == 1 else '.', end='')
        print()
    return 0
    
print('Part1 :', Part1())
print('Part2 :', Part2())