#-------------------------------------------------
#
# Project created by QtCreator 2016-05-29T16:38:33
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Qt_OCFractions
TEMPLATE = app


SOURCES += Qt\main.cpp\
    Qt\guicalulatrice.cpp \
    Commun\ZFraction.cpp \
    Commun\Membre.cpp

HEADERS  += \
    Qt\guicalulatrice.h \
    Commun\ZFraction.h \
    Commun\Membre.h

FORMS    += \
    Qt\guicalulatrice.ui
