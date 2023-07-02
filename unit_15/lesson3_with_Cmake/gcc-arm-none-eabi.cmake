set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR arm)

set(TOOLCHAIN_PREFIX arm-none-eabi-)
# set(FLAGS
#     "-fdata-sections -ffunction-sections --specs=nano.specs -Wl,--gc-sections")
# set(CPP_FLAGS
#     "-fno-rtti -fno-exceptions -fno-threadsafe-statics")

set(FLAGS
    "-mcpu=cortex-m3  -mthumb  -gdwarf-2 -O0")
set(CPP_FLAGS
    "-mcpu=cortex-m3  -mthumb  -gdwarf-2 -O0")

set(CMAKE_C_COMPILER ${TOOLCHAIN_PREFIX}gcc ${FLAGS})
# set(CMAKE_C_COMPILER ${TOOLCHAIN_PREFIX}gcc)
set(CMAKE_ASM_COMPILER ${CMAKE_C_COMPILER})
# set(CMAKE_CXX_COMPILER ${TOOLCHAIN_PREFIX}g++)
set(CMAKE_CXX_COMPILER ${TOOLCHAIN_PREFIX}g++ ${FLAGS} ${CPP_FLAGS})
set(CMAKE_OBJCOPY ${TOOLCHAIN_PREFIX}objcopy)
set(CMAKE_SIZE ${TOOLCHAIN_PREFIX}size)
set(CMAKE_OBJDUMP ${TOOLCHAIN_PREFIX}objdump)

set(CMAKE_EXECUTABLE_SUFFIX_ASM ".axf")
set(CMAKE_EXECUTABLE_SUFFIX_C ".axf")
set(CMAKE_EXECUTABLE_SUFFIX_C ".elf")
set(CMAKE_EXECUTABLE_SUFFIX_CXX ".axf")
set(CMAKE_EXECUTABLE_SUFFIX_CXX ".elf")

set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)