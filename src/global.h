#ifndef GLOBAL_H
#define GLOBAL_H

#include <GL/gl.h>
#include "enumeradores/enumcsg.h"
#include "enumeradores/enumdirecao.h"

using namespace enumeradores;

int OPCAO_DO_MENU = CSG_A;

int DIRECAO_DA_ANIMACAO = ANIM_LEFT;

GLfloat ANGULO_DE_ROTACAO;

GLfloat POSICAO_DA_ESFERA_NO_EIXO_X = 0.f, POSICAO_DA_ESFERA_NO_EIXO_Y = 0.f, POSICAO_DA_ESFERA_NO_EIXO_Z = 0.f;

GLfloat POSICAO_DO_CONE_NO_EIXO_X = 0.f, POSICAO_DO_CONE_NO_EIXO_Y = 0.f, POSICAO_DO_CONE_NO_EIXO_Z = 0.f;

int picked_object;
int xpos = 0, ypos = 0;
int newxpos, newypos;
int startx, starty;

#endif // GLOBAL_H
