cmake_minimum_required(VERSION 3.30)
project(Cesame)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt6 COMPONENTS
        Core
        Gui
        Widgets
        REQUIRED)

add_executable(Cesame src/Client/main.cpp
        src/Client/TimeManager.cpp
        src/Client/Metrics/MetricType.cpp
        src/Client/Monitors/CpuMonitor.cpp
        src/Client/Monitors/CpuMonitor.h
        src/Client/Monitors/MemoryMonitor.cpp
        src/Client/Monitors/MemoryMonitor.h
)

target_include_directories(Cesame PRIVATE
        src/
        src/Client/
        src/Client/Exceptions
        src/Client/Metrics
        src/Client/Monitors
        dependencies/
)

target_link_libraries(Cesame
        Qt::Core
        Qt::Gui
        Qt::Widgets
)

