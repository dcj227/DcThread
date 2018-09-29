#CMakeLists.txt


cmake_minimum_required(VERSION 2.8)
add_executable(example 
    example.cpp
)

target_link_libraries(example
    pthread
)
