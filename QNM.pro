#-------------------------------------------------
#
# Project created by QtCreator 2013-05-19T14:25:29
#
#-------------------------------------------------

QT       += core gui xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QNM
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    NotesManager.cpp \
    Note.cpp \
    NoteFactory.cpp \
    ArticleWidget.cpp \
    NotesExporter.cpp \
    NUtils.cpp \
    Article_modif.cpp \
    Document_modif.cpp \
    QNMListWidgetItem.cpp \
    Image_modif.cpp

HEADERS  += mainwindow.h \
    NotesManager.h \
    Note.h \
    NoteFactory.h \
    ArticleWidget.h \
    NotesExporter.h \
    NUtils.h \
    Article_modif.h \
    Document_modif.h \
    QNMListWidgetItem.h \
    Image_modif.h

FORMS    += mainwindow.ui \
    Article_modif.ui \
    Document_modif.ui \
    Image_modif.ui

RESOURCES += \
    icons/icons.qrc
