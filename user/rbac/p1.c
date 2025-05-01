// Process 1 - ADMIN

#include <syscall.h>
#include "rbac.h"
#include <stdio.h>
#include <sysenter.h>

#define MY_PID 0

int main(int argc, char **argv) {
	int pid = MY_PID;

	printf("trying to syssend\n");
	static unsigned int msg[2];
	msg[0] = 123;
	msg[1] = 456;
	uint32_t receiver_chid = 2;

	int ret = fast_sys_ssend(receiver_chid, msg, 2);
	if (ret < 0) {
		printf("Sender [4]: fast_sys_ssend failed: %d\n", ret);
	} else {
		printf("Sender [4]: message sent [%u, %u]\n", msg[0], msg[1]);
	}
	fast_sys_yield();
	
	
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
