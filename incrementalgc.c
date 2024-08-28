#include <stdio.h>
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>

// Function to run a Lua garbage collector command and print memory usage
void run_gc(lua_State *L, const char *gc_command, int steps) {
    if (steps > 0) {
        lua_getglobal(L, "collectgarbage");
        lua_pushstring(L, gc_command);
        lua_pushnumber(L, steps);
        lua_pcall(L, 2, 0, 0);
    } else {
        lua_getglobal(L, "collectgarbage");
        lua_pushstring(L, gc_command);
        lua_pcall(L, 1, 0, 0);
    }

    lua_getglobal(L, "collectgarbage");
    lua_pushstring(L, "count");
    lua_pcall(L, 1, 1, 0);
    double memory_usage = lua_tonumber(L, -1);
    lua_pop(L, 1);
    printf("Memory usage after %s: %.2f KB\n", gc_command, memory_usage);
}

int main(void) {
    // A new Lua state
    lua_State *L = luaL_newstate();

    // Opening Lua standard libraries
    luaL_openlibs(L);

    // Loading and running the Lua testbench
    if (luaL_loadfile(L, "testbench.lua") || lua_pcall(L, 0, 0, 0)) {
        fprintf(stderr, "Error: %s\n", lua_tostring(L, -1));
        lua_pop(L, 1);
        lua_close(L);
        return 1;
    }

    // Initial memory usage
    run_gc(L, "count", 0);

    // Performing full garbage collection before
    run_gc(L, "collect", 0);

    // Calling the Lua function 'test'
    lua_getglobal(L, "test");
    if (lua_pcall(L, 0, 0, 0) != LUA_OK) {
        fprintf(stderr, "Error: %s\n", lua_tostring(L, -1));
        lua_pop(L, 1);
        lua_close(L);
        return 1;
    }
    run_gc(L, "count", 0);

    // Performing a garbage collection step
    run_gc(L, "step", 100);

    // Switching back to incremental garbage collection
    run_gc(L, "incremental", 0);

    // Calling the lua function again
    lua_getglobal(L, "test");
    if (lua_pcall(L, 0, 0, 0) != LUA_OK) {
        fprintf(stderr, "Error: %s\n", lua_tostring(L, -1));
        lua_pop(L, 1);
        lua_close(L);
        return 1;
    }
    run_gc(L, "collect", 0);

    lua_close(L);

    return 0;
}
