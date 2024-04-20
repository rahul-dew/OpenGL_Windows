cmake_minimum_required(VERSION 3.16)

project(opengl)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_INSTALL OFF CACHE BOOL "" FORCE)
add_subdirectory(libs_thirdparty/glfw-3.3.2)			#window oppener
add_subdirectory(libs_thirdparty/glad)					#opengl loader
add_subdirectory(libs_thirdparty/stb_image)				#loading immaged
add_subdirectory(libs_thirdparty/stb_truetype)			#loading ttf files
add_subdirectory(libs_thirdparty/glm)					#math
add_subdirectory(libs_thirdparty/imgui-docking)			#ui

add_subdirectory(project_00_template)
add_subdirectory(project_01_hello_triangle)
add_subdirectory(project_02_draw_rectangle)