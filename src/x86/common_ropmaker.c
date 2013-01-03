/*
** RopGadgetX - Release v1.0.0
** Jonathan Salwan - http://twitter.com/JonathanSalwan
** Allan Wirth - http://allanwirth.com/
** http://shell-storm.org
** 2012-1-4
**
** This program is free software; you can redistribute it and/or modify
** it under the terms of the GNU General Public License as published by
** the Free Software Foundation; either version 2 of the License, or
** (at your option) any later version.
**
** This program is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU General Public License for more details.
**
** You should have received a copy of the GNU General Public License
** along with this program; if not, write to the Free Software
** Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*/

#include "ropgadget.h"

void x86_ropmaker(size_t word_size)
{
  int flag;
  t_gadget *gadgets;
  char **ropsh;
  t_asm *table = (word_size==4)?tab_x8632:tab_x8664;

  if (importsc_mode.opcode.flag)
    ropsh = (word_size==4)?tab_x8632_importsc:tab_x8664_importsc;
  else
    ropsh = (word_size==4)?tab_x8632_ropmaker:tab_x8664_ropmaker;

  flag = !combo_ropmaker(ropsh, table, &gadgets);

  if (importsc_mode.opcode.flag)
    {
      if (importsc_mode.opcode.size > (binary->writable_exec_size))
        {
          eprintf("\n\t%s/!\\ Possible to make a ROP payload but .got size & .got.plt size isn't sufficient.%s\n", RED, ENDC);
          eprintf("  \t%s    got + got.plt = %s" SIZE_FORMAT " bytes%s and your shellcode size is %s" SIZE_FORMAT " bytes%s\n", RED, YELLOW, SIZE_WIDTH, (binary->writable_exec_size), RED, YELLOW, SIZE_WIDTH, (Size)importsc_mode.opcode.size, ENDC);
          return ;
        }
      /* build a python code */
      if (!flag)
        x86_makecode_importsc(gadgets, word_size);
    }
  else
    {
    /* build a python code */
    if (!flag)
      x86_makecode(gadgets, word_size);
    }
  free(gadgets);
}