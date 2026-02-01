cmake_minimum_required(VERSION 4.1)
project(RedBlackTree)

set(CMAKE_CXX_STANDARD 20)

add_library(RedBlackTreeLibrary INTERFACE
        include/Iterator.tpp
        include/Iterator.h)

target_sources(RedBlackTreeLibrary
        INTERFACE
            include/RedBlackTree.tpp
            include/Node.tpp
            include/Iterator.tpp
        PUBLIC
            FILE_SET HEADERS
            BASE_DIRS
                include
            FILES
                include/RedBlackTree.h
                include/Node.h
                include/Color.h
                include/Iterator.h
)

add_executable(exec main.cpp)

target_link_libraries(exec
        PRIVATE
            RedBlackTreeLibrary
)