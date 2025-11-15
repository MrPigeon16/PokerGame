cmake_minimum_required(VERSION 3.20)
project(myserver)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(Protobuf CONFIG REQUIRED)
find_package(gRPC CONFIG REQUIRED)
find_package(jwt-cpp CONFIG REQUIRED)
find_package(PkgConfig REQUIRED)
pkg_check_modules(SQLITE3 REQUIRED sqlite3) # Finds the 'sqlite3' package
include_directories(${CMAKE_SOURCE_DIR}/include)

file(GLOB ALL_PROTO_FILES "${CMAKE_SOURCE_DIR}/protos/*.proto")

if(NOT ALL_PROTO_FILES)
    message(FATAL_ERROR "No .proto files found in the protos directory: ${CMAKE_SOURCE_DIR}/protos")
endif()

add_library(protolib)
target_link_libraries(protolib gRPC::grpc++)

target_include_directories(protolib PUBLIC ${CMAKE_CURRENT_BINARY_DIR})

get_target_property(grpc_cpp_plugin_location gRPC::grpc_cpp_plugin LOCATION)


protobuf_generate(
    TARGET protolib
    LANGUAGE cpp
    PROTOS ${ALL_PROTO_FILES}

    IMPORT_DIRS "${CMAKE_SOURCE_DIR}/protos"
)

protobuf_generate(
    TARGET protolib
    LANGUAGE grpc
    GENERATE_EXTENSIONS .grpc.pb.h .grpc.pb.cc
    PLUGIN "protoc-gen-grpc=${grpc_cpp_plugin_location}"
    PROTOS ${ALL_PROTO_FILES}
    IMPORT_DIRS "${CMAKE_SOURCE_DIR}/protos"
)

file(GLOB_RECURSE SERVER_SRC "src/*.cpp")

add_executable(server ${SERVER_SRC})
target_link_libraries(server gRPC::grpc++ protolib jwt-cpp::jwt-cpp ${SQLITE3_LIBRARIES} )
target_include_directories(server PUBLIC ${CMAKE_SOURCE_DIR}/include /usr/include ${SQLITE3_LIBRARIES})
