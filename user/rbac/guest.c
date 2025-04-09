// Process 2

#include "rbac.h"
#include <syscall.h>

int main
(int argc, char **argv) {

	User login = {"user1", "pass1", ROLE_USER};
	RbacMessage msg = {MSG_AUTH_USER, login};
	RbacMessage response;
	unsigned int ret_val;

	sys_send(3, (unsigned int)&msg, sizeof(msg));
	sys_recv(3, unsigned int)&response, sizeof(response), &ret_val);

	if (response.type == MSG_AUTH_RESULT) {
		if (response.user.role == ROLE_USER) {
			printf("Authentication SUCCESS for user %s\n", login.username);
		} else {
			printf("Authentication FAILED for user %s\n", login.username);
		}
	}

	yield();

	return 0;
}
