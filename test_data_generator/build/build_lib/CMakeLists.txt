project(test_data_generator)

cmake_minimum_required(VERSION 2.8)

set(CMAKE_CXX_FLAGS "${CAMKE_CXX_FLAGS} -std=c++11 -g")
set(CMAKE_INSTALL_PREFIX ${CMAKE_CURRENT_SOURCE_DIR})

set(SOURCE
    generator_define.hpp
    utils.hpp
    generator_param.hpp
    command_parser.hpp
    test_rec_data_generator.hpp
    real_rec_data_generator.hpp
    ueupload_data_generator.hpp
    ipcupload_data_generator.hpp
    sds_data_generator.hpp
    test_rec_data_generator_factory.hpp
    gen_test_data_itf.hpp
    
    utils.cpp
    generator_param.cpp
    command_parser.cpp
    test_rec_data_generator.cpp
    real_rec_data_generator.cpp
    ueupload_data_generator.cpp
    ipcupload_data_generator.cpp
    sds_data_generator.cpp
    test_rec_data_generator_factory.cpp
    gen_test_data_itf.cpp
)

add_library(test_data_generator SHARED ${SOURCE})

install(TARGETS test_data_generator LIBRARY DESTINATION lib)
