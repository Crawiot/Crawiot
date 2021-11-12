from typing import List, Tuple
from queue import Queue

import sympy.geometry as geoma
import itertools as itool


def bfs(graph, n, s, t):
    q = Queue(maxlen=100000)
    q.put(s)
    used = [False for _ in range(n)]
    dist = [0 for _ in range(n)]
    pred = [0 for _ in range(n)]
    used[s] = True
    pred[s] = -1
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

def get_path(start_pos: Tuple[float], end_pos: Tuple[float], barriers: List[Tuple[Tuple[float]]], 
             borders: List[Tuple[Tuple[float]]]) -> List[Tuple[float]]:

    rays = []

    def add_rays(source_point: geoma.Point2D, *dirs):
        for dir in dirs:
            rays.append(
                source_point,
                geoma.Point2D(
                    source_point.coordinates[0] + dir[0],
                    source_point.coordinates[1] + dir[1]
                )
            )
    add_rays(start_pos, (1, 1), (-1, -1))
    add_rays(end_pos, (1, 1), (-1, -1))

    segments = []
    for x1, y1, x2, y2 in itool.chain(barriers, borders):
        if x1 > x2:
            x1, x2 = x2, x1
        if y1 > y2:
            y1, y2 = y2, y1
        
        pt4 = geoma.Point(x1, y1) # (-1, -1)
        pt3 = geoma.Point(x1, y2) # (-1, 1)
        pt2 = geoma.Point(x2, y1) # (1, -1)
        pt1 = geoma.Point(x2, y2) # (1, 1)

        segments.append(geoma.Segment2D(pt4, pt3))
        segments.append(geoma.Segment2D(pt4, pt2))
        segments.append(geoma.Segment2D(pt3, pt1))
        segments.append(geoma.Segment2D(pt2, pt1))

        if (x1, y1, x2, y2) in borders:
            continue

        for pt, dir in zip([pt1, pt2, pt3, pt4], [(-1, -1), (-1, 1), (1, -1), (1, 1)]):
            add_rays(pt, dir)

    nodes = [start_pos, end_pos]
    def intersections(ray: geoma.Ray2D, is_void=False):
        pts = []
        for seg in segments:
            if len(seg.intersection(ray)) == 0:
                continue
            pts.append(seg.intersection(ray))
        if len(pts) < 2:
                return 0
        if not is_void and isinstance(ray, geoma.Ray2D):
            minv = pts[0]
            for pt in pts:
                if ray.p1.distance(pt) < ray.p1.distance(minv):
                    minv = pt
            nodes.append(geoma.Segment2D(minv, ray.p1).midpoint)
        return len(pts)

    for ray in rays:
        intersections(ray)

    mappa = dict()
    for i in range(len(nodes)):
        mappa[nodes[i]] = i

    graph = [[] for i in range(len(nodes))]
    for i in range(len(nodes)):
        for j in range(i):
            seg = geoma.Segment2D(nodes[i], nodes[j])
            if intersections(seg, is_void=True) != 0:
                continue
            graph[mappa[nodes[i]]].append(mappa[nodes[j]])
            graph[mappa[nodes[j]]].append(mappa[nodes[i]])

    path = bfs(graph, len(nodes), mappa[start_pos], mappa[end_pos])
    path = list(map(lambda x: mappa[x].coordinates, path))
    return path