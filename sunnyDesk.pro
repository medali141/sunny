QT       += core gui sql widgets printsupport charts

CONFIG += c++17

SOURCES += \
    createaccount.cpp \
    employe.cpp \
    event.cpp \
    login.cpp \
    main.cpp \
    mainwindow.cpp \
    connection.cpp \
    matriel.cpp \
    participant.cpp \
    sponsor.cpp

HEADERS += \
    createaccount.h \
    employe.h \
    event.h \
    login.h \
    mainwindow.h \
    connection.h \
    matriel.h \
    participant.h \
    sponsor.h

FORMS += \
    createaccount.ui \
    employe.ui \
    event.ui \
    login.ui \
    mainwindow.ui \
    matriel.ui \
    participant.ui \
    sponsor.ui

RESOURCES += resources.qrc

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    SunnyDesk.qss
