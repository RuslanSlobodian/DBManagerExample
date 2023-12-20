QT  += core gui widgets sql

TARGET = DataBase
TEMPLATE = app

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++17

SOURCES += \
        main.cpp \
        mainwindow.cpp \
        message.cpp \
        mysqldbmanager.cpp \
        sqlitedbmanager.cpp

HEADERS += \
        dbmanager.h \
        mainwindow.h \
        message.h \
        mysqldbmanager.h \
        sqlitedbmanager.h

FORMS += \
        mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

# Share all project output files by directories
MOC_DIR = moc
RCC_DIR = rcc
UI_DIR = ui
unix:OBJECTS_DIR = unix
win32:OBJECTS_DIR = win32
macx:OBJECTS_DIR = mac

# If release-buid -> run windeploy applications, that will collect all the dlls
CONFIG(release, debug|release) {
    win32:QMAKE_POST_LINK = $$(QTDIR)/bin/windeployqt $$OUT_PWD/release
}
