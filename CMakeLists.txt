cmake_minimum_required (VERSION 3.2)

project(capif LANGUAGES CXX VERSION 0.0.1)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Get the latest commit hash
execute_process(
    COMMAND git rev-parse HEAD
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    OUTPUT_VARIABLE GIT_COMMIT_HASH
    OUTPUT_STRIP_TRAILING_WHITESPACE)
write_file(.VERSION "${CMAKE_PROJECT_VERSION}")
message("Version: ${CMAKE_PROJECT_VERSION} (${GIT_COMMIT_HASH})")

add_subdirectory(lib/capif)

set(CCF_NAME ccf)

file(GLOB_RECURSE CCF_SRCS
    ${CMAKE_CURRENT_SOURCE_DIR}/src/ccf/*.cpp
)

add_executable(${CCF_NAME} ${CCF_SRCS})
target_link_libraries(${CCF_NAME} PUBLIC capif pistache pthread)
target_include_directories(${CCF_NAME} PUBLIC
                          lib/capif/include/
                          )