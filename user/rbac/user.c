// Process 3

#include <stdio.h>
#include "rbac.h"
#include <syscall.h>


int main 
(int argc, char **argv) {

	unsigned int ret_val;
	RbacMessage msg;
	RbacMessage reply;

	while(1) {
		sys_recv(-1, (unsigned int)&msg, sizeof(msg), &ret_val);
	
		if (msg.type == MSG_ADD_USER) {
			add_user(msg.user);
			printf("RBAC_DB: Added user %s\n", msg.user.username);
		} else if (msg.type == MSG_AUTH_USER) {
			int auth = authenticate_user(msg.user);
			User res = msg.user;
			res.role = auth ? ROLE_USER : -1;
			reply = (RbacMessage){MSG_AUTH_RESULT, res};
			sys_send(ret_val, (unsigned int)&reply, sizeof(reply));
		}

		yield();
	}

	return 0;
}
