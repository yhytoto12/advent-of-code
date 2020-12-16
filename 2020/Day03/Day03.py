files = open('input.txt', 'r')
inputs = files.readlines()
N = len(inputs)
M = len(inputs[0]) - 1

def Part1():
    x = 0
    cnt = 0
    for y in range(N):
        if (inputs[y][x] == '#'):
            cnt += 1
        x = (x + 3) % M
    return cnt

def Part2():
    ans = 1
    for slope in [(1, 1), (3, 1), (5, 1), (7, 1), (1, 2)]:
        cnt = 0
        x = y = 0
        while (y < N):
            if (inputs[y][x] == '#'):
                cnt += 1
            x = (x + slope[0]) % M
            y += slope[1]
        ans *= cnt
    return ans

print('Part 1 : %d' % Part1())
print('Part 2 : %d' % Part2())