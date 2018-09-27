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


void testCirclesInCircles()
{
    Circle arenaCircle = Circle(Point2D(0.0,0.0), 8.0);
    Circle outerCircle = Circle(Point2D(10.0,10.0), 2.0);
    Circle innerCircle = Circle(Point2D(0.0,0.0), 4.0);
    Circle intersectCircle = Circle(Point2D(4.1,0.0), 4.0);
    
    std::cout << "Circle-in-Circle: ";
    if (innerCircle.containedWithin(arenaCircle)) 
        std::cout << "PASS\n";
    else 
        std::cout << "FAIL\n";

    std::cout << "Circle-intersect-Circle: ";
    if(!intersectCircle.containedWithin(arenaCircle))
    	std::cout << "PASS\n";
    else
    	std::cout << "FAIL\n";

    std::cout << "Circle-outside-Circle: ";
    if(!outerCircle.containedWithin(arenaCircle))
    	std::cout << "PASS\n";
    else
    	std::cout << "FAIL\n";
}

void testCirclesInTriangle()
{
    RegularConvexPolygon arenaTriangle = RegularConvexPolygon( {Point2D(0.0, 9.0), Point2D(9.0, 0), Point2D(-9.0, 0)} );
    Circle outerCircle = Circle(Point2D(10.0,10.0), 2.0);
    Circle innerCircle = Circle(Point2D(0.0,4.0), 2.0);
    Circle intersectCircle = Circle(Point2D(0,4.0), 4.0);
    
    std::cout << "Circle-in-Triangle: ";
    if (innerCircle.containedWithin(arenaTriangle)) 
        std::cout << "PASS\n";
    else 
        std::cout << "FAIL\n";

    std::cout << "Circle-intersect-Triangle: ";
    if(!intersectCircle.containedWithin(arenaTriangle))
    	std::cout << "PASS\n";
    else
    	std::cout << "FAIL\n";

    std::cout << "Circle-outside-Triangle: ";
    if(!outerCircle.containedWithin(arenaTriangle))
    	std::cout << "PASS\n";
    else
    	std::cout << "FAIL\n";
}

void testCirclesInReuTriangle()
{
    Point2D vertices[3];
    vertices[0] = Point2D(0.0,0.0);
    vertices[1] = Point2D(3.0, 5.196152423);
    vertices[2] = Point2D(6.0, 0.0);
	ReuleauxTriangle arenaReuTriangle = ReuleauxTriangle(vertices);
    Circle outerCircle = Circle(Point2D(15.0,15.0), 2.0);
    Circle innerCircle = Circle(Point2D(3.0,1.0), 1.0);
    Circle intersectCircle = Circle(Point2D(0.0,4.0), 6.0);
    
    std::cout << "Circle-in-ReuleauxTriangle: ";
    if (innerCircle.containedWithin(arenaReuTriangle)) 
        std::cout << "PASS\n";
    else 
        std::cout << "FAIL\n";

    std::cout << "Circle-intersect-ReuleauxTriangle: ";
    if(!intersectCircle.containedWithin(arenaReuTriangle))
        std::cout << "PASS\n";
    else
        std::cout << "FAIL\n";

    std::cout << "Circle-outside-ReuleauxTriangle: ";
    if(!outerCircle.containedWithin(arenaReuTriangle))
        std::cout << "PASS\n";
    else
        std::cout << "FAIL\n";

}

void testTrianglesInTriangle()
{
	RegularConvexPolygon arenaTriangle = RegularConvexPolygon({Point2D(0.0, 9.0), Point2D(9.0, 0.0), Point2D(-9.0, 0.0)});
	RegularConvexPolygon innerTriangle = RegularConvexPolygon( {Point2D(0.0, 3.0), Point2D(3.0, 1.0), Point2D(-3.0, 1.0)} );
    RegularConvexPolygon intersectTriangle = RegularConvexPolygon( {Point2D(4.5, 4.5), Point2D(-1.0, 0.0), Point2D(12.0, 0.0)} );
    RegularConvexPolygon outerTriangle = RegularConvexPolygon( {Point2D(20.0,20.0), Point2D(15.0, 15.0), Point2D(30.0, 0.0)} );
    
    std::cout << "Triangle-in-Triangle: ";
    if (innerTriangle.containedWithin(arenaTriangle)) 
        std::cout << "PASS\n";
    else 
        std::cout << "FAIL\n";

    std::cout << "Triangle-intersect-Triangle: ";
    if(!intersectTriangle.containedWithin(arenaTriangle))
    	std::cout << "PASS\n";
    else
    	std::cout << "FAIL\n";

    std::cout << "Triangle-outside-Triangle: ";
    if(!outerTriangle.containedWithin(arenaTriangle))
    	std::cout << "PASS\n";
    else
    	std::cout << "FAIL\n";   
}

