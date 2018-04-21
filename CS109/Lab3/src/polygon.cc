/*
 * Copyright (C) 2018 David C. Harrison. All right reserved.
 *
 * You may not use, distribute, publish, or modify this code without 
 * the express written permission of the copyright holder.
 */

#include <iostream>

#include "circle.h"
#include "polygon.h"
#include "reuleauxtriangle.h"
#include "geom.h"
RegularConvexPolygon::RegularConvexPolygon(std::vector<Point2D> vertices) {
    vertices_ = vertices;
}

std::vector<Point2D> RegularConvexPolygon::vertices() {
    return vertices_;
}

std::vector<Line> RegularConvexPolygon::edges() {
    std::vector<Line> edges;
    for (unsigned int i = 0; i < vertices_.size()-1; i++) 
        edges.push_back(Line(vertices_[i],vertices_[i+1]));
    edges.push_back(Line(vertices_[vertices_.size()-1],vertices_[0]));
    return edges;
}

int RegularConvexPolygon::vertexCount() {
    return vertices_.size();
}

//https://opencast-player-1.lt.ucsc.edu:8443/engage/theodul/ui/core.html?id=956436f9-b748-4ab7-b7b7-2e27605f1667
bool RegularConvexPolygon::containedWithin(Circle &circle) {

    //https://opencast-player-1.lt.ucsc.edu:8443/engage/theodul/ui/core.html?id=956436f9-b748-4ab7-b7b7-2e27605f1667
    for (Point2D const &vertex : vertices())
    {
        if(Geom::distance(vertex, circle.center()) >= circle.radius())
        {
            return false;
        }
    }

    return true;
}

//https://opencast-player-1.lt.ucsc.edu:8443/engage/theodul/ui/core.html?id=956436f9-b748-4ab7-b7b7-2e27605f1667
bool RegularConvexPolygon::containedWithin(RegularConvexPolygon &polygon) {
    std::vector<Line> edges_o = RegularConvexPolygon::edges();
    std::vector<Line> edges_p = polygon.RegularConvexPolygon::edges();
    for(unsigned i = 0; i < edges_o.size(); i++)
    {
        for(unsigned j = 0; j < edges_p.size(); j++)
        {
            if(Geom::intersects(edges_o[i], edges_p[j])) return false;
        }    
    }
    
    Point2D center_o = Geom::center(*this);
    Point2D center_p = Geom::center(polygon);
    Line lineBetweenCenter = Line(center_p, center_o);
    for(int i = 0; i < RegularConvexPolygon::vertexCount(); i++)
    {
        if(Geom::intersects(edges_p[i], lineBetweenCenter)) return false;
    }
    
    return true;
}

//https://opencast-player-1.lt.ucsc.edu:8443/engage/theodul/ui/core.html?id=956436f9-b748-4ab7-b7b7-2e27605f1667
bool RegularConvexPolygon::containedWithin(ReuleauxTriangle &rt) {
    Circle circleA = Circle(rt.getCircle(0).center(), rt.getCircle(0).radius());
    Circle circleB = Circle(rt.getCircle(1).center(), rt.getCircle(0).radius());
    Circle circleC = Circle(rt.getCircle(2).center(), rt.getCircle(0).radius());


    return (containedWithin(circleA) && 
        containedWithin(circleB) &&
        containedWithin(circleC));

}
