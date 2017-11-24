#include "janela.h"

infraestrutura::Janela::Janela()
    : altura(0), largura(0)
{
    inicialize();
}

/**
 * @brief infraestrutura::Janela::Janela Construtor com altura e largura.
 * @param altura Altura da janela.
 * @param largura Largura da janela.
 */
infraestrutura::Janela::Janela(int altura, int largura)
    : altura(altura), largura(largura)
{
    inicialize();
}

/**
 * @brief infraestrutura::Janela::~Janela Destrutor padrão.
 */
infraestrutura::Janela::~Janela()
{

}

void infraestrutura::Janela::mostre()
{
    glutInitDisplayMode(GLUT_STENCIL|GLUT_DEPTH|GLUT_DOUBLE);
    (void)glutCreateWindow("Computação Gráfica");
}

void infraestrutura::Janela::inicialize()
{
    int argc = 0;
    char** argv;
    glutInit(&argc, argv);

    glutInitWindowSize(altura, largura);
}
