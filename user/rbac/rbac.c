#include "rbac.h"
#include <string.h>

static User users[MAX_USERS];
static int user_count = 0;

void add_user(User user) {
	if (user_count < MAX_USERS) {
		users[user_count++] = user;
	}
}

int authenticate_user (User input) {
	int i = 0;
	for (i=0; i <user_count; i++) {
		if (strcmp(users[i].username, input.username) == 0 &&
		    strcmp(users[i].password, input.password) == 0) {
			return 1; //success
		}
	}
	return 0; //fail
}

void print_users() {
	int i = 0 ;
	for (i=0; i<user_count; i++) {
		printf("User: %s, Role: %s\n", users[i].username, users[i].role == ROLE_ADMIN ? "Admin" : "User");
	}
}
