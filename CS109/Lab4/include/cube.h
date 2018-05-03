
#ifndef _CUBE_H_
#define _CUBE_H_

#include <vector>

#include "containable.h"
#include "point.h"
#include "sphere.h"
#include "line.h"

// C++ requires forward declaration of any cyclically dependent classes
class Sphere;

class Cube : public Containable3D {
    private:
        Point3D* upperFace_;
        Point3D* lowerFace_;

    public:
        
        Cube(Point3D upperFace[4], Point3D lowerFace[4]);

        Point3D* getUpperFace();
        Point3D* getLowerFace();
        //std::vector<Line> edges();
        int vertexCount();

        bool containedWithin(Sphere &sphere);
        bool containedWithin(Cube &cube);
        bool containedWithin(ReuleauxTetrahedron &rt);
};

#endif
