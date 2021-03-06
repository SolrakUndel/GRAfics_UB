#include "cotxe.h"
#include "readfile.h"

Cotxe::Cotxe(QString n) : Objecte(NumVerticesF)
{
    nom = n;
    Index = 0;
    tam = 1;

    xorig = 0;
    yorig = 0;
    zorig = 0;

    xRot = 0;
    yRot = 0;
    zRot = 0;

    this->direction[0] = -1;
    this->direction[1] = 0;
    this->direction[2] = 0;
    this->direction[3] = 0;
    readObj(n);

    make();
}

Cotxe::Cotxe(QString n, GLfloat tamanio, GLfloat x0, GLfloat y0, GLfloat z0,
             double girx, double giry, double girz,
             float xdir, float ydir, float zdir) : Objecte(0)
{
    // El seguent codi escala el cotxe entre 0 i 1 i el situa el seu centre  0,0,0. aixo fa que es vegi en la primera visualització
    //
    // Cal modificar el codi seguent
    GLfloat max;


    tam = tamanio;
    std::cout<<"Estic en el constructor parametritzat del cotxe\n";
    xorig = x0;
    yorig = y0;
    zorig = z0;

    xRot = girx;
    yRot = giry;
    zRot = girz;

    roda_devantera_esquerra.xRot = 0;
    roda_devantera_dreta.xRot = 0;
    roda_posterior_dreta.xRot = 0;
    roda_posterior_esquerra.xRot = 0;

    roda_devantera_esquerra.yRot = 0;
    roda_devantera_dreta.yRot = 0;
    roda_posterior_dreta.yRot = 0;
    roda_posterior_esquerra.yRot = 0;

    roda_devantera_esquerra.zRot = 0;
    roda_devantera_dreta.zRot = 0;
    roda_posterior_dreta.zRot = 0;
    roda_posterior_esquerra.zRot = 0;

    direction.x = xdir;
    direction.y = ydir;
    direction.z = zdir;
    direction.w = 0;

    nom = n;
    Index = 0;

    initialized = 0;

    readObj(n);

    make();

    calculCapsa3D();

    if (capsa.a > capsa.h) max = capsa.a;
    else max = capsa.h;
    if (capsa.p > max) max = capsa.p;

    mat4 m = Translate(xorig,yorig,zorig)*RotateZ(zRot)*RotateY(yRot-180)*RotateX(xRot)*Scale(tam/max,tam/max,tam/max);
    aplicaTG(m);


    /*double escalaX = 1.0 / 4.6;
    mat4 m= Translate(-1.93*escalaX, (+0.26)*escalaX, -2.16*escalaX)*Scale(escalaX, escalaX, escalaX)*Translate(+1.93, -0.26, 2.16);

    aplicaTG(m);*/

}

// Llegeix un fitxer .obj
//  Si el fitxer referencia fitxers de materials (.mtl), encara no es llegeixen
//  Tots els elements del fitxer es llegeixen com a un unic objecte.
//

void Cotxe::make()
{
    roda_devantera_esquerra.make();
    roda_devantera_dreta.make();
    roda_posterior_dreta.make();
    roda_posterior_esquerra.make();
    carro.make();
}

void Cotxe::toGPU(QGLShaderProgram *p){
    roda_devantera_esquerra.toGPU(p);
    roda_devantera_dreta.toGPU(p);
    roda_posterior_dreta.toGPU(p);
    roda_posterior_esquerra.toGPU(p);
    carro.toGPU(p);
}

void Cotxe::draw(){
    roda_devantera_esquerra.draw();
    roda_devantera_dreta.draw();
    roda_posterior_dreta.draw();
    roda_posterior_esquerra.draw();
    carro.draw();
}

void Cotxe::aplicaTG(mat4 m){
    roda_devantera_esquerra.aplicaTG(m);
    roda_devantera_dreta.aplicaTG(m);
    roda_posterior_dreta.aplicaTG(m);
    roda_posterior_esquerra.aplicaTG(m);
    carro.aplicaTG(m);
}

void Cotxe::aplicaTGPoints(mat4 m){
    roda_devantera_esquerra.aplicaTGPoints(m);
    roda_devantera_dreta.aplicaTGPoints(m);
    roda_posterior_dreta.aplicaTGPoints(m);
    roda_posterior_esquerra.aplicaTGPoints(m);
    carro.aplicaTGPoints(m);
}

