from typing import List, Tuple
import sympy.geometry as geoma
import itertools as itool

from sympy.geometry.line import Segment2D 

def get_path(map) -> List[Tuple[float]]:
    start_pos = map.start_pos
    end_pos = map.end_pos

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
    for x1, y1, x2, y2 in itool.chain(map.barriers, map.borders):
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

        if (x1, y1, x2, y2) in map.borders:
            continue

        for pt, dir in zip([pt1, pt2, pt3, pt4], [(-1, -1), (-1, 1), (1, -1), (1, 1)]):
            add_rays(pt, dir)

    nodes = [start_pos, end_pos]
    def add_intersections(ray: geoma.Ray2D):
        pts = []
        for seg in segments:
            if len(seg.intersection(ray)) == 0:
                continue
            pts.append(seg.intersection(ray))
        if len(pts) < 2:
                return 0
        minv = pts[0]
        for pt in pts:
            if ray.p1.distance(pt) < ray.p1.distance(minv):
                minv = pt
        nodes.append(minv)
        return len(pts)

    for ray in rays:
        add_intersections(ray)

    

        '''
        TODO:
        1. Добавить пересечения с лучами из start_pos, end_pos
        2. Добавить границу чтобы с ней мы тоже пересекались если что
        3. Перебрать ноды и посоединять их
        4. Дейкстра на графе с сохранением пути (отдельной функцией)
        5. Вернуть собственно путь (почему это вообще отдельны пункт)
        '''