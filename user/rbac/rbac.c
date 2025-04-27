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

//matrix gia rbac - elegxos dikaiwmatwn gia kathe rolo
bool rbac_matrix[3][NUM_ACTIONS] = {
	{true, true, true, true, true}, //admin
	{true, true, false, false, false}, //user
	{false, false, false, false, false} //guest
};

//domi xristwn
User users[MAX_USERS];
int user_count = 0;

ActionLog action_log_db[MAX_USERS * NUM_ACTIONS];
int current_log_count = 0;

//domi diergasiwn
Process processes[NUM_PROCESSES] = {
	{1, ROLE_ADMIN},
	{2, ROLE_USER},
	{3, ROLE_GUEST}
};

//sunartisi gia katagrafi energeiwn
void log_action(const char *username, const char *action) {
	if (current_log_count < MAX_USERS * NUM_ACTIONS) {
		strcpy(action_log_db[current_log_count].username, username);
		strcpy(action_log_db[current_log_count].action, action);

		current_log_count++;
		printf("Action logged: User '%s' performed action '%s'\n", username, action);
	} else {
		printf("Log database full, cannot record new action.\n");
	}
}

//arxikopoiisi rbac system
void init_rbac() {
	printf("RBAC system initialized.\n");
	user_count = 0; 
}

//elegxos dikaiwmatwn gia mia energeia me vasi ton rolo 
int check_permission(Role role, int action) {
	if (action < 1 || action > NUM_ACTIONS) return 0;
	return rbac_matrix[role][action-1] ? 1 : 0;
}

//prosthiki xristi 
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

//epistrofi tou rolou tou xristi me vasi to uid 
Role get_user_role(int uid) {
	int i = 0;
	for (i=0; i<user_count; i++) {
		if (users[i].uid == uid) {
			return users[i].role;
		}
	}
	return ROLE_GUEST;
}

//diagrafi xristi 
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

//afthentikopoiisi xristi
int authenticate_user(const char* username, const char* password) {
	int i = 0;
	for (i=0; i<user_count; i++) {
		if (strcmp(users[i].username, username) == 0 && strcmp(users[i].password, password) == 0) {
			return 1; //true
		}
	}
	return 0; //false
}

//ektelesi diadikasias an o xristis exei ta apaitoumena dikaiwmata
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

//ektupwsi olwn twn xristwn
void print_users() {
	if (user_count == 0) {
		printf("No users in the system.\n");
		return;
	}
	printf("Users in the system\n");
	int i = 0;
	for (i=0; i<user_count; i++) {
		printf("User ID: %d\n", users[i].uid);
		printf("Username: %s\n", users[i].username);
		printf("Role: ");

		//ektupwsi rolou
		switch (users[i].role) {
			case ROLE_ADMIN:
				printf("Admin\n");
				break;
			case ROLE_USER:
				printf("User\n");
				break;
			case ROLE_GUEST:
				printf("Guest\n");
				break;
			default:
				printf("Unkown\n");
				break;
			}
		printf("-------------------------------------------\n");
	}
}





















