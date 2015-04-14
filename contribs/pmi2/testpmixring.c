
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
//#include <mpi.h>
#include <slurm/pmi2.h>
#include <sys/time.h>

/*
 * gcc -g -O0 -o testpmixring testpmixring.c -I<slurm_install>/include -Wl,-rpath,<slurm_install>/lib -L<slurm_install>/lib -lpmi2
 */

static char *mrand(int, int);

int
main(int argc, char **argv)
{
	int spawned, size, rank, appnum;
	struct timeval tv, tv2;
        int ring_rank, ring_size;
	char jobid[128];
	char val[128];
	char buf[128];
	char left[128];
	char right[128];

	gettimeofday(&tv, NULL);
	srand(tv.tv_sec);

	PMI2_Init(&spawned, &size, &rank, &appnum);

	PMI2_Job_GetId(jobid, sizeof(buf));

        /* test PMIX_Ring */
	snprintf(val, sizeof(val), "pmi_rank=%d", rank);
	PMIX_Ring(val, &ring_rank, &ring_size, left, right, 128);

	printf("pmi_rank:%d ring_rank:%d ring_size:%d left:%s mine:%s right:%s\n",
		rank, ring_rank, ring_size, left, val, right);

	PMI2_Finalize();

	gettimeofday(&tv2, NULL);
	printf("%f\n",
		   ((tv2.tv_sec - tv.tv_sec) * 1000.0
			+ (tv2.tv_usec - tv.tv_usec) / 1000.0));

	return 0;
}

/* Generate a random number between
 * min and Max and convert it to
 * a string.
 */
static char *
mrand(int m, int M)
{
	int i;
	time_t t;
	static char buf[64];

	memset(buf, 0, sizeof(buf));
	for (i = 0; i  < 16; i++)
		buf[i] = rand() % (M - m + 1) + m;

	return buf;
}
