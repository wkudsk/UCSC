/*
 * Copyright (C) 2018 David C. Harrison. All right reserved.
 *
 * You may not use, distribute, publish, or modify this code without 
 * the express written permission of the copyright holder.
 */

#include <iostream>

#include "circle.h"
#include "polygon.h"

void testCirclesinCircles()
{
	//Tests for Circles
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

void testCirclesinTriangle()
{
	//Tests for Circles
    RegularConvexPolygon arenaTriangle = RegularConvexPolygon( {Point2D(0.0, 9.0), Point2D(9.0, 0), Point2D(-9.0, 0)} );
    Circle outerCircle = Circle(Point2D(10.0,10.0), 2.0);
    Circle innerCircle = Circle(Point2D(0.0,0.0), 4.0);
    Circle intersectCircle = Circle(Point2D(4.1,0.0), 10.0);
    
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


int main(int argc, char *argv[]) 
{
    int ununsed; // to fail warning test, remove

    testCirclesinCircles();
    testCirclesinTriangle();
    
}
