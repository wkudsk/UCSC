
#ifndef _SPHERE_H_
#define _SPHERE_H_

#include <vector>

#include "containable.h"
#include "point.h"
#include "line.h"
#include "cube.h"
#include "reuleauxtetrahedron.h"



class Sphere : public Containable3D {
    private:
        Point3D center_;
        double radius_;

    public:
        Sphere(Point3D center, double radius);
        
        Point3D center();
        void setCenter(const Point3D &center);

        double radius();
        void setRadius(double radius);

        bool containedWithin(Sphere &sphere);
        bool containedWithin(Cube &cube);
        bool containedWithin(ReuleauxTetrahedron &rt);
};

#endif
