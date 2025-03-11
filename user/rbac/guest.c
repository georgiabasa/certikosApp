// GUEST - READ only

#include <stdio.h>
#include <string.h>
#include <syscall.h>
#include "roles.h"

#define LOG_SIZE 10
#define ROLE_ADMIN 0
#define ROLE_USER 1
#define ROLE_GUEST 2

LogEntry logs[LOG_SIZE];
int log_index = 0;

typedef struct {
	int role;
	char* actions[3];
} RolePermission;

RolePermission role_permissions[] = {
	{ ROLE_ADMIN, {"sys_disk_op", "sys_send", "sys_hvm_run_vm" } },
	{ ROLE_USER,  {"sys_disk_op", "sys_send", NULL } },
	{ ROLE_GUEST, {"sys_disk_op", NULL, NULL } }
};

//elegxei an o xristis exei adeia na ektelesei mia energeia
int can_execute(int role, const char* action) {
	int i=0;
	for (i=0; i<3; i++) {
		if (role_permissions[role].actions[i] && strcmp(role_permissions[role].actions[i], action) ==0) {
			return 1;
		}
	}
	return 0;
}

//katagrafi energeias sto log
void log_action(const char* username, const char* action, int success) {
	log_index = (log_index + 1) % LOG_SIZE;
	strncpy(logs[log_index].username, username, 16);
	strncpy(logs[log_index].action, action, 16);
	logs[log_index].success = success;
	printf("[LOG] User: %s, Action: %s, Success: %d\n", username, action, success);
}

int
main (int argc, char **argv)
{
	printf("[RBAC] Running Access Control Checks...\n");

	//dokimi katagrafis
	log_action("admin", "sys_hvm_run_vm", 1);
	log_action("user1", "sys_disk_op", 1);
	log_action("guest1", "sys_hvm_run_vm", 0);
	
	printf("[RBAC] Yielding CPU to next process...\n");
		
	while (1) {
		yield(); //allagi diergasias
	}

	return 0;
}

