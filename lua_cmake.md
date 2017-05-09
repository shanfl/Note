cmakefile for lua 5.1.5
```
cmake_minimum_required(VERSION 2.8)
project (LUA C)

# the following two variables are defined for the use of packages 
# that wish to link or compile against lua
set (LUA_INCLUDE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/src")
set (LUA_LIBRARIES lua)

add_subdirectory (src)
```
##### another file ------------------------------------------------
```
#----------------------------------------------------
#-- lua/src/CMakeLists.txt
#---------------------------------------------------
# define the lua core source files
set (LUA_CORE_SRCS lapi.c lcode.c ldebug.c ldo.c ldump.c 
     lfunc.c lgc.c llex.c lmem.c lobject.c lopcodes.c
     lparser.c lstate.c lstring.c ltable.c ltm.c  lundump.c
     lvm.c lzio.c)

# define the lua lib source files
set (LUA_LIB_SRCS lauxlib.c lbaselib.c ldblib.c liolib.c
     lmathlib.c loslib.c ltablib.c lstrlib.c loadlib.c linit.c)

# create the library
add_library (lua ${LUA_LIB_SRCS} ${LUA_CORE_SRCS})

# create the lue executable and link it to the lib
add_executable (luaexec lua.c)
target_link_libraries (luaexec lua)

# name the executable lua just like the library
set_target_properties(luaexec PROPERTIES OUTPUT_NAME lua)

# create the luac thing (I have no clue) and link it
add_executable (luac luac.c print.c)
target_link_libraries (luac lua)
```
CMakeFile For Lua 5.2.3
=====
```
project(lua_project)
set(lua_core 
		lapi.c 
		lcode.c 
		lctype.c 
		ldebug.c 
		ldo.c 
		ldump.c 
		lfunc.c 
		lgc.c 
		llex.c
		lmem.c 
		lobject.c 
		lopcodes.c 
		lparser.c 
		lstate.c 
		lstring.c 
		ltable.c
		ltm.c 
		lundump.c
		lvm.c 
		lzio.c
	)
set(lua_lib 
		lauxlib.c 
		lbaselib.c
		lbitlib.c 
		lcorolib.c 
		ldblib.c 
		liolib.c
		lmathlib.c 
		loslib.c 
		lstrlib.c 
		ltablib.c 
		loadlib.c
		linit.c
	)
add_library(lua STATIC ${lua_core} ${lua_lib})


add_executable(luac luac.c)
target_link_libraries(luac lua)
add_executable(luaexe lua.c)
target_link_libraries(luaexe lua)
```

###lua 5.3 cmake 
```
project(lua_project)
set(lua_core 
        lapi.c 
        lcode.c 
        lctype.c 
        ldebug.c 
        ldo.c 
        ldump.c 
        lfunc.c 
        lgc.c 
        llex.c
        lmem.c 
        lobject.c 
        lopcodes.c 
        lparser.c 
        lstate.c 
        lstring.c 
        ltable.c
        ltm.c 
        lundump.c
        lvm.c 
        lzio.c
    )
set(lua_lib 
        lauxlib.c 
        lbaselib.c
        lbitlib.c 
        lcorolib.c 
        ldblib.c 
        liolib.c
        lmathlib.c 
        loslib.c 
        lstrlib.c 
        ltablib.c 
        loadlib.c
        linit.c
    )
add_library(lua STATIC ${lua_core} ${lua_lib})


add_executable(luac luac.c)
target_link_libraries(luac lua)
add_executable(luaexe lua.c)
target_link_libraries(luaexe lua)
```
