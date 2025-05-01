// Process 2 - User

#include <syscall.h>
#include "rbac.h"
#include <stdio.h>
#include <sysenter.h>

#define MY_PID 1

int main(int argc, char **argv) {

	unsigned int recv_buf[2];
	uint32_t sender_pid = 1;

	int ret = fast_sys_srecv(sender_pid, recv_buf, 2);
	if (ret < 0) {
		printf ("Receiver [5]: fast_sys_srecv failed: %d\n", ret);
	} else {
		printf ("Receiver [5]: received message [%u, %u]\n", recv_buf[0], recv_buf[1]);
	}

	fast_sys_yield();

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
