#include "obstacle.h"

Obstacle::Obstacle(float y, double girX, double girY, double girZ): Objecte(NumVerticesF)
{
    Index = 0;
    tam = 1;

    xorig = 0;
    yorig = y;
    zorig = 0;

    xRot = girX;
    yRot = girY;
    zRot = girZ;
}
