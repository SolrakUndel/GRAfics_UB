#ifndef TERRA_H
#define TERRA_H

#include <objecte.h>

class Terra : public Objecte
{
public:
    Terra(float a, float p, float y);
    void createTerra(float a, float p);

private:
    static const int NumVerticesF = 6;
    static const int NumCares = 2;

};

#endif // TERRA_H
