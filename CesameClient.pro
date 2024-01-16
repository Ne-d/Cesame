TEMPLATE = app
CONFIG += console c++20

QT += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++20

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        BarGraph.cpp \
        CesameWindow.cpp \
        Color.cpp \
        CpuCoreGraph.cpp \
        Label.cpp \
        LineGraph.cpp \
        MetricsManager.cpp \
        Monitor.cpp \
        Utils.cpp \
        main.cpp

HEADERS += \
	BarGraph.h \
	CesameWindow.h \
	Color.h \
	CpuCoreGraph.h \
	Label.h \
	LineGraph.h \
	MetricsManager.h \
	Monitor.h \
	MonitorTypes.h \
        Utils.h \
        ../CesameServer/common.h

DISTFILES += \
        Toto.txt \
        .gitignore

INCLUDEPATH += \
/opt/cuda/include/ \
../CesameServer


LIBS += -L"/usr/lib/" -lnvidia-ml

# Default rules for deployment.
#qnx: target.path = /tmp/$${TARGET}/bin
#else: unix:!android: target.path = /opt/$${TARGET}/bin
#!isEmpty(target.path): INSTALLS += target
