cmake_minimum_required(VERSION 2.8.9)
project (clibraries C)
set(CMAKE_BUILD_TYPE Release)

if (${USER_BUILD_IOS} MATCHES "true")
set(CMAKE_OSX_SYSROOT "iphoneos")
set(CMAKE_XCODE_EFFECTIVE_PLATFORMS "-iphoneos;-iphonesimulator")
set(CMAKE_OSX_ARCHITECTURES "$(ARCHS_STANDARD)")
endif()

# remove this to prevent log
add_definitions(-DAPP_DEBUG -DUSE_SDL)

include_directories(include)
if (${USER_BUILD_IOS} MATCHES "true")
include_directories(/Users/manhtran/Documents/lib/SDL2_image-2.0.1)
include_directories(/Users/manhtran/Documents/lib/SDL2-2.0.4/include)
endif()

if (${USER_BUILD_IOS} MATCHES "true")

file(GLOB SOURCES "src/*.c" "src/*.m" "src/node/*.c" "src/node/*.m")
add_library(clibraries STATIC ${SOURCES})

else()

file(GLOB SOURCES "src/*.c" "src/node/*.c")
add_library(clibraries STATIC ${SOURCES})

endif()
