cmake_minimum_required(VERSION 3.0.0)
project(ratio VERSION 0.1.0)

include(CTest)
enable_testing()

add_executable(ratioserver server.c)
add_executable(ratioclient client.c)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
