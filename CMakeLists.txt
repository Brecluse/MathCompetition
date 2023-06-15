cmake_minimum_required(VERSION 3.23)
project(MathComp)
set(CMAKE_CXX_STANDARD 98)

add_executable(
        MathComp
        main.cpp
        ui.h ui.cpp
        record.h record.cpp
        user.h user.cpp
        question.h question.cpp
        expr.h expr.cpp
)
