import numpy as np
import re

with open('input.txt', 'r') as f:
    lines = f.readlines()
    Lines = [[int(v) for v in re.split(',| -> ', line[:-1])] for line in lines]
    Lines = np.asarray(Lines, dtype=int)
    
def Part1():
    x_min, x_max = np.min(Lines[:, 0::2]), np.max(Lines[:, 0::2])
    y_min, y_max = np.min(Lines[:, 1::2]), np.max(Lines[:, 1::2])
    A = np.zeros((x_max + 1, y_max + 1), dtype=int)
    for i in range(Lines.shape[0]):
        # x1 <= x2, y1 <= y2
        x1, x2 = min(Lines[i, 0], Lines[i, 2]), max(Lines[i, 0], Lines[i, 2])
        y1, y2 = min(Lines[i, 1], Lines[i, 3]), max(Lines[i, 1], Lines[i, 3])
        if x1 == x2:
            A[x1, y1:y2+1] += 1
        elif y1 == y2:
            A[x1:x2+1, y1] += 1
    
    return np.count_nonzero(np.where(A >= 2, 1, 0))
    
def Part2():
    x_min, x_max = np.min(Lines[:, 0::2]), np.max(Lines[:, 0::2])
    y_min, y_max = np.min(Lines[:, 1::2]), np.max(Lines[:, 1::2])
    A = np.zeros((x_max + 1, y_max + 1), dtype=int)
    for i in range(Lines.shape[0]):
        # x1 <= x2, y1 <= y2
        x1, x2 = min(Lines[i, 0], Lines[i, 2]), max(Lines[i, 0], Lines[i, 2])
        y1, y2 = min(Lines[i, 1], Lines[i, 3]), max(Lines[i, 1], Lines[i, 3])
        if x1 == x2:
            A[x1, y1:y2+1] += 1
        elif y1 == y2:
            A[x1:x2+1, y1] += 1
        elif x2 - x1 == y2 - y1:
            if Lines[i, 0] - Lines[i, 2] == Lines[i, 1] - Lines[i, 3]:
                x = range(x1, x2 + 1)
                y = range(y1, y2 + 1)
                for _x, _y in zip(x, y):
                    A[_x, _y] += 1
            else:
                x = range(x1, x2 + 1)
                y = reversed(range(y1, y2 + 1))
                for _x, _y in zip(x, y):
                    A[_x, _y] += 1
    
    print(A)
    return np.count_nonzero(np.where(A >= 2, 1, 0))

print('Part1 :', Part1())
print('Part2 :', Part2())