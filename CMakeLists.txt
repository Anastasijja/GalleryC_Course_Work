cmake_minimum_required(VERSION 3.5)

project(GalleryC LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

#Укаижите путь к папке \msvc2019\ здесь
set (CMAKE_PREFIX_PATH "E:\\Qt\\5.15.0\\msvc2019\\")

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets REQUIRED)

if(ANDROID)
  add_library(GalleryC SHARED
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
  )
else()
  add_executable(GalleryC
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
  )
endif()

target_link_libraries(GalleryC PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
