cmake_minimum_required(VERSION 3.22)
project(QubeEngine)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(glfw3 REQUIRED)
find_package(Vulkan REQUIRED)

include_directories( 
                ${CMAKE_CURRENT_SOURCE_DIR}/backend
                ${CMAKE_CURRENT_SOURCE_DIR}/controller
                ${CMAKE_CURRENT_SOURCE_DIR}/logging)
set(SOURCE_FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/backend/Qube_window.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/controller/App.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/logging)


# add_library(CONTOUR_LIB SHARED ${SOURCE_FILES})


add_executable(${PROJECT_NAME} src/main.cpp ${SOURCE_FILES})

target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/backend
    ${CMAKE_CURRENT_SOURCE_DIR}/controller
)
target_link_libraries(${PROJECT_NAME} PRIVATE glfw Vulkan::Vulkan)

# add_subdirectory(test)

# install(TARGETS CONTOUR_LIB
#     ARCHIVE DESTINATION lib
#     LIBRARY DESTINATION lib    
#     RUNTIME DESTINATION bin
# )

# install(DIRECTORY inc/
#     DESTINATION include
#     FILES_MATCHING PATTERN "*.h"
# )

