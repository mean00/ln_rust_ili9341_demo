#-----------------------------------------------------------------------------
MESSAGE(STATUS "\tFinal name is ${EXTENSION}")
#
# CMakeLists for lnDSO
# An opensource firmware for the DSO SHELL 150
# With optional hardware mods :
#   - Alternative rotary encoder wiring : MUCH Better, almost mandatory
#
#-----------------------------------------------------------------------------

cmake_minimum_required(VERSION 3.0)
MESSAGE(STATUS "===============")
MESSAGE(STATUS "Starting lnDSO")
MESSAGE(STATUS "===============")
#____________________
# Options
#____________________

#SET(LN_ENABLE_I2C  OFF CACHE INTERNAL "")
#SET(LN_ENABLE_SPI  ON CACHE INTERNAL "")


include(./build_default.cmake)
SET(AF_FOLDER  ${CMAKE_SOURCE_DIR}/lnArduino/)
include(./mcuSelect.cmake)
SET(CMAKE_TOOLCHAIN_FILE ${AF_FOLDER}/lnArduino.cmake)

PROJECT(st7789 NONE) # the NONE is very important !

enable_language(C CXX ASM) # this is important too!
SET(DSO_EXTRA_LIB simplerILI9341HS)
SET(SIMPLER_ILI9341_FONT_COMPRESSION ON CACHE INTERNAL "")
SET(SIMPLER_ILI9341_2BPP_SUPPORT     ON CACHE INTERNAL "")

#

include_directories(${CMAKE_SOURCE_DIR})
include_directories(${CMAKE_SOURCE_DIR}/include)
add_subdirectory(${AF_FOLDER})

include(${AF_FOLDER}/setup.cmake)


include_directories(simplerILI9341/platformExample/lnArduino)
#include_directories(simplerILI9341/cpp/demo/example_st7735_160x128_partially_working/)
include_directories(simplerILI9341/cpp/demo/example_st7735_240x320/)
SET(ILI9341_DRIVER  platformExample/lnArduino/ili_lnSpi.cpp)
ADD_SUBDIRECTORY(simplerILI9341/cpp)
include_directories(simplerILI9341/cpp)
include_directories(simplerILI9341/cpp/platformExample/lnArduino)
#
GENERATE_GD32_FIRMWARE(st7789 main_ili3941.cpp)
TARGET_LINK_LIBRARIES( st7789  simplerILI9341 ${DSO_EXTRA_LIB})

