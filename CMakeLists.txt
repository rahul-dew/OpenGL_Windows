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
add_subdirectory(project_03_draw_circle)
add_subdirectory(project_03_01_draw_ring)
add_subdirectory(project_04_draw_line)
add_subdirectory(project_05_shaders_color_attr_interpolation)
add_subdirectory(project_06_texture)
add_subdirectory(project_07_transformation)
add_subdirectory(project_08_coordinate_system)
add_subdirectory(project_09_00_render_cube)
add_subdirectory(project_09_01_render_cubes)
add_subdirectory(project_10_camera)