
set(CMAKE_THREAD_PREFER_PTHREAD TRUE)
set(THREADS_PREFER_PTHREAD_FLAG TRUE)
find_package(Threads REQUIRED)

add_executable(queue_demo main.cpp)
add_compile_options(-Wall -Wextra -Wshadow -Wformat=2 -Wunused)

target_link_libraries(queue_demo ${CMAKE_THREAD_LIBS_INIT})



