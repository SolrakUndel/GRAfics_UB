#ifndef OBSTACLE_H
#define OBSTACLE_H

#include <objecte.h>

class Obstacle : public Objecte
{
public:
    Obstacle(float y, double girX, double girY, double girZ);

private:
    static const int NumVerticesF = 36;
    static const int NumCares = 6;
};

#endif // OBSTACLE_H
