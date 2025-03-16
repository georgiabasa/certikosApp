// ADMIN

#include <stdio.h>
#include <syscall.h>
#include "roles.h"


void process1(int* current_pid) {
	printf("Process1 (Admin) started.\n");

	int action = ACTION_1;
	Role role = ROLE_ADMIN;
	
	if (check_permission(role, action)) {
		printf("Process1 executed Action %d successfully.\n", action);
	} else {
		printf("Process1 does not have permission for Action %d.\n, action);
	}
	
	yield();
}

int main() {
	init_rbac();
	add_user(1, "admin", "password123", ROLE_ADMIN);

	if(authenticate_user("admin", "password123")) {
		int current_pid = 1;
		process1(&current_pid);
	}

	return 0;
}
