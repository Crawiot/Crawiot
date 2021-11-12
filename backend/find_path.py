from typing import List, Tuple, Union
from queue import Queue

import sympy.geometry as geoma
import itertools as itool

from coordinates import Coordinates


# source: https://e-maxx.ru/algo/bfs
def bfs(graph, n, s, t):
    q = Queue(maxsize=100000)
    q.put(s)
    used = [False for _ in range(n)]
    dist = [0 for _ in range(n)]
    pred = [0 for _ in range(n)]
    used[s] = True
    pred[s] = -1
    to = None
    while not q.empty():
        v = q.get()
        for i in range(len(graph[v])):
            to = graph[v][i]
            if not used[to]:
                used[to] = True
                q.put(to)
                dist[to] = dist[v] + 1
                pred[to] = v
    if not used[to]:
        return []
    else:
        path = []
        v = t
        while v != s:
            path.append(v)
            v = pred[v]
        return path[::-1]


def get_path(start_pos: Coordinates, end_pos: Coordinates, barriers: List[Tuple[Coordinates]],
             borders: List[Tuple[Coordinates]]) -> List[Coordinates]:
    rays = []

    def add_rays(source_point: geoma.Point2D, *dirs):
        for dir in dirs:
            rays.append(
                geoma.Ray2D(
                    source_point,
                    geoma.Point2D(
                        source_point.coordinates[0] + dir[0],
                        source_point.coordinates[1] + dir[1]
                    )
                )
            )

    add_rays(geoma.Point2D(start_pos.x, start_pos.y), (1, 1), (-1, -1))
    add_rays(geoma.Point2D(end_pos.x, end_pos.y), (1, 1), (-1, -1))

    segments = []
    for item in itool.chain(barriers, borders):
        x1 = item[0].x
        y1 = item[0].y
        x2 = item[1].x
        y2 = item[1].y

        if x1 > x2:
            x1, x2 = x2, x1
        if y1 > y2:
            y1, y2 = y2, y1

        # 'pt' == 'Point'
        pt4 = geoma.Point(x1, y1)  # (-1, -1)
        pt3 = geoma.Point(x1, y2)  # (-1, 1)
        pt2 = geoma.Point(x2, y1)  # (1, -1)
        pt1 = geoma.Point(x2, y2)  # (1, 1)

        segments.append(geoma.Segment2D(pt4, pt3))
        segments.append(geoma.Segment2D(pt4, pt2))
        segments.append(geoma.Segment2D(pt3, pt1))
        segments.append(geoma.Segment2D(pt2, pt1))

        if item in borders:
            continue

        for pt, dir in zip([pt1, pt2, pt3, pt4], [(-1, -1), (-1, 1), (1, -1), (1, 1)]):
            add_rays(pt, dir)

    start_point = start_pos.to_point()
    end_point = end_pos.to_point()
    nodes = [start_point, end_point]

    def intersections(ray: Union[geoma.Ray2D, geoma.Segment2D], nodes=None):
        pts = []
        for seg in segments:
            if len(seg.intersection(ray)) == 0:
                continue
            pts.append(seg.intersection(ray)[0])
        if len(pts) < 2:
            return 0
        if nodes:
            minv = pts[0]
            for pt in pts:
                if ray.p1.distance(pt) < ray.p1.distance(minv):
                    minv = pt
            nodes.append(minv.midpoint(ray.p1))
        return len(pts)

    for ray in rays:
        intersections(ray, nodes)

    pt_to_index = dict()
    for i in range(len(nodes)):
        pt_to_index[nodes[i]] = i

    graph = [[] for i in range(len(nodes))]
    for i in range(len(nodes)):
        for j in range(i):
            seg = geoma.Segment2D(nodes[i], nodes[j])
            if intersections(seg) != 0:
                continue
            graph[pt_to_index[nodes[i]]].append(pt_to_index[nodes[j]])
            graph[pt_to_index[nodes[j]]].append(pt_to_index[nodes[i]])

    path = bfs(graph, len(nodes), pt_to_index[start_point], pt_to_index[end_point])
    path = list(map(lambda x: pt_to_index[x].coordinates, path))
    return path