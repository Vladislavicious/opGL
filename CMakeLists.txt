cmake_minimum_required(VERSION 3.12)
project(CMakeGraphicsProject)

# OpenGL
set(OpenGL_GL_PREFERENCE GLVND)
find_package(OpenGL REQUIRED)
include_directories(edu/src edu/Tests ${OPENGL_INCLUDE_DIRS})

# Address Sanitizer
if (UNIX)
	set (CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -fno-omit-frame-pointer -fsanitize=address")
	set (CMAKE_LINKER_FLAGS_DEBUG "${CMAKE_LINKER_FLAGS_DEBUG} -fno-omit-frame-pointer -fsanitize=address")
endif()

# C++ Standard
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# GLFW
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_INSTALL OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_USE_HYBRID_HPG ON CACHE BOOL "" FORCE)

# glm
set(GLM_INCLUDE_DIR Dependencies/glm)

# stb_image
set(STB_IMAGE_DIR Dependencies/stb_image)

# ImGui
set(imgui-directory Dependencies/imgui)
set(imgui-source ${imgui-directory}/imconfig.h
	${imgui-directory}/imgui.h
	${imgui-directory}/imgui.cpp
	${imgui-directory}/imgui_draw.cpp
	${imgui-directory}/imgui_internal.h
	${imgui-directory}/imgui_widgets.cpp
	${imgui-directory}/imstb_rectpack.h
	${imgui-directory}/imstb_textedit.h
	${imgui-directory}/imstb_truetype.h
    ${imgui-directory}/imgui_stdlib.cpp
    ${imgui-directory}/imgui_tables.cpp
	${imgui-directory}/imgui_demo.cpp
	${imgui-directory}/imgui_impl_glfw.cpp
	${imgui-directory}/imgui_impl_opengl3.cpp
)

# Subprojects
add_subdirectory(Dependencies/glad)
add_subdirectory(Dependencies/glfw)
add_subdirectory(Dependencies/stb_image)
add_subdirectory(Dependencies/glm)

# Set `source` variable to all .h and .cpp files in `edu/src`
file(GLOB_RECURSE source CONFIGURE_DEPENDS "edu/src/*.h" "edu/src/*.cpp" "edu/Tests/*.h" "edu/Tests/*.cpp")

add_executable(CMakeGraphicsProject ${source} ${imgui-source})
target_link_libraries(CMakeGraphicsProject ${OPENGL_LIBRARIES} glad glfw stb_image glm)
target_include_directories(CMakeGraphicsProject PRIVATE ${imgui-directory} ${GLM_INCLUDE_DIR} ${STB_IMAGE_DIR})
