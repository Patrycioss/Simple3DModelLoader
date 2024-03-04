cmake_minimum_required(VERSION 3.28)
project(VulkanCPP)

set(CMAKE_CXX_STANDARD 23)

find_package(Vulkan REQUIRED)
find_package(OpenGL REQUIRED)

add_executable(VulkanCPP src/main.cpp
        src/window/impl/GlfwWindow.cpp
        src/window/impl/GlfwWindow.hpp
        src/window/impl/Win32Window.cpp
        src/window/impl/Win32Window.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/glad/src/gl.c
        ${CMAKE_CURRENT_SOURCE_DIR}/glad/src/vulkan.c
        src/data/Vec2.hpp
)

add_subdirectory(glfw)

target_include_directories(
        VulkanCPP 
        PUBLIC 
        ${CMAKE_CURRENT_SOURCE_DIR}/glfw/include
        ${CMAKE_CURRENT_SOURCE_DIR}/glm
        ${Vulkan_INCLUDE_DIRS}
        ${CMAKE_CURRENT_SOURCE_DIR}/glad/include
        
)
target_link_libraries(
        VulkanCPP 
        PUBLIC 
        glfw
        ${Vulkan_LIBRARIES}
        OpenGL::GL
)

