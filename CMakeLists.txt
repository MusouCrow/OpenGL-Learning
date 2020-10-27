cmake_minimum_required(VERSION 3.10)
project(BGFX_PROJECT)

set(CMAKE_CXX_STANDARD 11)
set(GLFW_DIR 3rd/glfw)
set(GLAD_DIR 3rd/glad)

# 把src目录下的所有cpp文件加入到SRC_DIR变量
aux_source_directory(${GLAD_DIR}/src/. SRC_DIR)
aux_source_directory(src/. SRC_DIR)
aux_source_directory(src/lib/. SRC_DIR)
aux_source_directory(src/util/. SRC_DIR)
aux_source_directory(src/render/. SRC_DIR)

# 编译库
add_subdirectory(${GLFW_DIR})

# 添加头文件目录
include_directories(${GLFW_DIR}/include/)
include_directories(${GLAD_DIR}/include/)
include_directories(src/)

# Mac需要引用Cocoa
IF (APPLE)
    set(FRAMEWORK "-framework Cocoa -framework IOKit")
ELSE()
    set(FRAMEWORK "")
ENDIF()

add_executable(opengl_learning main.cpp ${SRC_DIR})
target_link_libraries(opengl_learning glfw ${FRAMEWORK}) # 链接编译