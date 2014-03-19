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
    for (int i = 0; i < obstacles.size(); i++) capses.push_back(obstacles[i]->calculCapsa3D());

    if (capses.size() > 0) {
        //Requiere comprobacion de funcionamiento
        vec3 pmin = capses[0].pmin;
        vec3 pmax = vec3(capses[0].pmin.x + capses[0].a,capses[0].pmin.y + capses[0].h, capses[0].pmin.z + capses[0].p);

        for (int i = 1; i < capses.size(); ++i){
            if (capses[i].pmin.x < pmin.x) pmin.x = capses[i].pmin.x;
            if ((capses[i].pmin.x + capses[i].a) > pmax.x) pmax.x = capses[i].pmin.x + capses[i].a;

            if (capses[i].pmin.y < pmin.y) pmin.y = capses[i].pmin.y;
            if ((capses[i].pmin.y + capses[i].h) > pmax.y) pmax.y = capses[i].pmin.y + capses[i].h;

            if (capses[i].pmin.z < pmin.z) pmin.z = capses[i].pmin.z;
            if ((capses[i].pmin.z + capses[i].p) > pmax.z) pmax.z = capses[i].pmin.z + capses[i].p;
        }

        capsaMinima.pmin = pmin;
        capsaMinima.a = pmax.x - pmin.x;
        capsaMinima.p = pmax.z - pmin.y;
        capsaMinima.h = pmax.y - pmin.z;
    }
}

void escena::aplicaTG(mat4 m) {

    // Metode a modificar, modificar

    if (cotxe!=NULL)
        cotxe->aplicaTG(m);
    if (terra!=NULL)
        terra->aplicaTG(m);
    for (int i = 0; i < obstacles.size(); i++){
        obstacles[i]->aplicaTG(m);
    }

}

void escena::aplicaTGCentrat(mat4 m) {

    // Metode a modificar, modificat
    this->CapsaMinCont3DEscena();

    vec3 pmig = vec3(capsaMinima.pmin.x + capsaMinima.a/2, capsaMinima.pmin.y + capsaMinima.h/2, capsaMinima.pmin.z + capsaMinima.p/2);
    mat4 trans1 = Translate(pmig.x,pmig.y ,pmig.z)*m*Translate(-pmig.x,-pmig.y ,-pmig.z);
    if (cotxe!=NULL)
        cotxe->aplicaTG(m);
    if (terra!=NULL)
        terra->aplicaTG(m);
    for (int i = 0; i < obstacles.size(); i++){
        obstacles[i]->aplicaTG(m);
    }
}

void escena::draw() {

    // Metode a modificar, modificat

    if (cotxe!=NULL)
        cotxe->draw();
    if (terra!=NULL)
        terra->draw();
    for (int i = 0; i < obstacles.size(); i++){
        obstacles[i]->draw();
    }

}

void escena::reset() {

    // Metode a modificar, modificat

    if (cotxe!=NULL)
        cotxe->make();
    if (terra!=NULL)
        terra->make();
    for (int i = 0; i < obstacles.size(); i++){
        obstacles[i]->make();
    }
}

