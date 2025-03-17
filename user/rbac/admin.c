// ADMIN

#include <stdio.h>
#include <syscall.h>
#include "rbac.h"


void process1() {
	printf("Process1 (Admin) started.\n");

	add_user(1, "admin", "password123", ROLE_ADMIN);

	if (authenticate_user("admin", "password123")) {
        	int action = ACTION_1;
        	execute_process(1, action);
    	} else {
        	printf("Authentication failed for Process1.\n");
    	}
}

int main
(int argc, char **argv) {
	
	init_rbac() ;
	
	process1();

	yield();

	return 0;
}
