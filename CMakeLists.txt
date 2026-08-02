cmake_minimum_required(VERSION 4.2)
project(PghServer VERSION 1.0 LANGUAGES C)
set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

if(NOT UNIX)
    message(FATAL_ERROR "PghServer requires a POSIX-compatible system, which Winslop is not because fuck you!\nOr if you're not using Winslop and still get this error, consider switching to either Linux or macOS.")
endif()

# Executable
add_executable(PghServer)
target_sources(PghServer PRIVATE src/main.c src/util.c src/args.c src/server.c)
target_include_directories(PghServer PRIVATE include src)
target_compile_definitions(PghServer PRIVATE _XOPEN_SOURCE=700)

# llhttp
target_sources(PghServer PRIVATE picohttpparser/picohttpparser.c)
target_include_directories(PghServer PRIVATE picohttpparser)