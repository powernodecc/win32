cmake_minimum_required(VERSION 3.22)
project(win_mfc)

set(CMAKE_CXX_STANDARD 14)

# 启用 Microsoft 基础类 (MFC)
#add_definitions(-D_AFXDLL)
#set(CMAKE_MFC_FLAG 2)

#SET(CMAKE_CXX_FLAGS_DEBUG "-O0")
#SET(CMAKE_C_FLAGS_DEBUG "-O0")

#SET(CMAKE_CXX_FLAGS_RELEASE -O0)
#SET(CMAKE_C_FLAGS_RELEASE -O0)

#set(CMAKE_GENERATOR_PLATFORM win32)
#set(CMAKE_GENERATOR_PLATFORM x64)

ADD_DEFINITIONS(-DUNICODE)
ADD_DEFINITIONS(-D_UNICODE)

# 将源和执行字符集设置为 UTF-8
# /utf-8 (Set source and execution character sets to UTF-8)
add_compile_options("$<$<C_COMPILER_ID:MSVC>:/utf-8>")
add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")

add_executable(win_mfc WIN32 plant.cpp)
#add_executable(win_mfc test.cpp)
#add_executable(win_mfc WIN32 001.cpp)

# 显式指定应用程序入口点
#target_link_options(${PROJECT_NAME} PRIVATE "/entry:wWinMainCRTStartup")

#target_compile_definitions(win_mfc PRIVATE _UNICODE UNICODE)