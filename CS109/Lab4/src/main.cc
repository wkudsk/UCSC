/*
 * Copyright (C) 2018 David C. Harrison. All right reserved.
 *
 * You may not use, distribute, publish, or modify this code without 
 * the express written permission of the copyright holder.
 */

#include <iostream>
#include <fstream>
#include <sstream>
#include "circle.h"
#include "polygon.h"
#include "reuleauxtriangle.h"
#include "sphere.h"
#include "reuleauxtetrahedron.h"
#include "cube.h"


#define USAGE "USAGE %s test-file\n"

//https://opencast-player-1.lt.ucsc.edu:8443/engage/theodul/ui/core.html?id=2be08498-8350-4514-b8fe-06e265820e39
static Point2D getPoint2D(std::string &token)
{
	double x,y;
	std::stringstream vstream(token);
	std::string value;
	if(std::getline(vstream, value, ','))
	{
		//std::cout << value << std::endl;
		std::stringstream(value) >> x;
		if(std::getline(vstream, value, ','))
		{
			std::stringstream(value) >> y;
			return Point2D(x,y);
		}
	}
	throw "cant read a Point2D" + token;
}

static Point3D getPoint3D(std::string &token)
{
	double x,y,z;
	std::stringstream vstream(token);
	std::string value;
	if(std::getline(vstream, value, ','))
	{
		//std::cout << value << std::endl;
		std::stringstream(value) >> x;
		if(std::getline(vstream, value, ','))
		{
			std::stringstream(value) >> y;
			if(std::getline(vstream, value, ','))
			{
				std::stringstream(value) >> z;
				return Point3D(x,y,z);
			}	
		}
	}
	throw "cant read a Point3D" + token;
}

//https://opencast-player-1.lt.ucsc.edu:8443/engage/theodul/ui/core.html?id=2be08498-8350-4514-b8fe-06e265820e39
static double getRadius(const std::string &token)
{
	//converts string into double
	return std::stod(token);
}

