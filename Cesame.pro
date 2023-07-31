TEMPLATE = app
CONFIG += console c++20

QT += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++20

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        BarGraph.cpp \
        CesameWindow.cpp \
        Color.cpp \
        CpuCoreGraph.cpp \
        CpuMonitor.cpp \
        GpuMonitor.cpp \
        Label.cpp \
        LineGraph.cpp \
        MemoryMonitor.cpp \
        Monitor.cpp \
        NetworkMonitor.cpp \
        Utils.cpp \
        main.cpp

HEADERS += \
	BarGraph.h \
	CesameWindow.h \
	Color.h \
	CpuCoreGraph.h \
	CpuMonitor.h \
	GpuMonitor.h \
	Label.h \
	LineGraph.h \
	MemoryMonitor.h \
	Monitor.h \
	MonitorTypes.h \
	NetworkMonitor.h \
	Utils.h

DISTFILES += \
	Toto.txt

INCLUDEPATH += /opt/cuda/include/

LIBS += -L"/usr/lib/" -lnvidia-ml
LIBS += -lfmt

# Default rules for deployment.
#qnx: target.path = /tmp/$${TARGET}/bin
#else: unix:!android: target.path = /opt/$${TARGET}/bin
#!isEmpty(target.path): INSTALLS += target
