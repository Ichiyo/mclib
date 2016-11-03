cmake_minimum_required(VERSION 2.8.9)
project (test C)
set(CMAKE_BUILD_TYPE Release)

add_custom_command(
	OUTPUT temp
	WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/..
	COMMAND ${CMAKE_COMMAND} .
	COMMAND make
)
if (${CMAKE_SYSTEM_NAME} MATCHES "Windows")
    set(WINDOWS TRUE)
elseif (${CMAKE_SYSTEM_NAME} MATCHES "Linux")
    set(LINUX TRUE)
elseif (${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    set(MACOSX TRUE)
endif()

if(MACOSX)

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
include_directories( ${OPENGL_INCLUDE_DIRS}  ${GLUT_INCLUDE_DIRS} )
set(PROJECT_LINK_LIBS clibraries m pthread SDL2 SDL2_image ${OPENGL_LIBRARIES} ${GLUT_LIBRARY})
include_directories(/usr/local/include)

else() #linux

set(PROJECT_LINK_LIBS clibraries m pthread GL GLU glut SDL2 SDL2_image)

endif()

link_directories(${PROJECT_SOURCE_DIR}/..)

include_directories(${PROJECT_SOURCE_DIR}/../include)

add_executable(test test.c temp)
target_link_libraries(test ${PROJECT_LINK_LIBS})

add_executable(test_atomic test_atomic.c temp)
target_link_libraries(test_atomic ${PROJECT_LINK_LIBS})

add_executable(gltest gltest.c temp)
target_link_libraries(gltest ${PROJECT_LINK_LIBS})

add_executable(sdl_test sdl_test.c temp)
target_link_libraries(sdl_test ${PROJECT_LINK_LIBS})
