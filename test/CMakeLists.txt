cmake_minimum_required(VERSION 2.8.9)
project (test C)
set(CMAKE_BUILD_TYPE Release)

add_custom_command(
	OUTPUT temp
	WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/..
	COMMAND mkdir -p build
	COMMAND ${CMAKE_COMMAND} -Bbuild -H.
	COMMAND make -C build
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

link_directories(${PROJECT_SOURCE_DIR}/../build)

include_directories(${PROJECT_SOURCE_DIR}/../include)

add_executable(main_test test.c temp)
set_property(TARGET main_test PROPERTY LINK_DEPENDS ${PROJECT_SOURCE_DIR}/../build/libclibraries.a)
add_dependencies(main_test clibraries)
target_link_libraries(main_test ${PROJECT_LINK_LIBS})

add_executable(gltest gltest.c temp)
set_property(TARGET gltest PROPERTY LINK_DEPENDS ${PROJECT_SOURCE_DIR}/../build/libclibraries.a)
add_dependencies(gltest clibraries)
target_link_libraries(gltest ${PROJECT_LINK_LIBS})

add_executable(sdl_test sdl_test.c temp)
set_property(TARGET sdl_test PROPERTY LINK_DEPENDS ${PROJECT_SOURCE_DIR}/../build/libclibraries.a)
add_dependencies(sdl_test clibraries)
target_link_libraries(sdl_test ${PROJECT_LINK_LIBS})

add_executable(test_lambda test_lambda.c temp)
set_property(TARGET test_lambda PROPERTY LINK_DEPENDS ${PROJECT_SOURCE_DIR}/../build/libclibraries.a)
add_dependencies(test_lambda clibraries)
target_link_libraries(test_lambda ${PROJECT_LINK_LIBS})

add_executable(test_2d test_2d.c temp)
set_property(TARGET test_2d PROPERTY LINK_DEPENDS ${PROJECT_SOURCE_DIR}/../build/libclibraries.a)
add_dependencies(test_2d clibraries)
target_link_libraries(test_2d ${PROJECT_LINK_LIBS})

add_executable(xml_test xml_test.c temp)
set_property(TARGET xml_test PROPERTY LINK_DEPENDS ${PROJECT_SOURCE_DIR}/../build/libclibraries.a)
add_dependencies(xml_test clibraries)
target_link_libraries(xml_test ${PROJECT_LINK_LIBS})

add_executable(gen_code gen_code.c temp)
set_property(TARGET gen_code PROPERTY LINK_DEPENDS ${PROJECT_SOURCE_DIR}/../build/libclibraries.a)
add_dependencies(gen_code clibraries)
target_link_libraries(gen_code ${PROJECT_LINK_LIBS})
