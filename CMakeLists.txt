cmake_minimum_required(VERSION 3.10)

project(Queue LANGUAGES CXX)

set(CMAKE_THREAD_PREFER_PTHREAD TRUE)
set(THREADS_PREFER_PTHREAD_FLAG TRUE)
find_package(Threads REQUIRED)

add_executable(Queue main.cpp)
add_compile_options(-Wall -Wextra -Wshadow -Wformat=2 -Wunused)

target_link_libraries( Queue ${CMAKE_THREAD_LIBS_INIT} )

