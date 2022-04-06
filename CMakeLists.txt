cmake_minimum_required(VERSION 3.14)
project(MDMTracking)

set(CMAKE_CXX_STANDARD 14)

enable_language (Fortran)
set (CMAKE_Fortran_FLAGS "-fPIC -finit-local-zero -falign-commons -fno-automatic")
set (CMAKE_CXX_FLAGS "-fPIC")

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "$ENV{ROOTSYS}/etc/cmake")
list(APPEND CMAKE_PREFIX_PATH $ENV{ROOTSYS})

# Find ROOT
find_package(ROOT REQUIRED)
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${ROOT_CXX_FLAGS} -O3")
include_directories(${ROOT_INCLUDE_DIRS} ${CMAKE_SOURCE_DIR})
link_directories(${ROOT_LIBRARY_DIR})

include_directories(${PROJECT_SOURCE_DIR}/include
				    ${CMAKE_CURRENT_SOURCE_DIR}/include)

file(GLOB sources ${PROJECT_SOURCE_DIR}/src/*.cc ${PROJECT_SOURCE_DIR}/src/*.cpp ${PROJECT_SOURCE_DIR}/src/*.C ${PROJECT_SOURCE_DIR}/src/*.F)
file(GLOB headers ${PROJECT_SOURCE_DIR}/include/*.hh ${PROJECT_SOURCE_DIR}/include/*.h)
                    
# add_library (MDMTrace SHARED src/MDMTrace.cpp src/RAYTKIN1.F)
# target_link_libraries(MDMTrace c gfortran)

add_executable(MDMTracking TrackingExample.C ${sources} ${headers})

target_link_libraries(MDMTracking ${ROOT_LIBRARIES})

set(TRACKING_SCRIPTS rayin.dat)
foreach(_script ${TRACKING_SCRIPTS})
  configure_file(
    ${PROJECT_SOURCE_DIR}/dat/${_script}
    ${PROJECT_BINARY_DIR}/${_script}
    COPYONLY
    )
endforeach()