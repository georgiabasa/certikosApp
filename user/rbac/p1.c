// Process 1 - ADMIN

#include <stdio.h>
#include <syscall.h>
#include "rbac.h"


void admin_process() {
	printf("Process1 (Admin) started.\n");

	add_user(1, "admin", "adminpass", ROLE_ADMIN);

	if (authenticate_user("admin", "adminpass")) {
		int action = ACTION_1;
		execute_process(1, action);
	} else {
		printf("authentication failed for Process1\n");
	}
}

int main
(int argc, char **argv) {
	
	init_rbac();

	add_user(1, "admin", "adminpass", ROLE_ADMIN);
	add_user(2, "user1", "user1pass", ROLE_USER);
 	add_user(3, "user2", "user2pass", ROLE_USER);
 	add_user(4, "guest1", "guest1pass", ROLE_GUEST);
 	add_user(5, "guest2", "guest2pass", ROLE_GUEST);

	admin_process();

	print_users();

	yield();
	return 0;
}
