cmake_minimum_required(VERSION 3.16)

project(lab3_tablas_hash LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_library(hash_core
    src/dataset_reader.cpp
)

target_include_directories(hash_core
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

if(MSVC)
    target_compile_options(hash_core PRIVATE /W4)
else()
    target_compile_options(hash_core PRIVATE -Wall -Wextra -Wpedantic)
endif()

add_executable(hash_tests
    tests/hash_tests.cpp
)
target_link_libraries(hash_tests PRIVATE hash_core)

add_executable(hash_benchmark
    src/benchmark_main.cpp
)
target_link_libraries(hash_benchmark PRIVATE hash_core)

enable_testing()
add_test(NAME hash_tests COMMAND hash_tests)
set_tests_properties(hash_tests PROPERTIES
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)


add_executable(experimentos_linear_quadratic_probing
    hash_cerrado_linear_y_quadratic_probing/main.cpp
    hash_cerrado_linear_y_quadratic_probing/tabla_hash.cpp
    hash_cerrado_linear_y_quadratic_probing/load_dataset.cpp
)

target_include_directories(experimentos_linear_quadratic_probing
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/hash_cerrado_linear_y_quadratic_probing
)

