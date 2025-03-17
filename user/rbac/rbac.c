#include "rbac.h"
#include <stdio.h>
#include <string.h>

#define MAX_USERS 10
#define NUM_ACTIONS 5
#define NUM_PROCESSES 3

#define ACTION_1 1
#define ACTION_2 2
#define ACTION_3 3
#define ACTION_4 4
#define ACTION_5 5

#define true 1
#define false 0

bool rbac_matrix[3][NUM_ACTIONS] = {
	{true, true, true, true, true}, //admin
	{true, true, false, false, false}, //user
	{false, false, false, false, false} //guest
};

User users[MAX_USERS];
int user_count = 0;
Process processes[NUM_PROCESSES] = {
	{1, ROLE_ADMIN},
	{2, ROLE_USER},
	{3, ROLE_GUEST}
};

void init_rbac() {
	printf("RBAC system initialized.\n");
	user_count = 0;
}

int check_permission(Role role, int action) {
	if (action < 1 || action > NUM_ACTIONS) return 0;
	return rbac_matrix[role][action-1] ? 1 : 0;
}

void add_user(int uid, const char* username, const char* password, Role role) {
	if (user_count >= MAX_USERS) {
		printf("User database full!\n");
		return;
	}
	users[user_count].uid = uid;
	strncpy(users[user_count].username, username, sizeof(users[user_count].username) -1);
	strncpy(users[user_count].password, password, sizeof(users[user_count].password) -1);
	users[user_count].role = role;
	user_count++;
}

Role get_user_role(int uid) {
	int i = 0;
	for (i=0; i<user_count; i++) {
		if (users[i].uid == uid) {
			return users[i].role;
		}
	}
	return ROLE_GUEST;
}

void remove_user(int uid) {
	int i = 0;
	for (i=0; i<user_count; i++) {
		if (users[i].uid == uid) {
			users[i] = users[user_count - 1];
			user_count--;
			return;
		}
	}
}

int authenticate_user(const char* username, const char* password) {
	int i = 0;
	for (i=0; i<user_count; i++) {
		if (strcmp(users[i].username, username) == 0 && strcmp(users[i].password, password) == 0) {
			return 1; //true
		}
	}
	return 0; //false
}

void execute_process(int pid, int action) {
	int i = 0;
	for (i=0; i<NUM_PROCESSES; i++) {
		if (processes[i].pid == pid) {
			if (check_permission(processes[i].role, action)) {
				printf("Process %d executed Action %d successfully.\n", pid, action);
			} else {
				printf("Process %d does not have permission for Action %d.\n", pid, action);
			}
			return;
		}
	}
}








































