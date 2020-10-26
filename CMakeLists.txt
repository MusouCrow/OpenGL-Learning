cmake_minimum_required(VERSION 3.10)
project(BGFX_PROJECT)

set(CMAKE_CXX_STANDARD 11)
set(GLFW_DIR 3rd/glfw) # GLFW库所在路径
set(GLEW_DIR 3rd/glew) # GLEW库所在路径

# 把src目录下的所有cpp文件加入到SRC_DIR变量
aux_source_directory(src/. SRC_DIR)
aux_source_directory(src/lib/. SRC_DIR)

# 编译库
add_subdirectory(${GLFW_DIR})
add_subdirectory(${GLEW_DIR}/build/cmake)

# 添加头文件目录
include_directories(${GLFW_DIR}/include/)
include_directories(${GLEW_DIR}/include/)
include_directories(src/)

# Mac需要引用Cocoa
IF (APPLE)
    set(FRAMEWORK "-framework Cocoa -framework IOKit")
ELSE()
    set(FRAMEWORK "")
ENDIF()

# 添加平台宏
IF (WIN32)
    add_definitions(-DPLATFORM_WINDOWS)
ELSEIF (APPLE)
    add_definitions(-DPLATFORM_OSX)
ELSE()
    add_definitions(-DPLATFORM_LINUX)
ENDIF()

add_executable(opengl_learning main.cpp ${SRC_DIR})
target_link_libraries(opengl_learning glfw glew ${FRAMEWORK}) # 链接编译