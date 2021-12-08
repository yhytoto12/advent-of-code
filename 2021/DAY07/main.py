import numpy as np

with open('input.txt', 'r') as f:
    inputs = f.read().split(',')
    poses = np.asarray([int(v) for v in inputs], dtype=int)
    
# 0 1 1 2 2 2 4 7 14 16

def Part1():
    sorted_poses = np.sort(poses)
    x = sorted_poses[poses.shape[0] // 2]
    return np.sum(np.abs(sorted_poses - x))

def Part2():
    sorted_poses = np.sort(poses)
    ans = None
    for x in range(sorted_poses[0], sorted_poses[-1] + 1):
        d = np.sum(np.abs(sorted_poses - x) * (np.abs(sorted_poses - x) + 1)) // 2
        if ans is None:
            ans = d
        else:
            ans = min(ans, d)
    return ans

print(Part1())
print(Part2())    