cmake_minimum_required(VERSION 3.17)
project(VU_OP_Task_2_Pazymiu_skaiciuokle)

set(CMAKE_CXX_STANDARD 14)

include_directories(include)

add_executable(
        VU_OP_Task_2_Pazymiu_skaiciuokle
        include/Console.cpp
        include/Console.hpp
        include/Definitions.hpp
        include/File.cpp
        include/File.hpp
        include/Math.cpp
        include/Math.hpp
        include/RND.cpp
        include/RND.hpp
        include/String.cpp
        include/String.hpp
        include/Student.cpp
        include/Student.hpp
        include/Table.cpp
        include/Table.hpp
        include/Timer.cpp
        include/Timer.hpp
        include/Utils.cpp
        include/Utils.hpp
        main.cpp
)
