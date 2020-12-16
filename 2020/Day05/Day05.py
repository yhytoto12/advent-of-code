files = open('input.txt', 'r')
inputs = files.readlines()

def Part1():
    max_id = -1
    for s in inputs:
        row = 0
        col = 0
        for i in range(7):
            if (s[i] == 'B'):
                row += (1 << (6 - i))
        for i in range(3):
            if (s[i + 7] == 'R'):
                col += (1 << (2 - i))
        max_id = max(max_id, row * 8 + col)
    return max_id

def Part2():
    IDs = []
    max_id = -1
    for s in inputs:
        row = 0
        col = 0
        for i in range(7):
            if (s[i] == 'B'):
                row += (1 << (6 - i))
        for i in range(3):
            if (s[i + 7] == 'R'):
                col += (1 << (2 - i))
        max_id = max(max_id, row * 8 + col)
        IDs.append(row * 8 + col)
    for i in range(max_id):
        if (i not in IDs):
            print(i)
    return max_id

print('Part 1 : %d' % Part1())
print('Part 2 : %d' % Part2())