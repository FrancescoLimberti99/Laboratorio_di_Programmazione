cmake_minimum_required(VERSION 3.28)

project(Elaborato)

set(CMAKE_CXX_STANDARD 17)

include_directories(./cxxtest-master)

add_library(cxxtest STATIC
        ./cxxtest-master/cxxtest/TestSuite.cpp
        ./cxxtest-master/cxxtest/TestTracker.cpp
        ./cxxtest-master/cxxtest/LinkedList.cpp
        ./cxxtest-master/cxxtest/Descriptions.cpp
        ./cxxtest-master/cxxtest/RealDescriptions.cpp
        ./cxxtest-master/cxxtest/ValueTraits.cpp
        ./cxxtest-master/cxxtest/DummyDescriptions.cpp
        ./cxxtest-master/cxxtest/GlobalFixture.cpp
)

add_executable(Elaborato main.cpp Transaction.cpp BankAccount.cpp)

add_executable(Tests TestMain.cpp MyTestSuite.cpp Transaction.cpp BankAccount.cpp)

target_link_libraries(Tests PRIVATE cxxtest)