cmake_minimum_required(VERSION 3.28)
project(Elaborato)

set(CMAKE_CXX_STANDARD 17)

include_directories(C:/Libraries/cxxtest/cxxtest-master)
link_directories(C:/Libraries/cxxtest/cxxtest-master)

set(CXXTEST_DIR "C:/Libraries/cxxtest/cxxtest-master")

add_executable(Elaborato main.cpp Transaction.cpp BankAccount.cpp TestSuite.cpp)

add_executable(tests TestSuite.cpp Transaction.cpp BankAccount.cpp)

target_link_libraries(tests ${CXXTEST_LIBRARIES})
target_link_libraries(Elaborato CxxTest)
target_link_libraries(Elaborato -lkernel32 -luser32 -lgdi32 -lwinspool -lshell32 -lole32 -loleaut32 -luuid -lcomdlg32 -ladvapi32)