cmake_minimum_required(VERSION 3.5)
set( ProjNa Port4 )
project( ${ProjNa} )

#set(CMAKE_BUILD_TYPE,"Debug")
#set(CMAKE_CC_STANDARD 11)
#set(CMAKE_CC_STANDARD_REQUIRED ON)
add_compile_options("-fvisibility=hidden")
find_package(GDAL REQUIRED)

message(STATUS "=====PDAL Envorment=====")
message(Status "......${GDAL_INCLUDE_DIRS}")
message(Status "......${GDAL_LIBRARY}")

include_directories(${GDAL_INCLUDE_DIRS})
#link_directories(${GDAL_LIBRARY})


aux_source_directory(. DIR_SRCS)
message(Status "......${DIR_SRCS}")

#add_library( ${ProjNa} EXCLUDE_FROM_ALL main.c)
add_library( ${ProjNa} SHARED ${DIR_SRCS} )

#add_executable( LIBPort4 libport4.c)

target_link_libraries(  ${ProjNa} PRIVATE  ${GDAL_LIBRARY})



