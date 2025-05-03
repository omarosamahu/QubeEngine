cmake_minimum_required(VERSION 3.22)
project(QubeEngine)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(glfw3 REQUIRED)
find_package(Vulkan REQUIRED)

set(SOURCE_FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/backend/QubeWindow.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/controller/App.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/renderer/Renderer.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/renderer/Instance.cpp
)


add_executable(${PROJECT_NAME} src/main.cpp ${SOURCE_FILES})

target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/logging
    ${CMAKE_CURRENT_SOURCE_DIR}/backend
    ${CMAKE_CURRENT_SOURCE_DIR}/controller
    ${CMAKE_CURRENT_SOURCE_DIR}/renderer
)
target_link_libraries(${PROJECT_NAME} PRIVATE glfw Vulkan::Vulkan)

add_definitions(-DVULKAN_HPP_NO_EXCEPTIONS)