void testTrianglesInCircle()
{
	Circle arenaCircle = Circle(Point2D(0.0,0.0), 9);
    RegularConvexPolygon innerTriangle = RegularConvexPolygon( {Point2D(0.0, 0.0), Point2D(1.0, 0.0), Point2D(0.0, 1.0)} );
    RegularConvexPolygon intersectTriangle = RegularConvexPolygon( {Point2D(4.5, 4.5), Point2D(-1.0, 0.0), Point2D(12.0, 0.0)} );
    RegularConvexPolygon outerTriangle = RegularConvexPolygon( {Point2D(20.0,20.0), Point2D(15.0, 15.0), Point2D(30.0, 0.0)} );
    
    std::cout << "Triangle-in-Circle: ";
    if (innerTriangle.containedWithin(arenaCircle)) 
        std::cout << "PASS\n";
    else 
        std::cout << "FAIL\n";

    std::cout << "Triangle-intersect-Circle: ";
    if(!intersectTriangle.containedWithin(arenaCircle))
    	std::cout << "PASS\n";
    else
    	std::cout << "FAIL\n";

    std::cout << "Triangle-outside-Circle: ";
    if(!outerTriangle.containedWithin(arenaCircle))
    	std::cout << "PASS\n";
    else
    	std::cout << "FAIL\n";   
}


void testTrianglesInReuTriangle()
{
    Point2D vertices[3];
    vertices[0] = Point2D(0.0,0.0);
    vertices[1] = Point2D(3.0, 5.196152423);
    vertices[2] = Point2D(6.0, 0.0);
	ReuleauxTriangle arenaReuTriangle = ReuleauxTriangle(vertices);
    RegularConvexPolygon innerTriangle = RegularConvexPolygon( {Point2D(3.0, 1.0), Point2D(5.0, 1.0), Point2D(4.0, 2.0)} );
    RegularConvexPolygon intersectTriangle = RegularConvexPolygon( {Point2D(4.5, 4.5), Point2D(-1.0, 0.0), Point2D(12.0, 0.0)} );
    RegularConvexPolygon outerTriangle = RegularConvexPolygon( {Point2D(20.0,20.0), Point2D(15.0, 15.0), Point2D(30.0, 0.0)} );
    
    std::cout << "Triangle-in-ReuleauxTriangle: ";
    if (innerTriangle.containedWithin(arenaReuTriangle)) 
        std::cout << "PASS\n";
    else 
        std::cout << "FAIL\n";

    std::cout << "Triangle-intersect-ReuleauxTriangle: ";
    if(!intersectTriangle.containedWithin(arenaReuTriangle))
        std::cout << "PASS\n";
    else
        std::cout << "FAIL\n";

    std::cout << "Triangle-outside-ReuleauxTriangle: ";
    if(!outerTriangle.containedWithin(arenaReuTriangle))
        std::cout << "PASS\n";
    else
        std::cout << "FAIL\n";   
}

void testReuTrianglesInCircle()
{
	Circle arenaCircle = Circle(Point2D(0.0,0.0), 9);
    Point2D innerVertices[3] = {Point2D(0.0, 0.0), Point2D(3.0, 5.196152423), Point2D(6.0, 0.0)};
    ReuleauxTriangle innerReuTriangle = ReuleauxTriangle(innerVertices);
    Point2D intersectVertices[3] = {Point2D(5.0, 0.0), Point2D(8.0, 5.196152423), Point2D(11.0, 0.0)};
    ReuleauxTriangle intersectReuTriangle = ReuleauxTriangle(intersectVertices);
    Point2D outerVertices[3] ={Point2D(10.0, 0.0), Point2D(13.0, 5.196152423), Point2D(16.0, 0.0)};
    ReuleauxTriangle outerReuTriangle = ReuleauxTriangle(outerVertices);
    


    std::cout << "ReuleauxTriangle-in-Circle: ";
    if (innerReuTriangle.containedWithin(arenaCircle)) 
        std::cout << "PASS\n";
    else 
        std::cout << "FAIL\n";

    std::cout << "ReuleauxTriangle-intersect-Circle: ";
    if(!intersectReuTriangle.containedWithin(arenaCircle))
        std::cout << "PASS\n";
    else
        std::cout << "FAIL\n";

    std::cout << "ReuleauxTriangle-outside-Circle: ";
    if(!outerReuTriangle.containedWithin(arenaCircle))
        std::cout << "PASS\n";
    else
        std::cout << "FAIL\n";   
}

