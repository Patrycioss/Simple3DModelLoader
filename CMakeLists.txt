cmake_minimum_required(VERSION 3.6)
project(VulkanCPP)

set(CMAKE_CXX_STANDARD 23)

find_package(Vulkan REQUIRED)
find_package(OpenGL REQUIRED)

add_executable(VulkanCPP src/main.cpp
        libs/glad/src/gl.c
        libs/glad/src/vulkan.c
        src/rendering/ShaderProgram.cpp
        src/asyncoperations/ReadOperation.cpp
        src/rendering/GLTriangle.cpp
        src/rendering/GLRectangle.cpp
        src/asyncoperations/ReadImageOperation.cpp
        src/rendering/structures/Material.cpp
        src/rendering/structures/Texture.cpp
        src/rendering/GLCube.cpp
        src/window/Window.cpp
        src/Camera.cpp
        src/rendering/structures/Mesh.cpp
        src/obj-loading/LoadFastObjMeshOperation.cpp
        src/obj-loading/LoadFastObjMeshOperation.hpp
        src/FakeObjects.hpp
)

file(COPY resources DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

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
)

#set(CMAKE_EXE_LINKER_FLAGS " -static")

target_link_libraries(
        VulkanCPP PUBLIC
#        -static-libgcc
#        -static-libstdc++
        glfw
        ${Vulkan_LIBRARIES}
        OpenGL::GL
        dds_image
        rapidobj
)