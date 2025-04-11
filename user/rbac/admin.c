// process 1

#include <stdio.h>
#include "rbac.h"
#include <syscall.h>

static RbacMessage msg1 __attribute__((aligned(4)));
static RbacMessage msg2 __attribute__((aligned(4)));

int main
(int argc, char **argv) {
	msg1.type = MSG_ADD_USER;
	msg1.user = (User){"user1", "pass1", ROLE_USER};

	msg2.type = MSG_ADD_USER;
	msg2.user = (User){"admin1", "adminpass", ROLE_ADMIN};

	sys_send(5, (unsigned int)&msg1, sizeof(msg1));
	sys_send(5, (unsigned int)&msg2, sizeof(msg2));

	printf("Admin sent users to RBAC_DB\n");
	yield(); //manually yield to move to next process
	
	return 0;
}
