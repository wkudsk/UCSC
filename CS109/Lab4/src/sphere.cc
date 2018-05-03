
#include <iostream>

#include <string>
#include <math.h>
#include "sphere.h"
#include "circle.h"
#include "polygon.h"
#include "reuleauxtriangle.h"
#include "geom.h"
#include "reuleauxtetrahedron.h"
#include "cube.h"

Sphere::Sphere(Point3D center, double radius) {
    setCenter(center);
    setRadius(radius);
}

Point3D Sphere::center() {
    return center_;
}

void Sphere::setCenter(const Point3D &center) {
    center_.x = center.x;
    center_.y = center.y;
    center_.z = center.z;
}

double Sphere::radius() {
    return radius_;
}

void Sphere::setRadius(double radius) {
    radius_ = radius;
}

/*
 * If distance between centers is less than difference between the radius of containing 
 * circle and the radius of this circle, this circle is not contained
 */
bool Sphere::containedWithin(Sphere &sphere) {
    Point3D sphereCenter_o = this->center();
    Point3D sphereCenter_s = sphere.center();
    Point2D xycircleCenter_o = Point2D(sphereCenter_o.x, sphereCenter_o.y);
    Point2D yzcircleCenter_o = Point2D(sphereCenter_o.y, sphereCenter_o.z);
    Point2D xycircleCenter_s = Point2D(sphereCenter_s.x, sphereCenter_s.y);
    Point2D yzcircleCenter_s = Point2D(sphereCenter_s.y, sphereCenter_s.z);
    double radius_o = this->radius();
    double radius_s = sphere.radius();
    Circle xyCircle_o = Circle(xycircleCenter_o, radius_o);
    Circle yzCircle_o = Circle(yzcircleCenter_o, radius_o);
    Circle xyCircle_s = Circle(xycircleCenter_s, radius_s);
    Circle yzCircle_s = Circle(yzcircleCenter_s, radius_s);

    return xyCircle_o.containedWithin(xyCircle_s) && yzCircle_o.containedWithin(yzCircle_s);
}

/*
 * If circle intersects with any polygon edge, circle is not contained       
 * If line between centers intersects with any polygon edge, circle is not contained
 * Only other possibility is that the circle is contained
 */
bool Sphere::containedWithin(Cube &cube) 
{
    Point3D sphereCenter = this->center();
    Point3D* cubeUpperFace = cube.getUpperFace();
    Point3D* cubeLowerFace = cube.getLowerFace();
    std::vector<Point2D> xyVertices = {Point2D(cubeUpperFace[0].x, cubeUpperFace[0].y), 
        Point2D(cubeUpperFace[1].x, cubeUpperFace[1].y), Point2D(cubeUpperFace[2].x, cubeLowerFace[2].y), 
        Point2D(cubeUpperFace[3].x, cubeUpperFace[3].y)};
    std::vector<Point2D> yzVertices = {Point2D(cubeUpperFace[0].y, cubeUpperFace[0].z), 
        Point2D(cubeUpperFace[1].y, cubeUpperFace[1].z), Point2D(cubeLowerFace[0].y, cubeLowerFace[0].z), 
        Point2D(cubeLowerFace[0].y, cubeLowerFace[0].z)};
   Point2D xycircleCenter = Point2D(sphereCenter.x, sphereCenter.y);
   Point2D yzcircleCenter = Point2D(sphereCenter.y, sphereCenter.z);
   double radius = this->radius();
   Circle xyCircle = Circle(xycircleCenter, radius);
   Circle yzCircle = Circle(yzcircleCenter, radius); 
   RegularConvexPolygon xyPolygon = RegularConvexPolygon(xyVertices);
   RegularConvexPolygon yzPolygon = RegularConvexPolygon(yzVertices);

    return xyCircle.containedWithin(xyPolygon) && yzCircle.containedWithin(yzPolygon);
}

//https://opencast-player-1.lt.ucsc.edu:8443/engage/theodul/ui/core.html?id=956436f9-b748-4ab7-b7b7-2e27605f1667
bool Sphere::containedWithin(ReuleauxTetrahedron &rt) {
    double distance = sqrt(pow(rt.getVertex(2).x - rt.getVertex(1).x, 2) 
        + pow(rt.getVertex(2).y - rt.getVertex(1).y, 2) 
        + pow(rt.getVertex(2).z - rt.getVertex(1).z, 2));
    Sphere spherePointA = Sphere(rt.getVertex(1), distance);
    Sphere spherePointB = Sphere(rt.getVertex(2), distance);
    Sphere spherePointC = Sphere(rt.getVertex(3), distance);
    Sphere spherePointD = Sphere(rt.getVertex(4), distance); 
    return this->containedWithin(spherePointA) && this->containedWithin(spherePointB) 
    && this->containedWithin(spherePointC) && this->containedWithin(spherePointD);
}
