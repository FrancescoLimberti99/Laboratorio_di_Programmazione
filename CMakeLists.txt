cmake_minimum_required(VERSION 3.28)

project(Elaborato)

set(CMAKE_CXX_STANDARD 17)

include_directories(C:/Libraries/cxxtest/cxxtest-master)

add_library(cxxtest STATIC
        C:/Libraries/cxxtest/cxxtest-master/cxxtest/TestSuite.cpp
        C:/Libraries/cxxtest/cxxtest-master/cxxtest/TestTracker.cpp
        C:/Libraries/cxxtest/cxxtest-master/cxxtest/LinkedList.cpp
        C:/Libraries/cxxtest/cxxtest-master/cxxtest/Descriptions.cpp
        C:/Libraries/cxxtest/cxxtest-master/cxxtest/RealDescriptions.cpp
        C:/Libraries/cxxtest/cxxtest-master/cxxtest/ValueTraits.cpp
        C:/Libraries/cxxtest/cxxtest-master/cxxtest/DummyDescriptions.cpp
        C:/Libraries/cxxtest/cxxtest-master/cxxtest/GlobalFixture.cpp
)

add_executable(Elaborato main.cpp Transaction.cpp BankAccount.cpp)

add_executable(Tests TestMain.cpp MyTestSuite.cpp Transaction.cpp BankAccount.cpp)

target_link_libraries(Tests PRIVATE cxxtest)