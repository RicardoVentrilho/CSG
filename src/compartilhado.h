#ifndef COMPARTILHADO_H
#define COMPARTILHADO_H

#include "global.h"
#include "enumeradores/enumcsg.h"
#include "enumeradores/enumobjeto.h"
#include "enumeradores/enumdirecao.h"
#include "infraestrutura/janela.h"

/////////REFATORADO

void altere_opcao_do_menu(int opcao)
{
  OPCAO_DO_MENU = opcao;
  glutPostRedisplay();
}

void rotacione(void)
{
  if(DIRECAO_DA_ANIMACAO == ANIM_LEFT)
  {
    ANGULO_DE_ROTACAO -= 3.f;
  }
  else
  {
    ANGULO_DE_ROTACAO += 3.f;
  }

  glutPostRedisplay();
}

void ao_precionar_tecla(unsigned char tecla, int x, int y)
{
  switch(tecla) {
      case 'a':
        ANGULO_DE_ROTACAO -= 10.f;
        glutPostRedisplay();
        break;
      case 's':
        ANGULO_DE_ROTACAO += 10.f;
        glutPostRedisplay();
        break;
      case '\033': //ESC
        exit(0);
  }
}

void ao_clicar_no_mouse(int button, int state, int x, int y)
{
    if(state == GLUT_UP) {
        picked_object = button;
        xpos += newxpos;
        ypos += newypos;
        newxpos = 0;
        newypos = 0;
    } else { /* GLUT_DOWN */
        startx = x;
        starty = y;
    }
}


///////////////////

void one(void(*a)(void))
{
  glEnable(GL_DEPTH_TEST);
  a();
  glDisable(GL_DEPTH_TEST);
}

void ou(void(*a)(void), void(*b)())
{
  glEnable(GL_DEPTH_TEST);
  a();
  b();
  glDisable(GL_DEPTH_TEST);
}

void firstInsideSecond(void(*a)(void), void(*b)(void), GLenum face, GLenum test)
{
  glEnable(GL_DEPTH_TEST);
  glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE);
  glCullFace(face); /* controls which face of a to use*/
  a(); /* draw a face of a into depth buffer */

  /* use stencil plane to find parts of a in b */
  glDepthMask(GL_FALSE);
  glEnable(GL_STENCIL_TEST);
  glStencilFunc(GL_ALWAYS, 0, 0);
  glStencilOp(GL_KEEP, GL_KEEP, GL_INCR);
  glCullFace(GL_BACK);
  b(); /* increment the stencil where the front face of b is drawn */
  glStencilOp(GL_KEEP, GL_KEEP, GL_DECR);
  glCullFace(GL_FRONT);
  b(); /* decrement the stencil buffer where the back face of b is drawn */
  glDepthMask(GL_TRUE);
  glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);

  glStencilFunc(test, 0, 1);
  glDisable(GL_DEPTH_TEST);

  glCullFace(face);
  a(); /* draw the part of a that's in b */
}

void fixDepth(void(*a)(void))
{
  glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE);
  glEnable(GL_DEPTH_TEST);
  glDisable(GL_STENCIL_TEST);
  glDepthFunc(GL_ALWAYS);
  a(); /* draw the front face of a, fixing the depth buffer */
  glDepthFunc(GL_LESS);
}

/* "and" two objects together */
void e(void(*a)(void), void(*b)(void))
{
  firstInsideSecond(a, b, GL_BACK, GL_NOTEQUAL);

  fixDepth(b);

  firstInsideSecond(b, a, GL_BACK, GL_NOTEQUAL);

  glDisable(GL_STENCIL_TEST); /* reset things */
}

/* subtract b from a */
void sub(void(*a)(void), void(*b)(void))
{
  firstInsideSecond(a, b, GL_FRONT, GL_NOTEQUAL);

  fixDepth(b);

  firstInsideSecond(b, a, GL_BACK, GL_EQUAL);

  glDisable(GL_STENCIL_TEST); /* reset things */
}

void cone(void)
{
  glPushMatrix();
  glTranslatef(POSICAO_DO_CONE_NO_EIXO_X, POSICAO_DO_CONE_NO_EIXO_Y, POSICAO_DO_CONE_NO_EIXO_Z);
  glTranslatef(0.f, 0.f, -30.f);
  glCallList(CONE);
  glPopMatrix();
}

void sphere(void)
{
  glPushMatrix();
  glTranslatef(POSICAO_DA_ESFERA_NO_EIXO_X, POSICAO_DA_ESFERA_NO_EIXO_Y, POSICAO_DA_ESFERA_NO_EIXO_Z);
  glCallList(SPHERE);
  glPopMatrix();

}

void redraw()
{
  /* clear stencil each time */
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT|GL_STENCIL_BUFFER_BIT);

    glPushMatrix();
    glRotatef(ANGULO_DE_ROTACAO, 0.f, 1.f, 0.f);

    switch(OPCAO_DO_MENU) {
    case CSG_A:
      one(cone);
      break;
    case CSG_B:
      one(sphere);
      break;
    case CSG_A_OR_B:
      ou(cone, sphere);
      break;
    case CSG_A_AND_B:
      e(cone, sphere);
      break;
    case CSG_A_SUB_B:
      sub(cone, sphere);
      break;
    case CSG_B_SUB_A:
      sub(sphere, cone);
      break;
    }
    glPopMatrix();
    glutSwapBuffers();
}

/* special keys, like array and F keys */
void special(int key, int x, int y)
{
  switch(key) {
      case GLUT_KEY_LEFT:
        glutIdleFunc(rotacione);
        DIRECAO_DA_ANIMACAO = ANIM_LEFT;
        break;
      case GLUT_KEY_RIGHT:
        glutIdleFunc(rotacione);
        DIRECAO_DA_ANIMACAO = ANIM_RIGHT;
        break;
      case GLUT_KEY_UP:
      case GLUT_KEY_DOWN:
        glutIdleFunc(0);
        break;
  }
}


#define DEGTORAD (2 * 3.1415 / 360)
void motion(int x, int y)
{
  GLfloat r, objx, objy, objz;

  newxpos = x - startx;
  newypos = starty - y;

  r = (newxpos + xpos) * 50.f / 512.f;

  objx = r * (float)cos(ANGULO_DE_ROTACAO * DEGTORAD);
  objz = r * (float)sin(ANGULO_DE_ROTACAO * DEGTORAD);
  objy = (newypos + ypos) * 50.f/512.f;

  switch(picked_object) {
      case CSG_A:
        POSICAO_DO_CONE_NO_EIXO_X = objx;
        POSICAO_DO_CONE_NO_EIXO_Y = objy;
        POSICAO_DO_CONE_NO_EIXO_Z = objz;
        break;

      case CSG_B:
        POSICAO_DA_ESFERA_NO_EIXO_X = objx;
        POSICAO_DA_ESFERA_NO_EIXO_Y = objy;
        POSICAO_DA_ESFERA_NO_EIXO_Z = objz;
        break;
      default:
        break;
  }

  glutPostRedisplay();
}


#endif // COMPARTILHADO_H
