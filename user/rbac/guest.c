// GUEST

#include <stdio.h>
#include <syscall.h>
#include "rbac.h"

void process3() {
	printf("Process3 (Guest) started.\n");

	add_user(3, "guest", "guestpass", ROLE_GUEST);
	
	if (authenticate_user("guest", "guestpass")) {
		int action = ACTION_3;
		execute_process(3, action);
	} else {
		printf("Authentication failed for Process3.\n");
	}
}

int main
(int argc, char **argv) {

	process3();

	yield();

	return 0;
}
