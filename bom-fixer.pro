
QT       += core gui widgets

TARGET = bom-fixer
TEMPLATE = app

SOURCES += \
        main.cpp \
        mainwindow.cpp \
    bomfilesystemmodel.cpp

HEADERS += \
        mainwindow.h \
    bomfilesystemmodel.h

FORMS += \
        mainwindow.ui \
    about.ui

DISTFILES += \
    LICENSE \
    README.md \
    AUTHORS

CONFIG += static
