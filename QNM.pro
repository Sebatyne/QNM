#-------------------------------------------------
#
# Project created by QtCreator 2013-05-19T14:25:29
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QNM
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    NotesManager.cpp \
    Note.cpp \
    NoteFactory.cpp

HEADERS  += mainwindow.h \
    NotesManager.h \
    Note.h \
    NoteFactory.h

FORMS    += mainwindow.ui
