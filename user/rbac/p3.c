// Process 3 - Guest

#include <stdio.h>
#include <syscall.h>
#include "rbac.h"

void guest_process() {
	printf("Process3 (Guest) started\n");

	if (authenticate_user("guest1", "guest1pass")) {
		int action = ACTION_3;
		execute_process(3, action);
	} else {
		printf ("Authentication failed for Process3.\n");
	}
}

int main
(int argc, char **argv) {

	print_users();
	guest_process();
	yield();
	return 0;
}
