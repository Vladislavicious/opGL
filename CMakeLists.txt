cmake_minimum_required(VERSION 3.0.0)
project(pr2 VERSION 0.1.0 LANGUAGES C CXX)

find_package(OpenGL REQUIRED)

add_subdirectory (external)

include(CTest)
enable_testing()

include_directories(
	external/glew-2.1.0/include/
	external/glm/
	external/glfw-3.3.8/include/
	.
)

SET(TARGET_H
	Renderer.h
	Shader.h
	VertexBuffer.h
   )

# Local source files here
SET(TARGET_SRC
    main.cpp
	Renderer.cpp
	Shader.cpp
	VertexBuffer.cpp
    )

set(ALL_LIBS
	${OPENGL_LIBRARY}
	glfw
	GLEW
)

add_executable(pr2 ${TARGET_SRC} ${TARGET_H})

target_link_libraries(pr2
	${ALL_LIBS}
)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
