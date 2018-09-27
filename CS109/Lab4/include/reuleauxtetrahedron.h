
#ifndef _REULEAUXTETRAHEDRON_H_
#define _REULEAUXTETRAHEDRON_H_

#include <vector>

#include "containable.h"
#include "point.h"
#include "sphere.h"
#include "line.h"
#include "cube.h"

// C++ requires forward declaration of any cyclically dependent classes
class Sphere;

class ReuleauxTetrahedron : public Containable3D {
    private:
        Point3D* vertices_;
       
    public:
        
        ReuleauxTetrahedron(Point3D vertices[4]);

        int vertexCount();
        Point3D getVertex(int i);

        bool containedWithin(Sphere &sphere);
        bool containedWithin(Cube &cube);
        bool containedWithin(ReuleauxTetrahedron &rt);
};

#endif
