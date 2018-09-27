#include <iostream>

#include "circle.h"
#include "polygon.h"
#include "reuleauxtriangle.h"
#include "geom.h"

ReuleauxTriangle::ReuleauxTriangle(Point2D vertices[3]) {
    vertices_ = vertices;
    
    //if(Geom::distance(vertices[0], vertices[1]) != Geom::distance(vertices[0], vertices[2]) || 
    //    Geom::distance(vertices[0], vertices[2]) != Geom::distance(vertices[2], vertices[1]) ||
    //    Geom::distance(vertices[0], vertices[1]) != Geom::distance(vertices[1], vertices[2])) 
    //    throw "Not equilateral";
    
    circleA.setCenter(vertices[0]);
    circleB.setCenter(vertices[1]);
    circleC.setCenter(vertices[2]);

    circleA.setRadius(Geom::distance(vertices[1], vertices[0]));
    circleB.setRadius(Geom::distance(vertices[1], vertices[0]));
    circleC.setRadius(Geom::distance(vertices[1], vertices[0]));    
}

Point2D* ReuleauxTriangle::vertices() {
    return vertices_;
}

Circle ReuleauxTriangle::getCircle(int i)
{
    if(i == 0) return circleA;
    else if(i == 1) return circleB;
    else return circleC;
}

//https://opencast-player-1.lt.ucsc.edu:8443/engage/theodul/ui/core.html?id=956436f9-b748-4ab7-b7b7-2e27605f1667
bool ReuleauxTriangle::containedWithin(Circle &circle) {
    for(int i = 0; i < 3; i++)
    {
    	if(Geom::distance(vertices_[i], circle.center()) > circle.radius()) return false;
    }
    return true;
}

//https://opencast-player-1.lt.ucsc.edu:8443/engage/theodul/ui/core.html?id=956436f9-b748-4ab7-b7b7-2e27605f1667
bool ReuleauxTriangle::containedWithin(RegularConvexPolygon &polygon) {

	RegularConvexPolygon triangle = RegularConvexPolygon({vertices_[0], vertices_[1], vertices_[2]});
	//Point2D center_o = Geom::center(triangle);
    Point2D center_p = Geom::center(polygon);
	std::vector<Point2D> vertices_p = polygon.vertices();

	Circle circleA = Circle(getCircle(0).center(), getCircle(0).radius());
    Circle circleB = Circle(getCircle(1).center(), getCircle(1).radius());
    Circle circleC = Circle(getCircle(2).center(), getCircle(2).radius());

	for(int i = 0; i < polygon.vertexCount(); i++)
    {
    	Line line = Line(center_p, vertices_p[i]);
    	if(!Geom::intersects(line, circleA)
    		|| !Geom::intersects(line, circleB) 
    		|| !Geom::intersects(line, circleC)) return false;
    }
	
	return true;
}

//https://opencast-player-1.lt.ucsc.edu:8443/engage/theodul/ui/core.html?id=956436f9-b748-4ab7-b7b7-2e27605f1667
bool ReuleauxTriangle::containedWithin(ReuleauxTriangle &rt) {
    Circle circleA = Circle(rt.getCircle(0).center(), rt.getCircle(0).radius());
    Circle circleB = Circle(rt.getCircle(1).center(), rt.getCircle(1).radius());
    Circle circleC = Circle(rt.getCircle(2).center(), rt.getCircle(2).radius());

	return (containedWithin(circleA) && 
        containedWithin(circleB) &&
        containedWithin(circleC));
}