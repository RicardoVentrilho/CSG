#ifndef COMPARTILHADO_H
#define COMPARTILHADO_H

#include <GL/glut.h>

#include "global.h"
#include "enumeradores/enumcsg.h"
#include "enumeradores/enumobjeto.h"
#include "enumeradores/enumdirecao.h"

void altere_opcao_do_menu(int opcao)
{
  OPCAO_DO_MENU = opcao;
  glutPostRedisplay();
}

void rotacione(void)
{
  if(DIRECAO_DA_ANIMACAO == ESQUERDA)
  {
    ANGULO_DE_ROTACAO -= 3.f;
  }
  else
  {
    ANGULO_DE_ROTACAO += 3.f;
  }

  glutPostRedisplay();
}

void ao_clicar_no_mouse(int click, int estado, int x, int y)
{
    if(estado == GLUT_UP) {
        OBJETO_PINTADO = click;
        POSICAO_X += NOVA_POSICAO_X;
        POSICAO_Y += NOVA_POSICAO_Y;
        NOVA_POSICAO_X = 0;
        NOVA_POSICAO_Y = 0;
    } else {
        POSICAO_INICIAL_X = x;
        POSICAO_INICIAL_Y = y;
    }
}

void ao_pressionar_teclas_de_direcao(int key, int x, int y)
{
    switch(key) {
    case GLUT_KEY_LEFT:
        glutIdleFunc(rotacione);
        DIRECAO_DA_ANIMACAO = ESQUERDA;
        break;
    case GLUT_KEY_RIGHT:
        glutIdleFunc(rotacione);
        DIRECAO_DA_ANIMACAO = DIREITA;
        break;
    default:
        glutIdleFunc(0);
        break;
    }
}

void interseccione(void(*desenhe_objeto_a)(void), void(*desenhe_objeto_b)(void), GLenum face, GLenum test)
{
  glEnable(GL_DEPTH_TEST);
  glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE);
  glCullFace(face);
  desenhe_objeto_a();

  glDepthMask(GL_FALSE);
  glEnable(GL_STENCIL_TEST);
  glStencilFunc(GL_ALWAYS, 0, 0);
  glStencilOp(GL_KEEP, GL_KEEP, GL_INCR);
  glCullFace(GL_BACK);
  desenhe_objeto_b();
  glStencilOp(GL_KEEP, GL_KEEP, GL_DECR);
  glCullFace(GL_FRONT);
  desenhe_objeto_b();
  glDepthMask(GL_TRUE);
  glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);

  glStencilFunc(test, 0, 1);
  glDisable(GL_DEPTH_TEST);

  glCullFace(face);
  desenhe_objeto_a();
}

void disjunte(void(*desenhe_objeto)(void))
{
  glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE);
  glEnable(GL_DEPTH_TEST);
  glDisable(GL_STENCIL_TEST);
  glDepthFunc(GL_ALWAYS);
  desenhe_objeto();
  glDepthFunc(GL_LESS);
}

void ao_movimentar(int x, int y)
{
  GLfloat r, obj_x, obj_y, obj_z;

  NOVA_POSICAO_X = x - POSICAO_INICIAL_X;
  NOVA_POSICAO_Y = POSICAO_INICIAL_Y - y;

  r = (NOVA_POSICAO_X + POSICAO_X) * 50.f / 512.f;

  obj_x = r * (float)cos(ANGULO_DE_ROTACAO * DEGTORAD);
  obj_z = r * (float)sin(ANGULO_DE_ROTACAO * DEGTORAD);
  obj_y = (NOVA_POSICAO_Y + POSICAO_Y) * 50.f/512.f;

  switch(OBJETO_PINTADO) {
      case OBJETO_A:
        POSICAO_DO_CONE_NO_EIXO_X = obj_x;
        POSICAO_DO_CONE_NO_EIXO_Y = obj_y;
        POSICAO_DO_CONE_NO_EIXO_Z = obj_z;
        break;

      case OBJETO_B:
        POSICAO_DA_ESFERA_NO_EIXO_X = obj_x;
        POSICAO_DA_ESFERA_NO_EIXO_Y = obj_y;
        POSICAO_DA_ESFERA_NO_EIXO_Z = obj_z;
        break;
      default:
        break;
  }

  glutPostRedisplay();
}

void desenhe_cone(void)
{
  glPushMatrix();
  glTranslatef(POSICAO_DO_CONE_NO_EIXO_X, POSICAO_DO_CONE_NO_EIXO_Y, POSICAO_DO_CONE_NO_EIXO_Z);
  glTranslatef(0.f, 0.f, -30.f);
  glCallList(CONE);
  glPopMatrix();
}

void desenhe_esfera(void)
{
  glPushMatrix();
  glTranslatef(POSICAO_DA_ESFERA_NO_EIXO_X, POSICAO_DA_ESFERA_NO_EIXO_Y, POSICAO_DA_ESFERA_NO_EIXO_Z);
  glCallList(ESFERA);
  glPopMatrix();

}

void desenhe_um_objeto(void(*desenhe_objeto)(void))
{
  glEnable(GL_DEPTH_TEST);
  desenhe_objeto();
  glDisable(GL_DEPTH_TEST);
}

void desenhe_conjuncao(void(*desenhe_objeto_a)(void), void(*desenhe_objeto_b)())
{
  glEnable(GL_DEPTH_TEST);
  desenhe_objeto_a();
  desenhe_objeto_b();
  glDisable(GL_DEPTH_TEST);
}

void desenhe_disjuncao(void(*desenhe_objeto_a)(void), void(*desenhe_objeto_b)(void))
{
  interseccione(desenhe_objeto_a, desenhe_objeto_b, GL_BACK, GL_NOTEQUAL);

  disjunte(desenhe_objeto_b);

  interseccione(desenhe_objeto_b, desenhe_objeto_a, GL_BACK, GL_NOTEQUAL);

  glDisable(GL_STENCIL_TEST);
}

void desenhe_interseccao(void(*desenhe_objeto_a)(void), void(*desenhe_objeto_b)(void))
{
  interseccione(desenhe_objeto_a, desenhe_objeto_b, GL_FRONT, GL_NOTEQUAL);

  disjunte(desenhe_objeto_b);

  interseccione(desenhe_objeto_b, desenhe_objeto_a, GL_BACK, GL_EQUAL);

  glDisable(GL_STENCIL_TEST);
}

void redesenhe()
{
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT|GL_STENCIL_BUFFER_BIT);

    glPushMatrix();
    glRotatef(ANGULO_DE_ROTACAO, 0.f, 1.f, 0.f);

    switch(OPCAO_DO_MENU) {

    case OBJETO_A:
      desenhe_um_objeto(desenhe_cone);
      break;
    case OBJETO_B:
      desenhe_um_objeto(desenhe_esfera);
      break;
    case A_CONJUNCAO_COM_B:
      desenhe_conjuncao(desenhe_cone, desenhe_esfera);
      break;
    case A_DISJUNCAO_COM_B:
      desenhe_disjuncao(desenhe_cone, desenhe_esfera);
      break;
    case A_INTERSECCAO_COM_B:
      desenhe_interseccao(desenhe_cone, desenhe_esfera);
      break;
    case B_INTERSECCAO_COM_A:
      desenhe_interseccao(desenhe_esfera, desenhe_cone);
      break;
    }

    glPopMatrix();
    glutSwapBuffers();
}

#endif // COMPARTILHADO_H
