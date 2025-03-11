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
add_executable( main src/main.cpp )
add_executable( resize_img src/resize_img.cpp )
add_executable( test_transformations src/test_transformations.cpp )
add_executable( test_filters src/test_filters.cpp )
add_executable( task1 src/lab1/task1.cpp )
add_executable( task2 src/lab1/task2.cpp )
add_executable( task3 src/lab1/task3.cpp )
add_executable( task4 src/lab1/task4.cpp )
add_executable( task5 src/lab1/task5.cpp )
add_executable( task6 src/lab1/task6.cpp )

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR}/lib)
target_link_libraries(main image_lib)
target_link_libraries(resize_img image_lib)
target_link_libraries(test_transformations image_lib)
target_link_libraries(test_filters image_lib)
target_link_libraries(task1 image_lib)
target_link_libraries(task2 image_lib)
target_link_libraries(task3 image_lib)
target_link_libraries(task4 image_lib)
target_link_libraries(task5 image_lib)
target_link_libraries(task6 image_lib)