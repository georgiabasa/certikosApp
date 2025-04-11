// Process 2

#include <stdio.h>
#include "rbac.h"
#include <syscall.h>

static RbacMessage send_msg __attribute__((aligned(4)));
static RbacMessage recv_msg __attribute__((aligned(4)));
static unsigned int from_pid;

int main
(int argc, char **argv) {
	send_msg.type = MSG_AUTH_USER;
	send_msg.user = (User){"user1", "pass1", ROLE_USER};

	sys_send(6, (unsigned int)&send_msg, sizeof(send_msg));
	sys_recv(6, (unsigned int)&recv_msg, sizeof(recv_msg), &from_pid);

	if (recv_msg.type == MSG_AUTH_RESULT) {
		if (recv_msg.user.role == ROLE_USER) {
			printf("Authentication SUCCESS for user %s\n", recv_msg.user.username);
		} else {
			printf("Authentication FAILED for user %s\n", send_msg.user.username);
		}
	}

	yield();

	return 0;
}
