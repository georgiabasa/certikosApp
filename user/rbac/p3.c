// Process 3 - Viewer

#include <syscall.h>
#include "rbac.h"
#include <stdio.h>

#define MY_PID 2

int main(int argc, char **argv) {
	int pid = MY_PID;
	int val;

	if (secure_read(pid, &val) == 0)
		printf("[VIEWER] Resource value: %d\n", val);
	else
		printf("[VIEWER] Read denied.\n");

	printf("[VIEWER] Tryind to write 123 (should fail)...\n");
	if (secure_write(pid, 123) == 0)
		printf("[VIEWER] Unexpectedly succeeded in writing!\n");
	else
		printf("[VIEWER] Correctly denied write access.\n");

	yield();  //back to admin

	return 0;
}
