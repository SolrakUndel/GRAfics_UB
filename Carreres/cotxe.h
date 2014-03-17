#ifndef COTXE_H
#define COTXE_H

#include <Common.h>
#include <objecte.h>

#include <iostream>
#include <carrosseria.h>
#include <roda.h>

using namespace std;

class Cotxe: public Objecte
{
public:
    Cotxe(QString n);
    Cotxe(QString n, GLfloat tamanio, GLfloat x0, GLfloat y0, GLfloat z0,
          double girx, double giry, double girz,
          float xdir, float ydir, float zdir);
    virtual void readObj(QString filename);
    virtual void make();
    virtual void toGPU(QGLShaderProgram *p);
    virtual void draw();
    void aplicaTG(mat4 m);
    void aplicaTGPoints(mat4 m);
    Capsa3D calculCapsa3D();


    void forward();
    void backward();
    void turnleft();
    void turnright();
    point4 direction;

private:

    Carrosseria carro;
    Roda roda_devantera_esquerra;
    Roda roda_devantera_dreta;
    Roda roda_posterior_dreta;
    Roda roda_posterior_esquerra;

    static const int NumVerticesF = 100000;
    static const int NumCares = 300000;


};

#endif // COTXE_H
