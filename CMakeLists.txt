cmake_minimum_required(VERSION 3.10)

project(Queue LANGUAGES CXX)

# set(CMAKE_THREAD_PREFER_PTHREAD TRUE)
# set(THREADS_PREFER_PTHREAD_FLAG TRUE)
# find_package(Threads REQUIRED)

# include(CTest)
enable_testing()
add_subdirectory(src)
add_subdirectory(tests)

add_test(NAME Run_demo COMMAND queue_demo)



