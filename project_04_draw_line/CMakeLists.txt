cmake_minimum_required(VERSION 3.16)

project(template)
set (CURRENT_PROJECT_NAME "draw_line")

# Define MY_SOURCES to be a list of all the source files for my game 
file(GLOB_RECURSE MY_SOURCES CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")

add_executable("${CURRENT_PROJECT_NAME}")

set_property(TARGET "${CURRENT_PROJECT_NAME}" PROPERTY CXX_STANDARD 17)

target_compile_definitions("${CURRENT_PROJECT_NAME}" PUBLIC RESOURCES_PATH="${CMAKE_CURRENT_SOURCE_DIR}/resources/") # This is useful to get an ASSETS_PATH in your IDE during development but you should comment this if you compile a release version and uncomment the next line
#target_compile_definitions("${CURRENT_PROJECT_NAME}" PUBLIC RESOURCES_PATH="./resources/") # Uncomment this line to setup the ASSETS_PATH macro to the final assets directory when you share the game

target_sources("${CURRENT_PROJECT_NAME}" PRIVATE ${MY_SOURCES} )

if(MSVC) # If using the VS compiler...

	target_compile_definitions("${CURRENT_PROJECT_NAME}" PUBLIC _CRT_SECURE_NO_WARNINGS)

	#remove console
	#set_target_properties("${CURRENT_PROJECT_NAME}" PROPERTIES LINK_FLAGS "/SUBSYSTEM:WINDOWS /ENTRY:mainCRTStartup")
	
endif()

target_include_directories("${CURRENT_PROJECT_NAME}" PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/../include/")

target_link_libraries("${CURRENT_PROJECT_NAME}" PRIVATE glm glfw 
	glad stb_image stb_truetype imgui)
