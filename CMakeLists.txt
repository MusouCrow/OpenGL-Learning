cmake_minimum_required(VERSION 3.10)
project(opengl_learning)

set(CMAKE_CXX_STANDARD 11)
set(GLFW_DIR 3rd/glfw)
set(GLAD_DIR 3rd/glad)
set(GLM_DIR 3rd/glm)
set(STB_DIR 3rd/stb)
set(IMGUI_DIR 3rd/imgui)
set(ASSIMP_DIR 3rd/assimp)
set(ASSIMP_DIR2 build/3rd/assimp)
set(JSONXX 3rd/jsonxx)

set(IMGUI_SRC ${IMGUI_DIR}/backends/imgui_impl_glfw.cpp ${IMGUI_DIR}/backends/imgui_impl_opengl3.cpp)

# 编译库
add_subdirectory(${GLFW_DIR})
add_subdirectory(${ASSIMP_DIR})

# 把src目录下的所有cpp文件加入到SRC_DIR变量
aux_source_directory(${GLAD_DIR}/src/. SRC_DIR)
aux_source_directory(${STB_DIR}/. SRC_DIR)
aux_source_directory(${IMGUI_DIR}/. SRC_DIR)

aux_source_directory(src/. SRC_DIR)
aux_source_directory(src/lib/. SRC_DIR)
aux_source_directory(src/util/. SRC_DIR)
aux_source_directory(src/render/. SRC_DIR)
aux_source_directory(src/render/renderer/. SRC_DIR)

# 添加头文件目录
include_directories(${GLFW_DIR}/include/)
include_directories(${GLAD_DIR}/include/)
include_directories(${GLM_DIR}/)
include_directories(${STB_DIR}/)
include_directories(${IMGUI_DIR}/)
include_directories(${ASSIMP_DIR}/include/)
include_directories(${ASSIMP_DIR2}/include/)
include_directories(${JSONXX}/include/)
include_directories(src/)

# Mac需要引用Cocoa
IF (APPLE)
    set(FRAMEWORK "-framework Cocoa -framework IOKit")
ELSE()
    set(FRAMEWORK "")
ENDIF()

add_executable(opengl_learning main.cpp ${SRC_DIR} ${IMGUI_SRC})
target_link_libraries(opengl_learning glfw assimp ${FRAMEWORK}) # 链接编译