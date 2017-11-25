TEMPLATE = app
CONFIG += console c++14
CONFIG -= app_bundle
CONFIG -= qt
LIBS += -lGL -lGLU -lglut

SOURCES += main.cpp

HEADERS += \
    enumeradores/enumcsg.h \
    enumeradores/enumobjeto.h \
    global.h \
    enumeradores/enumdirecao.h \
    compartilhado.h