void testReuTrianglesInTriangle()
{
    RegularConvexPolygon arenaTriangle = RegularConvexPolygon({Point2D(0.0, 9.0), Point2D(9.0, 0.0), Point2D(-9.0, 0.0)});
    Point2D innerVertices[3] = {Point2D(0.0, 0.0), Point2D(3.0, 5.196152423), Point2D(6.0, 0.0)};
    ReuleauxTriangle innerReuTriangle = ReuleauxTriangle(innerVertices);
    Point2D intersectVertices[3] = {Point2D(5.0, 0.0), Point2D(8.0, 5.196152423), Point2D(11.0, 0.0)};
    ReuleauxTriangle intersectReuTriangle = ReuleauxTriangle(intersectVertices);
    Point2D outerVertices[3] ={Point2D(10.0, 0.0), Point2D(13.0, 5.196152423), Point2D(16.0, 0.0)};
    ReuleauxTriangle outerReuTriangle = ReuleauxTriangle(outerVertices);
    


    std::cout << "ReuleauxTriangle-in-Triangle: ";
    if (innerReuTriangle.containedWithin(arenaTriangle)) 
        std::cout << "PASS\n";
    else 
        std::cout << "FAIL\n";

    std::cout << "ReuleauxTriangle-intersect-Triangle: ";
    if(!intersectReuTriangle.containedWithin(arenaTriangle))
        std::cout << "PASS\n";
    else
        std::cout << "FAIL\n";

    std::cout << "ReuleauxTriangle-outside-Triangle: ";
    if(!outerReuTriangle.containedWithin(arenaTriangle))
        std::cout << "PASS\n";
    else
        std::cout << "FAIL\n";   
	
}

void testReuTrianglesInReuTriangle()
{
    Point2D arenaVertices[3] = {Point2D(0.0, 0.0), Point2D(4.5, 7.794228634), Point2D(9.0, 0.0)};
	ReuleauxTriangle arenaReuTriangle = ReuleauxTriangle(arenaVertices);
    Point2D innerVertices[3] = {Point2D(1.0, 1.0), Point2D(4.0, 6.196152423), Point2D(7.0, 1.0)};
    ReuleauxTriangle innerReuTriangle = ReuleauxTriangle(innerVertices);
    Point2D intersectVertices[3] = {Point2D(5.0, 0.0), Point2D(8.0, 5.196152423), Point2D(11.0, 0.0)};
    ReuleauxTriangle intersectReuTriangle = ReuleauxTriangle(intersectVertices);
    Point2D outerVertices[3] ={Point2D(10.0, 0.0), Point2D(13.0, 5.196152423), Point2D(16.0, 0.0)};
    ReuleauxTriangle outerReuTriangle = ReuleauxTriangle(outerVertices);




    std::cout << "ReuleauxTriangle-in-ReuleauxTriangle: ";
    if (innerReuTriangle.containedWithin(arenaReuTriangle)) 
        std::cout << "PASS\n";
    else 
        std::cout << "FAIL\n";

    std::cout << "ReuleauxTriangle-intersect-ReuleauxTriangle: ";
    if(!intersectReuTriangle.containedWithin(arenaReuTriangle))
        std::cout << "PASS\n";
    else
        std::cout << "FAIL\n";

    std::cout << "ReuleauxTriangle-outside-ReuleauxTriangle: ";
    if(!outerReuTriangle.containedWithin(arenaReuTriangle))
        std::cout << "PASS\n";
    else
        std::cout << "FAIL\n";   
}

int main(int argc, char *argv[]) 
{
    testCirclesInCircles();
    testCirclesInTriangle();
 	testCirclesInReuTriangle();
    testTrianglesInCircle();
 	testTrianglesInTriangle();
 	testTrianglesInReuTriangle();
    testReuTrianglesInCircle();
 	testReuTrianglesInTriangle();
 	testReuTrianglesInReuTriangle();
}
