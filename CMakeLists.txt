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

find_package(GTest REQUIRED)

find_package(CUDAToolkit REQUIRED)

add_executable(Client
        src/Client/main.cpp
        src/Client/TimeManager.cpp
        src/Client/Metrics/MetricType.cpp
        src/Client/Monitors/CpuMonitor.cpp
        src/Client/Monitors/CpuMonitor.h
        src/Client/Monitors/MemoryMonitor.cpp
        src/Client/Monitors/MemoryMonitor.h
        src/Client/Monitors/GpuMonitor.cpp
        src/Client/Monitors/GpuMonitor.h
        src/Client/Window/MainWindow.cpp
        src/Client/Window/MainWindow.h
        src/Client/Window/MainWidget.cpp
        src/Client/Window/MainWidget.h
        src/Client/Window/Widgets/Label.cpp
        src/Client/Window/Widgets/Label.h
        src/Client/Window/Widgets/Bar.cpp
        src/Client/Window/Widgets/Bar.h
        src/Client/Window/Widgets/CpuCoresBarGraph.cpp
        src/Client/Window/Widgets/CpuCoresBarGraph.h
        src/Client/Window/Widgets/LineGraph.cpp
        src/Client/Window/Widgets/LineGraph.h
        src/Client/Window/Widgets/LineGraphLabeled.cpp
        src/Client/Window/Widgets/LineGraphLabeled.h
        src/Client/Window/Style/ColorPalette.cpp
        src/Client/Window/Style/ColorPalette.h
        src/Client/Window/Style/ColorRange.cpp
        src/Client/Window/Style/ColorRange.h
)

target_include_directories(Client PRIVATE
        src/
        src/Client/
        src/Client/Exceptions
        src/Client/Metrics
        src/Client/Monitors
        src/Client/Window
        src/Client/Window/Widgets
)

target_link_libraries(Client
        Qt::Core
        Qt::Gui
        Qt::Widgets
        CUDA::nvml
)

# Tests
enable_testing()

add_executable(Tests
        # Source files
        src/Client/TimeManager.cpp
        src/Client/Metrics/MetricType.cpp
        src/Client/Monitors/CpuMonitor.cpp
        src/Client/Monitors/CpuMonitor.h
        src/Client/Monitors/MemoryMonitor.cpp
        src/Client/Monitors/MemoryMonitor.h
        src/Client/Monitors/GpuMonitor.cpp
        src/Client/Monitors/GpuMonitor.h
        src/Client/Window/MainWindow.cpp
        src/Client/Window/MainWindow.h
        src/Client/Window/MainWidget.cpp
        src/Client/Window/MainWidget.h
        src/Client/Window/Widgets/Label.cpp
        src/Client/Window/Widgets/Label.h
        src/Client/Window/Widgets/Bar.cpp
        src/Client/Window/Widgets/Bar.h
        src/Client/Window/Widgets/CpuCoresBarGraph.cpp
        src/Client/Window/Widgets/CpuCoresBarGraph.h
        src/Client/Window/Widgets/LineGraph.cpp
        src/Client/Window/Widgets/LineGraph.h
        src/Client/Window/Widgets/LineGraphLabeled.cpp
        src/Client/Window/Widgets/LineGraphLabeled.h
        src/Client/Window/Style/ColorPalette.cpp
        src/Client/Window/Style/ColorPalette.h
        src/Client/Window/Style/ColorRange.cpp
        src/Client/Window/Style/ColorRange.h

        # Test files
        tests/ColorPaletteTests.cpp
        tests/ColorRangeTests.cpp
)

target_include_directories(Tests PRIVATE
        src/
        src/Client/
        src/Client/Exceptions
        src/Client/Metrics
        src/Client/Monitors
        src/Client/Window
        src/Client/Window/Widgets
)

target_link_libraries(Tests
        GTest::gtest_main
        Qt::Core
        Qt::Gui
        Qt::Widgets
        CUDA::nvml
)

include(GoogleTest)
gtest_discover_tests(Tests)
