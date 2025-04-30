#ifndef RBAC_H
#define RBAC_H

#define ROLE_NONE	0
#define ROLE_ADMIN	1
#define ROLE_USER	2
#define ROLE_VIEWER	3

#define ACTION_READ	0
#define ACTION_WRITE	1
#define ACTION_MANAGE	2

int get_role(int pid);
void set_role(int manager_pid, int target_pid, int role); //only admin can set
int check_permission(int pid, int action);

int secure_read(int pid, int *value);
int secure_write(int pid, int value);
void show_roles(int pid);

#endif //RBAC_H
