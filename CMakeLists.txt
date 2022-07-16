# Copyright (c) Kk Shinkai. All Rights Reserved. See LICENSE.txt in the project
# root for license information.

cmake_minimum_required(VERSION 3.20)

project(SayakaLLVM)

set(CMAKE_CXX_STANDARD 20)

# This directive will look for the `LLVMConfig.cmake` file. The path should be
# `<INSTALL_PREFIX>/lib/cmake/llvm/LLVMConfig.cmake` where `<INSTALL_PREFIX>`
# is the install prefix of an installed version of LLVM. Set `$LLVM_DIR` to
# `<INSTALL_PREFIX>/lib/cmake/llvm` to use the installed version of LLVM, On
# Linux typically this is `/usr/lib/cmake/llvm/LLVMConfig.cmake`.
#
#     export LLVM_DIR="<INSTALL_PREFIX>/lib/cmake/llvm"
#
# You can also pass `-DLLVM_DIR=<INSTALL_PREFIX>/lib/cmake/llvm` to use the
# `cmake` command or set it directly in `ccmake` or `cmake-gui`.
#
# See https://llvm.org/docs/CMake.html for more information.
find_package(LLVM REQUIRED CONFIG)

message(STATUS "Found LLVM version ${LLVM_PACKAGE_VERSION}")
message(STATUS "Using 'LLVMConfig.cmake' in '${LLVM_DIR}'")

include_directories(${LLVM_INCLUDE_DIRS})
separate_arguments(LLVM_DEFINITIONS_LIST NATIVE_COMMAND ${LLVM_DEFINITIONS})
add_definitions(${LLVM_DEFINITIONS_LIST})

include_directories(./include)
add_executable(sayaka
    src/main.cpp
    src/ast/TokenKind.cpp
    src/parse/Lex.cpp
)

llvm_map_components_to_libnames(llvm_libs support core irreader)

target_link_libraries(sayaka ${llvm_libs})
