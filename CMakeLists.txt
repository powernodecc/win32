cmake_minimum_required(VERSION 3.22)
project(win_mfc)

set(CMAKE_CXX_STANDARD 14)

#add_definitions(-D_AFXDLL)
#set(CMAKE_MFC_FLAG 2)

#SET(CMAKE_CXX_FLAGS_DEBUG "-O0")
#SET(CMAKE_C_FLAGS_DEBUG "-O0")

#set(CMAKE_GENERATOR_PLATFORM win32)
#SET(CMAKE_CXX_FLAGS_RELEASE -O0)
#SET(CMAKE_C_FLAGS_RELEASE -O0)
#set(CMAKE_GENERATOR_PLATFORM x64)

add_executable(win_mfc WIN32 winmine.cpp)
#add_executable(win_mfc WIN32 001.cpp)
