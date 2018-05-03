
#include <iostream>

#include "sphere.h"
#include "circle.h"
#include "polygon.h"
#include "reuleauxtriangle.h"
#include "geom.h"
#include "reuleauxtetrahedron.h"
#include "cube.h"

Cube::Cube(Point3D upperFace[4], Point3D lowerFace[4]){
    upperFace_ = upperFace;
    lowerFace_ = lowerFace;
}


Point3D* Cube::getUpperFace()
{
	return upperFace_;
}
Point3D* Cube::getLowerFace()
{
	return lowerFace_;
}

/*std::vector<Line> Cube::edges()
{
	std::vector<Line> edges;
    for (unsigned int i = 0; i < vertices_.size()-1; i++) 
        edges.push_back(Line(vertices_[i],vertices_[i+1]));
    edges.push_back(Line(vertices_[vertices_.size()-1],vertices_[0]));
    return edges;
}*/

int Cube::vertexCount()
{
	return 8;
}

/*
 * If distance between centers is less than difference between the radius of containing 
 * circle and the radius of this circle, this circle is not contained
 */
bool Cube::containedWithin(Sphere &sphere) {
    return false;
}

/*
 * If circle intersects with any polygon edge, circle is not contained       
 * If line between centers intersects with any polygon edge, circle is not contained
 * Only other possibility is that the circle is contained
 */
bool Cube::containedWithin(Cube &cube) 
{
    return false;
}

//https://opencast-player-1.lt.ucsc.edu:8443/engage/theodul/ui/core.html?id=956436f9-b748-4ab7-b7b7-2e27605f1667
bool Cube::containedWithin(ReuleauxTetrahedron &rt) {
    return false;
}
