#ifndef GLOBAL_H
#define GLOBAL_H

#include <GL/gl.h>
#include "enumeradores/enumcsg.h"
#include "enumeradores/enumdirecao.h"

using namespace enumeradores;

int OPCAO_DO_MENU = OBJETO_A;

int DIRECAO_DA_ANIMACAO = ESQUERDA;

GLfloat ANGULO_DE_ROTACAO;

GLfloat POSICAO_DA_ESFERA_NO_EIXO_X = 0.f, POSICAO_DA_ESFERA_NO_EIXO_Y = 0.f, POSICAO_DA_ESFERA_NO_EIXO_Z = 0.f;

GLfloat POSICAO_DO_CONE_NO_EIXO_X = 0.f, POSICAO_DO_CONE_NO_EIXO_Y = 0.f, POSICAO_DO_CONE_NO_EIXO_Z = 0.f;

double DEGTORAD = (2 * 3.1415 / 360);

int OBJETO_PINTADO;

int POSICAO_X = 0, POSICAO_Y = 0;

int NOVA_POSICAO_X, NOVA_POSICAO_Y;

int POSICAO_INICIAL_X, POSICAO_INICIAL_Y;

#endif // GLOBAL_H
