cmake_minimum_required(VERSION 3.0.0)
project(c-react-ssr-example VERSION 0.1.0)

find_package(duktape CONFIG REQUIRED)

include_directories(${CMAKE_CURRENT_SOURCE_DIR} ${DUKTAPE_INCLUDE_DIRS})

find_package(civetweb CONFIG REQUIRED)

add_executable(c-react-ssr-example server/main.c)
target_link_libraries(c-react-ssr-example ${DUKTAPE_LIBRARY} civetweb::civetweb m)
set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)