cmake_minimum_required(VERSION 3.17)
project(HACKING_exec)
set(CMAKE_CXX_STANDARD 17)

add_executable(HACKING_exec Hacking.c)
target_link_libraries(HACKING_exec -lcrypto)
