import re
files = open('input.txt', 'r')
inputs = files.readlines()

N = len(inputs)
IndexMap = dict()
Bag = []
Adj = [[] for i in range(N)]
RevAdj = [[] for i in range(N)]

def Preprocessing():
    # [Set index for each color bag]
    for i, s in enumerate(inputs):
        pos = s.find('bag')
        IndexMap[s[:pos-1]] = i
        Bag.append(s[:pos-1])
    
    
    # [Build Graph]
    # A contains x1 X1, x2 X2, x3 X3, ... xn Xn.
    # A --x1--> X1, ....
    for i, s in enumerate(inputs):
        s = s.replace('contain', '').replace('bags', '').replace('bag', '').replace('no other', '').replace(',', '').replace('.', '').replace('\n', '')
        relations = re.split('\s+', s)
        n = (len(relations) - 3) // 3
        for j in range(n):
            k = IndexMap[' '.join(relations[2+j*3+1:2+j*3+3])]
            Adj[i].append((k, int(relations[2 + j * 3])))
            RevAdj[k].append((i, int(relations[2 + j * 3])))

def DFS1(curr : int, visit : list):
    visit[curr] = True
    cnt = 1
    for edge in RevAdj[curr]:
        if not visit[edge[0]]:
            cnt += DFS1(edge[0], visit)
    return cnt

def Part1():
    visit = [False for i in range(N)]
    root = IndexMap['shiny gold']
    cnt = DFS1(root, visit)
    return cnt - 1

def DFS2(curr : int, n : int):
    cnt = n
    for edge in Adj[curr]:
        cnt += DFS2(edge[0], edge[1] * n)
    return cnt

def Part2():
    root = IndexMap['shiny gold']
    cnt = DFS2(root, 1)
    return cnt - 1

Preprocessing()
print('Part 1 : %d' % Part1())
print('Part 2 : %d' % Part2())