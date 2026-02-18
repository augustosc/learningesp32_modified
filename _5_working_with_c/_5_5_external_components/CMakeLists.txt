# For more information about build system see
# https://docs.espressif.com/projects/esp-idf/en/latest/api-guides/build-system.html
# The following five lines of boilerplate have to be in your project's
# CMakeLists in this exact order for cmake to work correctly
cmake_minimum_required(VERSION 3.16)

set(EXTRA_COMPONENT_DIRS /Users/augustosherman/Documents/esp-projects/_5_working_with_c/_5_5_external_components/calc)

include($ENV{IDF_PATH}/tools/cmake/project.cmake)

project(5_5_extra_components)
