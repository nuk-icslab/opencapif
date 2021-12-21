cmake_minimum_required (VERSION 3.2)
include(FindPkgConfig)

find_package(spdlog REQUIRED)
find_package(yaml-cpp REQUIRED)
pkg_check_modules(LIBPISTACHE libpistache)

add_executable(standalone_apf
              api_publishing_function/standalone_apf.cpp
              )
target_link_libraries(standalone_apf PUBLIC
                     capif apf
                     yaml-cpp
                     spdlog::spdlog
                     )
target_include_directories(standalone_apf PUBLIC
    include/
    lib/capif/include/
)
configure_file(api_publishing_function/config/apf.yaml
              config/apf.yaml
              )
configure_file(api_publishing_function/config/api.yaml
              config/api.yaml
              )

#=========
find_package(spdlog REQUIRED)
find_package(yaml-cpp REQUIRED)
pkg_check_modules(LIBPISTACHE libpistache)

add_executable(simple_invoker
              api_invoker/simple_invoker.cpp
              )
target_link_libraries(simple_invoker PUBLIC
                     capif capifinvoker
                     yaml-cpp
                     spdlog::spdlog
                     )
target_include_directories(simple_invoker PUBLIC
    include/
    lib/capif/include/
)