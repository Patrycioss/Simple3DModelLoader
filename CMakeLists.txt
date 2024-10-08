cmake_minimum_required(VERSION 3.6)
project(VulkanCPP)

set(CMAKE_CXX_STANDARD 23)

find_package(Vulkan REQUIRED)
find_package(OpenGL REQUIRED)

add_executable(VulkanCPP src/main.cpp
        libs/glad/src/gl.c
        libs/glad/src/vulkan.c
        src/shaders/ShaderProgram.cpp
        src/shapes/GLTriangle.cpp
        src/shapes/GLRectangle.cpp
        src/shapes/GLCube.cpp
        src/window/Window.cpp
        src/scene/Camera.cpp
        src/scene/Scene.cpp
        src/IO/IO.cpp
        src/renderer/MeshRenderer.cpp
        src/scene/GameObject.cpp
        src/renderer/Renderer.cpp
        src/scene/Component.cpp
        src/scene/Transform.cpp
        src/IO/ModelLoader.cpp
)

file(COPY resources DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/dlls/libassimp-5.dll ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)

add_subdirectory(libs/glfw)
add_subdirectory(libs/glm)
add_subdirectory(libs/rapidobj)
add_subdirectory(libs/dds_image)

target_include_directories(
        VulkanCPP 
        PUBLIC
        glfw
        glm
        ${Vulkan_INCLUDE_DIRS}
        ${CMAKE_CURRENT_SOURCE_DIR}/libs/glad/include
        ${RAPIDOBJ_INCLUDE_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}/libs/zlib/include
        ${CMAKE_CURRENT_SOURCE_DIR}/libs/assimp/include
        ${CMAKE_CURRENT_SOURCE_DIR}/libs/stb
)


add_library(zlib STATIC IMPORTED)
SET_TARGET_PROPERTIES(zlib PROPERTIES LINKER_LANGUAGE C)
SET_TARGET_PROPERTIES(zlib PROPERTIES IMPORTED_LOCATION ${CMAKE_CURRENT_SOURCE_DIR}/libs/zlib/libzlibstatic.a)

set(CMAKE_EXE_LINKER_FLAGS " -static")

target_link_libraries(
        VulkanCPP PUBLIC
        -static-libgcc
        -static-libstdc++
        glfw
        ${Vulkan_LIBRARIES}
        OpenGL::GL
        dds_image
#        rapidobj
        zlib
        ${CMAKE_CURRENT_SOURCE_DIR}/libs/assimp/libassimp.dll.a
)