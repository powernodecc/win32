cmake_minimum_required(VERSION 3.22)
project(win_mfc)

set(CMAKE_CXX_STANDARD 14)

add_definitions(-D_AFXDLL)
set(CMAKE_MFC_FLAG 2)

add_executable(win_mfc WIN32 win32.cpp)
