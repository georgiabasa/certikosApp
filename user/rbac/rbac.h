#ifndef RBAC_H
#define RBAC_H

#define MAX_USERS 10
#define MAX_NAME_LEN 16
#define MAX_PASS_LEN 16

typedef enum { ROLE_ADMIN< ROLE_USER } Role;

typedef struct {
	char username[MAX_NAME_LEN];
	char password[MAX_PASS_LEN];
	Role role;
} User;

typedef enum {
	MSG_ADD_USER,
	MSG_AUTH_USER,
	MSG_AUTH_RESULT
} MsgType;

typedef struct {
	MsgType type;
	User user;
} RbacMessage;

void add_user(User user); //for P3 internal DB
int authenticate_user(User user); //for P3 internal DB
void print_users(); //for debug/log

#endif //RBAC_H
