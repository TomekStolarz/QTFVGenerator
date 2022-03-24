cmake_minimum_required(VERSION 3.5)

project(FVGeneratorV2 VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets REQUIRED)
find_package(Qt6 COMPONENTS PrintSupport REQUIRED)

include_directories(include)

set(PROJECT_SOURCES
        createcustomerdialog.cpp
        createitemdialog.cpp
        createfvdialog.cpp
        src/customer.cpp
        src/address.cpp
        src/producent.cpp
        src/person.cpp
        src/fvorder.cpp
        src/item.cpp
        src/database.cpp
        src/lastid.cpp
        include/loadingexception.h
        include/createcustomerdialog.h
        include/createitemdialog.h
        include/createfvdialog.h
        include/lastid.h
        include/database.h
        include/item.h
        include/fvorder.h
        include/person.h
        include/producent.h
        include/customer.h
        include/address.h
        src/main.cpp
        mainwindow.cpp
        include/mainwindow.h
        mainwindow.ui
        createcustomerdialog.ui
        createitemdialog.ui
        createfvdialog.ui
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(FVGeneratorV2
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET FVGeneratorV2 APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(FVGeneratorV2 SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(FVGeneratorV2
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(FVGeneratorV2 PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
target_link_libraries(FVGeneratorV2 PRIVATE Qt6::PrintSupport)

set_target_properties(FVGeneratorV2 PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(FVGeneratorV2)
endif()
