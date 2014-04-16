set(FlexOutput scanner.cc)
if(FLEX_FOUND)
  add_custom_command(
    OUTPUT ${FlexOutput}
    COMMAND ${FLEX_EXECUTABLE} -I -8 -o ${FlexOutput} scanner.ll)
endif()

set(BisonOutput parser-yacc.cc)
set(BisonFlags -d --defines=parser-yacc.h -p yy)
if(BISON_FOUND)
  add_custom_command(
    OUTPUT ${BisonOutput}
    COMMAND ${BISON_EXECUTABLE} ${BisonFlags} parser.yy -o ${BisonOutput}
    DEPENDS ${FlexOutput})
endif()

add_definitions(-DTEXT_SIZE=65536 -DDATA_SIZE=131072 -DK_TEXT_SIZE=65536)
set(CMAKE_CXX_FLAGS "-O -g -Wall -pedantic -Wextra -Wunused -Wno-write-strings")

set_source_files_properties(parser-yacc.cc GENERATED)

list(APPEND SPIM_SOURCES
  utils.cc
  run.cc
  mem.cc
  inst.cc
  data.cc
  symbol-table.cc
  parser-yacc.cc
  scanner.cc
  syscall.cc
  display.cc
  string-stream.cc)

add_library(spim_core OBJECT ${SPIM_SOURCES})
