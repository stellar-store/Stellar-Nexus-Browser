cmake_minimum_required(VERSION 3.16)
project(Stellar VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt6 COMPONENTS Core Gui Widgets WebEngineWidgets WebEngineCore Network PrintSupport QUIET)

if(NOT Qt6_FOUND)
    find_package(Qt5 COMPONENTS Core Gui Widgets WebEngineWidgets Network PrintSupport REQUIRED)
    set(QT_VERSION_MAJOR 5)
else()
    set(QT_VERSION_MAJOR 6)
endif()

set(SOURCES
    src/main.cpp
    src/mainwindow.cpp
    src/mainwindow.h
    src/browserpage.cpp
    src/browserpage.h
    src/tabbar.cpp
    src/tabbar.h
    src/navbar.cpp
    src/navbar.h
    src/settingsdialog.cpp
    src/settingsdialog.h
    src/bookmarkmanager.cpp
    src/bookmarkmanager.h
    src/downloadmanager.cpp
    src/downloadmanager.h
    src/historymanager.cpp
    src/historymanager.h
    src/translationmanager.cpp
    src/translationmanager.h
    resources/resources.qrc
)

add_executable(stellar ${SOURCES})

if(QT_VERSION_MAJOR EQUAL 6)
    target_link_libraries(stellar PRIVATE
        Qt6::Core Qt6::Gui Qt6::Widgets
        Qt6::WebEngineWidgets Qt6::WebEngineCore
        Qt6::Network Qt6::PrintSupport
    )
else()
    target_link_libraries(stellar PRIVATE
        Qt5::Core Qt5::Gui Qt5::Widgets
        Qt5::WebEngineWidgets
        Qt5::Network Qt5::PrintSupport
    )
endif()

install(TARGETS stellar DESTINATION bin)
