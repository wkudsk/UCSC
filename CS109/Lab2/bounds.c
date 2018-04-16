#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "bounds.h"

//https://opencast-player-1.lt.ucsc.edu:8443/engage/theodul/ui/core.html?id=785d50a3-c653-46b8-b9f6-0c468e959ac7
// for the part that checks circle within circle

static Shape *a;

/*
 * Intialise a two or three dimensional space of shape ARENA containing NUMSHAPES 
 * SHAPES, all of which may or may not be entirely contained within ARENA.
 */
void setup(Shape *arena, Shape *shapes[], int numShapes)
{
	a = arena;
}

static bool isBounded(float x, float y, Point pointA, Point pointB)
{
	//http://www.cplusplus.com/reference/cmath/
	return x <= fmax(pointA.x, pointB.x) && y <= fmax(pointA.y, pointB.y) &&
	 y >= fmin(pointA.y, pointB.y) && x >= fmin(pointA.x, pointB.x);
}

static Point** makeLineArray(int n, Polygon *polygon)
{
	Point** lines = malloc(n*sizeof(Point*));
	for(int i = 0; i < n; i++) lines[i] = malloc(2*sizeof(Point));

	lines[0][0] = polygon->vertices[0];
	lines[0][1] = polygon->vertices[n-1];
	
	//
	for(int i = 1; i < n; i++)
	{
		lines[i][0] = polygon->vertices[i];
		lines[i][1] = polygon->vertices[i-1];
	}
	return lines;
}

static bool itIntersectsLines(Point pointA, Point pointB, Point pointC, Point pointD)
{
	//https://www.topcoder.com/community/data-science/data-science-tutorials/geometry-concepts-line-intersection-and-its-applications/
	float aOuter = pointA.y - pointB.y;
	float bOuter = pointB.x - pointA.x;
	float cOuter = pointA.x*aOuter + (bOuter*pointA.y);

	float aInner = pointC.y - pointD.y;
	float bInner = pointD.x - pointC.x;
	float cInner = pointC.x*aInner + (bInner*pointC.y);
		
	float det = aOuter*bInner - aInner*bOuter;

	if(det != 0)
	{
		//this should give the point of intersection
		float x = (bInner*cOuter - bOuter*cInner)/det;
		float y = (aOuter*cInner - aInner*cOuter)/det;

		//if the coordinate is bounded by the two line segments, then return false.	
		if(isBounded(x, y, pointA, pointB) && isBounded(x, y, pointC, pointD)) return true;
		else return false;
	}
	else return false;
}

static bool itIntersectsCircle(int n, Point** lines, Circle *circle)
{
	float x = circle->center.x;
	float y = circle->center.y;
	for(int i = 0; i < n; i++)
	{
		//https://math.stackexchange.com/questions/637922/how-can-i-find-coefficients-a-b-c-given-two-points
		Point pointA = lines[i][0];
		Point pointB = lines[i][1];
		
		float a = pointA.y - pointB.y;
		float b = pointB.x - pointA.x;
		float c = pointA.x*a - (b*pointA.y);

		//https://www.geeksforgeeks.org/check-line-touches-intersects-circle/
	    // Finding the distance of line from center.
	    float dist = (abs((a * x) + (b * y) + c)) / 
	                     sqrt(a * a + b * b);
	 
	    // Checking if the distance is less than, 
	    // greater than or equal to radius.
	    if (circle->radius > dist )
	        return true;
	}
	return false;
}

