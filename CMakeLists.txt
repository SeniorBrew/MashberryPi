cmake_minimum_required(VERSION 3.0)
project(MashberryPi)

set(HEADER_FILES $("inc/*.h"))
include_directories(inc)
file(GLOB SOURCES "src/*.cpp")

add_executable(MashberryPi ${SOURCES})

# Locate libraries and headers
find_package(WiringPi REQUIRED)
#find_package(Threads REQUIRED)

# Include headers
include_directories(${WIRINGPI_INCLUDE_DIRS})

# Link against libraries
target_link_libraries(MashberryPi ${WIRINGPI_LIBRARIES})
#target_link_libraries(MashberryPi ${CMAKE_THREAD_LIBS_INIT})
