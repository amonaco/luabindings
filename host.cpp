#include <iostream>
#include <lua.hpp> // there's also lua.h

int host_function(lua_State *L)
{
    int argc = lua_gettop(L);

    std::cerr << "-- host_function() called with " << argc
        << " arguments:" << std::endl;

    for (int n = 1; n <= argc; ++n)
        std::cerr << "-- arg: " << n << ": "
        << lua_tostring(L, n) << std::endl;

    lua_pushnumber(L, 123); // return value
    return 1; // number of return values
}

void report_errors(lua_State *L, int status)
{
    if (status != 0) {
        std::cerr << "-- " << lua_tostring(L, -1) << std::endl;
        lua_pop(L, 1); // remove error message
    }
}

int main(int argc, char** argv)
{
    const char* file = argv[1];

    lua_State *L = lua_open();
    luaL_openlibs(L); // 5.1 way to do it

    lua_register(L, "host_function", host_function);
    std::cerr << "-- Loading file: " << file << std::endl;

    int status = luaL_loadfile(L, file);

    if (status == 0) {
        status = lua_pcall(L, 0, LUA_MULTRET, 0); // execute
    }

    report_errors(L, status);
    lua_close(L);

    return 0;
}
