cmake_minimum_required(VERSION 3.22)
project(progetto)

#set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD 20)

#add_executable(progetto main_seq.cpp util.cpp util.hpp)
#add_executable(progetto main_th.cpp util.cpp util.hpp)
#add_executable(progetto main_ff.cpp util.cpp util.hpp)

#add_executable(progetto seq_rand_test.cpp util.cpp util.hpp)
add_executable(progetto main_all_double.cpp util.cpp util.hpp utimer.cpp)




