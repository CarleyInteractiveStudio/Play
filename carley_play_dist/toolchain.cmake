# Carley Play Toolchain para Unity/Unreal

set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR arm)

# Compilador
set(CMAKE_C_COMPILER arm-none-eabi-gcc)
set(CMAKE_CXX_COMPILER arm-none-eabi-g++)

# Banderas para RK3128 (Cortex-A7)
set(COMMON_FLAGS "-mcpu=cortex-a7 -mfloat-abi=hard -mfpu=neon-vfpv4 -O3")
set(CMAKE_C_FLAGS "${COMMON_FLAGS}" CACHE STRING "")
set(CMAKE_CXX_FLAGS "${COMMON_FLAGS} -std=c++11" CACHE STRING "")

# Script de enlace y flags de sistema
set(CMAKE_EXE_LINKER_FLAGS "-T link.ld -nostartfiles -Wl,--gc-sections" CACHE STRING "")

set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
