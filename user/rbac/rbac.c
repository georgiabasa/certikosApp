#include "rbac.h"
#include <stdio.h>

static int roles[3] = { ROLE_ADMIN, ROLE_USER, ROLE_VIEWER };
static int resource_data = 100;

//permission_matrix[role][action]
static int permissions[4][3] = {
	{0, 0, 0},   // NONE
	{1, 1, 1},   // ADMIN
	{1, 1, 0},   // USER
	{1, 0, 0},   // VIEWER
};

int get_role(int pid) {
	if (pid < 0 || pid >= 3) return ROLE_NONE;
	return roles[pid];
}

int check_permission(int pid, int action) {
	int role = get_role(pid);
	if (role < 0 || role > 3) return 0;
	return permissions[role][action];
}

void set_role(int manager_pid, int target_pid, int role) {
	if (!check_permission(manager_pid, ACTION_MANAGE)) {
		printf("[SECURITY] PID %d attempted unauthorizd role change!\n", manager_pid);
		return;
	}
	if (target_pid >= 0 && target_pid < 3)
		roles[target_pid] = role;
}

int secure_read(int pid, int *value) {
	if (!check_permission(pid, ACTION_READ))
		return -1;
	*value = resource_data;
	return 0;
}

int secure_write(int pid, int value) {
	if (!check_permission(pid, ACTION_WRITE))
		return -1;
	resource_data = value;
	return 0;
}

void show_roles(int pid) {
	if (!check_permission(pid, ACTION_MANAGE)) {
		printf("[SECURITY] PID %d not allowed to view roles.\n", pid);
		return;
	}

	printf("[ADMIN] Current Roles:\n");
	int i = 0;
	for (i = 0; i < 3; i++) {
		printf("  PID %d - ROLE_%s\n", i,
			(roles[i] == ROLE_ADMIN) ? "ADMIN" :
			(roles[i] == ROLE_USER) ? "USER" :
			(roles[i] == ROLE_VIEWER) ? "VIEWER" : "NONE"
		);
	}
}

