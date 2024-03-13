cmake_minimum_required(VERSION 3.28)
project(VulkanCPP)

set(CMAKE_CXX_STANDARD 23)

find_package(Vulkan REQUIRED)
find_package(OpenGL REQUIRED)

add_executable(VulkanCPP src/main.cpp
        src/window/impl/GlfwWindow.cpp
        src/window/impl/Win32Window.cpp
        glad/src/gl.c
        glad/src/vulkan.c
        src/rendering/ShaderProgram.cpp
        src/asyncoperations/ReadOperation.cpp
        src/rendering/Triangle.cpp
        src/rendering/Rectangle.cpp
        src/asyncoperations/ReadImageOperation.hpp
        src/asyncoperations/ReadImageOperation.cpp
)

file(COPY resources
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

add_subdirectory(glfw)

target_include_directories(
        VulkanCPP 
        PUBLIC 
        glfw/include
        glm
        ${Vulkan_INCLUDE_DIRS}
        glad/include
)
target_link_libraries(
        VulkanCPP 
        PUBLIC 
        glfw
        ${Vulkan_LIBRARIES}
        OpenGL::GL
)

