## cmake note
- find_package
 ```
As you may already know, pkg_search_module() relies on the pkg-config program in order to locate dependencies. As you point out, Windows doesn't come with pkg-config. You might be able to install it and get things working that way, but probably a better alternative for crossplatform builds is to use CMake's find_package() function instead. This way you can eliminate the dependency on having pkg-config installed on the developer's machine.

cmake_minimum_required(VERSION 3.1)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules")

find_package(SDL2 REQUIRED)

add_executable(sdl2demo sdl2demo.cpp)
target_include_directories(sdl2demo SYSTEM PRIVATE "${SDL2_INCLUDE_DIR}")
target_link_libraries(sdl2demo "${SDL2_LIBRARY}")
CMake doesn't come with a module for finding SDL2 so you'll need to add that to your source directory. That's why the above sets the CMAKE_MODULE_PATH; you add a cmake script that works cross platform for finding SDL2 to ${CMAKE_SOURCE_DIR}/cmake/Modules and then you can deliver that script with your source code.

The FindSDL2.cmake module I've used is: http://freerct.googlecode.com/svn/trunk/CMake/FindSDL2.cmake

This script should be able to locate SDL2 if it's installed in a standard location. If SDL2 isn't installed in a standard location or otherwise can't be located by this script, the developer has to configure the appropriate CMake variables to tell CMake the appropriate location, after which the configure and build will be able to procede normally.

cmake <source dir> -G "Visual Studio 12 2013 Win64" -DSDL2_INCLUDE_DIR=<sdl dir>/include -DSDL2MAIN_LIBRARY=<sdl dir>/lib/x64/SDL2main.lib -DSDL2_LIBRARY=<sdl dir>/lib/x64/SDL2.lib
```
