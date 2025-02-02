cmake_minimum_required(VERSION 3.10)

project(networking)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

function(collect_sources dir output)
    file(GLOB_RECURSE files ${dir}/*.cpp)
    set(${output} ${files} PARENT_SCOPE)
endfunction()

collect_sources("server" SERVER_SOURCES)
collect_sources("client" CLIENT_SOURCES)

add_executable(server ${SERVER_SOURCES})
add_executable(client ${CLIENT_SOURCES})
