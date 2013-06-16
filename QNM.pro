#-------------------------------------------------
#
# Project created by QtCreator 2013-05-19T14:25:29
#
#-------------------------------------------------

QT       += core gui xml webkit

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QNM
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    NotesManager.cpp \
    Note.cpp \
    NoteFactory.cpp \
    NotesExporter.cpp \
    NUtils.cpp \
    Article_modif.cpp \
    Document_modif.cpp \
    QNMListWidgetItem.cpp \
    Image_modif.cpp \
    Audio_modif.cpp \
    Video_modif.cpp \
    Corbeille_modif.cpp \
    TagManager.cpp \
    Tag.cpp \
    Show_source.cpp \
    Tag_modif.cpp

HEADERS  += mainwindow.h \
    NotesManager.h \
    Note.h \
    NoteFactory.h \
    NotesExporter.h \
    NUtils.h \
    Article_modif.h \
    Document_modif.h \
    QNMListWidgetItem.h \
    Image_modif.h \
    Audio_modif.h \
    Video_modif.h \
    Corbeille_modif.h \
    TagManager.h \
    Tag.h \
    Show_source.h \
    Tag_modif.h

FORMS    += mainwindow.ui \
    Article_modif.ui \
    Document_modif.ui \
    Image_modif.ui \
    Audio_modif.ui \
    Video_modif.ui \
    Corbeille_modif.ui \
    Show_source.ui \
    Tag_modif.ui

RESOURCES += \
    icons/icons.qrc
