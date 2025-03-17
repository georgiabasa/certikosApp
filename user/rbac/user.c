// USER

#include <stdio.h>
#include <syscall.h>
#include "rbac.h"

void process2() {
	printf("Process2 (User) started.\n");
	
	//add_user(2, "user", "userpass", ROLE_USER);

	if (authenticate_user("user2", "user2pass")) {
		int action = ACTION_2;
		execute_process(2, action);
	} else {
		printf("Authentication failed for Process2.\n");
	}
}

int main 
(int argc, char **argv) {

	process2();

	yield();

	return 0;
}
