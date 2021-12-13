from itertools import count
import numpy as np
import networkx as nx

G = nx.Graph()
S = 'start'
T = 'end'

with open('input.txt', 'r') as f:
    lines = f.readlines()
    edges = [line[:-1].split('-') for line in lines]
    G.add_edges_from(edges)

def countPath1(curr, visited):
    if curr == T:
        return 1
    num_path = 0
    for next in G.neighbors(curr):
        if next[0].isupper() or visited[next] == 0:
            visited[next] += 1
            num_path += countPath1(next, visited)
            visited[next] -= 1
    return num_path

def Part1():
    visited = dict(zip(G.nodes(), [0] * G.number_of_nodes()))
    visited[S] = 1
    return countPath1(S, visited)

def countPath2(curr, visited, twice_visited):
    if curr == T:
        return 1
    num_path = 0
    for next in G.neighbors(curr):
        if next[0].isupper() or visited[next] == 0:
            visited[next] += 1
            num_path += countPath2(next, visited, twice_visited)
            visited[next] -= 1
        elif visited[next] == 1 and not twice_visited and next != T:
            visited[next] += 1
            num_path += countPath2(next, visited, True)
            visited[next] -= 1
            
    return num_path

def Part2():
    visited = dict(zip(G.nodes(), [0] * G.number_of_nodes()))
    visited[S] = 2
    visited[T] = 0
    return countPath2(S, visited, False)

print('Part1 :', Part1())
print('Part2 :', Part2())
        
    