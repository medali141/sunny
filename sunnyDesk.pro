QT       += core gui sql charts
QT       += network
QT += core gui widgets sql printsupport
QT += serialport

CONFIG += c++17

SOURCES += \
    ard.cpp \
    createaccount.cpp \
    employe.cpp \
    event.cpp \
    flamehistory.cpp \
    login.cpp \
    main.cpp \
    mainwindow.cpp \
    connection.cpp \
    matriel.cpp \
    participant.cpp \
    sponsor.cpp \
    qrcodegen.cpp \
    statistiques.cpp \
    evenement.cpp \
    meteoassistant.cpp


HEADERS += \
    ard.h \
    createaccount.h \
    employe.h \
    event.h \
    flamehistory.h \
    login.h \
    mainwindow.h \
    connection.h \
    matriel.h \
    participant.h \
    qrcodegen.hpp \
    sponsor.h \
    statistiques.h \
    evenement.h \
    meteoassistant.h

FORMS += \
    createaccount.ui \
    employe.ui \
    event.ui \
    flamehistory.ui \
    login.ui \
    mainwindow.ui \
    matriel.ui \
    participant.ui \
    sponsor.ui\
    statistiques.ui

RESOURCES += resources.qrc

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    SunnyDesk.qss
