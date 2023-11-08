cmake_minimum_required(VERSION 3.5.0)
project(big_integer VERSION 0.1.0)
set (CMAKE_CXX_STANDARD 98)

add_executable(big_integer 
    main.cpp
    Array.h
    Array.cpp
    BigInteger.h
    BigInteger.cpp
)
