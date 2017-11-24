#ifndef JANELA_H
#define JANELA_H

#include <GL/gl.h>
#include <GL/glut.h>

namespace infraestrutura
{
    class Janela
    {
        public:
            Janela();
            Janela(int altura, int largura);
            ~Janela();
            void mostre(const char *descricao);

        private:
            void inicialize();
            int altura, largura;
    };
}

#endif // JANELA_H
