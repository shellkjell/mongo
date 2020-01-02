/* libunwind - a platform-independent unwind library
   Copyright (C) 2012 Tommi Rantala <tt.rantala@gmail.com>

This file is part of libunwind.

Permission is hereby granted, free of charge, to any person obtaining
a copy of this software and associated documentation files (the
"Software"), to deal in the Software without restriction, including
without limitation the rights to use, copy, modify, merge, publish,
distribute, sublicense, and/or sell copies of the Software, and to
permit persons to whom the Software is furnished to do so, subject to
the following conditions:

The above copyright notice and this permission notice shall be
included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.  */

#include "unwind_i.h"

static inline int
common_init (struct cursor *c, unsigned use_prev_instr)
{
  int ret;

  c->dwarf.loc[UNW_SH_R0]  = DWARF_REG_LOC (&c->dwarf, UNW_SH_R0);
  c->dwarf.loc[UNW_SH_R1]  = DWARF_REG_LOC (&c->dwarf, UNW_SH_R1);
  c->dwarf.loc[UNW_SH_R2]  = DWARF_REG_LOC (&c->dwarf, UNW_SH_R2);
  c->dwarf.loc[UNW_SH_R3]  = DWARF_REG_LOC (&c->dwarf, UNW_SH_R3);
  c->dwarf.loc[UNW_SH_R4]  = DWARF_REG_LOC (&c->dwarf, UNW_SH_R4);
  c->dwarf.loc[UNW_SH_R5]  = DWARF_REG_LOC (&c->dwarf, UNW_SH_R5);
  c->dwarf.loc[UNW_SH_R6]  = DWARF_REG_LOC (&c->dwarf, UNW_SH_R6);
  c->dwarf.loc[UNW_SH_R7]  = DWARF_REG_LOC (&c->dwarf, UNW_SH_R7);
  c->dwarf.loc[UNW_SH_R8]  = DWARF_REG_LOC (&c->dwarf, UNW_SH_R8);
  c->dwarf.loc[UNW_SH_R9]  = DWARF_REG_LOC (&c->dwarf, UNW_SH_R9);
  c->dwarf.loc[UNW_SH_R10] = DWARF_REG_LOC (&c->dwarf, UNW_SH_R10);
  c->dwarf.loc[UNW_SH_R11] = DWARF_REG_LOC (&c->dwarf, UNW_SH_R11);
  c->dwarf.loc[UNW_SH_R12] = DWARF_REG_LOC (&c->dwarf, UNW_SH_R12);
  c->dwarf.loc[UNW_SH_R13] = DWARF_REG_LOC (&c->dwarf, UNW_SH_R13);
  c->dwarf.loc[UNW_SH_R14] = DWARF_REG_LOC (&c->dwarf, UNW_SH_R14);
  c->dwarf.loc[UNW_SH_R15] = DWARF_REG_LOC (&c->dwarf, UNW_SH_R15);
  c->dwarf.loc[UNW_SH_PC]  = DWARF_REG_LOC (&c->dwarf, UNW_SH_PC);
  c->dwarf.loc[UNW_SH_PR]  = DWARF_REG_LOC (&c->dwarf, UNW_SH_PR);

  ret = dwarf_get (&c->dwarf, c->dwarf.loc[UNW_SH_PC], &c->dwarf.ip);
  if (ret < 0)
    return ret;

  ret = dwarf_get (&c->dwarf, c->dwarf.loc[UNW_TDEP_SP], &c->dwarf.cfa);
  if (ret < 0)
    return ret;

  c->sigcontext_format = SH_SCF_NONE;
  c->sigcontext_addr = 0;
  c->sigcontext_sp = 0;
  c->sigcontext_pc = 0;

  c->dwarf.args_size = 0;
  c->dwarf.stash_frames = 0;
  c->dwarf.use_prev_instr = use_prev_instr;
  c->dwarf.pi_valid = 0;
  c->dwarf.pi_is_dynamic = 0;
  c->dwarf.hint = 0;
  c->dwarf.prev_rs = 0;

  return 0;
}