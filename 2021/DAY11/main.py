import numpy as np

with open('input.txt', 'r') as f:
    data = f.readlines()
    data = [[int(v) for v in row[:-1]] for row in data]
    Oct = np.asarray(data)
    n_row, n_col = Oct.shape
    
ADJ = [ (1, 1), (1, 0), (1, -1), (0, 1), (0, -1), (-1, 1), (-1, 0), (-1, -1) ]

def Part1():
    num_flashes = 0
    oct = np.copy(Oct)
    for step in range(100):
        # the energy level of each octopus increase by 1
        for r in range(n_row):
            for c in range(n_col):
                oct[r, c] += 1
        
        # find
        flashed = np.zeros_like(oct, dtype=bool)
        queue = []
        for r in range(n_row):
            for c in range(n_col):
                if oct[r, c] > 9:
                    flashed[r, c] = True
                    queue.append((r, c))
        
        while len(queue) > 0:
            cr, cc = queue.pop(0)
            for d in ADJ:
                nr, nc = cr + d[0], cc + d[1]
                if nr < 0 or nr >= n_row or nc < 0 or nc >= n_col:
                    continue
                if flashed[nr, nc] == 0:
                    oct[nr, nc] += 1
                    if oct[nr, nc] > 9:
                        flashed[nr, nc] = True
                        queue.append((nr, nc))
        
        num_flashes += np.sum(flashed)
        oct[flashed] = 0
        
        # print('After step {}:'.format(step))
        # for r in range(n_row):
        #     for c in range(n_col):
        #         print(oct[r, c], end='')
        #     print('')
            
    return num_flashes

def Part2():
    oct = np.copy(Oct)
    for step in range(10000):
        # the energy level of each octopus increase by 1
        for r in range(n_row):
            for c in range(n_col):
                oct[r, c] += 1
        
        # find
        flashed = np.zeros_like(oct, dtype=bool)
        queue = []
        for r in range(n_row):
            for c in range(n_col):
                if oct[r, c] > 9:
                    flashed[r, c] = True
                    queue.append((r, c))
        
        while len(queue) > 0:
            cr, cc = queue.pop(0)
            for d in ADJ:
                nr, nc = cr + d[0], cc + d[1]
                if nr < 0 or nr >= n_row or nc < 0 or nc >= n_col:
                    continue
                if flashed[nr, nc] == 0:
                    oct[nr, nc] += 1
                    if oct[nr, nc] > 9:
                        flashed[nr, nc] = True
                        queue.append((nr, nc))
        
        oct[flashed] = 0
        
        # Check if synchronized?
        if np.all(flashed):
            return step + 1
            
    return -1

print('Part1 :', Part1())
print('Part2 :', Part2())