cmake_minimum_required(VERSION 3.10.0 FATAL_ERROR)
project(NesEmu VERSION 0.1.0)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)

file(GLOB_RECURSE _NesEmu_Sources
    "src/*.c"
)

add_executable(NesEmu
	${_NesEmu_Sources}
)

target_include_directories(NesEmu PRIVATE
	include/
)

target_link_directories(NesEmu PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/lib/x64
)
