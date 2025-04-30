// Process 1 - ADMIN

#include <syscall.h>
#include "rbac.h"
#include <stdio.h>

#define MY_PID 0

int main(int argc, char **argv) {
	int pid = MY_PID;
	
	printf("[ADMIN] Managing system...\n");
	show_roles(pid);

	int val;
	if (secure_read(pid, &val) == 0)
		printf("[ADMIN] Resource is: %d\n", val);

	printf("[ADMIN] Changing resource to 999...\n");
	secure_write(pid, 999);

	if (secure_read(pid, &val) == 0)
		printf("[ADMIN] Resource is: %d\n", val);

	printf("[ADMIN] Revoking USER (PID 1)...\n");
	set_role(pid, 1, ROLE_NONE);

	yield(); //to proc2

	return 0;
}
