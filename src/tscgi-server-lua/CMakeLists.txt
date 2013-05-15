find_package (Lua51 REQUIRED)

add_library (tscgi-hash-header header.c)

add_executable (tinyscgi-lua tscgi-server-lua.c)
target_link_libraries (tinyscgi-lua ${LUA_LIBRARIES} tscgi tscgi-server tscgi-hash-header)
