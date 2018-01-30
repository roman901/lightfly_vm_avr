cmake_minimum_required(VERSION 3.9)

set(CMAKE_TOOLCHAIN_FILE "${CMAKE_SOURCE_DIR}/generic-avr-gcc.cmake")
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}")

set(AVR_MCU atmega16)
set(MCU_FREQ 8000000UL)
set(AVR_PROGRAMMER avr109)
set(AVR_PROGRAMMER_PORT /dev/ttyUSB0)

project(lightfly_vm_avr C)

include_directories(
        lightfly_vm/lightfly_vm_lib/include
        include)
link_directories(lightfly_vm/lightfly_vm_lib/src)

avr_add_executable(lightfly_vm_avr
        src/main.c

        include/errors.h
        src/errors.c

        include/opcodes.h
        src/opcodes.c

        lightfly_vm/lightfly_vm_lib/src/lf_loader.c
        lightfly_vm/lightfly_vm_lib/src/lf_executor.c
        lightfly_vm/lightfly_vm_lib/src/lf_opcodes.c
        lightfly_vm/lightfly_vm_lib/src/lf_stack.c)