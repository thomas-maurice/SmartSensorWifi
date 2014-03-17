CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

PROJECT(SmartSensor)

SET(CMAKE_TOOLCHAIN_FILE "/home/thomas/RaspberryPi/rpi-toolchain.cmake")

INCLUDE_DIRECTORIES("include")
LINK_DIRECTORIES()

FILE(
	GLOB_RECURSE
	sources
	src/*.c
	src/*.cpp
	include/*.hpp
	include/*.h
)

ADD_EXECUTABLE(
	SmartSensor
	${sources}
)

LINK_LIBRARIES(

)
