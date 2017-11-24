#include "janela.h"

infraestrutura::Janela::Janela()
    : altura(0), largura(0)
{
    inicialize();
}

infraestrutura::Janela::Janela(int altura, int largura)
    : altura(altura), largura(largura)
{
    inicialize();
}

infraestrutura::Janela::~Janela()
{

}

void infraestrutura::Janela::mostre(const char * descricao)
{
    glutInitDisplayMode(GLUT_STENCIL|GLUT_DEPTH|GLUT_DOUBLE);
    (void)glutCreateWindow(descricao);
}

void infraestrutura::Janela::inicialize()
{
    int argc = 0;
    char** argv;
    glutInit(&argc, argv);

    glutInitWindowSize(altura, largura);
}
