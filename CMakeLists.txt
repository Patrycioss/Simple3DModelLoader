cmake_minimum_required(VERSION 3.28)
project(VulkanCPP)

set(CMAKE_CXX_STANDARD 26)

find_package(Vulkan REQUIRED)

add_executable(VulkanCPP main.cpp)
add_subdirectory(glfw)

target_include_directories(
        VulkanCPP 
        PUBLIC 
        ${CMAKE_CURRENT_SOURCE_DIR}/glfw/include
        ${CMAKE_CURRENT_SOURCE_DIR}/glm
        ${Vulkan_INCLUDE_DIRS}
)
target_link_libraries(
        VulkanCPP 
        PUBLIC 
        glfw
        ${Vulkan_LIBRARIES}
)

