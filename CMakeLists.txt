cmake_minimum_required(VERSION 3)
project(MashberryPi)

set(HEADER_FILES $("inc/*.h"))
include_directories(inc)
file(GLOB SOURCES "src/*.cpp")

# Locate libraries and headers
find_package(WiringPi REQUIRED)
find_package(Threads REQUIRED)

# Include headers
include_directories(${WIRINGPI_INCLUDE_DIRS})

# Link against libraries
target_link_libraries(MashberryPi ${WIRINGPI_LIBRARIES})
target_link_libraries(MashberryPi ${CMAKE_THREAD_LIBS_INIT})

add_executable(MashberryPi ${SOURCES})
#add_definitions(-std=c++0x -L/path/to/libwiringPi.???.(so|a) -lwiringPi -lpthread)

