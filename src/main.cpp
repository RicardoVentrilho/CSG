#include <math.h>
#include <iostream>

#include "global.h"
#include "compartilhado.h"
#include "enumeradores/enumcsg.h"
#include "enumeradores/enumobjeto.h"
#include "enumeradores/enumdirecao.h"
#include "infraestrutura/janela.h"

using namespace enumeradores;
using namespace infraestrutura;
using namespace std;

int main()
{
    try
    {
        static GLfloat lightpos[] = {25.f, 50.f, -50.f, 1.f};
        static GLfloat sphere_mat[] = {1.f, .5f, 0.f, 1.f};
        static GLfloat cone_mat[] = {0.f, .5f, 1.f, 1.f};
        GLUquadricObj *sphere, *cone, *base;

        auto janela = new Janela(512, 512);

        janela->mostre("Computação Gráfica");

//        janela->set_funcao_de_tela(redraw);
//        janela->set_funcao_de_teclado(key);
//        janela->set_funcao_especial(special);
//        janela->set_funcao_de_Mouse(mouse);
//        janela->set_funcao_de_Movimento(motion);
//        janela->set_menu(menu);

        //set_funcoes
        glutDisplayFunc(redraw);
        glutKeyboardFunc(ao_precionar_tecla);
        glutSpecialFunc(special);
        glutMouseFunc(ao_clicar_no_mouse);
        glutMotionFunc(motion);

        //set_menu
        glutCreateMenu(altere_opcao_do_menu);
        glutAddMenuEntry("A only", CSG_A);
        glutAddMenuEntry("B only", CSG_B);
        glutAddMenuEntry("A or B", CSG_A_OR_B);
        glutAddMenuEntry("A and B", CSG_A_AND_B);
        glutAddMenuEntry("A sub B", CSG_A_SUB_B);
        glutAddMenuEntry("B sub A", CSG_B_SUB_A);
        glutAttachMenu(GLUT_RIGHT_BUTTON);

        glEnable(GL_CULL_FACE);
        glEnable(GL_LIGHTING);
        glEnable(GL_LIGHT0);

        glLightfv(GL_LIGHT0, GL_POSITION, lightpos);
        glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);

        glNewList(SPHERE, GL_COMPILE);
        sphere = gluNewQuadric();
        glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, sphere_mat);
        gluSphere(sphere, 20.f, 64, 64);
        gluDeleteQuadric(sphere);
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







