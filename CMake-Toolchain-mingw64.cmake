set(CMAKE_SYSTEM_NAME "Windows")
set(TOOLCHAIN_PREFIX "x86_64-w64-mingw32")

set(CMAKE_C_COMPILER "${TOOLCHAIN_PREFIX}-gcc")
set(CMAKE_CXX_COMPILER "${TOOLCHAIN_PREFIX}-g++")

set(CMAKE_FIND_ROOT_PATH "/usr/${TOOLCHAIN_PREFIX}")
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)

set(CURSES_LIBRARY "/usr/${TOOLCHAIN_PREFIX}/lib/libpdcurses.a")
set(CURSES_INCLUDE_PATH "/usr/${TOOLCHAIN_PREFIX}/include/pdcurses/")

set(CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static-libstdc++ -Wl,-Bstatic,--whole-archive -lwinpthread -Wl,-Bdynamic,--no-whole-archive")
