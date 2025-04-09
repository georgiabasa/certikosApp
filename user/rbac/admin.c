// process 1

#include "rbac.h"
#include <syscall.h>

int main
(int argc, char **argv) {
	User u1 = {"user1", "pass1", ROLE_USER};
	User u2 = {"admin1", "adminpass", ROLE_ADMIN};

	RbacMessage msg1 = {MSG_ADD_USER, u1};
	RbacMessage msg2 = {MSG_ADD_USER, u2};

	sys_send(3, (unsigned_int)&msg1, sizeof(msg1));
	sys_send(3, (unsigned_int)&msg2, sizeof(msg2));

	printf("Admin sent users to RBAC_DB\n");
	yield(); //manually yield to move to next process
	
	return 0;
}
