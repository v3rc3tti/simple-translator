cmake_minimum_required(VERSION 3.10)

project(translator)

add_executable(translator main.c
                    MemoryState.c
                    Token.c
                    StringBuilder.c
                    StringTable.c
                    Translator.c
                    Environment.c)

target_include_directories(translator PRIVATE "${CMAKE_SOURCE_DIR}/include")