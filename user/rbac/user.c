// Process 3

#include <stdio.h>
#include "rbac.h"
#include <syscall.h>

static RbacMessage buffer __attribute__((aligned(4)));
static RbacMessage reply __attribute__((aligned(4)));
static unsigned int sender_pid;

int main 
(int argc, char **argv) {

	while(1) {
		sys_recv(3, (unsigned int)&buffer, sizeof(buffer), &sender_pid);
	
		if (buffer.type == MSG_ADD_USER) {
			add_user(buffer.user);
			printf("RBAC_DB: Added user %s\n", buffer.user.username);
		} else if (buffer.type == MSG_AUTH_USER) {
			int ok = authenticate_user(buffer.user);
			User u = buffer.user;
			u.role = ok ? ROLE_USER : -1;

			reply.type = MSG_AUTH_RESULT;
			reply.user = u;

			sys_send(sender_pid, (unsigned int)&reply, sizeof(reply));
		}

		yield();
	}

	return 0;
}
