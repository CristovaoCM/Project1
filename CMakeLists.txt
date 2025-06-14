cmake_minimum_required(VERSION 3.5)

project(HospitalQt LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets)
find_package(Qt6 REQUIRED COMPONENTS Sql)

# Habilita autogen (geração de moc, rcc e uic)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

# Se estiver no Windows com MySQL
include_directories("C:/Program Files/MySQL/MySQL Server 8.0/include")
link_directories("C:/Program Files/MySQL/MySQL Server 8.0/lib")

add_executable(HospitalQt
    main.cpp
    hospital.cpp
    hospital.h
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
)

target_link_libraries(HospitalQt
    Qt6::Widgets
    Qt6::Sql
    libmysql
)