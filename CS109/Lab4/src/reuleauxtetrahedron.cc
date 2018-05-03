#include <iostream>

#include "sphere.h"
#include "circle.h"
#include "polygon.h"
#include "reuleauxtriangle.h"
#include "geom.h"
#include "reuleauxtetrahedron.h"
#include "cube.h"

ReuleauxTetrahedron::ReuleauxTetrahedron(Point3D vertices[4]) {
    vertices_ = vertices;
}

int ReuleauxTetrahedron::vertexCount()
{
	return 4;
}

Point3D ReuleauxTetrahedron::getVertex(int i)
{
	if(i == 1) return vertices_[0];
	else if(i == 2) return vertices_[1];
	else if(i == 3) return vertices_[2];
	else return vertices_[3];
}

/*
 * If distance between centers is less than difference between the radius of containing 
 * circle and the radius of this circle, this circle is not contained
 */
bool ReuleauxTetrahedron::containedWithin(Sphere &sphere) {
    return false;
}

/*
 * If circle intersects with any polygon edge, circle is not contained       
 * If line between centers intersects with any polygon edge, circle is not contained
 * Only other possibility is that the circle is contained
 */
bool ReuleauxTetrahedron::containedWithin(Cube &cube) 
{
    return false;
}

//https://opencast-player-1.lt.ucsc.edu:8443/engage/theodul/ui/core.html?id=956436f9-b748-4ab7-b7b7-2e27605f1667
bool ReuleauxTetrahedron::containedWithin(ReuleauxTetrahedron &rt) {
    return false;
}
