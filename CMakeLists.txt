cmake_minimum_required(VERSION 3.28)
project(VulkanCPP)

set(CMAKE_CXX_STANDARD 23)

find_package(Vulkan REQUIRED)
find_package(OpenGL REQUIRED)

add_executable(VulkanCPP src/main.cpp
        src/window/impl/GlfwImpl.cpp
        src/window/impl/GlfwImpl.hpp
        src/window/impl/Win32Window.cpp
        src/window/impl/Win32Window.hpp
)

add_subdirectory(glfw)
add_subdirectory(glew)

target_include_directories(
        VulkanCPP 
        PUBLIC 
        ${CMAKE_CURRENT_SOURCE_DIR}/glfw/include
        ${CMAKE_CURRENT_SOURCE_DIR}/glm
        ${Vulkan_INCLUDE_DIRS}
        ${CMAKE_CURRENT_SOURCE_DIR}/glew/auto/src
)
target_link_libraries(
        VulkanCPP 
        PUBLIC 
        glfw
        ${Vulkan_LIBRARIES}
        ${OPENGL_LIBRARY}
        
)

