cmake_minimum_required(VERSION 3.15)
project(test_ceres)

set(CMAKE_CXX_STANDARD 14)

find_package(Ceres REQUIRED COMPONENTS EigenSparse)
# FIND_PACKAGE(Protobuf REQUIRED)

# PROTOBUF_GENERATE_CPP(PROTO_SRC PROTO_HEADER message.proto) 
# ADD_LIBRARY(proto ${PROTO_HEADER} ${PROTO_SRC})

include_directories(
    ${CERES_INCLUDE_DIRS}
    ${PROTOBUF_INCLUDE_DIR}
)

#set(CMAKE_CXX_FLAGS "-fsanitize=address -g")

add_executable(out main.cc)
target_link_libraries(out ${CERES_LIBRARIES})
