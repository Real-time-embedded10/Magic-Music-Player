PROJECT(Hello)
CMAKE_MINIMUM_REQUIRED(VERSION 3.0)
AUX_SOURCE_DIRECTORY(. DIR_SRCS)
ADD_EXECUTABLE(main ${DIR_SRCS})
TARGET_LINK_LIBRARIES(main wiringPi)
