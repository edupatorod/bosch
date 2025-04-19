

set(CMAKE_THREAD_PREFER_PTHREAD TRUE)
set(THREADS_PREFER_PTHREAD_FLAG TRUE)
find_package(Threads REQUIRED)

add_compile_options(-Wall -Wextra -Wshadow -Wformat=2 -Wunused)

add_executable(test_queue_simple test_queue.cpp)
target_link_libraries(test_queue_simple ${CMAKE_THREAD_LIBS_INIT})

add_executable(test_queue_pop_lock test_queue_pop_lock.cpp)
target_link_libraries(test_queue_pop_lock ${CMAKE_THREAD_LIBS_INIT})

add_executable(test_queue_pop_fill_all test_queue_fill_all.cpp)
target_link_libraries(test_queue_pop_fill_all ${CMAKE_THREAD_LIBS_INIT})

add_executable(test_queue_pop_timeout test_queue_pop_timeout.cpp)
target_link_libraries(test_queue_pop_timeout ${CMAKE_THREAD_LIBS_INIT})

add_executable(test_queue_double test_queue_double.cpp)
target_link_libraries(test_queue_double ${CMAKE_THREAD_LIBS_INIT})


add_test(NAME Queue_simple COMMAND test_queue_simple)
add_test(NAME Queue_pop_lock COMMAND test_queue_pop_lock)
add_test(NAME Queue_pop_fill_all COMMAND test_queue_pop_fill_all)
add_test(NAME Queue_pop_timeout COMMAND test_queue_pop_timeout)
add_test(NAME Queue_double COMMAND test_queue_double)







