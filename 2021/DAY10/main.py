import numpy as np

with open('input.txt', 'r') as f:
    lines = f.readlines()
    lines = [line[:-1] for line in lines]

score_map_1 = { ')' : 3, ']' : 57, '}' : 1197, '>' : 25137 }
opens = ['(', '[', '{', '<']
closes = [')', ']', '}', '>']
match = {'(' : ')', '[' : ']', '{' : '}', '<' : '>'}

def Part1():
    score = 0
    for line in lines:
        stack = []
        for v in line:
            if len(stack) == 0 or v in opens:
                stack.append(v)
            else:
                if match[stack[-1]] == v:
                    stack.pop()
                else:
                    # corrupted
                    # print('Error Expected {}, but found {} instead'.format(match[stack[-1]], v))
                    score += score_map_1[v]
                    break
    return score

score_map_2 = { ')' : 1, ']' : 2, '}' : 3, '>' : 4 }            

def Part2():
    scores = []
    for i, line in enumerate(lines):
        stack = []
        corrupted = False
        for v in line:
            if len(stack) == 0 or v in opens:
                stack.append(v)
            else:
                if match[stack[-1]] == v:
                    stack.pop()
                else:
                    corrupted = True
                    break
                
        if not corrupted:
            score = 0
            while len(stack) > 0:
                score *= 5
                score += score_map_2[match[stack[-1]]]
                stack.pop()
                
            scores.append(score)
        
    
    scores = sorted(scores)
    return scores[len(scores) // 2]
    

print('Part1 :', Part1())    
print('Part2 :', Part2())    