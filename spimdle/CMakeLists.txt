add_definitions(-DDEFAULT_EXCEPTION_HANDLER="/usr/share/spim/exceptions.s")

add_executable(spim spim.cc $<TARGET_OBJECTS:spim_core>)
add_executable(spim-dump-ops dump-ops.cc)
