cmake_minimum_required(VERSION 3.1)

project (atollis)

find_package(CGAL REQUIRED)
find_package(Eigen3 3.3 REQUIRED NO_MODULE)

file(GLOB HEADER_FILES "header/*.h")
file(GLOB SOURCE_FILES "source/*.cpp")

include_directories(${EIGEN3_INCLUDE_DIR})

if (NOT CGAL_FOUND)
	message(FATAL_ERROR "CGAL wasn't found.")
endif()

add_compile_options(-frounding-math)

set(CMAKE_CXX_STANDARD 20)

add_executable(run main.cpp ${SOURCE_FILES} ${HEADER_FILES})

target_link_libraries(run CGAL::CGAL)