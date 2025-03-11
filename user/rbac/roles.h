#ifndef RBAC_H
#define RBAC_H

#define ROLE_ADMIN 0
#define ROLE_USER 1
#define ROLE_GUEST 2

#define LOG_SIZE 10
#define MAX_USERS 10 //megistos arithmos xristwn

typedef struct User {
	char username[16];
	int role;
} User;

typedef struct LogEntry {
	char username[16];
	char action[16];
	int success;
} LogEntry;

//dilwsi metavlitvn pou xrisimopoiountai se polla arxeia
extern User user_list[MAX_USERS];
extern LogEntry logs[LOG_SIZE];
extern int log_index;

//sunartiseis gia diaxeirisi xristwn
int add_user(const char* username, int role);
User* find_user(const char* username);
void print_users();

//RBAC sunartiseis
int can_execute(int role, const char* action);
void log_action(const char* username, const char* action, int success);

//system calls ektelesi
void execute_syscalls(const char* username);

#endif //RBAC_H
