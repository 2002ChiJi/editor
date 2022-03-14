QT       += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    anyview.cpp \
    csvsheet.cpp \
    main.cpp \
    mainwindow.cpp \
    menu.cpp \
    menuButton.cpp \
    mybutton.cpp \
    titlemenu.cpp \
    txtview.cpp

HEADERS += \
    CSVSheet.h \
    ViewImplement.h \
    anyview.h \
    mainwindow.h \
    menu.h \
    menuButton.h \
    mybutton.h \
    titlemenu.h \
    txtview.h

FORMS += \
    CSVSheet.ui \
    anyview.ui \
    mainwindow.ui \
    menu.ui \
    menuButton.ui \
    mybutton.ui \
    titlemenu.ui \
    txtview.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    SRC.qrc

DISTFILES +=
