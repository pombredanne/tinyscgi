add_subdirectory (tscgi)
add_subdirectory (tscgi-server)
add_subdirectory (tscgi-server-lua)

find_package (Libuv REQUIRED)

# add excutable target
add_executable (tinyscgi tinyscgi.c)
target_link_libraries (tinyscgi ${LIBUV_LIBRARIES} tscgi tscgi-server)

# install executable target
install (TARGETS tinyscgi
         DESTINATION "bin")
