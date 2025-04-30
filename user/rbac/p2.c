// Process 2 - User

#include <syscall.h>
#include "rbac.h"
#include <stdio.h>

#define MY_PID 1

int main(int argc, char **argv) {
	int pid = MY_PID;
	int val;

	if (secure_read(pid, &val) == 0)
		printf("[USER] Read resource: %d\n", val);
	else
		printf("[USER] Read denied.\n");

	printf("[USER] Trying to write 555...\n");
	if (secure_write(pid, 555) == 0)
		printf("[USER] Wrote 555.\n");
	else
		printf("[USER[ Write denied.\n");

	yield();  // to proc3
	
	return 0;
}
