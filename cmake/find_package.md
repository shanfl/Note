## [FindGoogleTest.cmake]

**${GooleTest_LIBRARIES}**  

**${GooleTest_INCLUDE_DIR}**  

```cmake
MESSAGE(STATUS "CMAKE_SOURCE_DIR:" ${CMAKE_SOURCE_DIR})
MESSAGE(STATUS "CMAKE_MODULE_PATH:" ${CMAKE_MODULE_PATH})
MESSAGE(STATUS "CMAKE_CURRENT_SOURCE_DIR:" ${CMAKE_CURRENT_SOURCE_DIR})

FIND_PATH(GooleTest_INCLUDE_DIR "gtest/gtest.h"
	HINTS ${CMAKE_MODULE_PATH}
	PATH_SUFFIXES googletest/include
	)
	
MESSAGE(STATUS "GooleTest_INCLUDE_DIR:" ${GooleTest_INCLUDE_DIR})

FIND_LIBRARY(GooleTest_LIBRARY_CORE NAMES gtestd 
		HINTS ${CMAKE_MODULE_PATH}
		PATH_SUFFIXES build/lib/debug
	)
	
FIND_LIBRARY(GooleTest_LIBRARY_MAIN NAMES gtest_maind 
		HINTS ${CMAKE_MODULE_PATH}
		PATH_SUFFIXES build/lib/debug
	)
	
MESSAGE(STATUS "GooleTest_LIBRARY_CORE:" ${GooleTest_LIBRARY_CORE})
MESSAGE(STATUS "GooleTest_LIBRARY_MAIN:" ${GooleTest_LIBRARY_MAIN})


set(GooleTest_LIBRARIES ${GooleTest_LIBRARY_CORE}  ${GooleTest_LIBRARY_MAIN})
set(GooleTest_INCLUDE_DIR ${GooleTest_INCLUDE_DIR} )

```





----------------

#### [find_package(GoogleTest MODULE)]

```cmake
project(googletestdemo)
set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR} "D:/repos/googletest")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MTd")
find_package(GoogleTest MODULE)
add_executable(main main.cxx)
target_include_directories(main PRIVATE ${GooleTest_INCLUDE_DIR})
target_link_libraries(main ${GooleTest_LIBRARIES})
```



#### how to understand

------------------------------

```cmake
FIND_PATH(GooleTest_INCLUDE_DIR "gtest/gtest.h"
	HINTS ${CMAKE_MODULE_PATH}
	PATH_SUFFIXES googletest/include
	)
```

`${CMAKE_MODULE_PATH}`   

​		+			`googletest/include `

​						to-search							`gtest/gtest.h`

