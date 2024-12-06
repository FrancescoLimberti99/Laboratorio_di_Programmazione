cmake_minimum_required(VERSION 3.28)
project(Elaborato)

set(CMAKE_CXX_STANDARD 17)

add_executable(Elaborato main.cpp Transaction.cpp BankAccount.cpp)


Project(Tests)

set(CMAKE_CXX_STANDARD 17)

add_executable(Tests TestSuite.cpp Transaction.cpp BankAccount.cpp)

include_directories(C:/Libraries/cxxtest/cxxtest-master)
link_directories(C:/Libraries/cxxtest/cxxtest-master)
