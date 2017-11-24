TEMPLATE = app
CONFIG += console c++14
CONFIG -= app_bundle
CONFIG -= qt
LIBS += -lGL -lGLU -lglut

SOURCES += main.cpp \
    infraestrutura/janela.cpp \
    infraestrutura/esfera.cpp

HEADERS += \
    enumeradores/enumcsg.h \
    infraestrutura/janela.h \
    infraestrutura/esfera.h \
    enumeradores/enumobjeto.h \
    global.h \
    enumeradores/enumdirecao.h \
    compartilhado.h
