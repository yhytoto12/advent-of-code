files = open('input.txt', 'r')
inputs = files.readlines()

class PWFormant:
    def __init__(self, s : str):
        p1 = s.find('-')
        p2 = s.find(' ')
        p3 = s.find(':')
        self.L = int(s[:p1])
        self.R = int(s[p1+1:p2])
        self.Letter = s[p2+1:p3]
        self.Password = s[p3+2:]
    
pw_list = [PWFormant(s) for s in inputs]

def Part1():
    # number of valid passwords
    cnt = 0
    for pw in pw_list:
        icnt = pw.Password.count(pw.Letter)
        if (icnt >= pw.L and icnt <= pw.R):
            cnt += 1
    return cnt

def Part2():
    # number of valid passwords
    cnt = 0
    for pw in pw_list:
        icnt = 0
        if (pw.Password[pw.L - 1] == pw.Letter): icnt += 1
        if (pw.Password[pw.R - 1] == pw.Letter): icnt += 1
        if (icnt == 1): cnt += 1
    return cnt


print('Part 1 : %d' % Part1())
print('Part 2 : %d' % Part2())