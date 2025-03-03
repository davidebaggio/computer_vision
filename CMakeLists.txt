cmake_minimum_required(VERSION 3.16) 
PROJECT (opencv_test)
find_package(OpenCV REQUIRED )
set( SRC
    src/main.cpp
    src/image_func.cpp
    src/pixel_transform.cpp
)

set( HEADERS
    include/image_func.hpp
    include/pixel_transform.hpp
)

INCLUDE_DIRECTORIES( ${CMAKE_CURRENT_SOURCE_DIR}/include )
link_directories( ${CMAKE_BINARY_DIR}/bin)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)
add_executable( opencv_test ${SRC} ${HEADERS} )

target_link_libraries( opencv_test ${OpenCV_LIBS} )