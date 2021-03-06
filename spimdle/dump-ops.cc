/* SPIM S20 MIPS simulator.
   Dump the op.h file in a readable format to allow checking of encodings.

   Copyright (c) 1990-2010, James R. Larus.
   All rights reserved.

   Redistribution and use in source and binary forms, with or without modification,
   are permitted provided that the following conditions are met:

   Redistributions of source code must retain the above copyright notice,
   this list of conditions and the following disclaimer.

   Redistributions in binary form must reproduce the above copyright notice,
   this list of conditions and the following disclaimer in the documentation and/or
   other materials provided with the distribution.

   Neither the name of the James R. Larus nor the names of its contributors may be
   used to endorse or promote products derived from this software without specific
   prior written permission.

   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
   AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
   IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
   ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
   LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
   CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE
   GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
   HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
   LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
   OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#include <cstdio>
#include <cstdlib>
#include <cstdint>

typedef struct inst_t {
  char *opcode;
  union {
    int x;
    struct {
      unsigned int funct:6;
      unsigned int pad:10;
      unsigned int rt:5;
      unsigned int rs:5;
      unsigned int op:6;
    } f;
  };
} inst;

#define OP(a, b, c, d) {a, d},

inst ops [] = {
#include "spim/op.h"
};

int compare_ops(const void *a, const void *b) {
  inst* p1 = (inst*)a;
  inst* p2 = (inst*)b;
  if (p1->f.op < p2->f.op) {
    return (-1);
  } else if (p1->f.op > p2->f.op) {
    return (1);
  }

  if (p1->f.rs < p2->f.rs) {
    return (-1);
  } else if (p1->f.rs > p2->f.rs) {
    return (1);
  }

  if (p1->f.rt < p2->f.rt) {
    return (-1);
  } else if (p1->f.rt > p2->f.rt) {
    return (1);
  }

  if (p1->f.funct < p2->f.funct) {
    return (-1);
  } else if (p1->f.funct > p2->f.funct) {
    return (1);
  }
  return 0;
}

int main() {
  // Remove pseudo ops (opcode == -1) from table.
  uint32_t empty = 0;
  for (uint32_t next = 0; next < (sizeof(ops) / sizeof(ops[0])); next += 1) {
    if (ops[next].x == -1) {
      continue;
    }
    ops[empty] = ops[next];
    empty += 1;
  }

  // Radix sort instructions by field: op, rs, rt, funct
  qsort(ops, empty, sizeof(ops[0]), compare_ops);

  // Print related instructions in groups
  for (uint32_t i = 0; i < empty; i += 1) {
    if (0 < i && ops[i - 1].f.op != ops[i].f.op) {
      printf ("\n");
    }
    printf("%10s  op=%2d  rs=%2d  rt=%2d  funct=%02x      0x%08x\n",
           ops[i].opcode,
           ops[i].f.op,
           ops[i].f.rs,
           ops[i].f.rt,
           ops[i].f.funct,
           ops[i].x);
  }
}