//https://opencast-player-1.lt.ucsc.edu:8443/engage/theodul/ui/core.html?id=f1b2136b-19ef-4971-b4c6-504eadc46eac
static void parse(const std::string line)
{
	std::stringstream stream(line);
	std::string token;

	//https://opencast-player-1.lt.ucsc.edu:8443/engage/theodul/ui/core.html?id=2be08498-8350-4514-b8fe-06e265820e39
	Circle *innerCircle = NULL;
	Circle *outerCircle = NULL;
	RegularConvexPolygon *innerPolygon = NULL;
	RegularConvexPolygon *outerPolygon = NULL;
	ReuleauxTriangle *innerReuTriangle = NULL;
	ReuleauxTriangle *outerReuTriangle = NULL;
	Sphere *innerSphere = NULL;
	Sphere *outerSphere = NULL;
	Cube *innerCube = NULL;
	Cube *outerCube = NULL;
	ReuleauxTetrahedron *innerReuTetrahedron = NULL;
	ReuleauxTetrahedron *outerReuTetrahedron = NULL;	

	bool expected = false;

	//Every time a token goes pass me, extract it.
	while(stream >> token)
	{
		//std::cout << token << std::endl;
		if(token == "ReuleauxTriangle")
		{
			stream >> token;
			Point2D vertices[3];
			for(int i = 0; i < 2; i++)
			{
				vertices[i] = getPoint2D(token);
				stream >> token;
			}
			vertices[2] = getPoint2D(token);
			if(innerCircle == NULL && innerPolygon == NULL && innerReuTriangle == NULL && innerSphere == NULL
				&& innerCube == NULL && innerReuTetrahedron == NULL)
				innerReuTriangle = (new ReuleauxTriangle(vertices));
			
			else outerReuTriangle = (new ReuleauxTriangle(vertices));
		}
		if(token == "RegularConvexPolygon")
		{
			stream >> token;
			std::vector<Point2D> vertices;
			while(token.find(",") != std::string::npos)
			{
				vertices.push_back(getPoint2D(token));
				stream >> token;
			}

			if(innerCircle == NULL && innerPolygon == NULL && innerReuTriangle == NULL && innerSphere == NULL
				&& innerCube == NULL && innerReuTetrahedron == NULL)
				innerPolygon = (new RegularConvexPolygon(vertices));
			
			else outerPolygon = (new RegularConvexPolygon(vertices));
		}
		//https://opencast-player-1.lt.ucsc.edu:8443/engage/theodul/ui/core.html?id=2be08498-8350-4514-b8fe-06e265820e39
		if(token == "Circle")
		{
			stream >> token;
			Point2D center = getPoint2D(token);
			stream >> token;
			double radius = getRadius(token);
			
			if(innerCircle == NULL && innerPolygon == NULL && innerReuTriangle == NULL && innerSphere == NULL
				&& innerCube == NULL && innerReuTetrahedron == NULL)
				innerCircle = (new Circle(center , radius));
			
			else outerCircle = (new Circle(center , radius));
		}
		if(token == "Sphere")
		{
			stream >> token;
			Point3D center = getPoint3D(token);
			stream >> token;
			double radius = getRadius(token);
			
			if(innerCircle == NULL && innerPolygon == NULL && innerReuTriangle == NULL && innerSphere == NULL
				&& innerCube == NULL && innerReuTetrahedron == NULL) 
				innerSphere = (new Sphere(center , radius));
			
			else outerSphere = (new Sphere(center , radius));
		}
		if(token == "Cube")
		{
			stream >> token;
			Point3D upperFace[4];
			Point3D lowerFace[4];
			for(int i = 0; i < 4; i++)
			{
				upperFace[i] = getPoint3D(token);
				stream >> token;	
			}
			for(int i = 0; i < 4; i++)
			{
				lowerFace[i] = getPoint3D(token);
				stream >> token;
			}
			if(innerCircle == NULL && innerPolygon == NULL && innerReuTriangle == NULL && innerSphere == NULL
				&& innerCube == NULL && innerReuTetrahedron == NULL)
				innerCube = (new Cube(upperFace, lowerFace));
			
			else outerCube = (new Cube(upperFace, lowerFace));
		}
		if(token == "ReuleauxTetrahedron")
		{
			stream >> token;
			Point3D vertices[4];
			for(int i = 0; i < 3; i++)
			{
				vertices[i] = getPoint3D(token);
				stream >> token;
			}
			vertices[3] = getPoint3D(token);
			if(innerCircle == NULL && innerPolygon == NULL && innerReuTriangle == NULL && innerSphere == NULL
				&& innerCube == NULL && innerReuTetrahedron == NULL)
				innerReuTetrahedron = (new ReuleauxTetrahedron(vertices));
			
			else outerReuTetrahedron = (new ReuleauxTetrahedron(vertices));
		}
		if(token == "true") expected = true;
	}

	//I know this looks gross, but its the best way to find which shapes are being used.
	if(innerCircle != NULL)
	{	
		if(outerCircle != NULL)
		{
			bool got = innerCircle->containedWithin(*outerCircle);
			std::cout << (got == expected ? "PASS" : "FAIL") << std::endl;
		}
		else if(outerPolygon != NULL)
		{
			bool got = innerCircle->containedWithin(*outerPolygon);
			std::cout << (got == expected ? "PASS" : "FAIL") << std::endl;
		}
		else if(outerReuTriangle != NULL)
		{
			bool got = innerCircle->containedWithin(*outerReuTriangle);
			std::cout << (got == expected ? "PASS" : "FAIL") << std::endl;	
		}
	}
	else if(innerPolygon != NULL)
	{
		if(outerCircle != NULL)
		{
			bool got = innerPolygon->containedWithin(*outerCircle);
			std::cout << (got == expected ? "PASS" : "FAIL") << std::endl;
		}
		else if(outerPolygon != NULL)
		{
			bool got = innerPolygon->containedWithin(*outerPolygon);
			std::cout << (got == expected ? "PASS" : "FAIL") << std::endl;
		}
		else if(outerReuTriangle != NULL)
		{
			bool got = innerPolygon->containedWithin(*outerReuTriangle);
			std::cout << (got == expected ? "PASS" : "FAIL") << std::endl;	
		}
	}
	else if(innerReuTriangle != NULL)
	{
		if(outerCircle != NULL)
		{
			bool got = innerReuTriangle->containedWithin(*outerCircle);
			std::cout << (got == expected ? "PASS" : "FAIL") << std::endl;
		}
		else if(outerPolygon != NULL)
		{
			bool got = innerReuTriangle->containedWithin(*outerPolygon);
			std::cout << (got == expected ? "PASS" : "FAIL") << std::endl;
		}
		else if(outerReuTriangle != NULL)
		{
			bool got = innerReuTriangle->containedWithin(*outerReuTriangle);
			std::cout << (got == expected ? "PASS" : "FAIL") << std::endl;	
		}
	}
	else if(innerSphere != NULL)
	{
		if(outerSphere != NULL)
		{
			bool got = innerSphere->containedWithin(*outerSphere);
			std::cout << (got == expected ? "PASS" : "FAIL") << std::endl;
		}
		else if(outerCube != NULL)
		{
			bool got = innerSphere->containedWithin(*outerCube);
			std::cout << (got == expected ? "PASS" : "FAIL") << std::endl;
		}
		else if(outerReuTetrahedron != NULL)
		{
			bool got = innerSphere->containedWithin(*outerReuTetrahedron);
			std::cout << (got == expected ? "PASS" : "FAIL") << std::endl;	
		}
	}
	else if(innerCube != NULL)
	{
		if(outerSphere != NULL)
		{
			bool got = innerCube->containedWithin(*outerSphere);
			std::cout << (got == expected ? "PASS" : "FAIL") << std::endl;
		}
		else if(outerCube != NULL)
		{
			bool got = innerCube->containedWithin(*outerCube);
			std::cout << (got == expected ? "PASS" : "FAIL") << std::endl;
		}
		else if(outerReuTetrahedron != NULL)
		{
			bool got = innerCube->containedWithin(*outerReuTetrahedron);
			std::cout << (got == expected ? "PASS" : "FAIL") << std::endl;	
		}
	}
	else if(innerReuTetrahedron != NULL)
	{
		if(outerSphere != NULL)
		{
			bool got = innerReuTetrahedron->containedWithin(*outerSphere);
			std::cout << (got == expected ? "PASS" : "FAIL") << std::endl;
		}
		else if(outerCube != NULL)
		{
			bool got = innerReuTetrahedron->containedWithin(*outerCube);
			std::cout << (got == expected ? "PASS" : "FAIL") << std::endl;
		}
		else if(outerReuTetrahedron != NULL)
		{
			bool got = innerReuTetrahedron->containedWithin(*outerReuTetrahedron);
			std::cout << (got == expected ? "PASS" : "FAIL") << std::endl;	
		}
	}
}


int main(int argc, char *argv[]) 
{
    if (argc < 2) {
        printf(USAGE, argv[0]);
        return -1;
    }
    
    std::cout << "Test file: " << argv[1] << std::endl;
    

    //https://opencast-player-1.lt.ucsc.edu:8443/engage/theodul/ui/core.html?id=f1b2136b-19ef-4971-b4c6-504eadc46eac
    std::ifstream ifs(argv[1]);
    
    if(ifs) 
    {
    	std::string line;
    	while(std::getline(ifs, line))
    	{
    		if(line[0] != '#' && line != "") parse(line);
    	}
    }
	
	return 0;
}
