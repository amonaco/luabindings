#include <stdio.h>
#include <lua.h>

int host_function(lua_State *L)
{
    int n, argc;
    
    argc = lua_gettop(L);
    fprintf(stderr, "host_function called with %d args\n", argc);

    for (n = 1; n <= argc; ++n)
        fprintf(stderr, "arg %d: %s\n", n, lua_tostring(L, n));

    lua_pushnumber(L, 123);
    return 1;
}

void report_errors(lua_State *L, int status)
{
    if (status != 0) {
        fprintf(stderr, "-- %s\n", lua_tostring(L, -1));
        lua_pop(L, 1);
    }
}

int main(int argc, char** argv)
{
    int status;
    const char* file;

    file = argv[1];

    lua_State *L = lua_open();
    luaL_openlibs(L); // 5.1 way to do it

    lua_register(L, "host_function", host_function);
    fprintf(stderr, "running: %s\n", file);

    status = luaL_loadfile(L, file);

    if (status == 0) {
        status = lua_pcall(L, 0, LUA_MULTRET, 0); // execute
    }

    report_errors(L, status);
    lua_close(L);

    return 0;
}