void Cotxe::aplicaTGCentrat(mat4 m){
    mat4 mat = Translate(xorig,yorig,zorig)*m*Translate(-xorig,-yorig,-zorig);
    this->aplicaTG(m);
}

Capsa3D Cotxe::calculCapsa3D(){
    vector<Capsa3D> capses;

    capses.push_back(roda_devantera_esquerra.calculCapsa3D());
    capses.push_back(roda_devantera_dreta.calculCapsa3D());
    capses.push_back(roda_posterior_dreta.calculCapsa3D());
    capses.push_back(roda_posterior_esquerra.calculCapsa3D());
    capses.push_back(carro.calculCapsa3D());

    if (initialized == 0){
        //Initialization of the wheels
        roda_devantera_esquerra.xorig = capses[0].pmin.x+capses[0].a/2;
        roda_devantera_esquerra.yorig = capses[0].pmin.y+capses[0].h/2;
        roda_devantera_esquerra.zorig = capses[0].pmin.z+capses[0].p/2;

        roda_devantera_dreta.xorig = capses[1].pmin.x+capses[1].a/2;
        roda_devantera_dreta.yorig = capses[1].pmin.y+capses[1].h/2;
        roda_devantera_dreta.zorig = capses[1].pmin.z+capses[1].p/2;

        roda_posterior_dreta.xorig = capses[2].pmin.x+capses[2].a/2;
        roda_posterior_dreta.yorig = capses[2].pmin.y+capses[2].h/2;
        roda_posterior_dreta.zorig = capses[2].pmin.z+capses[2].p/2;

        roda_posterior_esquerra.xorig = capses[3].pmin.x+capses[3].a/2;
        roda_posterior_esquerra.yorig = capses[3].pmin.y+capses[3].h/2;
        roda_posterior_esquerra.zorig = capses[3].pmin.z+capses[3].p/2;

        initialized = 1;
    }

    vec3 pmin = capses[0].pmin;
    vec3 pmax = vec3(capses[0].pmin.x + capses[0].a, capses[0].pmin.y + capses[0].h, capses[0].pmin.z + capses[0].p);

    for (int i = 1; i < capses.size(); ++i){
        if (capses[i].pmin.x < pmin.x) pmin.x = capses[i].pmin.x;
        if ((capses[i].pmin.x + capses[i].a) > pmax.x) pmax.x = capses[i].pmin.x + capses[i].a;

        if (capses[i].pmin.y < pmin.y) pmin.y = capses[i].pmin.y;
        if ((capses[i].pmin.y + capses[i].h) > pmax.y) pmax.y = capses[i].pmin.y + capses[i].h;

        if (capses[i].pmin.z < pmin.z) pmin.z = capses[i].pmin.z;
        if ((capses[i].pmin.z + capses[i].p) > pmax.z) pmax.z = capses[i].pmin.z + capses[i].p;
    }

    capsa.pmin = pmin;
    capsa.a = pmax.x - pmin.x;
    capsa.p = pmax.z - pmin.y;
    capsa.h = pmax.y - pmin.z;

    return capsa;
}

void Cotxe::forward(mat4 rot1, mat4 rot2){
    // Metode a implementar per fer el moviment del cotxe
    /*if (direction.x < max_speed){
        direction += 0.1;
    }*/
    if (((xorig + capsa.a) > 2) || ((zorig + capsa.p) > 2)) {

    } else {
        mat4 m = Translate(0.2,0,0);
        vec4 aux(xorig, yorig, zorig, 1);
        aux = m*aux;
        xorig = aux.x;
        yorig = aux.y;
        zorig = aux.z;
        mat4 mat = rot2*RotateY(yRot)*m*RotateY(-yRot)*rot1;

        aplicaTG(mat);
    }
}

void Cotxe::backward(mat4 rot1, mat4 rot2){
    /*if (direction.x < max_speed){
        direction -= 0.1;
    }*/
    if (((xorig) < -2) || ((zorig) < -2)) {

    } else {
        mat4 m = Translate(-0.2,0,0);
        vec4 aux(xorig, yorig, zorig, 1);
        aux = m*aux;
        xorig = aux.x;
        yorig = aux.y;
        mat4 mat = rot2*RotateY(yRot)*m*RotateY(-yRot)*rot1;
        aplicaTG(mat);
        // Metode a implementar per fer el moviment del cotxe
    }
}

