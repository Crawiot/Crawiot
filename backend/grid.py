from find_path import bfs
from coordinates import Coordinates
from typing import Tuple, List
from itertools import chain


def get_path(start_pos, end_pos, barriers: Tuple[Coordinates], borders: Tuple[Coordinates]):
    # width and heigth of grid
    n = max(
        borders[1].x - borders[0].x + 1,
        borders[1].y - borders[0].y + 1
    )

    # moving the origin of the coordinate system (to eliminate negative values)
    norm_coords = borders[0]

    def update(example: Coordinates):
        example.x -= norm_coords.x
        example.y -= norm_coords.y
        
    for example in barriers:
        update(example[0])
        update(example[1])
    update(start_pos)
    update(end_pos)

    # creating a grid
    grid = [[True for _ in range(n)] for _ in range(n)]
    for barrier in barriers:
        for x in range(barrier[0].x, barrier[1].x + 1):
            for y in range(barrier[0].y, barrier[1].y + 1):
                grid[x][y] = False

    # creating the graph and transformation coordinates to node nmumbers
    pt_to_ind = dict()
    for x in range(n):
        for y in range(n):
            pt_to_ind[x * n + y] = Coordinates(x, y)
    graph = [[] for _ in range(n * n)]
    for x in range(n):
        for y in range(n):

            def add_edge(node1, node2):
                if not grid[node1[0]][node1[1]] or not grid[node2[0]][node2[1]]:
                    return None
                graph[node1[0] * n + node1[1]].append(node2[0] * n + node2[1])
                graph[node2[0] * n + node2[1]].append(node1[0] * n + node1[1])

            if x > 0: add_edge((x, y), (x - 1, y))
            if y > 0: add_edge((x, y), (x, y - 1))

    # start bfs
    s = start_pos.x * n + start_pos.y
    t = end_pos.x * n + end_pos.y
    path = bfs(graph, n * n, s, t)
    path = list(map(lambda ind: pt_to_ind[ind], path))

    # restoring original coordinates
    norm_coords = Coordinates(-norm_coords.x, -norm_coords.y)
    for node in path:
        update(node)

    return path
