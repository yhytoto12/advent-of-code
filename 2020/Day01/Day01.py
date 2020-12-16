import os

files = open('input.txt', 'r')
inputs = files.readlines()
A = [int(i) for i in inputs]
N = len(A)

def Part1():
    ans = -1
    for i in range(N):
        for j in range(i + 1, N):
            if (A[i] + A[j] == 2020):
                ans = A[i] * A[j]
    return ans

def Part2():
    ans = -1
    for i in range(N):
        for j in range(i + 1, N):
            for k in range(j + 1, N):
                if (A[i] + A[j] + A[k] == 2020):
                    ans = A[i] * A[j] * A[k]
    return ans


print('Part 1 : %d' % Part1())
print('Part 2 : %d' % Part2())