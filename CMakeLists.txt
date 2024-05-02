#-----------------------------------------------------------------------------
MESSAGE(STATUS "\tFinal name is ${EXTENSION}")
#
# CMakeLists for lnDSO
# An opensource firmware for the DSO SHELL 150
# With optional hardware mods :
#   - Alternative rotary encoder wiring : MUCH Better, almost mandatory
#
#-----------------------------------------------------------------------------

cmake_minimum_required(VERSION 3.10)
SET(CMAKE_EXPORT_COMPILE_COMMANDS ON)

MESSAGE(STATUS "===============")
MESSAGE(STATUS "Starting lnDSO")
MESSAGE(STATUS "===============")
#____________________
# Options
#____________________

#SET(LN_ENABLE_I2C  OFF CACHE INTERNAL "")
#SET(LN_ENABLE_SPI  ON CACHE INTERNAL "")


include(./build_default.cmake)
#SET(RP2040_NO_FLASH True CACHE INTERNAL "")
SET(AF_FOLDER  ${CMAKE_SOURCE_DIR}/lnArduino/)
include(./mcuSelect.cmake)
#ADD_DEFINITIONS("-O0")
SET(CMAKE_TOOLCHAIN_FILE ${AF_FOLDER}/lnArduino.cmake)

PROJECT(st7789 NONE) # the NONE is very important !

enable_language(C CXX ASM) # this is important too!
#SET(LN_CUSTOM_LD_SCRIPT ${AF_FOLDER}/mcus/arm_rp2040/boards/rp2040/rp2040_linker_ram.ld.in)

#

add_subdirectory(${AF_FOLDER})
include(${AF_FOLDER}/setup.cmake)
# Add our rust demo
add_subdirectory(simplerILI9341/rust/demo_st7735_160x128)
GENERATE_GD32_FIRMWARE(st7789 main_rust.cpp)
TARGET_LINK_LIBRARIES( st7789  rsdemo )
#TARGET_LINK_LIBRARIES( st7789  simplerILI9341 ${DSO_EXTRA_LIB})
TARGET_LINK_LIBRARIES( st7789  lnarduino_c_bindings )

