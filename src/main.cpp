#include <math.h>
#include <iostream>

#include "global.h"
#include "compartilhado.h"
#include "enumeradores/enumcsg.h"
#include "enumeradores/enumobjeto.h"
#include "enumeradores/enumdirecao.h"

using namespace enumeradores;
using namespace std;

int main(int argc, char** argv)
{
    try
    {
        static GLfloat light_posicoes[] = { 25.f, 50.f, -50.f, 1.f };
        static GLfloat esfera_mat[] = { 1.f, .5f, 0.f, 1.f };
        static GLfloat cone_mat[] = { 0.f, .5f, 1.f, 1.f };

        GLUquadricObj *esfera, *cone, *base;

        glutInit(&argc, argv);
        glutInitWindowSize(512, 512);
        glutInitDisplayMode(GLUT_STENCIL|GLUT_DEPTH|GLUT_DOUBLE);
        (void)glutCreateWindow("Computação Gráfica");

        glutDisplayFunc(redesenhe);
        glutSpecialFunc(ao_pressionar_teclas_de_direcao);
        glutMouseFunc(ao_clicar_no_mouse);
        glutMotionFunc(ao_movimentar);

        glutCreateMenu(altere_opcao_do_menu);
        glutAddMenuEntry("Somente objeto A", OBJETO_A);
        glutAddMenuEntry("Somente objeto B", OBJETO_B);
        glutAddMenuEntry("A conjuncao com B", A_CONJUNCAO_COM_B);
        glutAddMenuEntry("A disjuncao com B", A_DISJUNCAO_COM_B);
        glutAddMenuEntry("A interseccao com B", A_INTERSECCAO_COM_B);
        glutAddMenuEntry("B interseccao com A", B_INTERSECCAO_COM_A);
        glutAttachMenu(GLUT_RIGHT_BUTTON);

        glEnable(GL_CULL_FACE);
        glEnable(GL_LIGHTING);
        glEnable(GL_LIGHT0);

        glLightfv(GL_LIGHT0, GL_POSITION, light_posicoes);
        glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);

        glNewList(ESFERA, GL_COMPILE);
        esfera = gluNewQuadric();
        glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, esfera_mat);
        gluSphere(esfera, 20.f, 64, 64);
        gluDeleteQuadric(esfera);
        glEndList();

        glNewList(CONE, GL_COMPILE);
        cone = gluNewQuadric();
        base = gluNewQuadric();
        glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, cone_mat);
        gluQuadricOrientation(base, GLU_INSIDE);
        gluDisk(base, 0., 15., 64, 1);
        gluCylinder(cone, 15., 0., 60., 64, 64);
        gluDeleteQuadric(cone);
        gluDeleteQuadric(base);
        glEndList();

        glMatrixMode(GL_PROJECTION);
        glOrtho(-50., 50., -50., 50., -50., 50.);
        glMatrixMode(GL_MODELVIEW);
        glutMainLoop();
    }
    catch(const char * erro)
    {
        cerr << erro << endl;
    }

    return 0;
}







