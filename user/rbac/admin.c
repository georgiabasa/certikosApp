// ADMIN - READ, WRITE, EXECUTE

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <syscall.h>
#include "roles.h"


User user_list[MAX_USERS]; //statikos pinakas xristwn
int user_count = 0;

//prosthiki xristwn
int add_user(const char* username, int role) {
	if (user_count >= MAX_USERS) return -1; //an i lista einai gemati

	strncpy(user_list[user_count].username, username, 16);
	user_list[user_count].role = role;
	user_count++;

	return 0;
}

//evresi xristwn
User* find_user(const char* username) {
	int i = 0;
	for (i=0; i<user_count; i++) {
		if (strcmp(user_list[i].username, username) == 0) {
			return &user_list[i];
		}
	}
	return NULL; //den vrethike
}

//emfanisi xristwn
void print_users() {
	printf("=== Registered Users ===\n");
	int i = 0;
	for (i=0; i<user_count; i++) {
		printf("User: %s, Role: %d\n", user_list[i].username, user_list[i].role);
	}
}



int
main (int argc, char **argv)
{
	printf("[User Management] Initializing...\n");

	//prosthiki kapoiwn xristwn (xeirokinita)
	add_user("admin", ROLE_ADMIN);
	add_user("user1", ROLE_USER);
	add_user("guest1", ROLE_GUEST);

	print_users();

	printf("[User Management] Yielding CPU to next process...\n");
		
	while (1) {
		yield(); //allagi diergasias
	}

	return 0;
}

