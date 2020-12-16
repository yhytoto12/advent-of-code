files = open('input.txt', 'r')
inputs = files.read()
groups = inputs.split('\n\n')
# for i, g in enumerate(groups):
#     print('========== Group %d ==========' % i)
#     print(g)

def Part1():
    ans = 0
    for g in groups:
        questions = [0 for i in range(26)]
        members = g.split('\n')
        for m in members:
            for c in m:
                if c >= 'a' and c <= 'z':
                    questions[ord(c) - ord('a')] += 1
        for cnt in questions:
            if (cnt > 0):
                ans += 1
    return ans

def Part2():
    ans = 0
    for g in groups:
        questions = [0 for i in range(26)]
        members = g.split('\n')
        for m in members:
            for c in m:
                if c >= 'a' and c <= 'z':
                    questions[ord(c) - ord('a')] += 1
        for cnt in questions:
            if (cnt == len(members)):
                ans += 1
    return ans

print('Part 1 : %d' % Part1())
print('Part 2 : %d' % Part2())