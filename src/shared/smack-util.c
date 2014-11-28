/*-*- Mode: C; c-basic-offset: 8; indent-tabs-mode: nil -*-*/

/***
  This file is part of systemd.

  Copyright (C) 2013 Intel Corporation
  Authors:
        Nathaniel Chen <nathaniel.chen@intel.com>

  systemd is free software; you can redistribute it and/or modify it
  under the terms of the GNU Lesser General Public License as published
  by the Free Software Foundation; either version 2.1 of the License,
  or (at your option) any later version.

  systemd is distributed in the hope that it will be useful, but
  WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public License
  along with systemd; If not, see <http://www.gnu.org/licenses/>.
***/

#include <stdio.h>

#include "smack-util.h"
#include "util.h"

static int use_smack_cached = -1;

bool use_smack(void) {
#ifdef HAVE_SMACK
        _cleanup_fclose_ FILE *smack = NULL;

        if (use_smack_cached < 0) {
                smack = fopen("/sys/fs/smackfs", "r");
                if (!smack)
                        use_smack_cached = false;
                else
                        use_smack_cached = true;
        }

        return use_smack_cached;
#else
        return false;
#endif
}