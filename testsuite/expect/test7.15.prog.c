/*****************************************************************************\
 *  test7.15.prog.c - Test for blocked signals
 *****************************************************************************
 *  Copyright (C) 2012 LLNS, Inc.
 *  Produced at Lawrence Livermore National Laboratory (cf, DISCLAIMER).
 *  CODE-OCEC-09-009. All rights reserved.
 *
 *  This file is part of SLURM, a resource management program.
 *  For details, see <http://www.schedmd.com/slurmdocs/>.
 *  Please also read the included file: DISCLAIMER.
 *
 *  SLURM is free software; you can redistribute it and/or modify it under
 *  the terms of the GNU General Public License as published by the Free
 *  Software Foundation; either version 2 of the License, or (at your option)
 *  any later version.
 *
 *  SLURM is distributed in the hope that it will be useful, but WITHOUT ANY
 *  WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 *  FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more
 *  details.
 *
 *  You should have received a copy of the GNU General Public License along
 *  with SLURM; if not, write to the Free Software Foundation, Inc.,
 *  51 Franklin Street, Fifth Floor, Boston, MA 02110-1301  USA.
\*****************************************************************************/
#include <stdio.h>
#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>

int main (int ac, char **av)
{
	char hostname[1024];
	int i, rc = 0;
	struct sigaction act;

	if (gethostname (hostname, sizeof (hostname)) < 0) {
		fprintf (stderr, "Failed to get hostname on this node\n");
		strcpy (hostname, "Unknown");
	}
	for (i = 1; i < SIGRTMAX; i++) {
		sigaction (i, NULL, &act);
		if (act.sa_handler == SIG_IGN) {
			fprintf (stderr, "%s: Signal %d is ignored!\n",
				 hostname, i);
			rc = 1;
		} else if (act.sa_handler != SIG_DFL) {
			fprintf (stderr,
				 "%s: Signal %d has handler function!\n",
				 hostname, i);
			rc = 1;
		}
	}
	return (rc);
}
