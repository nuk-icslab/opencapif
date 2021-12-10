cmake_minimum_required (VERSION 3.2)
include(FindPkgConfig)

find_package(spdlog REQUIRED)
pkg_check_modules(LIBPISTACHE libpistache)

add_executable(standalone_apf
              api_provider/standalone_apf.cpp
              )
target_link_libraries(standalone_apf PUBLIC
                     capif apf
                     spdlog::spdlog
                     )
target_include_directories(standalone_apf PUBLIC
    include/
    lib/capif/include/
)