cmake_minimum_required(VERSION 2.5...3.5)

project(sp_cstring VERSION 0.1 LANGUAGES C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

set(CMAKE_INSTALL_PREFIX /usr/local)

set(SOURCES
    src/sp/cstring.c
)

add_library(sp_cstring ${SOURCES})

target_include_directories(sp_cstring PRIVATE include/sp)

install(TARGETS sp_cstring DESTINATION lib)
install(FILES include/sp/cstring.h DESTINATION include/sp)


find_package(check CONFIG)

if(check_FOUND)
    add_executable(test_string tests/test_cstring.c)

    target_include_directories(test_string PRIVATE include)
    target_link_libraries(test_string PRIVATE sp_cstring Check::checkShared)
endif()
