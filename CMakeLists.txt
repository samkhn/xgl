cmake_minimum_required(VERSION 3.6)

project(xgl)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_MODULE_PATH "${CMAKE_MODULE_PATH};${CMAKE_CURRENT_SOURCE_DIR}/vendor/scripts/cmake")

set(OpenGL_GL_PREFERENCE GLVND)
find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIRS})

find_package(GLEW REQUIRED)

find_package(GLFW3 REQUIRED)
option(GLFW_BUILD_DOCS OFF)
option(GLFW_BUILD_EXAMPLES OFF)
option(GLFW_BUILD_TESTS OFF)
if (NOT WIN32)
  set(GLAD_LIBRARIES dl)
endif()
add_subdirectory(vendor/glfw)
include_directories(vendor/glfw/include)
target_compile_options(glfw PRIVATE "-w")  # suppress warnings from glfw

add_subdirectory(vendor/glad)

add_executable(game xgl/main.cpp)
target_link_libraries(game glfw ${GLFW_LIBRARIES} ${OPENGL_LIBRARIES} GLEW::GLEW glad)
if (MSVC)
  target_compile_options(game PUBLIC /W4 /w14640 $<$<CONFIG:Release>:/O2> $<$<CONFIG:Debug>:/Z7>)
else()
  target_compile_options(game PUBLIC -Wall -Wextra -Wshadow -Wdelete-abstract-non-virtual-dtor -pedantic $<$<CONFIG:Release>:-O3> $<$<CONFIG:Debug>:-g>)
endif()
