cmake_minimum_required(VERSION 3.5)
project( CLIPort4 )

set( PORT4_LIB_PATH "${PROJECT_SOURCE_DIR}/../libport4/build/libPort4.so")
set( PORT4_LIB_H "${PROJECT_SOURCE_DIR}/../libport4/")
message(STATUS "${PORT4_LIB_PATH}")
message(STATUS "${PORT4_LIB_H}")


#set(CMAKE_BUILD_TYPE,"Debug")
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)



aux_source_directory(. DIR_SRCS)
message(Status "......${DIR_SRCS}")
add_executable( CLIPort4 ${DIR_SRCS})

#add_executable( LIBPort4 libport4.c)

target_link_libraries( CLIPort4  PRIVATE ${PORT4_LIB_PATH})


