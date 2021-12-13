import numpy as np

with open('input.txt', 'r') as f:
    data = f.readlines()
    data = [[int(v) for v in row[:-1]] for row in data]
    height = np.asarray(data)
    n_row, n_col = height.shape
    
ADJ = [(-1, 0), (0, 1), (1, 0), (0, -1)]

def Part1():
    ans = 0
    for r in range(n_row):
        for c in range(n_col):
            min_adj_height = 10
            for d in ADJ:
                nr, nc = r + d[0], c + d[1]
                if  nr < 0 or nr >= n_row or nc < 0 or nc >= n_col:
                    continue
                min_adj_height = min(min_adj_height, height[nr, nc])
            if height[r, c] < min_adj_height:
                # print(r, c, height[r, c], min_adj_height)
                ans += height[r, c] + 1
                    
    return ans

basin = np.full_like(height, -1, dtype=int)

def DFS(r, c, n_basin):
    basin[r, c] = n_basin
    for d in ADJ:
        nr, nc = r + d[0], c + d[1]
        if  nr < 0 or nr >= n_row or nc < 0 or nc >= n_col:
            continue
        if height[nr, nc] != 9 and basin[nr, nc] == -1:
            DFS(nr, nc, n_basin)
    
def Part2():
    # solve by DFS
    n_basin = 0
    for r in range(n_row):
        for c in range(n_col):
            if height[r, c] != 9 and basin[r, c] == -1:
                DFS(r, c, n_basin)
                n_basin += 1
                
    basin_cnt = np.zeros(n_basin, dtype=int)
    for r in range(n_row):
        for c in range(n_col):
            if basin[r, c] >= 0:
                basin_cnt[basin[r, c]] += 1
    
    basin_cnt = np.sort(basin_cnt)
    return basin_cnt[-1] * basin_cnt[-2] * basin_cnt[-3]
    

print('Part1 :', Part1())    
print('Part2 :', Part2())    