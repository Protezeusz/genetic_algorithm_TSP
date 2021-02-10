TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    environment.cpp \
    population.cpp \
    reader.cpp \
    salesman.cpp

HEADERS += \
    environment.h \
    population.h \
    reader.h \
    salesman.h
