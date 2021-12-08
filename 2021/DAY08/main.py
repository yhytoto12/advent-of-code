import numpy as np

with open('input.txt', 'r') as f:
    lines = f.readlines()
    lines = [line[:-1].split() for line in lines]
    references = [line[:10] for line in lines]
    targets = [line[-4:] for line in lines]
    
def Part1():
    cnt = 0
    for refs, tgts in zip(references, targets):
        refs = [sorted(v) for v in refs]
        tgts = [sorted(v) for v in tgts]
        
        for tgt in tgts:
            if tgt in refs and \
                (len(tgt) == 2 or len(tgt) == 3 or len(tgt) == 4 or len(tgt) == 7):
                cnt += 1
    return cnt

def set2binary(s):
    ans = 0
    for v in s:
        ans += 1 << v
    return ans

segments = {
    set2binary({0, 1, 2, 4, 5, 6}) : 0,
    set2binary({2, 5}) : 1,
    set2binary({0, 2, 3, 4, 6}) : 2,
    set2binary({0, 2, 3, 5, 6}) : 3,
    set2binary({1, 2, 3, 5}) : 4,
    set2binary({0, 1, 3, 5, 6}) : 5,
    set2binary({0, 1, 3, 4, 5, 6}) : 6,
    set2binary({0, 2, 5}) : 7,
    set2binary({0, 1, 2, 3, 4, 5, 6}) : 8,
    set2binary({0, 1, 2, 3, 5, 6}) : 9,
}

def Part2():
    ans = 0
    for idx, (refs, tgts) in enumerate(zip(references, targets)):
        refs = [sorted(v) for v in refs]
        refs = sorted(refs, key=lambda x : len(x))
        tgts = [sorted(v) for v in tgts]
        
        seg_maps = dict()
        maps = dict()
        
        nums = dict()
        for ref in refs:
            for c in ref:
                nums[c] = nums.get(c, 0) + 1
        
        # print('Line ', idx)
        # print(refs)
        # print(nums)
        
        seg_maps[0] = [v for v in refs[1] if v not in refs[0]][0]
        S13 = [v for v in refs[2] if v not in refs[0]]
        # print('S13', S13)
        seg_maps[1] = [v for v in S13 if nums[v] == 6][0]
        seg_maps[3] = [v for v in S13 if nums[v] == 7][0]
        S25 = [v for v in refs[0]]
        # print('S25', S25)
        seg_maps[2] = [v for v in S25 if nums[v] == 8][0]
        seg_maps[5] = [v for v in S25 if nums[v] == 9][0]
        S46 = [v for v in refs[-1] if v not in refs[1] and v not in refs[2]]
        # print('S46', S46)
        seg_maps[4] = [v for v in S46 if nums[v] == 4][0]
        seg_maps[6] = [v for v in S46 if nums[v] == 7][0]
                
        maps = {v : k for k, v in seg_maps.items()}
        
        for i, tgt in enumerate(tgts):
            ans += 10 ** (3 - i) * segments[set2binary({maps[v] for v in tgt})]

    return ans

print(Part1())
print(Part2())