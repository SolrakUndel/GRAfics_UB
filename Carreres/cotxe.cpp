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


    nom = n;
    Index = 0;

    readObj(n);

    make();

    calculCapsa3D();

    if (capsa.a > capsa.h) max = capsa.a;
    else max = capsa.h;
    if (capsa.p > max) max = capsa.p;

    aplicaTG(Translate(-x0,-y0,-z0));
    aplicaTG(Scale(tam/max,tam/max,tam/max));
    //aplicaTG(Translate(x0/min,y0/min,z0/min));

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
    roda_posterior_dreta.make();
    carro.make();
}

void Cotxe::toGPU(QGLShaderProgram *p){
    roda_devantera_esquerra.toGPU(p);
    roda_devantera_dreta.toGPU(p);
    roda_posterior_dreta.toGPU(p);
    roda_posterior_dreta.toGPU(p);
    carro.toGPU(p);
}

void Cotxe::draw(){
    roda_devantera_esquerra.draw();
    roda_devantera_dreta.draw();
    roda_posterior_dreta.draw();
    roda_posterior_dreta.draw();
    carro.draw();
}

void Cotxe::aplicaTG(mat4 m){
    roda_devantera_esquerra.aplicaTG(m);
    roda_devantera_dreta.aplicaTG(m);
    roda_posterior_dreta.aplicaTG(m);
    roda_posterior_dreta.aplicaTG(m);
    carro.aplicaTG(m);
}

void Cotxe::aplicaTGPoints(mat4 m){
    roda_devantera_esquerra.aplicaTGPoints(m);
    roda_devantera_dreta.aplicaTGPoints(m);
    roda_posterior_dreta.aplicaTGPoints(m);
    roda_posterior_dreta.aplicaTGPoints(m);
    carro.aplicaTGPoints(m);
}

Capsa3D Cotxe::calculCapsa3D(){
    vector<Capsa3D> capses;

    capses.push_back(roda_devantera_esquerra.calculCapsa3D());
    capses.push_back(roda_devantera_dreta.calculCapsa3D());
    capses.push_back(roda_posterior_dreta.calculCapsa3D());
    capses.push_back(roda_posterior_dreta.calculCapsa3D());
    capses.push_back(carro.calculCapsa3D());

    vec3 pmin = capses[0].pmin;
    vec3 pmax = vec3(capses[0].a,capses[0].h,capses[0].p);

    for (int i = 1; i < capses.size(); ++i){
        if (capses[i].pmin.x < pmin.x) pmin.x = capses[i].pmin.x;
        if (capses[i].a > pmax.x) pmax.x = capses[i].a;

        if (capses[i].pmin.y < pmin.y) pmin.y = capses[i].pmin.y;
        if (capses[i].h > pmax.y) pmax.y = capses[i].h;

        if (capses[i].pmin.z < pmin.z) pmin.z = capses[i].pmin.z;
        if (capses[i].p > pmax.z) pmax.z = capses[i].p;
    }

    capsa.pmin = pmin;
    capsa.a = pmax.x;
    capsa.p = pmax.z;
    capsa.h = pmax.y;

    return capsa;
}

void Cotxe::forward(){
    // Metode a implementar per fer el moviment del cotxe
}

void Cotxe::backward(){
    // Metode a implementar per fer el moviment del cotxe

}

void Cotxe::turnleft(){
    // Metode a implementar per fer el moviment del cotxe

}

void Cotxe::turnright(){
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
