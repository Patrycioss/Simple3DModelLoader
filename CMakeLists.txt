cmake_minimum_required(VERSION 3.28)
project(VulkanCPP)

set(CMAKE_CXX_STANDARD 26)

find_package(Vulkan REQUIRED)

add_executable(VulkanCPP main.cpp)

target_include_directories(
        VulkanCPP 
        PUBLIC 
        ${CMAKE_CURRENT_SOURCE_DIR}/include/GLFW 
        ${CMAKE_CURRENT_SOURCE_DIR}/include/glm
        ${Vulkan_INCLUDE_DIRS}
)
target_link_libraries(
        VulkanCPP 
        PUBLIC 
        ${CMAKE_CURRENT_SOURCE_DIR}/libs/glfw3-lib-mingw-w64/libglfw3.a
        ${Vulkan_LIBRARIES}
)