void Cotxe::turnleft(mat4 rot1, mat4 rot2){
    yRot += 10;
    if (yRot > 360) {
        yRot -= 360;
    }
    mat4 mat = rot2*Translate(xorig,yorig,zorig)*RotateY(10)*Translate(-xorig,-yorig,-zorig)*rot1;

    aplicaTG(mat);
    // Metode a implementar per fer el moviment del cotxe

}

void Cotxe::turnright(mat4 rot1, mat4 rot2){
    yRot -= 10;
    if (yRot < 0) {
        yRot += 360;
    }
    mat4 mat = rot2*Translate(xorig,yorig,zorig)*RotateY(-10)*Translate(-xorig,-yorig,-zorig)*rot1;
    aplicaTG(mat);

    // Metode a implementar per fer el moviment del cotxe

}


void Cotxe::readObj(QString filename)
{

    FILE *fp = fopen(filename.toLocal8Bit(),"rb");
    if (!fp)
    {
        cout << "No puc obrir el fitxer " << endl;
    }
    else {
        Objecte * obj_pointer;
        int vindexAct = 0;
        int vindexUlt = 0;

        while (true)
        {
            char *comment_ptr = ReadFile::fetch_line (fp);

            if (comment_ptr == (char *) -1)  /* end-of-file */
                break;

            /* did we get a comment? */
            if (comment_ptr) {
                //make_comment (comment_ptr);
                continue;
            }

            /* if we get here, the line was not a comment */
            int nwords = ReadFile::fetch_words();

            /* skip empty lines */
            if (nwords == 0)
                continue;

            char *first_word = ReadFile::words[0];

            if (!strcmp (first_word, "v"))
            {
                if (nwords < 4)
                {
                    fprintf (stderr, "Too few coordinates");//: '%s'", str_orig);
                    exit (-1);
                }
                QString sx(ReadFile::words[1]);
                QString sy(ReadFile::words[2]);
                QString sz(ReadFile::words[3]);
                double x = sx.toDouble();
                double y = sy.toDouble();
                double z = sz.toDouble();

                if (nwords == 5)
                {
                  QString sw(ReadFile::words[4]);
                  double w = sw.toDouble();
                  x/=w;
                  y/=w;
                  z/=w;
                }
                // S'afegeix el vertex a l'objecte
                obj_pointer->vertexs.push_back(point4(x, y, z, 1));
                vindexAct++;

            }
            else if (!strcmp (first_word, "vn")) {
            }
            else if (!strcmp (first_word, "vt")) {
            }
            else if (!strcmp (first_word, "f")) {
                // S'afegeix la cara a l'objecte
                construeix_cara (&ReadFile::words[1], nwords-1, obj_pointer, vindexUlt);
            }
            // added
            else if (!strcmp (first_word, "mtllib")) {
                //read_mtllib (&words[1], nwords-1, matlib, filename);
            }
            else if (!strcmp (first_word, "usemtl")) {
                //int size = strlen(words[1])-1;
                //while (size && (words[1][size]=='\n' || words[1][size]=='\r') ) words[1][size--]=0;
                //currentMaterial = matlib.index(words[1]);
            }
            else if (!strcmp (first_word, "o")) {
                //cada nou objecte s'actualitza aquest Ã­ndex
                vindexUlt = vindexAct;
                if (nwords == 2)
                {
                    QString aux(ReadFile::words[1]);
                    if (aux == "Roda_Esquerra_Posterior_Untitled") obj_pointer = &roda_posterior_esquerra;
                    else if (aux == "Roda_Dreta_Posterior_04") obj_pointer = &roda_posterior_dreta;
                    else if (aux == "Roda_Esquerra_Davantera_02") obj_pointer = &roda_devantera_esquerra;
                    else if (aux == "Roda_Dreta_Davantera_03") obj_pointer = &roda_devantera_dreta;
                    else if (aux == "Carrosseria_00") obj_pointer = &carro;
                }
            }
            // fadded
            else {
                //fprintf (stderr, "Do not recognize: '%s'\n", str_orig);
            }

            //free(words);
        }
    }

}
