#include <escena.h>

using namespace std;

escena::escena()

{
    // Capsa minima contenidora provisional: S'ha de fer un recorregut dels objectes de l'escenes
    capsaMinima.pmin[0] = 0; capsaMinima.pmin[1] = 0; capsaMinima.pmin[2]=0;
    capsaMinima.a = 1; capsaMinima.h = 1; capsaMinima.p = 1;

    cotxe = NULL;
    terra = NULL;
}


escena::~escena()
{
    printf("DESTRUCTOR!");

}

void escena::addObjecte(Objecte *obj) {
    if (dynamic_cast<Cotxe*>(obj))
        this->cotxe = (Cotxe*)obj;
    else if (dynamic_cast<Terra*>(obj))
        this->terra = (Terra*)obj;
    else if (dynamic_cast<Obstacle*>(obj))
        this->obstacles.push_back((Obstacle *)obj);
}


void escena::CapsaMinCont3DEscena()
{
    //Metode a modificar, modificar
    vector<Capsa3D> capses;

    if (cotxe!=NULL)
        capses.push_back(cotxe->calculCapsa3D());
    if (terra!=NULL)
        capses.push_back(terra->calculCapsa3D());

    if (capses.size() > 0) {
        //Requiere comprobacion de funcionamiento
        vec3 pmin = capses[0].pmin;
        vec3 pmax = capses[0].pmin + vec3(capses[0].a,capses[0].h,capses[0].p);

        for (int i = 1; i < capses.size(); ++i){
            if (capses[i].pmin.x < pmin.x) pmin.x = capses[i].pmin.x;
            if ((capses[i].pmin.x + capses[i].a) > pmax.x) pmax.x = capses[i].pmin.x + capses[i].a;

            if (capses[i].pmin.y < pmin.y) pmin.y = capses[i].pmin.y;
            if ((capses[i].pmin.y + capses[i].h)> pmax.y) pmax.y = capses[i].pmin.y + capses[i].h;

            if (capses[i].pmin.z < pmin.z) pmin.z = capses[i].pmin.z;
            if ((capses[i].pmin.z + capses[i].p) > pmax.z) pmax.z = capses[i].pmin.z + capses[i].p;
        }

        capsaMinima.pmin = pmin;
        capsaMinima.a = pmax.x-pmin.x;
        capsaMinima.p = pmax.z-pmin.z;
        capsaMinima.h = pmax.y-pmin.y;
    } else {
        capsaMinima.pmin = vec3(0,0,0);
        capsaMinima.a = 1;
        capsaMinima.p = 1;
        capsaMinima.h = 1;
    }
}

void escena::aplicaTG(mat4 m) {

    // Metode a modificar, modificar

    if (cotxe!=NULL)
        cotxe->aplicaTG(m);
    if (terra!=NULL)
        terra->aplicaTG(m);

}

void escena::aplicaTGCentrat(mat4 m) {

    // Metode a modificar, modificat

    if (cotxe!=NULL)
        cotxe->aplicaTGCentrat(m);
    if (terra!=NULL)
        terra->aplicaTGCentrat(m);

}

void escena::draw() {

    // Metode a modificar, modificat

    if (cotxe!=NULL)
        cotxe->draw();
    if (terra!=NULL)
        terra->draw();

}

void escena::reset() {

    // Metode a modificar, modificat

    if (cotxe!=NULL)
        cotxe->make();
    if (terra!=NULL)
        terra->make();
}

