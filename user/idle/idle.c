#include <proc.h>
#include <stdio.h>
#include <syscall.h>
#include <sysenter.h>

#define NUM_PROC 64
#define ROOT_QUOTA 720896

#define _1K		1024
#define _1M		_1K * 1024
#define _256M	(_1M * 256)

#define BLOB_PAGES	_256M / PAGESIZE
#define BLOB_SIZE	_256M

volatile int blob1[BLOB_SIZE] __attribute__((aligned (PAGESIZE))); // 1G
volatile int blob2[BLOB_SIZE] __attribute__((aligned (PAGESIZE))); // 2G
volatile int blob3[BLOB_SIZE - 0x3000 ] __attribute__((aligned (PAGESIZE))); // 3G

#define MAGIC	0xaabbccdd

int mem_test(int volatile blob[])
{
	int i;

	printf("start from 0x%08x, size: %d pages\n", &(blob[0]), BLOB_PAGES);

    for(i = 0; i < BLOB_PAGES; i++)
    {
    	blob[i * PAGESIZE + 1] = i ^ MAGIC;
    	//printf(".");
    }

    for(i = 0; i < BLOB_PAGES; i++)
    {
    	if ((blob[i * PAGESIZE + 1] ^ 0xaabbccdd) == i)
    	{
    		//printf("x");
    	}
    	else
    	{
    		PANIC("memory test failed @ 0x%08x\n", &(blob[i * PAGESIZE + 1]));
    		return 1;
    	}
    }

    return 0;
}

int
main (int argc, char **argv)
{
    printf ("idle\n");

#ifdef CONFIG_APP_USER_PROC

    pid_t p1_pid, p3_pid, p2_pid;
    unsigned int p1q = 100;
    unsigned int p3q = 50;
    unsigned int p2q = 22;
    printf ("USER\n");

    if ((p1_pid = spawn (3,p1q)) != NUM_PROC)
      printf ("Process_1 in process %d with %d quota (including some pages reserved for kernel use only).\n", p1_pid, p1q);
    else
        printf ("Failed to launch Process_1.\n");

    if ((p2_pid = spawn (4,p2q)) != NUM_PROC)
      printf ("Process_2 in process %d with %d quota (including some pages reserved for kernel use only).\n", p2_pid, p2q);
    else
        printf ("Failed to launch Process_2.\n");

    if ((p3_pid = spawn (5,p3q)) != NUM_PROC)
      printf ("Process_3 in process %d with %d quota (including some pages reserved for kernel use only).\n", p3_pid, p3q);
    else
        printf ("Failed to launch Process_3.\n");

#endif

#ifdef CONFIG_APP_RING0_PROC
    pid_t ring0_id1, ring0_id2;
    if ((ring0_id1 = sys_ring0_spawn (1,10)) != NUM_PROC)
        printf ("The first ring0 process in process %d.\n", ring0_id1);
    else
        printf ("Failed to launch the first ring0 process.\n");

    if ((ring0_id2 = sys_ring0_spawn (2,10)) != NUM_PROC)
        printf ("The second ring0 process in process %d.\n", ring0_id2);
    else
        printf ("Failed to launch the second ring0 process.\n");
#endif

    printf("memory test: ");
//    mem_test(blob1);
//    mem_test(blob2);
//    mem_test(blob3);

    printf("all pass\n");



#ifdef CONFIG_APP_VMM
    pid_t vmm_pid;

    if ((vmm_pid = spawn (1, ROOT_QUOTA - 20)) != -1)
        printf ("VMM in process %d.\n", vmm_pid);
    else
        printf ("Failed to launch VMM.\n");
#endif

#ifdef CONFIG_APP_USER_PROFILE
    pid_t unit_pid;
    if ((unit_pid = spawn (4,10)) != NUM_PROC)
        printf ("unit in process %d.\n", unit_pid);
    else
        printf ("Failed to launch unit.\n");
#endif

    while (1) {
      yield ();
    }

    return 0;
}
