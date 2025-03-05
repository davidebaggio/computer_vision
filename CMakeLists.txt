cmake_minimum_required(VERSION 3.16) 
PROJECT (opencv_test)
find_package(OpenCV REQUIRED )
set(LIB_SRC
    src/image_func.cpp
    src/pixel_transform.cpp
)

set(HEADERS
    include/image_func.hpp
    include/pixel_transform.hpp
)

add_library(image_lib STATIC ${LIB_SRC} ${HEADERS})
target_link_libraries(image_lib ${OpenCV_LIBS})

INCLUDE_DIRECTORIES( ${CMAKE_CURRENT_SOURCE_DIR}/include )
link_directories( ${CMAKE_BINARY_DIR}/bin )
add_executable( opencv_test src/main.cpp )
add_executable( resize_img src/resize_img.cpp )

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR}/lib)
target_link_libraries(opencv_test image_lib)
target_link_libraries(resize_img image_lib)