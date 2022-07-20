QT       += core gui sql printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    StaffInterface.cpp \
    addbrend.cpp \
    addccient.cpp \
    addcomp.cpp \
    addconsig.cpp \
    addorder.cpp \
    addprod.cpp \
    addtreaty.cpp \
    initwindow.cpp \
    inputdate.cpp \
    main.cpp \
    prodbrend.cpp \
    selectprod.cpp

HEADERS += \
    StaffInterface.h \
    addbrend.h \
    addccient.h \
    addcomp.h \
    addconsig.h \
    addorder.h \
    addprod.h \
    addtreaty.h \
    initwindow.h \
    inputdate.h \
    prodbrend.h \
    selectprod.h

FORMS += \
    StaffInterface.ui \
    addbrend.ui \
    addccient.ui \
    addcomp.ui \
    addconsig.ui \
    addorder.ui \
    addprod.ui \
    addtreaty.ui \
    initwindow.ui \
    inputdate.ui \
    prodbrend.ui \
    selectprod.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
