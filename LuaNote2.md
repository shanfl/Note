#Lua

--------

**Lua Note**

> by **shanfl**

> Date:2015.11.5







![luaicon](http://www.lua.org/images/lua.gif)



----



###lua functions:

*	Lua Set&Get Functions 

  - 	void **lua_setglobal** (lua_State *L, const char *name);

   	 ```Lua

       [-1, +0, e]

        Pushes onto the stack the value of the global name. It is defined as a macro:

		#define lua_getglobal(L,s)  lua_getfield(L, LUA_GLOBALSINDEX, s)

	```

  -  void **lua_getglobal** (lua_State *L, const char *name);

	```Lua

    [-0, +1, e]

    Pushes onto the stack the value of the global name. It is defined as a macro:

    #define lua_getglobal(L,s)  lua_getfield(L, LUA_GLOBALSINDEX, s)

    ```

  - void **lua_settable** (lua_State *L, int index);

	```Lua

    [-2, +0, e]

    Does the equivalent to t[k] = v, where t is the value at the given valid index, v is the value at the top of the stack, and k is the value just below the top.

	This function pops both the key and the value from the stack. As in Lua, this function may trigger a metamethod for the "newindex" event```



  -  void **lua_gettable** (lua_State *L, int index);

	```Lua

  [-1, +1, e]

  Pushes onto the stack the value t[k], where t is the value at the given valid index and k is the value at the top of the stack.

  This function pops the key from the stack (putting the resulting value in its place). As in Lua, this function may trigger a metamethod for the "index" event```



  - void **lua_setfield** (lua_State *L, int index, const char *k);

 ```Java

 [-1, +0, e]

 Does the equivalent to t[k] = v, where t is the value at the given valid index and v is the value at the top of the stack.

 This function pops the value from the stack. As in Lua, this function may trigger a metamethod for the "newindex" event```



  - void **lua_getfield** (lua_State *L, int index, const char *k);

	```Java

    [-0, +1, e]

    Pushes onto the stack the value t[k], where t is the value at the given valid index. As in Lua, this function may trigger a metamethod for the "index" event ```



  - int **lua_setmetatable** (lua_State *L, int index);

  ```Lua

  [-1, +0, -]

  Pops a table from the stack and sets it as the new metatable for the value at the given acceptable index.```



 - int **lua_getmetatable** (lua_State *L, int index);

  ```Lua

  [-0, +(0|1), -]

  Pushes onto the stack the metatable of the value at the given acceptable index. If the index is not valid, or if the value does not have a metatable, the function returns 0 and pushes nothing on the stack.

  ```



  - void lua_rawgeti (lua_State *L, int index, int n);

  ```Lua

  [-0, +1, -]

  Pushes onto the stack the value t[n], where t is the value at the given valid index. The access is raw; that is, it does not invoke metamethods.

  ```

  - void **lua_rawseti**(lus_State*L,int index,int n)

  ```Lua

  [-1, +0, m]

  Does the equivalent of t[n] = v, where t is the value at the given valid index and v is the value at the top of the stack.

  This function pops the value from the stack. The assignment is raw; that is, it does not invoke metamethods.

  ```

  - void **lua_rawget** (lua_State *L, int index);

    > Similar to ==lua_gettable==, but does a raw access (i.e., without metamethods).



  - void **lua_rawset** (lua_State *L, int index);

	> [-2, +0, m]

	Similar to ==lua_settable==, but does a raw assignment (i.e., without metamethods).



* lua ==New&Create== Functions

  - void **lua_createtable** (lua_State *L, int narr, int nrec);

  > ```Lua

  [-0, +1, m]

  Creates a new empty table and pushes it onto the stack. The new table has space pre-allocated for narr array elements and nrec non-array elements. This pre-allocation is useful when you know exactly how many elements the table will have. Otherwise you can use the function lua_newtable.

  ```



 - lua_State \* **lua_newstate** (lua_Alloc f, void *ud);

 >  [-0, +0, -]

 Creates a new, independent state. Returns NULL if cannot create the state (due to lack of memory). The argument f is the allocator function; Lua does all memory allocation for this state through this function. The second argument, ud, is an opaque pointer that Lua simply passes to the allocator in every call.



  - void **lua_newtable** (lua_State *L);

  	> [-0, +1, m]

	  Creates a new empty table and pushes it onto the stack. It is equivalent to lua_createtable(L, 0, 0).



  - void \* **lua_newuserdata** (lua_State *L, size_t size);

	> [-0, +1, m]

	  This function allocates a new block of memory with the given size, pushes onto the stack a new full userdata with         the block address, and returns this address.

      Userdata represent C values in Lua. A full userdata represents a block of memory. It is an object (like a table):         you must create it, it can have its own metatable, and you can detect when it is being collected. A full userdata         is only equal to itself (under raw equality).

      When Lua collects a full userdata with a gc metamethod, Lua calls the metamethod and marks the userdata as               finalized. When this userdata is collected again then Lua frees its corresponding memory.



###Utils

* require

    > ```Lua

	function require(name)

    	if not package.loaded[name] then

        	local loader = findloader(name)

            if loader == nil then

            	error("unable to load module"..name)

            end

            package.load[name] = true

            local res = loader(name)

            if res ~= nil then

            	package.load[name] = res

            end

            return package.loaded[name]

        end

     ```



*  ==int **lua_next** (lua_State *L, int index);==

  > int lua_next (lua_State *L, int index);

    [-1, +(2|0), e]

    Pops a key from the stack, and pushes a key-value pair from the table at the given index (the "next" pair after the       given key). If there are no more elements in the table, then lua_next returns 0 (and pushes nothing).

    A typical traversal looks like this:

     ```Cpp

     /* table is in the stack at index 't' */

     lua_pushnil(L);  /* first key */

     while (lua_next(L, t) != 0) {

       /* uses 'key' (at index -2) and 'value' (at index -1) */

       printf("%s - %s\n",

              lua_typename(L, lua_type(L, -2)),

              lua_typename(L, lua_type(L, -1)));

       /* removes 'value'; keeps 'key' for next iteration */

       lua_pop(L, 1);

     }

     ```

     While traversing a table, do not call lua_tolstring directly on a key, unless you know that the key is actually a        string. Recall that lua_tolstring changes the value at the given index; this confuses the next call to lua_next.



