project(thread_pool)

cmake_minimum_required(VERSION 2.8)

set(CMAKE_CXX_FLAGS "${CAMKE_CXX_FLAGS} -std=c++11 -pthread -g")

set(source
    RequestQueue.h
    HshaThreadPool.hpp
    HshaThreadPool.cpp
    promise_thread_pool.hpp
    promise_thread_pool.cpp
    Main.cpp
)

add_executable(a.out ${source})
