#include "terra.h"

Terra::Terra(float a, float p, float y) : Objecte(NumVerticesF)
{
    Index = 0;
    tam = 1;

    xorig = 0;
    yorig = y;
    zorig = 0;

    xRot = 0;
    yRot = 0;
    zRot = 0;

    createTerra(a, p);

    make();
}

void Terra::createTerra(float a, float p){
    //Construir vertexs
    point4 tl(xorig-a/2,yorig,zorig+p/2,1);
    point4 tr(xorig+a/2,yorig,zorig+p/2,1);
    point4 br(xorig+a/2,yorig,zorig-p/2,1);
    point4 bl(xorig-a/2,yorig,zorig-p/2,1);
    vertexs.push_back(tl);
    vertexs.push_back(tr);
    vertexs.push_back(br);
    vertexs.push_back(bl);

    //Construir cares
    Cara cara1(0,3,2);
    cara1.color = vec4(1.0, 0.0, 0.0, 1.0);
    Cara cara2(2,1,0);
    cara2.color = vec4(1.0, 0.0, 0.0, 1.0);

    //Afegir cares a vector de cares
    cares.push_back(cara1);
    cares.push_back(cara2);
}
