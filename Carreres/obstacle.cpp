#include "obstacle.h"

Obstacle::Obstacle(float y): Objecte(NumVerticesF)
{
    Index = 0;
    tam = 1;

    a = ((float)(rand()%1001)) / 100;
    h = ((float)(rand()%1001)) / 100;
    p = ((float)(rand()%1001)) / 100;

    xorig = (((float)(rand()%5001))/100 -25.0) -a/2;
    yorig = y+h/2;
    zorig = (((float)(rand()%5001))/100 -25.0)-p/2;

    yRot = (((float)(rand()%5001))/100 -25.0)*180;


    createObstacle();

    make();
}

void Obstacle::createObstacle(){
    //Construir vertexs
    point4 base_tl(xorig-a/2,yorig-h/2,zorig+p/2,1);
    point4 base_tr(xorig+a/2,yorig-h/2,zorig+p/2,1);
    point4 base_br(xorig+a/2,yorig-h/2,zorig-p/2,1);
    point4 base_bl(xorig-a/2,yorig-h/2,zorig-p/2,1);

    point4 top_tl(xorig-a/2,yorig+h/2,zorig+p/2,1);
    point4 top_tr(xorig+a/2,yorig+h/2,zorig+p/2,1);
    point4 top_br(xorig+a/2,yorig+h/2,zorig-p/2,1);
    point4 top_bl(xorig-a/2,yorig+h/2,zorig-p/2,1);

    base_tl = RotateY(yRot)*base_tl;
    base_tr = RotateY(yRot)*base_tr;
    base_br = RotateY(yRot)*base_br;
    base_bl = RotateY(yRot)*base_bl;

    top_tl = RotateY(yRot)*top_tl;
    top_tr = RotateY(yRot)*top_tr;
    top_br = RotateY(yRot)*top_br;
    top_bl = RotateY(yRot)*top_bl;

    vertexs.push_back(base_tl);
    vertexs.push_back(base_tr);
    vertexs.push_back(base_br);
    vertexs.push_back(base_bl);
    vertexs.push_back(top_tl);
    vertexs.push_back(top_tr);
    vertexs.push_back(top_br);
    vertexs.push_back(top_bl);

    //Construir cares
    //Cares base
    Cara cara1(0,2,3);
    cara1.color = vec4(1.0, 0.0, 0.0, 1.0);
    Cara cara2(2,0,1);
    cara2.color = vec4(1.0, 0.0, 0.0, 1.0);

    //Cares esquerra
    Cara cara3(3,7,4);
    cara3.color = vec4(1.0, 0.0, 0.0, 1.0);
    Cara cara4(7,0,1);
    cara4.color = vec4(1.0, 0.0, 0.0, 1.0);

    //Cares fons
    Cara cara5(0,4,5);
    cara5.color = vec4(1.0, 0.0, 0.0, 1.0);
    Cara cara6(5,1,0);
    cara6.color = vec4(1.0, 0.0, 0.0, 1.0);

    //Cares dreta
    Cara cara7(2,5,6);
    cara7.color = vec4(1.0, 0.0, 0.0, 1.0);
    Cara cara8(5,2,1);
    cara8.color = vec4(1.0, 0.0, 0.0, 1.0);

    //Cares front
    Cara cara9(3,6,7);
    cara9.color = vec4(1.0, 0.0, 0.0, 1.0);
    Cara cara10(6,3,2);
    cara10.color = vec4(1.0, 0.0, 0.0, 1.0);

    //Cares top
    Cara cara11(4,7,6);
    cara11.color = vec4(1.0, 0.0, 0.0, 1.0);
    Cara cara12(6,5,4);
    cara12.color = vec4(1.0, 0.0, 0.0, 1.0);

    //Afegir cares a vector de cares
    cares.push_back(cara1);
    cares.push_back(cara2);
    cares.push_back(cara3);
    cares.push_back(cara4);
    cares.push_back(cara5);
    cares.push_back(cara6);
    cares.push_back(cara7);
    cares.push_back(cara8);
    cares.push_back(cara9);
    cares.push_back(cara10);
    cares.push_back(cara11);
    cares.push_back(cara12);

}
