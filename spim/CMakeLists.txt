set(FlexOutput scanner.c)
if(FLEX_FOUND)
  add_custom_command(
    OUTPUT ${FlexOutput}
    COMMAND ${FLEX_EXECUTABLE} -I -8 -o ${FlexOutput} scanner.l)
endif()

set(BisonOutput parser_yacc.c)
set(BisonFlags -d --defines=parser_yacc.h -p yy)
if(BISON_FOUND)
  add_custom_command(
    OUTPUT ${BisonOutput}
    COMMAND ${BISON_EXECUTABLE} ${BisonFlags} parser.y -o ${BisonOutput}
    DEPENDS ${FlexOutput})
endif()

add_definitions(-DTEXT_SIZE=65536 -DDATA_SIZE=131072 -DK_TEXT_SIZE=65536)
add_definitions(-DDEFAULT_EXCEPTION_HANDLER="/usr/share/spim/exceptions.s")
set(CMAKE_C_FLAGS "-O -g -Wall -pedantic -Wextra -Wunused -Wno-write-strings -x c++")

set_source_files_properties(parser_yacc.c GENERATED)

list(APPEND SPIM_SOURCES
  spim.c
  spim-utils.c
  run.c
  mem.c
  inst.c
  data.c
  sym-tbl.c
  parser_yacc.c
  scanner.c
  syscall.c
  display-utils.c
  string-stream.c)

add_executable(spim ${SPIM_SOURCES})
