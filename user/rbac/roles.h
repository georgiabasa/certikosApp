#ifndef RBAC_H
#define RBAC_H

#include <stdbool.h>

typedef enum {
	ROLE_ADMIN,
	ROLE_USER,
	ROLE_GUEST
} Role;

typedef struct {
	int pid;
	Role role;
} Process;

typedef struct {
	int uid;
	char username[32];
	char password[32];
	Role role;
} User;

void init_rbac();
bool check_permission(Role role, int action);
void add_user(int uid, const char* username, const char* password, Role role);
Role get_user_role(int uid);
void remove_user(int uid);
bool authenticate_user(const char* username, const char* password);
void execute_process(int pid, int action);

#endif //RBAC_H
