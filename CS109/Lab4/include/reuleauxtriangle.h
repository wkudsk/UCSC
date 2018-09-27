
#ifndef _REULEAUXTRIANGLE_H_
#define _REULEAUXTRIANGLE_H_

#include <vector>

#include "containable.h"
#include "point.h"
#include "circle.h"
#include "line.h"
#include "polygon.h"

// C++ requires forward declaration of any cyclically dependent classes
class Circle;

class ReuleauxTriangle: public Containable2D {
    private:
        Point2D* vertices_;
        Circle circleA = Circle(Point2D(0.0, 0.0), 0.0);
        Circle circleB = Circle(Point2D(0.0, 0.0), 0.0);
        Circle circleC = Circle(Point2D(0.0, 0.0), 0.0);

    public:
        // do not change this constructor
        ReuleauxTriangle(Point2D vertices[3]);

        Point2D* vertices();
        Circle getCircle(int i);
        bool containedWithin(Circle &circle);
        bool containedWithin(RegularConvexPolygon &polygon);
        bool containedWithin(ReuleauxTriangle &rt);
};

#endif
