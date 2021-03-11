cmake_minimum_required(VERSION 3.17)
project(VU_OP_Task_2_Pazymiu_skaiciuokle)

set(CMAKE_CXX_STANDARD 14)
#set(CMAKE_CXX_FLAGS "-O3 -Wall -Wextra")

include_directories(include)

add_executable(VU_OP_Task_2_Pazymiu_skaiciuokle
        include/Comparator.cpp
        include/Comparator.hpp
        include/Console.cpp
        include/Console.hpp
        include/Definitions.hpp
        include/File.cpp
        include/File.hpp
        include/Grades.cpp
        include/Grades.hpp
        include/Math.cpp
        include/Math.hpp
        include/RND.cpp
        include/RND.hpp
        include/String.cpp
        include/String.hpp
        include/Student.cpp
        include/Student.hpp
        include/Students.cpp
        include/Students.hpp
        include/Table.hpp
        include/Timer.cpp
        include/Timer.hpp
        include/Utils.cpp
        include/Utils.hpp
        main.cpp)