static bool isPointInPolygon(int n, Point point, Point** lines)
{
	//https://www.geeksforgeeks.org/how-to-check-if-a-given-point-lies-inside-a-polygon/
	Point *infinitePoint = malloc(sizeof(struct point_t));
	infinitePoint->x = INFINITY;
	infinitePoint->y = point.y;
	infinitePoint->z = point.z;

	int counter = 0;
	for(int i = 0; i < n; i++)
	{
		Point pointA = lines[i][0];
		Point pointB = lines[i][1];
  		if(itIntersectsLines(pointA, pointB, point, *infinitePoint)) counter++;
		else if(counter == 2) return false;
		
	}
	if(counter == 1 ) return true;
	else
	{
		counter = 0;
		infinitePoint->x = -1*INFINITY;
		for(int i = 0; i < n; i++)
		{
			Point pointA = lines[i][0];
			Point pointB = lines[i][1];

   			if(itIntersectsLines(pointA,pointB,point, *infinitePoint)) counter++;
			else if(counter == 2) return false;
		}	
	}
	return true;
}
static bool isCircleInsideCircle(Circle *outer, Circle *inner)
{
	float distance = sqrt(
		pow(outer->center.x - inner->center.x, 2) + 
		pow(outer->center.y - inner->center.y, 2));
	return distance <= outer->radius - inner->radius;
}

static bool isCircleInsidePolygon(Polygon *outer, Circle *inner)
{
	int n = outer->numVertices;
	
	//List of all lines made by the polygon using pairs of points
	Point** lines = makeLineArray(n, outer);

	//For all lines in lines, find if they intersect the circle
	if(itIntersectsCircle(n, lines, inner)) return false;
	else
	{
		//if the circle exists inside the polygon, then its center should be bounded by all lines of the polygon.
		if(isPointInPolygon(n, inner->center, lines)) return true;
		else return false;
	}
}

static bool isPolygonInsideCircle(Circle *outer, Polygon *inner)
{
	int n = inner->numVertices;
	Point** lines = makeLineArray(n, inner);
	
	if(itIntersectsCircle(n, lines, outer)) return false;
	else return true;
}

static bool isPolygonInsidePolygon(Polygon *outer, Polygon *inner)
{
	int n = outer->numVertices;
	int m = inner->numVertices;

	Point** linesOuter = makeLineArray(n, outer);
	Point** linesInner = makeLineArray(m, inner);

	//Compares the set of lines from polygon outer and the set of lines from polygon inner.
	//If any of these lines intersect and a point that is bounded by the polygon's perimeter, then return false
	for(int i = 0; i < n; i++)
	{
		Point pointA = linesOuter[i][0];
		Point pointB = linesOuter[i][1];
		for(int j = 0; j < m; j++)
		{

			Point pointC = linesInner[j][0];
			Point pointD = linesInner[j][1];

			if(itIntersectsLines(pointA, pointB, pointC, pointD)) return false;
		}
	}
	return true;
}

/*
 * Move the centroid of SHAPE to POINT. 
 *
 * Return TRUE if SHAPE remains entirely within the space defined by the 
 * ARENA parameter of setup(), FALSE otherwise.
 */
bool move(Shape *shape, Point *point) {
    if(shape->type == CIRCLE)
    {
    	Circle *inner = (Circle *) shape;
    	inner->center.x = point->x;
    	inner->center.y = point->y;
    	if(a->type == CIRCLE) return isCircleInsideCircle((Circle *)a, inner);
    	else if(a->type == POLYGON) return isCircleInsidePolygon((Polygon *)a, inner);
    }
    if(shape->type == POLYGON)
    {
    	Polygon *inner = (Polygon *) shape;
    	
    	//https://en.wikipedia.org/wiki/Centroid
    	//Find the centroid, find the difference between the current and moved centroid, then add that to each vertex
    	float sumX = 0;
    	float sumY = 0;
    	for(int i = 0; i < inner->numVertices; i++)
    	{
    		sumX = sumX + inner->vertices[i].x;
    		sumY = sumY + inner->vertices[i].y;
    	}
    	float centroidX = sumX/inner->numVertices;
    	float centroidY = sumY/inner->numVertices;
    	float xDifference = point->x - centroidX;
    	float yDifference = point->y - centroidY;
    	for(int i = 0; i < inner->numVertices; i++)
    	{
    		inner->vertices[i].x = xDifference + inner->vertices[i].x;
    		inner->vertices[i].y = yDifference + inner->vertices[i].y;
    	}

    	if(a->type == CIRCLE) return isPolygonInsideCircle((Circle *)a, inner);
    	else if(a->type == POLYGON) return isPolygonInsidePolygon((Polygon *)a, inner);
    }
    return true;
}
