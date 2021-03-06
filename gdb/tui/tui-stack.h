/* TUI display locator.

   Copyright (C) 1998-2019 Free Software Foundation, Inc.

   Contributed by Hewlett-Packard Company.

   This file is part of GDB.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

#ifndef TUI_TUI_STACK_H
#define TUI_TUI_STACK_H

#include "tui/tui-data.h"

struct frame_info;

#ifdef PATH_MAX
# define MAX_LOCATOR_ELEMENT_LEN        PATH_MAX
#else
# define MAX_LOCATOR_ELEMENT_LEN        1024
#endif

/* Locator window class.  */

struct tui_locator_window : public tui_gen_win_info
{
  tui_locator_window ()
    : tui_gen_win_info (LOCATOR_WIN)
  {
    full_name[0] = 0;
    proc_name[0] = 0;
  }

  void rerender () override;

  /* Update the locator, with the provided arguments.

     Returns true if any of the locator's fields were actually
     changed, and false otherwise.  */
  bool set_locator_info (struct gdbarch *gdbarch,
			 const char *fullname,
			 const char *procname,
			 int lineno, CORE_ADDR addr);

  /* Set the full_name portion of the locator.  */
  void set_locator_fullname (const char *fullname);

  char full_name[MAX_LOCATOR_ELEMENT_LEN];
  char proc_name[MAX_LOCATOR_ELEMENT_LEN];
  int line_no = 0;
  CORE_ADDR addr = 0;
  /* Architecture associated with code at this location.  */
  struct gdbarch *gdbarch = nullptr;
};

extern void tui_update_locator_fullname (const char *);
extern void tui_show_locator_content (void);
extern int tui_show_frame_info (struct frame_info *);

#endif /* TUI_TUI_STACK_H */
