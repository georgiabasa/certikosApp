// Process 2 - User

#include <stdio.h>
#include <syscall.h>
#include "rbac.h"


void user_process() {
	printf("Process2 (User) started.\n");

	if (authenticate_user("user2", "user2pass")) {
		int action = ACTION_2;
		execute_process(2, action);
	} else {
		printf("Authentication failed for Process2.\n");
	}
}

int main
(int argc, char **argv) {
	
	user_process();
	yield();
	return 0;
}
