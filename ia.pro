TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    gravitationalalgorithm.cpp

include(deployment.pri)
qtcAddDeployment()

HEADERS += \
    gravitationalalgorithm.h

