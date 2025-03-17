#ifndef RBAC_H
#define RBAC_H

// Ορισμός ενεργειών (actions)
#define ACTION_1 1
#define ACTION_2 2
#define ACTION_3 3
#define ACTION_4 4
#define ACTION_5 5

//orismos twn rolwn
typedef enum {
	ROLE_ADMIN,
	ROLE_USER,
	ROLE_GUEST
} Role;

typedef struct {
	int pid;
	Role role;
} Process;

//orismos tis domis gia tous xristes
typedef struct {
	int uid;
	char username[32];
	char password[32];
	Role role;
} User;

//orismos domis gia tis katagrafes energeiwn
typedef struct {
	char username[50];
	char action[50];
} ActionLog;

void log_action(const char *username, const char *action);
void init_rbac();
int check_permission(Role role, int action);
void add_user(int uid, const char* username, const char* password, Role role);
Role get_user_role(int uid);
void remove_user(int uid);
int authenticate_user(const char* username, const char* password);
void execute_process(int pid, int action);
void print_users();

#endif //RBAC_H
