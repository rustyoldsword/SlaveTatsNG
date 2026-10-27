set(VCPKG_TARGET_ARCHITECTURE x64)
set(VCPKG_CRT_LINKAGE dynamic)

if (${PORT} MATCHES "fully-dynamic-game-engine|skse|qt*")
    set(VCPKG_LIBRARY_LINKAGE dynamic)
else ()
    set(VCPKG_LIBRARY_LINKAGE static)
endif ()



# keep the local checkout path out of everything built from these ports (__FILE__ strings)
get_filename_component(SLAVETATS_ROOT "${CMAKE_CURRENT_LIST_DIR}/.." ABSOLUTE)
file(TO_NATIVE_PATH "${SLAVETATS_ROOT}" SLAVETATS_ROOT)
set(VCPKG_C_FLAGS "/d1trimfile:${SLAVETATS_ROOT}")
set(VCPKG_CXX_FLAGS "/d1trimfile:${SLAVETATS_ROOT}")
