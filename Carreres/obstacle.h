#ifndef OBSTACLE_H
#define OBSTACLE_H

#include <objecte.h>

class Obstacle : public Objecte
{
public:
    Obstacle(float y);

private:
    void createObstacle();
    float a;
    float h;
    float p;

    static const int NumVerticesF = 36;
    static const int NumCares = 1;
};

#endif // OBSTACLE_H
