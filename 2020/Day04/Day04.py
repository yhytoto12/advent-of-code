files = open('input.txt', 'r')
inputs = files.read()
passports = inputs.split('\n\n')

require_field = ['byr', 'iyr', 'eyr', 'hgt', 'hcl', 'ecl', 'pid']
optional = 'cid'

def Part1():
    # count valid passport
    cnt = 0
    for p in passports:
        fcnt = 0
        for field in require_field:
            if (p.find(field) != -1):
                fcnt += 1
        if (fcnt == 7):
            cnt += 1
    return cnt

def IsVaild(field : str, value : str):
    if (field == 'byr'):
        try:
            if (len(value) != 4): return False
            v = int(value)
            if (v < 1920 or v > 2002): return False
            return True
        except:
            return False
    if (field == 'iyr'):
        try:
            if (len(value) != 4): return False
            v = int(value)
            if (v < 2010 or v > 2020): return False
            return True
        except:
            return False
    if (field == 'eyr'):
        try:
            if (len(value) != 4): return False
            v = int(value)
            if (v < 2020 or v > 2030): return False
            return True
        except:
            return False
    if (field == 'hgt'):
        try:
            if (value[-2:] == 'cm'):
                v = int(value[:-2])
                if (v < 150 or v > 193): return False
                return True
            elif (value[-2:] == 'in'):
                v = int(value[:-2])
                if (v < 59 or v > 76): return False
                return True
            else:
                return False
        except:
            return False
    if (field == 'hcl'):
        if (value[0] != '#'): return False
        if (len(value) != 7): return False
        for c in value[1:]:
            if (not((c >= '0' and c <= '9') or (c >= 'a' and c <= 'f'))):
                return False
        return True
    if (field == 'ecl'):
        if (value == 'amb' or value == 'blu' or value == 'brn' or value == 'gry' or
            value == 'grn' or value == 'hzl' or value == 'oth'): return True
        return False
    if (field == 'pid'):
        if (len(value) != 9): return False
        for c in value:
            if (not(c >= '0' and c <= '9')): return False
        return True
    return True

def Part2():
    cnt = 0
    for p in passports:
        fcnt = 0
        l = len(p)
        for field in require_field:
            if (p.find(field) == -1):
                break
            pos_s = p.find(field)
            pos_e = pos_s + 4
            while (pos_e < l and p[pos_e] != '\n' and p[pos_e] != ' '):
                pos_e += 1
            if (IsVaild(p[pos_s:pos_s+3], p[pos_s+4:pos_e])):
                fcnt += 1

        if (fcnt == 7):
            cnt += 1


    return cnt

print('Part 1 : %d' % Part1())
print('Part 2 : %d' % Part2())