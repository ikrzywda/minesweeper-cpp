cmake_minimum_required(VERSION 3.0)
project(minesweeper)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address -fno-omit-frame-pointer")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -fsanitize=address")


set(SFML_INCLUDE_DIR "/usr/local/include")
set(SFML_LIBRARY_DIR "/usr/local/lib")

link_directories(${SFML_LIBRARY_DIR})
include_directories(${SFML_INCLUDE_DIR})

find_package(SFML 2.5.1 COMPONENTS system window graphics network audio)


# tego brakuje !! To są opcje, których ja sam używam w moich programach
# te opcje muszą być ZAWSZE włączone
add_compile_options(-Wall -Wextra)


# chcemy, by nasz kod był w pełni zgodny ze standardem
add_compile_options(-pedantic)

# zmieniamy niektóre ostrzeżenia na błędy
# missing return in non-void function: “control reaches end of non-void function"
add_compile_options(-Werror=return-type)

# misleading parentheses - read here: https://www.ibm.com/docs/en/ztpf/1.1.0.14?topic=warnings-parentheses
add_compile_options(-Werror=parentheses)

# VLA is a non-standard feature of some c++ compilers - this prevents its usage
add_compile_options(-Werror=vla)

# detect some trivial array-bounds errors in code (only compile-time !!)
add_compile_options(-Werror=array-bounds)

# additional warnings
add_compile_options ( -Wcast-qual )
add_compile_options ( -Wuninitialized )

file(GLOB SOURCES "src/*.cpp")

add_executable(minesweeper ${SOURCES} main.cpp)

target_link_libraries (minesweeper sfml-graphics sfml-window sfml-system)



