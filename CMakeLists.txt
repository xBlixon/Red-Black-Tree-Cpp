cmake_minimum_required(VERSION 4.1)
project(RedBlackTree)

set(CMAKE_CXX_STANDARD 20)

add_library(RedBlackTreeLibrary INTERFACE)

target_sources(RedBlackTreeLibrary
        PRIVATE
            include/RedBlackTree.tpp
            include/Node.tpp
        PUBLIC
            FILE_SET HEADERS
            BASE_DIRS
                include
            FILES
                include/RedBlackTree.h
                include/Node.h
                include/Color.h
)

add_executable(RBT main.cpp)

target_link_libraries(RBT
        PRIVATE
            RedBlackTreeLibrary
)