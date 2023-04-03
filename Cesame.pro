TEMPLATE = app
CONFIG += console c++20

QT += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        cesamebargraph.cpp \
        cesamecpucoregraph.cpp \
        cesamelabel.cpp \
        cesamelinegraph.cpp \
        cesamewindow.cpp \
        cpumonitor.cpp \
        gpumonitor.cpp \
        main.cpp \
        memorymonitor.cpp \
        utils.cpp

HEADERS += \
	cesamebargraph.h \
	cesamecpucoregraph.h \
	cesamelabel.h \
	cesamelinegraph.h \
	cesamewindow.h \
	cpumonitor.h \
	gpumonitor.h \
	memorymonitor.h \
	utils.h

DISTFILES += \
	Toto.txt

INCLUDEPATH += /opt/cuda/include/

LIBS += -L"/usr/lib/" -lnvidia-ml
LIBS += -lfmt

# Default rules for deployment.
#qnx: target.path = /tmp/$${TARGET}/bin
#else: unix:!android: target.path = /opt/$${TARGET}/bin
#!isEmpty(target.path): INSTALLS += target
