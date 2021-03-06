cmake_minimum_required(VERSION 3.5)
project(MDMTracking)

set(CMAKE_CXX_STANDARD 14)

enable_language (Fortran)
set (CMAKE_Fortran_FLAGS "-fPIC -finit-local-zero -falign-commons -fno-automatic")
set (CMAKE_CXX_FLAGS "-fPIC")

# Find ROOT
find_package(ROOT CONFIG REQUIRED)
if(ROOT_FOUND) 
    message ("ROOT found")
    include_directories(${ROOT_INCLUDE_DIRS})
else()
    message (FATAL_ERROR "Cannot find ROOT")
endif()

# build library libMDMTraceFit
add_library (MDMTraceFit SHARED src/MDMTraceFit.cpp src/MDMTrace.cpp src/RAYTKIN1.F)
target_include_directories(MDMTraceFit  PUBLIC ${PROJECT_SOURCE_DIR}/include)

# build executable file ${PROJECT_NAME} (MDMTracking)
add_executable(${PROJECT_NAME} TrackingExample.C)
target_include_directories(${PROJECT_NAME} PRIVATE  ${PROJECT_SOURCE_DIR}/include)
target_link_libraries(${PROJECT_NAME} PRIVATE MDMTraceFit ROOT::MathCore)

# copy rayin.dat from dat/ to build/
set(DAT_FILES rayin.dat)
foreach(_datFiles ${DAT_FILES})
    configure_file(${PROJECT_SOURCE_DIR}/dat/${_datFiles} ${PROJECT_BINARY_DIR}/${_datFiles} COPYONLY)
endforeach()