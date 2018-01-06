CMAKE_MINIMUM_REQUIRED (VERSION 2.8)
PROJECT (px5-api)

#SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY ./bin)
SET(LIBRARY_OUTPUT_PATH ../../../../src/main/resources)
SET(CMAKE_C_COMPILER g++ )
#SET(CMAKE_C_FLAGS ??)

IF(NOT DEFINED ENV{JAVA_HOME})
    message(FATAL_ERROR "not defined environment variable:JAVA_HOME")  
ENDIF()
INCLUDE_DIRECTORIES($ENV{JAVA_HOME}/include $ENV{JAVA_HOME}/include/linux)

#aux_source_directory(../ DIR_SRCS)
#add_executable(controller controller.cpp)

AUX_SOURCE_DIRECTORY(../ DIR_LIB_SRCS)
ADD_LIBRARY(btjoystick SHARED ${DIR_LIB_SRCS})