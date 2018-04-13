#include <stdio.h>
#include <stdlib.h>

#include "bounds.h"

//https://opencast-player-1.lt.ucsc.edu:8443/engage/theodul/ui/core.html?id=785d50a3-c653-46b8-b9f6-0c468e959ac7
// for the part that checks circle within circle
/*
 * Intialise a two or three dimensional space of shape ARENA containing NUMSHAPES 
 * SHAPES, all of which may or may not be entirely contained within ARENA.
 */
void setup(Shape *arena, Shape *shapes[], int numShapes) {
    int ununsed; // here to fail warnings test, remove it
}

/*
 * Move the centroid of SHAPE to POINT. 
 *
 * Return TRUE if SHAPE remains entirely within the space defined by the 
 * ARENA parameter of setup(), FALSE otherwise.
 */
bool move(Shape *shape, Point *point) {
    printf("Not implemented!\n");
    exit(-1);
}
